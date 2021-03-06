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
    m_letterValidator = std::make_shared<LetterValidator>();

    DiscountDAO::Ptr discountDAO = std::make_shared<DBDiscountDAO>(db, m_discountValidator);
    CustomerDAO::Ptr customerDAO = std::make_shared<DBCustomerDAO>(db, m_customerValidator);
    MaterialDAO::Ptr materialDAO = std::make_shared<DBMaterialDAO>(db, m_materialValidator);
    BillItemDAO::Ptr billItemDAO = std::make_shared<DBBillItemDAO>(db, m_billItemValidator, materialDAO);
    BillDAO::Ptr billDAO = std::make_shared<DBBillDAO>(db, m_billValidator, customerDAO, billItemDAO, discountDAO);
    TemplateDAO::Ptr templateDAO = std::make_shared<DBTemplateDAO>(db, m_templateValidator, materialDAO);
    OfferItemDAO::Ptr offerItemDAO = std::make_shared<DBOfferItemDAO>(db, m_billItemValidator, materialDAO);
    OfferDAO::Ptr offerDAO = std::make_shared<DBOfferDAO>(db, m_offerValidator, offerItemDAO, customerDAO);
    LetterDAO::Ptr letterDAO = std::make_shared<DBHTMLFileLetterDAO>(db, m_letterValidator, customerDAO);

    m_customerService = std::make_shared<CustomerServiceImpl>(customerDAO, m_customerValidator);
    m_billService = std::make_shared<BillServiceImpl>(billDAO, billItemDAO, discountDAO, m_billValidator, m_billItemValidator);
    m_materialService = std::make_shared<MaterialServiceImpl>(materialDAO, m_materialValidator);
    m_templateService = std::make_shared<TemplateServiceImpl>(templateDAO, m_templateValidator);
    m_printService = std::make_shared<PrintServiceImpl>();
    m_statisticsService = std::make_shared<StatisticsServiceImpl>(billDAO);
    m_offerService = std::make_shared<OfferServiceImpl>(offerDAO, offerItemDAO, m_offerValidator, m_billItemValidator);
    m_letterService = std::make_shared<LetterServiceImpl>(letterDAO, m_letterValidator);

    m_billTableModel = new BillTableModel();
    m_customerTableModel = new CustomerTableModel();
    m_materialTableModel = new MaterialTableModel();
    m_templateTableModel = new TemplateTableModel();
    m_offerTableModel = new OfferTableModel();
    m_letterTableModel = new LetterTableModel();

    connect(m_billTableModel, &BillTableModel::billPayedStatusChanged, [=](Bill::Ptr bill) {
        m_billService->updateBill(bill);
    });

    connect(ui->actionNewBill, SIGNAL(triggered(bool)), SLOT(createBill()));
    connect(ui->actionNewOffer, SIGNAL(triggered(bool)), SLOT(createOffer()));
    connect(ui->actionNewLetter, SIGNAL(triggered(bool)), SLOT(createLetter()));
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

