#-------------------------------------------------
#
# Project created by QtCreator 2015-03-20T16:59:12
#
#-------------------------------------------------

QT       += core gui svg
QT       += sql printsupport

CONFIG (debug, debug|release) {
    QT += testlib
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

win32 {
    INCLUDEPATH += C:\Qwt-6.1.2\include
    DEPENDPATH += C:/Qwt-6.1.2/lib
    LIBS += -LC:/Qwt-6.1.2/lib

    CONFIG(debug, debug|release) {
         LIBS += -lqwtd
    } else {
         LIBS += -lqwt
    }

} else {
    INCLUDEPATH += /usr/include/qwt
    LIBS += -L/usr/lib -lqwt

    INCLUDEPATH += $$PWD/../qdecimal/src
    INCLUDEPATH += $$PWD/../qdecimal/decnumber
    LIBS += -L$$PWD/../qdecimal/lib -lqdecimal
}

CONFIG += qwt
QMAKE_CXXFLAGS += -std=c++0x

TARGET = BusinessManager2
TEMPLATE = app

TRANSLATIONS = languages/BusinessManager2_de.ts

RC_FILE = res.rc

SOURCES += main.cpp\
        ui/mainwindow.cpp \
    domain/bill.cpp \
    domain/billitem.cpp \
    domain/template.cpp \
    domain/customer.cpp \
    domain/offer.cpp \
    domain/letter.cpp \
    persistence/billdao.cpp \
    persistence/billitemdao.cpp \
    persistence/customerdao.cpp \
    persistence/templatedao.cpp \
    persistence/impl/dbbilldao.cpp \
    persistence/impl/dbbillitemdao.cpp \
    persistence/impl/dbcustomerdao.cpp \
    persistence/impl/dbtemplatedao.cpp \
    service/billservice.cpp \
    service/customerservice.cpp \
    service/templateservice.cpp \
    service/impl/billserviceimpl.cpp \
    service/impl/customerserviceimpl.cpp \
    service/impl/templateserviceimpl.cpp \
    persistence/databasesingleton.cpp \
    persistence/validation/impl/billitemvalidator.cpp \
    persistence/validation/impl/billvalidator.cpp \
    logging.cpp \
    persistence/validation/impl/customervalidator.cpp \
    exception.cpp \
    persistence/validation/validationexception.cpp \
    persistence/persistenceexception.cpp \
    service/serviceexception.cpp \
    ui/widgets/customerswidget.cpp \
    ui/dialogs/customerdialog.cpp \
    ui/widgets/billwidget.cpp \
    ui/models/customertablemodel.cpp \
    ui/models/billtablemodel.cpp \
    ui/models/billsortfilterproxymodel.cpp \
    ui/dialogs/billdialog.cpp \
    ui/models/billitemtablemodel.cpp \
    ui/wizards/billitemwizard.cpp \
    ui/delegates/spinboxdelegate.cpp \
    domain/discount.cpp \
    persistence/discountdao.cpp \
    persistence/impl/dbdiscountdao.cpp \
    persistence/validation/impl/discountvalidator.cpp \
    ui/dialogs/discountdialog.cpp \
    persistence/validation/impl/templatevalidator.cpp \
    ui/widgets/templateswidget.cpp \
    ui/models/templatetablemodel.cpp \
    ui/models/templatesortfilterproxymodel.cpp \
    ui/wizards/abstractbillitemwizard.cpp \
    ui/wizards/templatewizard.cpp \
    ui/dialogs/settingsdialog.cpp \
    ui/widgets/usersettingswidget.cpp \
    ui/widgets/documentssettingswidget.cpp \
    ui/widgets/financialsettingswidget.cpp \
    ui/widgets/settingswidget.cpp \
    service/printservice.cpp \
    service/impl/printserviceimpl.cpp \
    ui/dialogs/abstractbilldialog.cpp \
    ui/dialogs/offerdialog.cpp \
    ui/dialogs/letterdialog.cpp \
    ui/dialogs/envelopedialog.cpp \
    domain/envelope.cpp \
    ui/widgets/statisticswidget.cpp \
    domain/material.cpp \
    persistence/materialdao.cpp \
    persistence/impl/dbmaterialdao.cpp \
    persistence/validation/impl/materialvalidator.cpp \
    service/materialservice.cpp \
    service/impl/materialserviceimpl.cpp \
    ui/dialogs/materialdialog.cpp \
    ui/dialogs/materialselectiondialog.cpp \
    ui/widgets/materialswidget.cpp \
    ui/models/materialsortfilterproxymodel.cpp \
    ui/models/materialtablemodel.cpp \
    decimal.cpp \
    service/statisticsservice.cpp \
    domain/statistics.cpp \
    service/impl/statisticsserviceimpl.cpp \
    ui/dialogs/customerselectiondialog.cpp \
    ui/models/customersortfilterproxymodel.cpp \
    persistence/offerdao.cpp \
    persistence/letterdao.cpp \
    persistence/impl/dbofferdao.cpp \
    persistence/itemdao.cpp \
    persistence/offeritemdao.cpp \
    persistence/impl/dbitemdao.cpp \
    persistence/impl/dbofferitemdao.cpp \
    service/offerservice.cpp \
    service/impl/offerserviceimpl.cpp \
    persistence/validation/impl/offervalidator.cpp \
    ui/widgets/offerwidget.cpp \
    ui/models/offertablemodel.cpp \
    ui/models/offersortfilterproxymodel.cpp \
    persistence/impl/dbhtmlfileletterdao.cpp \
    persistence/validation/impl/lettervalidator.cpp \
    service/letterservice.cpp \
    service/impl/letterserviceimpl.cpp \
    ui/widgets/letterwidget.cpp \
    ui/models/lettertablemodel.cpp \
    ui/models/lettersortfilterproxymodel.cpp \
    ui/widgets/appsettingswidget.cpp \
    ui/dialogs/templateselectiondialog.cpp \
    qdecimal/QDecContext.cc \
    qdecimal/QDecDouble.cc \
    qdecimal/QDecNumber.cc \
    qdecimal/QDecPacked.cc \
    qdecimal/QDecQuad.cc \
    qdecimal/QDecSingle.cc \
    qdecimal/decBasic.c \
    qdecimal/decCommon.c \
    qdecimal/decContext.c \
    qdecimal/decDouble.c \
    qdecimal/decimal128.c \
    qdecimal/decimal32.c \
    qdecimal/decimal64.c \
    qdecimal/decNumber.c \
    qdecimal/decPacked.c \
    qdecimal/decQuad.c \
    qdecimal/decSingle.c

CONFIG(debug, debug|release) {
    SOURCES += tests/customerdaotest.cpp \
    tests/billdaotest.cpp \
    tests/letterdaotest.cpp \
    tests/billitemdaotest.cpp \
    tests/offerdaotest.cpp \
    tests/materialdaotest.cpp \
    tests/templatedaotest.cpp \
    tests/decimaltest.cpp
}

HEADERS  += ui/mainwindow.h \
    domain/bill.h \
    domain/billitem.h \
    domain/template.h \
    domain/customer.h \
    domain/offer.h \
    domain/letter.h \
    persistence/billdao.h \
    persistence/billitemdao.h \
    persistence/customerdao.h \
    persistence/templatedao.h \
    persistence/impl/dbbilldao.h \
    persistence/impl/dbbillitemdao.h \
    persistence/impl/dbcustomerdao.h \
    persistence/impl/dbtemplatedao.h \
    service/billservice.h \
    service/customerservice.h \
    service/templateservice.h \
    service/impl/billserviceimpl.h \
    service/impl/customerserviceimpl.h \
    service/impl/templateserviceimpl.h \
    persistence/databasesingleton.h \
    persistence/validation/validator.h \
    persistence/validation/impl/billitemvalidator.h \
    persistence/validation/impl/billvalidator.h \
    logging.h \
    persistence/validation/impl/customervalidator.h \
    persistence/persistenceexception.h \
    persistence/validation/validationexception.h \
    exception.h \
    service/serviceexception.h \
    ui/widgets/customerswidget.h \
    ui/dialogs/customerdialog.h \
    ui/widgets/billwidget.h \
    ui/models/customertablemodel.h \
    ui/models/billtablemodel.h \
    ui/models/billsortfilterproxymodel.h \
    ui/dialogs/billdialog.h \
    ui/models/billitemtablemodel.h \
    ui/models/domainitemmodel.h \
    ui/wizards/billitemwizard.h \
    ui/delegates/spinboxdelegate.h \
    domain/discount.h \
    persistence/discountdao.h \
    persistence/impl/dbdiscountdao.h \
    persistence/validation/impl/discountvalidator.h \
    ui/dialogs/discountdialog.h \
    persistence/validation/impl/templatevalidator.h \
    ui/widgets/templateswidget.h \
    ui/models/templatetablemodel.h \
    ui/models/templatesortfilterproxymodel.h \
    ui/wizards/abstractbillitemwizard.h \
    ui/wizards/templatewizard.h \
    ui/dialogs/settingsdialog.h \
    ui/widgets/usersettingswidget.h \
    ui/widgets/documentssettingswidget.h \
    ui/widgets/financialsettingswidget.h \
    ui/widgets/settingswidget.h \
    service/printservice.h \
    service/impl/printserviceimpl.h \
    ui/dialogs/abstractbilldialog.h \
    ui/dialogs/offerdialog.h \
    ui/dialogs/letterdialog.h \
    ui/dialogs/envelopedialog.h \
    domain/envelope.h \
    ui/widgets/statisticswidget.h \
    domain/material.h \
    persistence/materialdao.h \
    persistence/impl/dbmaterialdao.h \
    persistence/validation/impl/materialvalidator.h \
    service/materialservice.h \
    service/impl/materialserviceimpl.h \
    ui/dialogs/materialdialog.h \
    ui/dialogs/materialselectiondialog.h \
    ui/widgets/materialswidget.h \
    ui/models/materialsortfilterproxymodel.h \
    ui/models/materialtablemodel.h \
    decimal.h \
    service/statisticsservice.h \
    domain/statistics.h \
    service/impl/statisticsserviceimpl.h \
    ui/dialogs/customerselectiondialog.h \
    ui/models/customersortfilterproxymodel.h \
    persistence/offerdao.h \
    persistence/letterdao.h \
    persistence/impl/dbofferdao.h \
    persistence/itemdao.h \
    persistence/offeritemdao.h \
    persistence/impl/dbitemdao.h \
    persistence/impl/dbofferitemdao.h \
    service/offerservice.h \
    service/impl/offerserviceimpl.h \
    persistence/validation/impl/offervalidator.h \
    ui/widgets/offerwidget.h \
    ui/models/offertablemodel.h \
    ui/models/offersortfilterproxymodel.h \
    persistence/impl/dbhtmlfileletterdao.h \
    persistence/validation/impl/lettervalidator.h \
    service/letterservice.h \
    service/impl/letterserviceimpl.h \
    ui/widgets/letterwidget.h \
    ui/models/lettertablemodel.h \
    ui/models/lettersortfilterproxymodel.h \
    ui/widgets/appsettingswidget.h \
    ui/dialogs/templateselectiondialog.h \
    qdecimal/decContext.h \
    qdecimal/decDouble.h \
    qdecimal/decDPD.h \
    qdecimal/decimal128.h \
    qdecimal/decimal32.h \
    qdecimal/decimal64.h \
    qdecimal/decNumber.h \
    qdecimal/decNumberLocal.h \
    qdecimal/decPacked.h \
    qdecimal/decQuad.h \
    qdecimal/decSingle.h \
    qdecimal/Port_stdint.h \
    qdecimal/QDecContext.hh \
    qdecimal/QDecDouble.hh \
    qdecimal/QDecFwd.hh \
    qdecimal/QDecNumber.hh \
    qdecimal/QDecPacked.hh \
    qdecimal/QDecQuad.hh \
    qdecimal/QDecSingle.hh \
    qdecimal/VCpp_stdint.h


CONFIG(debug, debug|release) {
    HEADERS += tests/materialdaotest.h \
    tests/letterdaotest.h \
    tests/offerdaotest.h \
    tests/templatedaotest.h \
    tests/customerdaotest.h \
    tests/billdaotest.h \
    tests/billitemdaotest.h \
    tests/decimaltest.h
}

FORMS    += ui/mainwindow.ui \
    ui/widgets/customerswidget.ui \
    ui/dialogs/customerdialog.ui \
    ui/widgets/billwidget.ui \
    ui/dialogs/billdialog.ui \
    ui/dialogs/discountdialog.ui \
    ui/widgets/templateswidget.ui \
    ui/wizards/abstractbillitemwizard.ui \
    ui/dialogs/settingsdialog.ui \
    ui/widgets/usersettingswidget.ui \
    ui/widgets/documentssettingswidget.ui \
    ui/widgets/financialsettingswidget.ui \
    ui/dialogs/letterdialog.ui \
    ui/dialogs/envelopedialog.ui \
    ui/widgets/statisticswidget.ui \
    ui/dialogs/materialdialog.ui \
    ui/dialogs/materialselectiondialog.ui \
    ui/widgets/materialswidget.ui \
    ui/dialogs/customerselectiondialog.ui \
    ui/widgets/offerwidget.ui \
    ui/widgets/letterwidget.ui \
    ui/widgets/appsettingswidget.ui \
    ui/dialogs/templateselectiondialog.ui

RESOURCES += \
    resources.qrc
