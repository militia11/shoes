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
	NowyHandlowiecDialog.cc \
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
    NowaMatrycaDialog.cc \
    NowyModelDialog.cc \
    clickableLabel.cc \
    nowySpodDialog.cc \
    ManagerZdjec.cc \
    ZdjecieDialog.cc \
    nowyKolorDialog.cc \
    nowaSkoraDialog.cc \
    nowywzorDialog.cc \
    DelegateArrows.cc \
    DoRozkrojuDialog.cc \
    RozkrojeDialog.cc \
    RozniceDialog.cc \
    edycjazamowieniadialog.cpp \
    NaglowkiZamowienia.cc

HEADERS += \
		MainWindow.h \
	ustawieniaform.h \
	nowyKlientDialog.h \
	noweZamowienieDialog.h \
	Klient.h \
	Delegate.h \
	BazaDanychManager.h \
	CSettings.h \
	NowyHandlowiecDialog.h \
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
    NowaMatrycaDialog.h \
    NowyModelDialog.h \
    zamowienie.h \
    clickableLabel.h \
    nowySpodDialog.h \
    ManagerZdjec.h \
    ZdjecieDialog.h \
    nowyKolorDialog.h \
    nowaSkoraDialog.h \
    nowywzorDialog.h \
    DelegateArrows.h \
    DoRozkrojuDialog.h \
    RozkrojeDialog.h \
    RozniceDialog.h \
    edycjazamowieniadialog.h \
    NaglowkiZamowienia.h

FORMS += \
		MainWindow.ui \
	ustawieniaform.ui \
	nowyKlientDialog.ui \
	noweZamowienieDialog.ui \
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
    NowaMatrycaDialog.ui \
    NowyModelDialog.ui \
    nowySpodDialog.ui \
    ZdjecieDialog.ui \
    nowyKolorDialog.ui \
    nowaSkoraDialog.ui \
    nowywzorDialog.ui \
    DoRozkrojuDialog.ui \
    RozkrojeDialog.ui \
    RozniceDialog.ui \
    edycjazamowieniadialog.ui

RESOURCES += \
	zasoby.qrc
