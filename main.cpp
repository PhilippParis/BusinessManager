#include "ui/mainwindow.h"
#include <QApplication>

#ifdef QT_DEBUG
#include "tests/billitemdaotest.h"
#include "tests/customerdaotest.h"
#include "tests/billdaotest.h"
#include "tests/materialdaotest.h"
#include "tests/templatedaotest.h"
#include "tests/offerdaotest.h"
#include "tests/letterdaotest.h"
#include "tests/decimaltest.h"
#endif

bool execUnitTests();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("fusion");

#ifdef QT_DEBUG
    // exec unit tests
    if(!execUnitTests()) {
        return EXIT_FAILURE;
    }
#else
    //disable logging messages
    QLoggingCategory::setFilterRules(QStringLiteral("*.debug=false"));
#endif

    QString applicationDir = QApplication::applicationDirPath();
    QString lang = QLocale::system().name().split("_").first();
    applicationDir.append("/languages");

    // install translator for qt strings
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + lang,applicationDir);
    a.installTranslator(&qtTranslator);

    // install translator for application strings
    QTranslator translator;
    translator.load("BusinessManager2_" + lang, applicationDir);
    a.installTranslator(&translator);

    MainWindow w;
    w.showMaximized();

    return a.exec();
}

#ifdef QT_DEBUG
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
    DecimalTest decimalTest;

    success &= QTest::qExec(&billItemDAOTest) == 0;
    success &= QTest::qExec(&customerDAOTest) == 0;
    success &= QTest::qExec(&billDAOTest) == 0;
    success &= QTest::qExec(&materialDAOTest) == 0;
    success &= QTest::qExec(&templateDAOTest) == 0;
    success &= QTest::qExec(&offerDAOTest) == 0;
    success &= QTest::qExec(&letterDAOTest) == 0;
    success &= QTest::qExec(&decimalTest) == 0;

    return success;
}
#endif