void MainWindow::initWidgets()
{
    // bill widget
    ui->widgetBills->setBillModel(m_billTableModel);
    ui->widgetBills->setPrintService(m_printService);
    ui->widgetBills->setDateFilter(m_billService->billDateRange().first, QDate::currentDate());

    connect(ui->widgetBills, SIGNAL(remove(Bill::Ptr)), this, SLOT(removeBill(Bill::Ptr)));
    connect(ui->widgetBills, SIGNAL(edit(Bill::Ptr)), this, SLOT(editBill(Bill::Ptr)));
    connect(ui->widgetBills, SIGNAL(print(Bill::Ptr)), this, SLOT(printBill(Bill::Ptr)));
    connect(ui->widgetBills, SIGNAL(saveToFile(Bill::Ptr)), this, SLOT(exportBill(Bill::Ptr)));
    connect(ui->widgetBills, SIGNAL(sendMail(Customer::Ptr)), this, SLOT(openMailClient(Customer::Ptr)));

    // letters widget
    ui->widgetLetters->setLetterModel(m_letterTableModel);
    ui->widgetLetters->setPrintService(m_printService);

    connect(ui->widgetLetters, SIGNAL(edit(Letter::Ptr)), this, SLOT(editLetter(Letter::Ptr)));
    connect(ui->widgetLetters, SIGNAL(remove(Letter::Ptr)), this, SLOT(removeLetter(Letter::Ptr)));
    connect(ui->widgetLetters, SIGNAL(print(Letter::Ptr)), this, SLOT(printLetter(Letter::Ptr)));
    connect(ui->widgetLetters, SIGNAL(saveToFile(Letter::Ptr)), this, SLOT(exportLetter(Letter::Ptr)));

    // offers widget
    ui->offersWidget->setOfferModel(m_offerTableModel);
    ui->offersWidget->setPrintService(m_printService);

    connect(ui->offersWidget, SIGNAL(edit(Offer::Ptr)), this, SLOT(editOffer(Offer::Ptr)));
    connect(ui->offersWidget, SIGNAL(remove(Offer::Ptr)), this, SLOT(removeOffer(Offer::Ptr)));
    connect(ui->offersWidget, SIGNAL(print(Offer::Ptr)), this, SLOT(printOffer(Offer::Ptr)));
    connect(ui->offersWidget, SIGNAL(saveToFile(Offer::Ptr)), this, SLOT(exportOffer(Offer::Ptr)));

    // customer widget
    ui->widgetCustomers->setCustomerModel(m_customerTableModel);

    connect(ui->widgetCustomers, SIGNAL(create()), this, SLOT(createCustomer()));
    connect(ui->widgetCustomers, SIGNAL(edit(Customer::Ptr)), this, SLOT(editCustomer(Customer::Ptr)));
    connect(ui->widgetCustomers, SIGNAL(remove(Customer::Ptr)), this, SLOT(removeCustomer(Customer::Ptr)));
    connect(ui->widgetCustomers, SIGNAL(sendMail(Customer::Ptr)), this, SLOT(openMailClient(Customer::Ptr)));

    // materials widget
    ui->materialsWidget->setMaterialModel(m_materialTableModel);

    connect(ui->materialsWidget, SIGNAL(create()), this, SLOT(createMaterial()));
    connect(ui->materialsWidget, SIGNAL(edit(Material::Ptr)), this, SLOT(editMaterial(Material::Ptr)));
    connect(ui->materialsWidget, SIGNAL(remove(Material::Ptr)), this, SLOT(removeMaterial(Material::Ptr)));

    // templates widget
    ui->templatesWidget->setTemplateModel(m_templateTableModel);

    connect(ui->templatesWidget, SIGNAL(create()), this, SLOT(createTemplate()));
    connect(ui->templatesWidget, SIGNAL(edit(Template::Ptr)), this, SLOT(editTemplate(Template::Ptr)));
    connect(ui->templatesWidget, SIGNAL(remove(Template::Ptr)), this, SLOT(removeTemplate(Template::Ptr)));

    // statisticsWidget
    ui->statisticsWidget->setStatisticsService(m_statisticsService);
    ui->statisticsWidget->setDateFilter(m_billService->billDateRange().first, QDate::currentDate());

    // load data from datasource
    m_billTableModel->addAll(m_billService->getAllBills());
    m_offerTableModel->addAll(m_offerService->getAll());
    m_letterTableModel->addAll(m_letterService->getAll());
    m_customerTableModel->addAll(m_customerService->getAll());
    m_materialTableModel->addAll(m_materialService->getAll());
    m_templateTableModel->addAll(m_templateService->getAll());
}

void MainWindow::printBill(Bill::Ptr bill)
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setFullPage(true);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);

    QPrintPreviewDialog *dialog = new QPrintPreviewDialog(printer, this);
    dialog->setFixedHeight(900);

    connect(dialog, &QPrintPreviewDialog::paintRequested, [=](QPrinter *printer) {
        m_printService->printBill(printer, bill);
    });

    dialog->exec();
    delete dialog;
}

void MainWindow::printOffer(Offer::Ptr offer)
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setFullPage(true);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);

    QPrintPreviewDialog *dialog = new QPrintPreviewDialog(printer, this);
    dialog->setFixedHeight(900);

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
    printer->setFullPage(true);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);

    QPrintPreviewDialog *dialog = new QPrintPreviewDialog(printer, this);
    dialog->setFixedHeight(900);

    connect(dialog, &QPrintPreviewDialog::paintRequested, [=](QPrinter *printer) {
        m_printService->printLetter(printer, letter);
    });

    dialog->exec();
    delete dialog;
}

void MainWindow::printEnvelope(Envelope::Ptr envelope)
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);

    printer->setFullPage(true);
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
    QString fileName = QString::number(bill->date().year()) + " - " + QString::number(bill->billNumber()) + " - ";
    if (bill->customer()->organisation().isEmpty()) {
        fileName += bill->customer()->fullName();
    } else {
        fileName += bill->customer()->organisation();
    }
    QSettings settings;
    QString path = getSaveFileName(fileName, settings.value("app/billDir").toString());
    if(path.isEmpty()) {
        return;
    }

    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setResolution(600);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);
    printer->setOutputFileName(path);
    printer->setOutputFormat(QPrinter::PdfFormat);

    m_printService->printBill(printer, bill);
}

