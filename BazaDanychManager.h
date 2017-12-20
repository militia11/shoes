#ifndef BAZADANYCHMANAGER_H
#define BAZADANYCHMANAGER_H

#include <QtCore/qglobal.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QString>
#include <QSqlTableModel>
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


		void aktualizujStatus(int id, QString status);

		QAbstractItemModel *wyszukajKlientowPoNazwie(QString nazwa);
		QAbstractItemModel *wyszukajKlientowPoSkrocie(QString nazwa);
		QAbstractItemModel *wyszukajKlientow(QString nazwa, QString skrot);

		QAbstractItemModel *selectZamowieniaWgStatusu(QString status);

		void zachowajKlienta(const Klient &klient);
		void zachowajHandlowca(QString im, QString nz, QString skr);
		bool zamowienie(QString klientNazwa, QString handlNazwa, QDate zam,
				QDate realizacji, QStandardItemModel *pozycje,
				QString papierowe = QString(""));

		void ustawIdAktualnegoKlienta(const QModelIndex index);
		void ustawIdAktualnegoHandl(const QModelIndex index);
		QString pobierzNazweAktualnegoKlienta();
		QString pobierzNazweAktualnegoHandl();

		QSqlTableModel *getModelZamowienia();

		QAbstractItemModel *getModelZamowieniaModele();
		QAbstractItemModel *getModelZamowieniaModeleForMainWindow();

		QImage getImageZamowienia(int id);
		QSqlTableModel *getModelKlienci();
		QSqlTableModel *getModelHandlowce();
		QSqlTableModel *getModelKlienciWybieranie();
		QSqlTableModel *getModelmModeleWybieranie();

		void setIdZamowieniaModeleForMainWindow(const QModelIndex index,
							bool selectMode);
		int getIdZamowieniaZTabeli(QModelIndex index, bool selectMode);
		void ustawAktualnyModelId(const QModelIndex index);

		void setHeadersGlowneZamowienia();
		void setHeadersGlowneSelectZamowienia();
		void setHeadersForZamowienia(QAbstractItemModel *model);
		int GetIdOfLastInsertedRow();

		QList<QStandardItem *> zwrocWierszModel();

		QString getOstatniSelectZam() const;

	private:
		int getIdOstatniegoZam();
		int getNumerOstatniegoZamKomputerowego();
		QVariant GetFirstValueForQuery(QSqlQuery *aQuery);
		QSqlRecord getSqlRecordZModelu(const QAbstractItemModel *aItemModel);
		QAbstractItemModel *getModelForQuery(QSqlQuery *aQuery);

		bool wystapilBlad(const QSqlQuery &aQuery);
		void obsluzSqlError(const QSqlQuery &aQuery);
		void removeSqlModels();

		void aktualizujTabele();
		void aktualizujHeaderyKlient(QAbstractItemModel *model);
		void updateZamowieniaModele();
		void setZamowieniaModeleHeaders();

		void setZamowienia();
		void setKlienci();
		void setHandlowce();
		void setKlienciWybieranie();
		void setModeleWybieranie();
		void setHeaders(QStringList lista, QAbstractItemModel *model);

		QSqlDatabase db;
		QAbstractItemModel *mSelectZamowienia;
		QSqlTableModel *mZamowienia;
		QAbstractItemModel *mZamowieniaModele;
		QSqlTableModel *mHandlowce;
		QSqlTableModel *mKlienciWybieranie;
		QSqlTableModel *mKlienci;
		QSqlTableModel *mModeleWybieranie;
		int idKlienta;
		int64_t idHandlowca;
		int idModelu;
		int idZamowieniaModeleForMainWindow;
		QString nazwaKlienta;
		QString nazwaHandlowca;
		bool firstRun;
		QString ostatniSelectZam;
};

#endif // BAZADANYCHMANAGER_H
