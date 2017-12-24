#-------------------------------------------------
#
# Project created by QtCreator 2017-12-01T01:12:29
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ObuwieManager
TEMPLATE = app
QTPLUGIN += qsqlmysql
# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
CONFIG += c++11
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH+=/usr/include/mysql
LIBS+=-L/usr/lib/mysql
SOURCES += \
		main.cc \
		MainWindow.cc \
	ustawieniaform.cc \
	nowyKlientDialog.cc \
	noweZamowienieDialog.cc \
	Klient.cc \
	BazaDanychManager.cc \
	CSettings.cc \
	WybKlientaDialog.cc \
	WybModelDialog.cc \
	WybHandlDialog.cc \
	NowyHandlowiecDialog.cc \
	Zamowienia.cc \
	DokumentDoDruku.cc \
    klienciDialog.cc \
    handlowceDialog.cc \
    skoryDialog.cc \
    wzoryDialog.cc \
    spodyDialog.cc \
    wkladkaDialog.cc \
    ocieplenieDialog.cc \
    matryceDialog.cc \
    modeleDialog.cc \
    koloryDialog.cc \
    nowyModelDialog.cc

HEADERS += \
		MainWindow.h \
	ustawieniaform.h \
	nowyKlientDialog.h \
	noweZamowienieDialog.h \
	Klient.h \
	Delegate.h \
	BazaDanychManager.h \
	CSettings.h \
	WybKlientaDialog.h \
	WybModelDialog.h \
	WybHandlDialog.h \
	NowyHandlowiecDialog.h \
	Zamowienia.h \
	DokumentDoDruku.h \
    klienciDialog.h \
    handlowceDialog.h \
    skoryDialog.h \
    wzoryDialog.h \
    spodyDialog.h \
    wkladkaDialog.h \
    ocieplenieDialog.h \
    matryceDialog.h \
    modeleDialog.h \
    koloryDialog.h \
    nowyModelDialog.h

FORMS += \
		MainWindow.ui \
	ustawieniaform.ui \
	nowyKlientDialog.ui \
	noweZamowienieDialog.ui \
	WybKlientaDialog.ui \
	WybModelDialog.ui \
	WybHandlDialog.ui \
	NowyHandlowiecDialog.ui \
    klienciDialog.ui \
    handlowceDialog.ui \
    skoryDialog.ui \
    wzoryDialog.ui \
    spodyDialog.ui \
    wkladkaDialog.ui \
    ocieplenieDialog.ui \
    matryceDialog.ui \
    modeleDialog.ui \
    koloryDialog.ui \
    nowyModelDialog.ui

RESOURCES += \
	zasoby.qrc
