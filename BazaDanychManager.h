#ifndef BAZADANYCHMANAGER_H
#define BAZADANYCHMANAGER_H

#include <QtCore/qglobal.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlQueryModel>
#include <QCoreApplication>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <Qt>
#include <QAbstractItemModel>
#include <QDate>
#include <QStandardItem>
#include "Klient.h"

struct zamowienieStruct {
	QString nrZ;
	QString klNaz;
	int klNr;
	QString status;
	QString ociep;
	QString mat;
	//QString ;
};

class BazaDanychManager {

	public:
		enum FieldType {
			NUMBER_FIELD,
			STRING_FIELD,
			NO_FIELD
		};

		BazaDanychManager();
		~BazaDanychManager();

		bool ponowniePolacz();
		bool polacz();
		void rozlacz();
		bool lastConnectionError;
		void dodajWzor(int w);
		bool aktualizujStatus(int id, QString status);
		void setZamowieniaFilter();

		QAbstractItemModel *wyszukajKlientowPoNazwie(QString nazwa);
		QAbstractItemModel *wyszukajKlientowPoSkrocie(QString nazwa);
		QAbstractItemModel *wyszukajKlientow(QString nazwa, QString skrot);

		void zachowajKlienta(const Klient &klient);
		void zachowajHandlowca(QString im, QString nz, QString skr);
		bool zamowienie(QString klientNazwa, QString handlNazwa, QDate zam,
				QDate realizacji, QStandardItemModel *pozycje,
				QString papierowe = QString(""));

		void ustawIdAktualnegoKlienta(const QModelIndex index);
		void ustawIdAktualnegoHandl(const QModelIndex index);
		QString pobierzNazweAktualnegoKlienta();
		QString pobierzNazweAktualnegoHandl();

		QSqlRelationalTableModel *getModelZamowienia();

		QImage getImageZamowienia(int id);
		QSqlTableModel *getModelKlienci();
		QSqlTableModel *getModelKlienciWybieranie();
		QSqlTableModel *getModelHandlowce();
		QSqlTableModel *getModelHandlowceWybieranie();
		QSqlTableModel *getModelmModeleWybieranie();

		void setIdZamowieniaModeleForMainWindow(const QModelIndex index);
		int getIdZamowieniaZTabeli(QModelIndex index);
		void ustawAktualnyModelId(const QModelIndex index);

		void setHeadersGlowneZamowienia();
		int GetIdOfLastInsertedRow();

		QList<QStandardItem *> zwrocWierszModel();

		QString getOstatniSelectZam() const;

		void setZamowienia();
		void setKlienci();
		void setWzory();
		void setHandlowce();
		void setHandlowceWybieranie();
		void setKlienciWybieranie();
		void setModeleWybieranie();
		void setWkladki();
		void setHeaders(QStringList lista, QAbstractItemModel *model);

		void setUser(const QString &value);
		zamowienieStruct filterZamowien;

		QSqlTableModel *getWzory() const;
		void setWzory(QSqlTableModel *wzory);

	private:
		int getIdOstatniegoZam();
		int getNumerOstatniegoZamKomputerowego();
		QVariant GetFirstValueForQuery(QSqlQuery *aQuery);
		QSqlRecord getSqlRecordZModelu(const QAbstractItemModel *aItemModel);
		QAbstractItemModel *getModelForQuery(QSqlQuery *aQuery);

		bool wystapilBlad(const QSqlQuery &aQuery);
		void obsluzSqlError(const QSqlQuery &aQuery);
		void removeSqlModels();

		void aktualizujHeaderyKlient(QAbstractItemModel *model);
		void setZamowieniaModeleHeaders();

		QSqlDatabase db;
		QAbstractItemModel *mSelectZamowienia;
		QSqlRelationalTableModel *mZamowienia;
		QSqlTableModel *mHandlowce;
		QSqlTableModel *mHandlowceWybieranie;
		QSqlTableModel *mKlienciWybieranie;
		QSqlTableModel *mKlienci;
		QSqlTableModel *mModeleWybieranie;
		QSqlTableModel *mWkladki;
		QSqlTableModel *mWzory;
		int idKlienta;
		int64_t idHandlowca;
		int idModelu;
		int idZamowieniaModeleForMainWindow;
		QString nazwaKlienta;
		QString nazwaHandlowca;
		bool firstRun;
		QString ostatniSelectZam;
		QString user;
};

#endif // BAZADANYCHMANAGER_H
