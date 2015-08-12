#include "letterdaotest.h"
void LetterDAOTest::initTestCase()
{
    QSqlDatabase testDB = DatabaseSingleton::get()->getTestDatabase();

    m_customerDAO = std::make_shared<DBCustomerDAO>(testDB, std::make_shared<CustomerValidator>());
    m_letterDAO = std::make_shared<DBHTMLFileLetterDAO>(testDB, std::make_shared<LetterValidator>(), m_customerDAO);

    // create dummy valid customer
    m_validCustomer = std::make_shared<Customer>();
    m_validCustomer->setTitle("title");
    m_validCustomer->setName("name");
    m_validCustomer->setSurname("surname");
    m_validCustomer->setOrganisation("org");
    m_validCustomer->setCity("city");
    m_validCustomer->setStreet("street");
    m_validCustomer->setMail("mail");

    m_customerDAO->create(m_validCustomer);
    QVERIFY(m_validCustomer->id() >= 0);
}

void LetterDAOTest::insertTest_data()
{
    QTest::addColumn<QDate>("date");
    QTest::addColumn<Customer::Ptr>("customer");
    QTest::addColumn<QString>("html");
    QTest::addColumn<bool>("result");

    QString validHtml = "<!DOCTYPE html><html><body><h1>Test</h1></body></html>";
    Customer::Ptr invalidCustomer = std::make_shared<Customer>();
    Customer::Ptr nullCustomer = nullptr;

    QTest::newRow("validData_shouldPass") << QDate::currentDate() << m_validCustomer << validHtml << true;
    QTest::newRow("invalidDate_shouldFail") << QDate() << m_validCustomer << validHtml << false;
    QTest::newRow("invalidCustomer_shouldFail") << QDate::currentDate() << invalidCustomer << validHtml << false;
    QTest::newRow("nullCustomer_shouldFail") << QDate::currentDate() << nullCustomer << validHtml << false;
}

void LetterDAOTest::insertTest()
{
    QFETCH(QDate, date);
    QFETCH(Customer::Ptr, customer);
    QFETCH(QString, html);
    QFETCH(bool, result);

    // PREPARE
    QTextDocument *doc = new QTextDocument();
    doc->setHtml(html);

    Letter::Ptr letter = std::make_shared<Letter>();
    letter->setDate(date);
    letter->setCustomer(customer);
    letter->setTextDoc(doc);

    // WHEN / THEN
    try {
        m_letterDAO->create(letter);
        QVERIFY(letter->id() >= 0);

        Letter::Ptr letterFromData = m_letterDAO->get(letter->id());
        QVERIFY(letter->equals(letterFromData));

    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
    }
}

void LetterDAOTest::updateTest_data()
{
    QTest::addColumn<QDate>("date");
    QTest::addColumn<Customer::Ptr>("customer");
    QTest::addColumn<QString>("html");
    QTest::addColumn<bool>("result");

    QString validHtml = "<!DOCTYPE html><html><body><h1>Test</h1></body></html>";
    Customer::Ptr invalidCustomer = std::make_shared<Customer>();
    Customer::Ptr nullCustomer = nullptr;

    QTest::newRow("validData_shouldPass") << QDate::currentDate() << m_validCustomer << validHtml << true;
    QTest::newRow("invalidDate_shouldFail") << QDate() << m_validCustomer << validHtml << false;
    QTest::newRow("invalidCustomer_shouldFail") << QDate::currentDate() << invalidCustomer << validHtml << false;
    QTest::newRow("nullCustomer_shouldFail") << QDate::currentDate() << nullCustomer << validHtml << false;
}

