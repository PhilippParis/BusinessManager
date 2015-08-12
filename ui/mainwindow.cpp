#include "ui/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("ParisApps");
    QCoreApplication::setOrganizationDomain("parisApps.com");
    QCoreApplication::setApplicationName("BusinessManager");
    QCoreApplication::setApplicationVersion("2.0");

    setWindowTitle(QCoreApplication::applicationName());
    QSqlDatabase db = DatabaseSingleton::get()->getProductionDatabase();

    m_customerValidator = std::make_shared<CustomerValidator>();
    m_billValidator = std::make_shared<BillValidator>();
    m_billItemValidator = std::make_shared<BillItemValidator>();
    m_materialValidator = std::make_shared<MaterialValidator>();
    m_discountValidator = std::make_shared<DiscountValidator>();
    m_templateValidator = std::make_shared<TemplateValidator>();
    m_offerValidator = std::make_shared<OfferValidator>();

    DiscountDAO::Ptr discountDAO = std::make_shared<DBDiscountDAO>(db, m_discountValidator);
    CustomerDAO::Ptr customerDAO = std::make_shared<DBCustomerDAO>(db, m_customerValidator);
    MaterialDAO::Ptr materialDAO = std::make_shared<DBMaterialDAO>(db, m_materialValidator);
    BillItemDAO::Ptr billItemDAO = std::make_shared<DBBillItemDAO>(db, m_billItemValidator, materialDAO);
    BillDAO::Ptr billDAO = std::make_shared<DBBillDAO>(db, m_billValidator, customerDAO, billItemDAO, discountDAO);
    TemplateDAO::Ptr templateDAO = std::make_shared<DBTemplateDAO>(db, m_templateValidator, materialDAO);
    OfferItemDAO::Ptr offerItemDAO = std::make_shared<DBOfferItemDAO>(db, m_billItemValidator, materialDAO);
    OfferDAO::Ptr offerDAO = std::make_shared<DBOfferDAO>(db, m_offerValidator, offerItemDAO, customerDAO);

    m_customerService = std::make_shared<CustomerServiceImpl>(customerDAO, m_customerValidator);
    m_billService = std::make_shared<BillServiceImpl>(billDAO, billItemDAO, discountDAO, m_billValidator, m_billItemValidator);
    m_materialService = std::make_shared<MaterialServiceImpl>(materialDAO, m_materialValidator);
    m_templateService = std::make_shared<TemplateServiceImpl>(templateDAO, m_templateValidator);
    m_printService = std::make_shared<PrintServiceImpl>();
    m_statisticsService = std::make_shared<StatisticsServiceImpl>(billDAO);
    m_offerService = std::make_shared<OfferServiceImpl>(offerDAO, offerItemDAO, m_offerValidator, m_billItemValidator);

    m_billTableModel = new BillTableModel();
    m_customerTableModel = new CustomerTableModel();
    m_materialTableModel = new MaterialTableModel();
    m_templateTableModel = new TemplateTableModel();
    m_offerTableModel = new OfferTableModel();

    connect(ui->actionNewBill, SIGNAL(triggered(bool)), SLOT(createBill()));
    connect(ui->actionNewOffer, SIGNAL(triggered(bool)), SLOT(createOffer()));
    connect(ui->actionQuit, SIGNAL(triggered(bool)), SLOT(close()));

    initWidgets();
    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_billTableModel;
    delete m_customerTableModel;
    delete m_materialTableModel;
    delete m_templateTableModel;
    delete m_offerTableModel;
}

void MainWindow::printOffer(Offer::Ptr offer)
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);

    QPrintPreviewDialog *dialog = new QPrintPreviewDialog(printer, this);

    connect(dialog, &QPrintPreviewDialog::paintRequested, [=](QPrinter *printer) {
        m_printService->printOffer(printer, offer);
    });

    dialog->exec();
    delete dialog;
}

void MainWindow::printLetter(Letter::Ptr letter)
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);

    QPrintPreviewDialog *dialog = new QPrintPreviewDialog(printer, this);

    connect(dialog, &QPrintPreviewDialog::paintRequested, [=](QPrinter *printer) {
        m_printService->printLetter(printer, letter);
    });

    dialog->exec();
    delete dialog;
}

void MainWindow::printEnvelope(Envelope::Ptr envelope)
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);

    printer->setPaperSource(QPrinter::Envelope);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);
    printer->setPageSize((QPagedPaintDevice::PageSize) envelope->pageSize());
    printer->setOrientation((QPrinter::Orientation) envelope->orientation());

    QPrintPreviewDialog *dialog = new QPrintPreviewDialog(printer, this);

    connect(dialog, &QPrintPreviewDialog::paintRequested, [=](QPrinter *printer) {
        m_printService->printEnvelope(printer, envelope);
    });

    dialog->exec();
    delete dialog;
}

