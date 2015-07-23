#-------------------------------------------------
#
# Project created by QtCreator 2015-03-20T16:59:12
#
#-------------------------------------------------

QT       += core gui
QT       += sql printsupport
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++0x

TARGET = BusinessManager2
TEMPLATE = app

SOURCES += main.cpp\
        ui/mainwindow.cpp \
    domain/bill.cpp \
    domain/product.cpp \
    domain/billitem.cpp \
    domain/template.cpp \
    domain/customer.cpp \
    domain/document.cpp \
    domain/offer.cpp \
    domain/letter.cpp \
    persistence/billdao.cpp \
    persistence/productdao.cpp \
    persistence/billitemdao.cpp \
    persistence/customerdao.cpp \
    persistence/templatedao.cpp \
    persistence/impl/dbbilldao.cpp \
    persistence/impl/dbproductdao.cpp \
    persistence/impl/dbbillitemdao.cpp \
    persistence/impl/dbcustomerdao.cpp \
    persistence/impl/dbtemplatedao.cpp \
    service/billservice.cpp \
    service/customerservice.cpp \
    service/templateservice.cpp \
    service/productservice.cpp \
    service/impl/billserviceimpl.cpp \
    service/impl/productserviceimpl.cpp \
    service/impl/customerserviceimpl.cpp \
    service/impl/templateserviceimpl.cpp \
    tests/billitemdaotest.cpp \
    persistence/databasesingleton.cpp \
    persistence/validation/impl/billitemvalidator.cpp \
    persistence/validation/impl/billvalidator.cpp \
    logging.cpp \
    persistence/validation/impl/customervalidator.cpp \
    tests/customerdaotest.cpp \
    tests/billdaotest.cpp \
    tests/productdaotest.cpp \
    persistence/validation/impl/productvalidator.cpp \
    exception.cpp \
    persistence/validation/validationexception.cpp \
    persistence/persistenceexception.cpp \
    service/serviceexception.cpp \
    ui/widgets/customerswidget.cpp \
    ui/models/customermodel.cpp \
    ui/dialogs/customerdialog.cpp

HEADERS  += ui/mainwindow.h \
    domain/bill.h \
    domain/product.h \
    domain/billitem.h \
    domain/template.h \
    domain/customer.h \
    domain/document.h \
    domain/offer.h \
    domain/letter.h \
    persistence/billdao.h \
    persistence/productdao.h \
    persistence/billitemdao.h \
    persistence/customerdao.h \
    persistence/templatedao.h \
    persistence/impl/dbbilldao.h \
    persistence/impl/dbproductdao.h \
    persistence/impl/dbbillitemdao.h \
    persistence/impl/dbcustomerdao.h \
    persistence/impl/dbtemplatedao.h \
    service/billservice.h \
    service/customerservice.h \
    service/templateservice.h \
    service/productservice.h \
    service/impl/billserviceimpl.h \
    service/impl/productserviceimpl.h \
    service/impl/customerserviceimpl.h \
    service/impl/templateserviceimpl.h \
    tests/billitemdaotest.h \
    persistence/databasesingleton.h \
    persistence/validation/validator.h \
    persistence/validation/impl/billitemvalidator.h \
    persistence/validation/impl/billvalidator.h \
    logging.h \
    persistence/validation/impl/customervalidator.h \
    tests/customerdaotest.h \
    tests/billdaotest.h \
    tests/productdaotest.h \
    persistence/validation/impl/productvalidator.h \
    persistence/persistenceexception.h \
    persistence/validation/validationexception.h \
    exception.h \
    service/serviceexception.h \
    ui/widgets/customerswidget.h \
    ui/models/customermodel.h \
    ui/dialogs/customerdialog.h

FORMS    += ui/mainwindow.ui \
    ui/widgets/customerswidget.ui \
    ui/dialogs/customerdialog.ui
