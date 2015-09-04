#include "ui/mainwindow.h"
#include <QApplication>

#ifdef Q_DEBUG
#include "tests/billitemdaotest.h"
#include "tests/customerdaotest.h"
#include "tests/billdaotest.h"
#include "tests/materialdaotest.h"
#include "tests/templatedaotest.h"
#include "tests/offerdaotest.h"
#include "tests/letterdaotest.h"
#endif

bool execUnitTests();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("fusion");

#ifdef Q_DEBUG
    // exec unit tests
    if(!execUnitTests()) {
        return EXIT_FAILURE;
    }
#else
    //disable logging messages
     QLoggingCategory::setFilterRules(QStringLiteral("*.debug=false"));
#endif

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QString applicationDir = QApplication::applicationDirPath();
    applicationDir.append("/languages");

    QTranslator translator;
    translator.load("BusinessManager2_" + QLocale::system().name(), applicationDir);

    a.installTranslator(&translator);

    MainWindow w;
    w.showMaximized();

    return a.exec();
}

#ifdef Q_DEBUG
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
    success &= QTest::qExec(&letterDAOTest) == 0;

    return success;
}
#endif