void MainWindow::exportBill(Bill::Ptr bill)
{
    QString path = getSaveFileName();
    if(path.isEmpty()) {
        return;
    }

    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);
    printer->setOutputFileName(path);
    printer->setOutputFormat(QPrinter::PdfFormat);

    m_printService->printBill(printer, bill);
}

void MainWindow::exportOffer(Offer::Ptr offer)
{
    QString path = getSaveFileName();
    if(path.isEmpty()) {
        return;
    }

    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);
    printer->setOutputFileName(path);
    printer->setOutputFormat(QPrinter::PdfFormat);

    m_printService->printOffer(printer, offer);
}

void MainWindow::exportLetter(Letter::Ptr letter, QString path)
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);
    printer->setOutputFileName(path);
    printer->setOutputFormat(QPrinter::PdfFormat);

    m_printService->printLetter(printer, letter);
}

void MainWindow::createBill()
{
    Customer::Ptr customer = openCustomerSelectionDialog();
    if (customer == nullptr) {
        return;
    }

    BillDialog *dialog = new BillDialog(this, m_billService, m_customerService, m_materialService, m_templateService);
    connect(dialog, SIGNAL(print(Bill::Ptr)), this, SLOT(printBill(Bill::Ptr)));

    dialog->setDiscountValidator(m_discountValidator);
    dialog->prepareForCreate(customer);

    if(dialog->exec() == QDialog::Accepted) {
        Bill::Ptr bill = dialog->toDomainObject();
        try {
            m_billService->addBill(bill);
            m_billTableModel->add(bill);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }

    delete dialog;
}

void MainWindow::createCustomer()
{
    CustomerDialog *dialog = new CustomerDialog(this, m_customerService);
    dialog->prepareForCreate();

    if(dialog->exec() == QDialog::Accepted) {
        Customer::Ptr customer = dialog->toDomainObject();
        m_customerTableModel->add(customer);
    }
}

void MainWindow::createMaterial()
{
    MaterialDialog *dialog = new MaterialDialog(this, m_materialService->validator());
    dialog->prepareForCreate();
    if (dialog->exec() == QDialog::Accepted) {
        Material::Ptr material = dialog->toDomainObject();
        try {
            m_materialService->add(material);
            m_materialTableModel->add(material, 0.0);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }

    delete dialog;
}

void MainWindow::createTemplate()
{
    TemplateWizard *wizard = new TemplateWizard(this, m_materialService, m_templateService);
    wizard->prepareForCreate();

    if (wizard->exec() == QWizard::Accepted) {
        Template::Ptr templ = wizard->toDomainObject();
        try {
            m_templateService->add(templ);
            m_templateTableModel->add(templ);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }

    delete wizard;
}

void MainWindow::createOffer()
{
    Customer::Ptr customer = openCustomerSelectionDialog();
    if (customer == nullptr) {
        return;
    }

    OfferDialog *dialog = new OfferDialog(this, m_billService, m_customerService, m_materialService, m_templateService, m_offerService);
    connect(dialog, SIGNAL(print(Offer::Ptr)), SLOT(printOffer(Offer::Ptr)));

    dialog->prepareForCreate(customer);

    if (dialog->exec()) {
        Offer::Ptr offer = dialog->toDomainObject();
        try {
            m_offerService->add(offer);
            m_offerTableModel->add(offer);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }

    delete dialog;
}

void MainWindow::editBill(Bill::Ptr selected)
{
    BillDialog *dialog = new BillDialog(this, m_billService, m_customerService, m_materialService, m_templateService);
    connect(dialog, SIGNAL(print(Bill::Ptr)), this, SIGNAL(print(Bill::Ptr)));

    dialog->setDiscountValidator(m_discountValidator);
    dialog->prepareForUpdate(selected);

    if(dialog->exec() == QDialog::Accepted) {
        Bill::Ptr bill = dialog->toDomainObject();
        try {
            m_billService->updateBill(bill);
            m_billTableModel->replace(selected, bill);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }

    delete dialog;
}

void MainWindow::editCustomer(Customer::Ptr selected)
{
    CustomerDialog *dialog = new CustomerDialog(this, m_customerService);
    dialog->prepareForUpdate(selected);

    if(dialog->exec() == QDialog::Accepted) {
        Customer::Ptr editedCustomer = dialog->toDomainObject();
        m_customerTableModel->replace(selected, editedCustomer);
    }

    delete dialog;
}

void MainWindow::editMaterial(Material::Ptr selected)
{
    MaterialDialog *dialog = new MaterialDialog(this, m_materialService->validator());
    dialog->prepareForUpdate(selected);
    if (dialog->exec() == QDialog::Accepted) {
        Material::Ptr material = dialog->toDomainObject();
        try {
            m_materialService->update(material);
            m_materialTableModel->replace(selected, material);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }

    delete dialog;
}

void MainWindow::editTemplate(Template::Ptr selected)
{
    TemplateWizard *wizard = new TemplateWizard(this, m_materialService, m_templateService);
    wizard->prepareForUpdate(selected);

    if (wizard->exec() == QWizard::Accepted) {
        Template::Ptr updated = wizard->toDomainObject();
        try {
            m_templateService->update(updated);
            m_templateTableModel->replace(selected, updated);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }

    delete wizard;
}

void MainWindow::editOffer(Offer::Ptr selected)
{
    OfferDialog *dialog = new OfferDialog(this, m_billService, m_customerService, m_materialService, m_templateService, m_offerService);
    connect(dialog, SIGNAL(print(Offer::Ptr)), SLOT(printOffer(Offer::Ptr)));

    dialog->prepareForUpdate(selected);

    if (dialog->exec()) {
        Offer::Ptr offer = dialog->toDomainObject();
        try {
            m_offerService->update(offer);
            m_offerTableModel->replace(selected, offer);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }

    delete dialog;
}

void MainWindow::removeBill(Bill::Ptr selected)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Delete Bill"),
                                    tr("Are you sure you want to delete the selected Bill?"),
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        try {
            m_billService->removeBill(selected);
            m_billTableModel->remove(selected);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }
}

void MainWindow::removeCustomer(Customer::Ptr selected)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Delete Customer"),
                                    tr("Are you sure you want to delete the selected Customer?"),
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        try {
            m_customerService->remove(selected);
            m_customerTableModel->remove(selected);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
        }
    }
}

void MainWindow::removeMaterial(Material::Ptr selected)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Delete Material"),
                                    tr("Are you sure you want to delete the selected Material?"),
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        try {
            m_materialService->remove(selected);
            m_materialTableModel->remove(selected);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }
}

void MainWindow::removeTemplate(Template::Ptr selected)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Delete Template"),
                                    tr("Are you sure you want to delete the selected Template?"),
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        try {
            m_templateService->remove(selected);
            m_templateTableModel->remove(selected);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }
}

void MainWindow::removeOffer(Offer::Ptr selected)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Delete Offer"),
                                    tr("Are you sure you want to delete the selected Offer?"),
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        try {
            m_offerService->remove(selected);
            m_offerTableModel->remove(selected);
        } catch (ServiceException *e) {
            QMessageBox::information(this, tr("Error"), e->what());
            delete e;
        }
    }
}

void MainWindow::openMailClient(Customer::Ptr customer)
{
    QUrl url("mailto:" + customer->mail());
    QDesktopServices::openUrl(url);
}

void MainWindow::printBill(Bill::Ptr bill)
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);

    QPrintPreviewDialog *dialog = new QPrintPreviewDialog(printer, this);

    connect(dialog, &QPrintPreviewDialog::paintRequested, [=](QPrinter *printer) {
        m_printService->printBill(printer, bill);
    });

    dialog->exec();
    delete dialog;
}

