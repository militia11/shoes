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

	private:
		void updateTabele();
		void setZamowienia();
		void setKlienci();
		void setHeaders(QStringList lista, QSqlTableModel *model);

		QSqlTableModel *mZamowienia;
		QSqlTableModel *mKlienci;
};

#endif // BAZADANYCHMANAGER_H
