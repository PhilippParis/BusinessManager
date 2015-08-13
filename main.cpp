#include "ui/mainwindow.h"
#include <QApplication>

#include "tests/billitemdaotest.h"
#include "tests/customerdaotest.h"
#include "tests/billdaotest.h"
#include "tests/materialdaotest.h"
#include "tests/templatedaotest.h"
#include "tests/offerdaotest.h"
#include "tests/letterdaotest.h"

bool execUnitTests();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // exec unit tests
    if(!execUnitTests()) {
        return EXIT_FAILURE;
    }

    MainWindow w;
    w.showMaximized();

    return a.exec();
}

bool execUnitTests()
{
    bool success = true;

    BillItemDAOTest billItemDAOTest;
    CustomerDAOTest customerDAOTest;
    BillDAOTest billDAOTest;
    MaterialDAOTest materialDAOTest;
    TemplateDAOTest templateDAOTest;
    OfferDAOTest offerDAOTest;
    LetterDAOTest letterDAOTest;

    success &= QTest::qExec(&billItemDAOTest) == 0;
    success &= QTest::qExec(&customerDAOTest) == 0;
    success &= QTest::qExec(&billDAOTest) == 0;
    success &= QTest::qExec(&materialDAOTest) == 0;
    success &= QTest::qExec(&templateDAOTest) == 0;
    success &= QTest::qExec(&offerDAOTest) == 0;
    //success &= QTest::qExec(&letterDAOTest) == 0;

    return success;
}