void MainWindow::exportOffer(Offer::Ptr offer)
{
    QString fileName = tr("Offer") + " - " + offer->date().toString("dd-MM-yyyy") + " - ";
    if (offer->customer()->organisation().isEmpty()) {
        fileName += offer->customer()->fullName();
    } else {
        fileName += offer->customer()->organisation();
    }

    QSettings settings;
    QString path = getSaveFileName(fileName, settings.value("app/offerDir").toString());
    if(path.isEmpty()) {
        return;
    }

    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setOutputFormat(QPrinter::PdfFormat);
    printer->setPageSize(QPrinter::A4);
    printer->setFullPage(true);
    printer->setResolution(600);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);
    printer->setOutputFileName(path);

    m_printService->printOffer(printer, offer);
}

void MainWindow::exportLetter(Letter::Ptr letter)
{
    QString fileName = tr("Letter") + " - " + letter->date().toString("dd-MM-yyyy") + " - ";
    if (letter->customer()->organisation().isEmpty()) {
        fileName += letter->customer()->fullName();
    } else {
        fileName += letter->customer()->organisation();
    }

    QSettings settings;
    QString path = getSaveFileName(fileName, settings.value("app/letterDir").toString());
    if(path.isEmpty()) {
        return;
    }

    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setResolution(600);
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
    connect(dialog, SIGNAL(billAdded(Bill::Ptr)), ui->statisticsWidget, SLOT(update()));
    connect(dialog, &BillDialog::billAdded, m_billTableModel, &BillTableModel::add);
    connect(dialog, &BillDialog::customerAdded, m_customerTableModel, &CustomerTableModel::add);
    connect(dialog, &BillDialog::templateAdded, m_templateTableModel, &TemplateTableModel::add);
    connect(dialog, &BillDialog::materialAdded, [=](Material::Ptr material) {m_materialTableModel->add(material, 0.0);});

    dialog->setDiscountValidator(m_discountValidator);
    dialog->prepareForCreate(customer);
    dialog->exec();

    delete dialog;
}

void MainWindow::createCustomer()
{
    CustomerDialog *dialog = new CustomerDialog(this, m_customerService);
    connect(dialog, &CustomerDialog::customerAdded, m_customerTableModel, &CustomerTableModel::add);
    dialog->prepareForCreate();

    dialog->exec();
    delete dialog;
}

void MainWindow::createMaterial()
{
    MaterialDialog *dialog = new MaterialDialog(this, m_materialService);
    connect(dialog, &MaterialDialog::materialAdded, [=](Material::Ptr m) {m_materialTableModel->add(m, 0.0);});
    dialog->prepareForCreate();
    dialog->exec();
    delete dialog;
}

void MainWindow::createTemplate()
{
    TemplateWizard *wizard = new TemplateWizard(this, m_materialService, m_templateService);
    connect(wizard, &TemplateWizard::templateAdded, m_templateTableModel, &TemplateTableModel::add);
    wizard->prepareForCreate();
    wizard->exec();
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
    connect(dialog, &OfferDialog::offerAdded, m_offerTableModel, &OfferTableModel::add);
    connect(dialog, &OfferDialog::customerAdded, m_customerTableModel, &CustomerTableModel::add);
    connect(dialog, &OfferDialog::templateAdded, m_templateTableModel, &TemplateTableModel::add);
    dialog->prepareForCreate(customer);
    dialog->exec();
    delete dialog;
}

void MainWindow::createLetter()
{
    Customer::Ptr customer = openCustomerSelectionDialog();
    if (customer == nullptr) {
        return;
    }

    LetterDialog *dialog = new LetterDialog(this, m_letterService, m_customerService);
    connect(dialog, SIGNAL(print(Letter::Ptr)), SLOT(printLetter(Letter::Ptr)));
    connect(dialog, &LetterDialog::letterAdded, m_letterTableModel, &LetterTableModel::add);
    connect(dialog, &LetterDialog::customerAdded, m_customerTableModel, &CustomerTableModel::add);
    dialog->prepareForCreate(customer);
    dialog->exec();
    delete dialog;
}

