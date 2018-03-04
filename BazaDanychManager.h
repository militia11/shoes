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
#include "zamowienie.h"

struct KlientFilter {
    QString nazwa;
    QString skrot;
    QString miasto;
    QString nr;
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

        void zmienKlientaZam(QString nrzam);
        void zmienHandlZam(QString nrzam);
        int zwrocSumeZamowien();
        bool aktualizujStatus(int id, QString status);
        bool zamowienie(QDate zam, QDate realizacji,
                        QStringList uwagi1,
                        QString uwagi2, QString nr_zam, QStandardItemModel *pozycje);
        void insertPozycjazamowienie(QString nr_zam, int idKlienta, int idHandlowca);
        bool rozkroj(QStandardItemModel *pozycje, QStandardItemModel *bazowepozycje = 0);
        void ustawAktualnyModelId(const QModelIndex index);
        QList<QStandardItem *> zwrocWierszModel();
        QString getOstatniSelectZam() const;
        int getIdZamowieniaZTabeli(QModelIndex index);
        bool getCzyRoznicaZamowieniaZTabeli(QModelIndex index);
        QImage getImage(int id, int ktore, QString tab);
        bool updateImage(int id, int ktore, QImage im, QString tab);
        QImage getImageZamowienia(int id);

        QString getKlientSkrot(QString nr_zam);
        QString getHanlSkrot(QString nr_zam);

        void setHeadersGlowneZamowienia();
        void setUser(const QString &value);

        void setZamowienia();
        void setKlienci();
        void setWzory();
        void setMatryce();
        void setHandlowce();
        void setModele();
        void setWkladki();
        void setSpody();
        void setOciep();
        void setKolory();
        void setSkory();

        void setHeaders(QStringList lista, QAbstractItemModel *model);

        zamowienieStruct filterZamowien;
        KlientFilter filterKlientow;
        void setZamowieniaFilter();
        void setKlienciFilter();

        void oznaczDrukowano(int id);
        void removeZamowienie(int id);

        void ustawIdAktualnegoKlienta(const QModelIndex index);
        void ustawIdAktualnegoHandl(const QModelIndex index);
        QString pobierzNazweAktualnegoKlienta();
        QString pobierzNazweAktualnegoHandl();

        QString pobierzNazweMatrycy(const QModelIndex index);
        int pobierzAktualnyKolor(const QModelIndex index);
        QString pobierzNazwaSpodu(const QModelIndex index);
        QString pobierzNazweAktualejWkladki(const QModelIndex index);
        QString pobierzAktualnyOciep(const QModelIndex index);
        QString pobierzAktualnaSkore(const QModelIndex index);
        int getNrWzoru(const QModelIndex index);
        int getWysZdj(int id);
        QVector<QString> poberzRodzaje(int id);
        QString poberzOpis1(int id);
        QString poberzOpis2(int id);

        void zachowajKolor(int kolor, QString s1, QString s1d, QString s2, QString s2d,
                           QString s3, QString s3d, QString sdomi);
        void zachowajSkore(QString naz, QString dost, double cena);
        void zachowajMatryce(QString naz, QString infonaz);
        void zachowajWkla(QString naz, QString o);
        void zachowajKlienta(const Klient &klient);
        void zachowajHandlowca(QString im, QString nz, QString skr, QString uwagi);
        void zachowajModel(QVector<QImage> images, QString rodzaj_montazu,  QString typ,
                           QString  rodzaj_buta,  QString   rodzaj_buta_2,
                           QString  rodzaj_buta_3,  QString rodzaj_buta_4,
                           QString  rodzaj_buta_5, QString  rodzaj_buta_6, QString opis, QString opis2,
                           int zdj);
        void aktualizujModel(QVector<QImage> images, QString rodzaj_montazu,  QString   typ,
                             QString    rodzaj_buta,  QString   rodzaj_buta_2,
                             QString    rodzaj_buta_3,  QString rodzaj_buta_4,
                             QString    rodzaj_buta_5, QString  rodzaj_buta_6, QString opis, QString opis2,
                             int zdj);

