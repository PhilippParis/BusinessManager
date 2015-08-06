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

    connect(ui->actionNewBill, SIGNAL(triggered(bool)), ui->widgetBills, SLOT(actionNewBill()));
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

void MainWindow::saveBill(Bill::Ptr bill, QString path)
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);
    printer->setOutputFileName(path);
    printer->setOutputFormat(QPrinter::PdfFormat);

    m_printService->printBill(printer, bill);
}

void MainWindow::saveOffer(Offer::Ptr offer, QString path)
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);
    printer->setOutputFileName(path);
    printer->setOutputFormat(QPrinter::PdfFormat);

    m_printService->printOffer(printer, offer);
}

void MainWindow::saveLetter(Letter::Ptr letter, QString path)
{
    QPrinter *printer = new QPrinter(QPrinter::HighResolution);
    printer->setPageSize(QPrinter::A4);
    printer->setPageMargins(0.14, 0.14, 0.14, 0.14, QPrinter::Inch);
    printer->setOutputFileName(path);
    printer->setOutputFormat(QPrinter::PdfFormat);

    m_printService->printLetter(printer, letter);
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
    ui->widgetCustomers->setService(m_customerService);
    ui->widgetCustomers->setValidator(m_customerValidator);

    ui->widgetBills->setCustomerService(m_customerService);
    ui->widgetBills->setBillService(m_billService);
    ui->widgetBills->setDiscountValidator(m_discountValidator);
    ui->widgetBills->setMaterialService(m_materialService);
    ui->widgetBills->setTemplateService(m_templateService);

    ui->materialsWidget->setMaterialService(m_materialService);

    ui->templatesWidget->setMaterialService(m_materialService);
    ui->templatesWidget->setTemplateService(m_templateService);

    ui->statisticsWidget->setStatisticsService(m_statisticsService);
    ui->statisticsWidget->setBillService(m_billService);
    ui->statisticsWidget->update();

    connect(ui->widgetBills, SIGNAL(print(Bill::Ptr)), this, SLOT(printBill(Bill::Ptr)));
    connect(ui->widgetBills, SIGNAL(save(Bill::Ptr, QString)), this, SLOT(saveBill(Bill::Ptr, QString)));
    connect(ui->widgetBills, SIGNAL(sendMail(Customer::Ptr)), this, SLOT(openMailClient(Customer::Ptr)));
    connect(ui->widgetCustomers, SIGNAL(sendMail(Customer::Ptr)), this, SLOT(openMailClient(Customer::Ptr)));

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
    connect(dialog, SIGNAL(save(Offer::Ptr, QString)), SLOT(saveOffer(Offer::Ptr, QString)));
    dialog->exec();

    delete dialog;
}

void MainWindow::on_actionNewLetter_triggered()
{
    LetterDialog *dialog = new LetterDialog(this, m_customerService);
    connect(dialog, SIGNAL(print(Letter::Ptr)), SLOT(printLetter(Letter::Ptr)));
    connect(dialog, SIGNAL(save(Letter::Ptr, QString)), SLOT(saveLetter(Letter::Ptr, QString)));
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
