QT       += core gui
QT       += sql printsupport
QT       += testlib

greaterThan(QT_MAJOR_VERSION, 4):

QMAKE_CXXFLAGS += -std=c++0x

HEADERS = billitemdaotest.h
SOURCES = billitemdaotest.cpp