void MainWindow::initWidgets()
{
    // bill widget
    ui->widgetBills->setBillModel(m_billTableModel);
    ui->widgetBills->setBillService(m_billService);

    connect(ui->widgetBills, SIGNAL(remove(Bill::Ptr)), this, SLOT(removeBill(Bill::Ptr)));
    connect(ui->widgetBills, SIGNAL(edit(Bill::Ptr)), this, SLOT(editBill(Bill::Ptr)));
    connect(ui->widgetBills, SIGNAL(print(Bill::Ptr)), this, SLOT(printBill(Bill::Ptr)));
    connect(ui->widgetBills, SIGNAL(saveToFile(Bill::Ptr)), this, SLOT(exportBill(Bill::Ptr)));
    connect(ui->widgetBills, SIGNAL(sendMail(Customer::Ptr)), this, SLOT(openMailClient(Customer::Ptr)));

    // customer widget
    ui->widgetCustomers->setCustomerModel(m_customerTableModel);
    ui->widgetCustomers->setService(m_customerService);

    connect(ui->widgetCustomers, SIGNAL(create()), this, SLOT(createCustomer()));
    connect(ui->widgetCustomers, SIGNAL(edit(Customer::Ptr)), this, SLOT(editCustomer(Customer::Ptr)));
    connect(ui->widgetCustomers, SIGNAL(remove(Customer::Ptr)), this, SLOT(removeCustomer(Customer::Ptr)));
    connect(ui->widgetCustomers, SIGNAL(sendMail(Customer::Ptr)), this, SLOT(openMailClient(Customer::Ptr)));

    // offers widget
    ui->offersWidget->setOfferModel(m_offerTableModel);
    ui->offersWidget->setOfferService(m_offerService);

    connect(ui->offersWidget, SIGNAL(create()), this, SLOT(createOffer()));
    connect(ui->offersWidget, SIGNAL(edit(Offer::Ptr)), this, SLOT(editOffer(Offer::Ptr)));
    connect(ui->offersWidget, SIGNAL(remove(Offer::Ptr)), this, SLOT(removeOffer(Offer::Ptr)));
    connect(ui->offersWidget, SIGNAL(print(Offer::Ptr)), this, SLOT(printOffer(Offer::Ptr)));
    connect(ui->offersWidget, SIGNAL(saveToFile(Offer::Ptr)), this, SLOT(exportOffer(Offer::Ptr)));

    // materials widget
    ui->materialsWidget->setMaterialModel(m_materialTableModel);
    ui->materialsWidget->setMaterialService(m_materialService);

    connect(ui->materialsWidget, SIGNAL(create()), this, SLOT(createMaterial()));
    connect(ui->materialsWidget, SIGNAL(edit(Material::Ptr)), this, SLOT(editMaterial(Material::Ptr)));
    connect(ui->materialsWidget, SIGNAL(remove(Material::Ptr)), this, SLOT(removeMaterial(Material::Ptr)));

    // templates widget
    ui->templatesWidget->setTemplateModel(m_templateTableModel);
    ui->templatesWidget->setTemplateService(m_templateService);

    connect(ui->templatesWidget, SIGNAL(create()), this, SLOT(createTemplate()));
    connect(ui->templatesWidget, SIGNAL(edit(Template::Ptr)), this, SLOT(editTemplate(Template::Ptr)));
    connect(ui->templatesWidget, SIGNAL(remove(Template::Ptr)), this, SLOT(removeTemplate(Template::Ptr)));

    // statisticsWidget
    ui->statisticsWidget->setStatisticsService(m_statisticsService);
    ui->statisticsWidget->setBillService(m_billService);
    ui->statisticsWidget->update();

    // other signals
    connect(this, SIGNAL(dataChanged()), ui->widgetBills, SLOT(update()));
    connect(this, SIGNAL(dataChanged()), ui->widgetCustomers, SLOT(update()));
}

