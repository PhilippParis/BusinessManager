#include "ui/mainwindow.h"
#include <QApplication>

#include "tests/billitemdaotest.h"
#include "tests/customerdaotest.h"
#include "tests/billdaotest.h"

bool execUnitTests();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // exec unit tests
    if(!execUnitTests()) {
        return EXIT_FAILURE;
    }

    MainWindow w;
    w.show();

    return a.exec();
}

bool execUnitTests()
{
    bool success = true;

    BillItemDAOTest billItemDAOTest;
    CustomerDAOTest customerDAOTest;
    BillDAOTest billDAOTest;

    success &= QTest::qExec(&billItemDAOTest) == 0;
    success &= QTest::qExec(&customerDAOTest) == 0;
    success &= QTest::qExec(&billDAOTest) == 0;

    return success;
}
