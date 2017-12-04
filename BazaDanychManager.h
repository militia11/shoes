#ifndef BAZADANYCHMANAGER_H
#define BAZADANYCHMANAGER_H

#include <QtCore/qglobal.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QSqlTableModel>

#include "Klient.h"

class BazaDanychManager {
	public:
		BazaDanychManager();
		~BazaDanychManager();

		bool ponowniePolacz();
		bool polacz();
		void rozlacz();
		bool lastConnectionError;

		void zachowajKlienta(const Klient &klient);
		void zamowienie();
		QSqlTableModel *getModelZamowienia();
		QSqlTableModel *getModelKlienci();
		QSqlTableModel *getModelKlienciWyb();


	private:
		void removeSqlModels();
		void updateTabele();
		void setZamowienia();
		void setKlienci();
		void setKlienciWyb();
		void setHeaders(QStringList lista, QSqlTableModel *model);

		QSqlDatabase db;
		QSqlTableModel *mZamowienia;
		QSqlTableModel *mKlienci;
		QSqlTableModel *mKlienciWyb;
		bool firstRun;
};

#endif // BAZADANYCHMANAGER_H