void MainWindow::loadSettings()
{
    QSettings settings;
    if (settings.value("print/emptyPaper").toBool()) {
        ui->actionEmptyPaper->setChecked(true);
    } else {
        ui->actionImprintedPaper->setChecked(true);
    }
}

Customer::Ptr MainWindow::openCustomerSelectionDialog()
{
    CustomerSelectionDialog *dialog = new CustomerSelectionDialog(this, m_customerService);
    if (dialog->exec() == QDialog::Accepted) {
        return dialog->selectedCustomer();
    }
    return nullptr;
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog *dialog = new SettingsDialog(this);
    dialog->exec();

    delete dialog;
}

void MainWindow::on_actionEmptyPaper_triggered()
{
    QSettings settings;
    settings.setValue("print/emptyPaper", true);

    ui->actionImprintedPaper->setChecked(false);
}

void MainWindow::on_actionImprintedPaper_triggered()
{
    QSettings settings;
    settings.setValue("print/emptyPaper", false);

    ui->actionEmptyPaper->setChecked(false);
}

void MainWindow::on_actionNewLetter_triggered()
{
    LetterDialog *dialog = new LetterDialog(this, m_customerService);
    connect(dialog, SIGNAL(print(Letter::Ptr)), SLOT(printLetter(Letter::Ptr)));
    connect(dialog, SIGNAL(save(Letter::Ptr, QString)), SLOT(exportLetter(Letter::Ptr, QString)));
    dialog->exec();

    delete dialog;
}

void MainWindow::on_actionPrintEnvelope_triggered()
{
    Customer::Ptr customer = openCustomerSelectionDialog();
    if (customer == nullptr) {
        return;
    }

    EnvelopeDialog *dialog = new EnvelopeDialog(this, m_customerService);
    connect(dialog, SIGNAL(print(Envelope::Ptr)), SLOT(printEnvelope(Envelope::Ptr)));
    dialog->setCustomer(customer);
    dialog->exec();

    delete dialog;
}

QString MainWindow::getSaveFileName()
{
    QFileDialog dialog(this,  tr("Save"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDefaultSuffix("pdf");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("PDF Files (*.pdf)");

    if (dialog.exec()) {
       return dialog.selectedFiles().first();
    }
    return QString();
}
