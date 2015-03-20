#-------------------------------------------------
#
# Project created by QtCreator 2015-03-20T16:59:12
#
#-------------------------------------------------

QT       += core gui
QT       += sql printsupport

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
    domain/printable.cpp \
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
    service/billitemservice.cpp \
    service/customerservice.cpp \
    service/templateservice.cpp \
    service/productservice.cpp \
    service/impl/billserviceimpl.cpp \
    service/impl/productserviceimpl.cpp \
    service/impl/customerserviceimpl.cpp \
    service/impl/billitemserviceimpl.cpp \
    service/impl/templateserviceimpl.cpp

HEADERS  += ui/mainwindow.h \
    domain/bill.h \
    domain/product.h \
    domain/billitem.h \
    domain/template.h \
    domain/customer.h \
    domain/printable.h \
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
    service/billitemservice.h \
    service/customerservice.h \
    service/templateservice.h \
    service/productservice.h \
    service/impl/billserviceimpl.h \
    service/impl/productserviceimpl.h \
    service/impl/customerserviceimpl.h \
    service/impl/billitemserviceimpl.h \
    service/impl/templateserviceimpl.h

FORMS    += ui/mainwindow.ui