void LetterDAOTest::updateTest()
{
    QFETCH(QDate, date);
    QFETCH(Customer::Ptr, customer);
    QFETCH(QString, html);
    QFETCH(bool, result);

    // PREPARE
    QString validHtml = "<!DOCTYPE html><html><body><h2>Test</h2></body></html>";
    QTextDocument *doc = new QTextDocument();
    doc->setHtml(validHtml);

    Letter::Ptr letter = std::make_shared<Letter>();
    letter->setDate(QDate::currentDate());
    letter->setCustomer(m_validCustomer);
    letter->setTextDoc(doc);

    m_letterDAO->create(letter);
    QVERIFY(letter->id() >= 0);

    // WHEN / THEN
    doc = new QTextDocument();
    doc->setHtml(html);

    letter->setDate(date);
    letter->setCustomer(customer);
    letter->setTextDoc(doc);

    try {
        m_letterDAO->update(letter);
        Letter::Ptr letterFromData = m_letterDAO->get(letter->id());
        QVERIFY(letter->equals(letterFromData));
    } catch (PersistenceException *e) {
        delete e;
        if(result) {
            QFAIL("should not throw exception");
        }
    }
}

void LetterDAOTest::updateWithInvalidIDTest()
{
    // PREPARE
    QString validHtml = "<!DOCTYPE html><html><body><h2>Test</h2></body></html>";
    QTextDocument *doc = new QTextDocument();
    doc->setHtml(validHtml);

    Letter::Ptr letter = std::make_shared<Letter>();
    letter->setDate(QDate::currentDate());
    letter->setCustomer(m_validCustomer);
    letter->setTextDoc(doc);

    // get not used id
    int id = 0;
    try {
        while(true) {
            m_letterDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }
    letter->setId(id);

    try {
        m_letterDAO->update(letter);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
}

void LetterDAOTest::removeTestWithValidIDShouldPass()
{
    // PREPARE
    QString validHtml = "<!DOCTYPE html><html><body><h2>Test</h2></body></html>";
    QTextDocument *doc = new QTextDocument();
    doc->setHtml(validHtml);

    Letter::Ptr letter = std::make_shared<Letter>();
    letter->setDate(QDate::currentDate());
    letter->setCustomer(m_validCustomer);
    letter->setTextDoc(doc);

    m_letterDAO->create(letter);
    QVERIFY(letter->id() >= 0);

    int prevDataSetCount = m_letterDAO->getAll().size();

    // WHEN / THEN
    m_letterDAO->remove(letter);
    QCOMPARE(m_letterDAO->getAll().size(), prevDataSetCount - 1);
}

void LetterDAOTest::removeTestWithInValidIDShouldFail()
{
    // PREPARE
    QString validHtml = "<!DOCTYPE html><html><body><h2>Test</h2></body></html>";
    QTextDocument *doc = new QTextDocument();
    doc->setHtml(validHtml);

    Letter::Ptr letter = std::make_shared<Letter>();
    letter->setDate(QDate::currentDate());
    letter->setCustomer(m_validCustomer);
    letter->setTextDoc(doc);

    // get not used id
    int id = 0;
    try {
        while(true) {
            m_letterDAO->get(++id);
        }
    } catch (PersistenceException *e) {
        delete e;
    }
    letter->setId(id);

    // WHEN / THEN
    try {
        m_letterDAO->remove(letter);
        QFAIL("should throw exception");
    } catch (PersistenceException *e) {
        delete e;
    }
}

void LetterDAOTest::getAllTest()
{
    int prevDataSetCount = m_letterDAO->getAll().size();

    QString validHtml = "<!DOCTYPE html><html><body><h2>Test</h2></body></html>";
    QTextDocument *doc = new QTextDocument();
    doc->setHtml(validHtml);

    Letter::Ptr letter = std::make_shared<Letter>();
    letter->setDate(QDate::currentDate());
    letter->setCustomer(m_validCustomer);
    letter->setTextDoc(doc);

    // WHEN / THEN
    m_letterDAO->create(letter);
    QVERIFY(letter->id() >= 0);

    QCOMPARE(m_letterDAO->getAll().size(), prevDataSetCount + 1);
}
