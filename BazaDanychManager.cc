#include "BazaDanychManager.h"
#include "CSettings.h"

BazaDanychManager::BazaDanychManager() {
	lastConnectionError = false;
	mKlienci = new QSqlTableModel();
	mZamowienia = new QSqlTableModel();
}

bool BazaDanychManager::polacz() {
	CSettings s;
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName(s.getHost());
	db.setDatabaseName(s.getDatabaseName());
	db.setUserName(s.getUser());
	db.setPassword(s.getPassword());
	updateTabele();
	if (!db.open()) {
		lastConnectionError = true;
		qDebug() << "Błąd: nie można się połączyć z bazą!";
		return false;
	} else {
		lastConnectionError = false;
		//QSqlQuery vStrictMode("SET sql_mode = 'STRICT_ALL_TABLES'", db);
		updateTabele();
		qDebug() << "Nawiązano połączenie z bazą danych.";
		return true;
	}
}

void BazaDanychManager::setZamowienia() {
	mZamowienia->setTable("zamowienia");
	mZamowienia->select();

	QStringList listaZamowienia;
	listaZamowienia << "NR ZAM KARTA" << "KLIENT" << "WZÓR" << "OCIEPLENIE " <<
			"SPÓD" << "KOLOR";
	QStringList listaZamowieniaEnd;
	listaZamowieniaEnd << "SUMA" << "ZDJECIE" << "SK1" <<	"SK2" <<	"SK3" <<
			   "UWAGI 1" << "UWAGI 2" << "DATA WPROWADZENIA" << "DATA REALIZACJI";
	setHeaders(listaZamowienia, mZamowienia);
}

QSqlTableModel *BazaDanychManager::getModelZamowienia() {
	return mZamowienia;
}

QSqlTableModel *BazaDanychManager::getModelKlienci() {
	return mKlienci;
}

void BazaDanychManager::updateTabele()
{
	setZamowienia();
	setKlienci();
}

void BazaDanychManager::setHeaders(QStringList lista, QSqlTableModel *model) {
	for (int i = 1; i < model->columnCount(); ++i) {
		model->setHeaderData(i, Qt::Horizontal, lista[i - 1]);
	}
}

void BazaDanychManager::setKlienci() {
	mKlienci->setTable("klienci");
	mKlienci->select();
	QStringList listaKlienci;
	listaKlienci << "NAZWA FIRMY" << "SKRÓT NAZWY" << "MIASTO" << "KOD" << "ULICA"
		     << "NUMER" << "TELEFON" << "TEL KOM 1"
		     << "TEL KOM 2" << "FAX" << "E-MAIL" << "UWAGI" << "ZAMÓWIONE" << "ODEBRANE" <<
		     "NIEODEBRANE";
	setHeaders(listaKlienci, mKlienci);
}

void BazaDanychManager::zachowajKlienta(const Klient &klient) {
	QSqlQuery qry;
	qry.prepare( "INSERT INTO klienci (nazwa, nazwa_skrot, miasto, kod_pocztowy, ulica, numer, fax, tel_kom1, tel_kom2, mail, uwagi, tel) "
		     "VALUES (:nazwa, :nazwa_skrot, :miasto, :kod_pocztowy, :ulica, :numer, :fax, :tel_kom1, :tel_kom2, :mail, :uwagi, :tel)" );
	qry.bindValue( ":nazwa", klient.getNazwa());
	qry.bindValue( ":nazwa_skrot", klient.getSkrot());
	qry.bindValue( ":miasto", klient.getMiasto());
	qry.bindValue( ":kod_pocztowy", klient.getKodPocztowy());
	qry.bindValue( ":ulica", klient.getUlica());
	qry.bindValue( ":numer", klient.getNumerDomu());
	qry.bindValue( ":fax", klient.getFax());
	qry.bindValue( ":tel_kom1", klient.getTel1());
	qry.bindValue( ":tel_kom2", klient.getTel2());
	qry.bindValue( ":mail", klient.getMail());
	qry.bindValue( ":uwagi", klient.getUwagi());
	qry.bindValue( ":tel", klient.getNumerTelefonu());
	if ( !qry.exec() ) {
		qDebug() << "Bląd przy wpisaniu klienta" ;
	}
	else {
		mKlienci->select();
	}
}

void BazaDanychManager::zamowienie() {

}

void BazaDanychManager::rozlacz() {
	if (QSqlDatabase::contains("obuwie_db")) {
		QSqlDatabase vDatabase = QSqlDatabase::database("obuwie_db", false);
		if (vDatabase.isOpen()) {
			vDatabase.close();
			//EmitSignalIfStateChanged(true);
		}
	}
	QSqlDatabase::removeDatabase("obuwie_db");
}

BazaDanychManager::~BazaDanychManager() {
	rozlacz();
}

bool BazaDanychManager::ponowniePolacz() {
	rozlacz();
	if (polacz()) {
		return true;
	} else {
		return false;
	}
}

//void CDatabaseConnection::CheckConnectionAndReconnectIfNecessary() {
//	QSqlDatabase vDatabase = QSqlDatabase::database("zssw", false);
//	if (!vDatabase.isOpen()) {
//		bool vSuccess = vDatabase.open();

//		if (vSuccess) {
//			QSqlQuery vConnectionTestQuery(vDatabase);
//			vSuccess = vConnectionTestQuery.exec(
//				"SELECT MIN(id) FROM events_types");

//			if (vSuccess) {
//				MakeDatabaseSpecificInitialQueries(
//					vDatabase.driverName(),
//					vDatabase);
//				mDatabasePath = CheckDatabasePath(
//					vDatabase.driverName(),
//					vDatabase);
//			}
//		}
//		EmitSignalIfStateChanged(!vSuccess);
//	}
//}