void MainWindow::editBill(Bill::Ptr selected)
{
    BillDialog *dialog = new BillDialog(this, m_billService, m_customerService, m_materialService, m_templateService);
    connect(dialog, SIGNAL(billUpdated(Bill::Ptr)), ui->statisticsWidget, SLOT(update()));
    connect(dialog, SIGNAL(print(Bill::Ptr)), this, SLOT(printBill(Bill::Ptr)));
    connect(dialog, &BillDialog::billUpdated, m_billTableModel, &BillTableModel::update);
    connect(dialog, &BillDialog::customerAdded, m_customerTableModel, &CustomerTableModel::add);
    connect(dialog, &BillDialog::templateAdded, m_templateTableModel, &TemplateTableModel::add);
    connect(dialog, &BillDialog::materialAdded, [=](Material::Ptr material) {m_materialTableModel->add(material, 0.0);});
    dialog->setDiscountValidator(m_discountValidator);
    dialog->prepareForUpdate(selected);
    dialog->exec();
    delete dialog;
}

void MainWindow::editCustomer(Customer::Ptr selected)
{
    CustomerDialog *dialog = new CustomerDialog(this, m_customerService);
    connect(dialog, &CustomerDialog::customerUpdated, m_customerTableModel, &CustomerTableModel::update);
    dialog->prepareForUpdate(selected);
    dialog->exec();
    delete dialog;
}

void MainWindow::editMaterial(Material::Ptr selected)
{
    MaterialDialog *dialog = new MaterialDialog(this, m_materialService);
    connect(dialog, &MaterialDialog::materialUpdated, m_materialTableModel, &MaterialTableModel::update);
    dialog->prepareForUpdate(selected);
    dialog->exec();
    delete dialog;
}

void MainWindow::editTemplate(Template::Ptr selected)
{
    TemplateWizard *wizard = new TemplateWizard(this, m_materialService, m_templateService);
    connect(wizard, &TemplateWizard::templateUpdated, m_templateTableModel, &TemplateTableModel::update);
    wizard->prepareForUpdate(selected);
    wizard->exec();
    delete wizard;
}

void MainWindow::editOffer(Offer::Ptr selected)
{
    OfferDialog *dialog = new OfferDialog(this, m_billService, m_customerService, m_materialService, m_templateService, m_offerService);
    connect(dialog, SIGNAL(print(Offer::Ptr)), SLOT(printOffer(Offer::Ptr)));
    connect(dialog, &OfferDialog::offerUpdated, m_offerTableModel, &OfferTableModel::update);
    dialog->prepareForUpdate(selected);
    dialog->exec();
    delete dialog;
}

void MainWindow::editLetter(Letter::Ptr selected)
{
    LetterDialog *dialog = new LetterDialog(this, m_letterService, m_customerService);
    connect(dialog, SIGNAL(print(Letter::Ptr)), SLOT(printLetter(Letter::Ptr)));
    connect(dialog, &LetterDialog::letterUpdated, m_letterTableModel, &LetterTableModel::update);
    connect(dialog, &LetterDialog::customerAdded, m_customerTableModel, &CustomerTableModel::add);
    dialog->prepareForUpdate(selected);
    dialog->exec();
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
            ui->statisticsWidget->update();
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

void MainWindow::removeLetter(Letter::Ptr selected)
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Delete Letter"),
                                    tr("Are you sure you want to delete the selected Letter?"),
                                    QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        try {
            m_letterService->remove(selected);
            m_letterTableModel->remove(selected);
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
    connect(dialog, &CustomerSelectionDialog::customerAdded, m_customerTableModel, &CustomerTableModel::add);

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

void MainWindow::on_actionPrintEnvelope_triggered()
{
    Customer::Ptr customer = openCustomerSelectionDialog();
    if (customer == nullptr) {
        return;
    }

    EnvelopeDialog *dialog = new EnvelopeDialog(this, m_customerService);
    connect(dialog, SIGNAL(print(Envelope::Ptr)), SLOT(printEnvelope(Envelope::Ptr)));
    connect(dialog, &EnvelopeDialog::customerAdded, m_customerTableModel, &CustomerTableModel::add);

    dialog->setCustomer(customer);
    dialog->exec();

    delete dialog;
}

QString MainWindow::getSaveFileName(QString defaultFileName, QString dir)
{
    QFileDialog dialog(this,  tr("Save"));
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    dialog.setDefaultSuffix("pdf");
    dialog.setFileMode(QFileDialog::AnyFile);
    dialog.setNameFilter("PDF Files (*.pdf)");
    dialog.selectFile(defaultFileName);
    dialog.setConfirmOverwrite(true);
    dialog.setDirectory(dir);

    if (dialog.exec()) {
       return dialog.selectedFiles().first();
    }
    return QString();
}
