#include "ui/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = DatabaseSingleton::get()->getProductionDatabase();

    m_customerValidator = std::make_shared<CustomerValidator>();
    m_billValidator = std::make_shared<BillValidator>();
    m_billItemValidator = std::make_shared<BillItemValidator>();
    m_productValidator = std::make_shared<ProductValidator>();
    m_discountValidator = std::make_shared<DiscountValidator>();
    m_templateValidator = std::make_shared<TemplateValidator>();

    DiscountDAO::Ptr discountDAO = std::make_shared<DBDiscountDAO>(db, m_discountValidator);
    CustomerDAO::Ptr customerDAO = std::make_shared<DBCustomerDAO>(db, m_customerValidator);
    ProductDAO::Ptr productDAO = std::make_shared<DBProductDAO>(db, m_productValidator);
    BillItemDAO::Ptr billItemDAO = std::make_shared<DBBillItemDAO>(db, m_billItemValidator, productDAO);
    BillDAO::Ptr billDAO = std::make_shared<DBBillDAO>(db, m_billValidator, customerDAO, billItemDAO, discountDAO);
    TemplateDAO::Ptr templateDAO = std::make_shared<DBTemplateDAO>(db, m_templateValidator, productDAO);

    m_customerService = std::make_shared<CustomerServiceImpl>(customerDAO, m_customerValidator);
    m_billService = std::make_shared<BillServiceImpl>(billDAO, billItemDAO, discountDAO, m_billValidator, m_billItemValidator);
    m_productService = std::make_shared<ProductServiceImpl>(productDAO, m_productValidator);
    m_templateService = std::make_shared<TemplateServiceImpl>(templateDAO, m_templateValidator);

    connect(ui->actionNewBill, SIGNAL(triggered(bool)), ui->widgetBills, SLOT(actionNewBill()));

    initWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initWidgets()
{
    ui->widgetCustomers->setService(m_customerService);
    ui->widgetCustomers->setValidator(m_customerValidator);

    ui->widgetBills->setCustomerService(m_customerService);
    ui->widgetBills->setBillService(m_billService);
    ui->widgetBills->setDiscountValidator(m_discountValidator);
    ui->widgetBills->setProductService(m_productService);
    ui->widgetBills->setTemplateService(m_templateService);

    ui->productsWidget->setProductService(m_productService);

    connect(this, SIGNAL(dataChanged()), ui->widgetBills, SLOT(update()));
    connect(this, SIGNAL(dataChanged()), ui->widgetCustomers, SLOT(update()));
}