        void zachowajSpod(QString nr, QString getNazwa, QString getProducent,
                          QVector<QImage> images, QString getRodzaj, QString getRozm,
                          QString getUwagi);
        void dodajWzor(int w, QString opis);
        void dodajOciep(QString w, QString o);

        QSqlTableModel *getSkory() const;
        QSqlTableModel *getOciep() const;
        QSqlTableModel *getKolory() const;
        QSqlTableModel *getWzory() const;
        QSqlTableModel *getMatryce() const;
        QSqlTableModel *getModele() const;
        QSqlTableModel *getSpody() const;
        QSqlTableModel *getModelZamowienia();
        QSqlTableModel *getModelKlienci();
        QSqlTableModel *getModelKlienciWybieranie();
        QSqlTableModel *getModelHandlowce();
        QSqlTableModel *getModelHandlowceWybieranie();
        QSqlTableModel *getWkladki() const;

        QSqlQueryModel *getSqlModelForQuery(QSqlQuery *aQuery);
        QAbstractItemModel *getModelForQuery(QSqlQuery *aQuery);
        QStandardItemModel *getDoRozkroju(const std::vector<int> &value);
        void clearFilterZam();
        int getNumerOstatniegoZamKomputerowego();
        int getNumerOstatniegoRozkroju();
        void stworzSzkieletRozkroju(QString nr);
        void stworzSzkieletZam(QString nr);
        void usunSzkieletRozkroju();
        void usunSzkieletZam();
        QVector<QString> zwrocListeModel(int id);
        QVector<int> zwrocListeIdSkladowychModelu(int id);
        void setZamowieniaSzczegolyFilter(QString f);

        QSqlTableModel *getRozkroje() const;
        void setRozkroje();

        QSqlTableModel *getRoznice() const;
        void setRoznice();

        void setTableWidokZamowienia(QString tabela);
        bool copyZamowienieArch(QStandardItemModel *pozycje);
        void setIdKoloru(int value);

        void setIdSpodu(int value);

        void setIdWzoru(int value);

        void setIdWkladki(int value);

        void setIdOciep(int value);

        void setIdSkory(int value);

        void setIdMatrycy(int value);

        void setIdModelu(int value);

private:
        QVariant GetFirstValueForQuery(QSqlQuery *aQuery);
        QSqlRecord getSqlRecordZModelu(const QAbstractItemModel *aItemModel);

        void removeSqlModels();

        void aktualizujHeaderyKlient(QAbstractItemModel *model);
        void setZamowieniaModeleHeaders();

        QSqlDatabase db;
        QAbstractItemModel *mSelectZamowienia;
        QSqlTableModel *mZamowienia;
        QSqlTableModel *mHandlowce;
        QSqlTableModel *mKlienci;
        QSqlTableModel *mModele;
        QSqlTableModel *mWkladki;
        QSqlTableModel *mWzory;
        QSqlTableModel *mMatryce;
        QSqlTableModel *mSpody;
        QSqlTableModel *mKolory;
        QSqlTableModel *mSkory;
        QSqlTableModel *mOciep;
        QSqlTableModel *mRozkroje;
        QSqlTableModel *mRoznice;

        int idKlienta;
        int idHandlowca;
        int idModelu;
        int idKoloru;
        int idSpodu;
        int idWzoru;
        int idWkladki;
        int idOciep;
        int idSkory;
        int idMatrycy;
        int idRozkroju;
        int idZam;
        int idRoznicy;

        QVector<int> idModeluL;
        QString nazwaKlienta;
        QString nazwaHandlowca;
        QString currentIdZamRozkroje;
        QString nrRozkroju;

        bool firstRun;
        QString ostatniSelectZam;
        QString user;
        QSqlQuery getIdsZamowienia(QString nrzam);
};

#endif // BAZADANYCHMANAGER_H
