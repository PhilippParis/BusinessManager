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

    DiscountDAO::Ptr discountDAO = std::make_shared<DBDiscountDAO>(db, m_discountValidator);
    CustomerDAO::Ptr customerDAO = std::make_shared<DBCustomerDAO>(db, m_customerValidator);
    MaterialDAO::Ptr materialDAO = std::make_shared<DBMaterialDAO>(db, m_materialValidator);
    BillItemDAO::Ptr billItemDAO = std::make_shared<DBBillItemDAO>(db, m_billItemValidator, materialDAO);
    BillDAO::Ptr billDAO = std::make_shared<DBBillDAO>(db, m_billValidator, customerDAO, billItemDAO, discountDAO);
    TemplateDAO::Ptr templateDAO = std::make_shared<DBTemplateDAO>(db, m_templateValidator, materialDAO);

    m_customerService = std::make_shared<CustomerServiceImpl>(customerDAO, m_customerValidator);
    m_billService = std::make_shared<BillServiceImpl>(billDAO, billItemDAO, discountDAO, m_billValidator, m_billItemValidator);
    m_materialService = std::make_shared<MaterialServiceImpl>(materialDAO, m_materialValidator);
    m_templateService = std::make_shared<TemplateServiceImpl>(templateDAO, m_templateValidator);
    m_printService = std::make_shared<PrintServiceImpl>();
    m_statisticsService = std::make_shared<StatisticsServiceImpl>(billDAO);

    m_billTableModel = new BillTableModel();

    connect(ui->actionNewBill, SIGNAL(triggered(bool)), SLOT(createBill()));
    connect(ui->actionQuit, SIGNAL(triggered(bool)), SLOT(close()));

    initWidgets();
    loadSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
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

void MainWindow::exportOffer(Offer::Ptr offer, QString path)
{
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
    BillDialog *dialog = new BillDialog(this, m_billService, m_customerService, m_materialService, m_templateService);
    connect(dialog, SIGNAL(print(Bill::Ptr)), this, SIGNAL(print(Bill::Ptr)));

    dialog->setDiscountValidator(m_discountValidator);
    dialog->prepareForCreate();

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
    ui->widgetCustomers->setService(m_customerService);
    ui->widgetCustomers->setValidator(m_customerValidator);

    connect(ui->widgetCustomers, SIGNAL(sendMail(Customer::Ptr)), this, SLOT(openMailClient(Customer::Ptr)));

    // materials widget
    ui->materialsWidget->setMaterialService(m_materialService);

    // templates widget
    ui->templatesWidget->setMaterialService(m_materialService);
    ui->templatesWidget->setTemplateService(m_templateService);

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

void MainWindow::on_actionNewOffer_triggered()
{
    OfferDialog *dialog = new OfferDialog(this, m_billService, m_customerService, m_materialService, m_templateService);
    connect(dialog, SIGNAL(print(Offer::Ptr)), SLOT(printOffer(Offer::Ptr)));
    connect(dialog, SIGNAL(save(Offer::Ptr, QString)), SLOT(exportOffer(Offer::Ptr, QString)));
    dialog->exec();

    delete dialog;
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
    EnvelopeDialog *dialog = new EnvelopeDialog(this, m_customerService);
    connect(dialog, SIGNAL(print(Envelope::Ptr)), SLOT(printEnvelope(Envelope::Ptr)));
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
