#include "BazaDanychManager.h"
#include "CSettings.h"
#include <QBuffer>
#include <QImageReader>
#include <QImageWriter>

void BazaDanychManager::clearFilterZam() {
    filterZamowien.nrZ = QString("");
    filterZamowien.klNaz = QString("");
    filterZamowien.klNr = QString("");
    filterZamowien.wzor = QString("");
    filterZamowien.kolor = QString("");
    filterZamowien.mat = QString("");
    filterZamowien.ociep = QString("");
    filterZamowien.status = QString("");
    filterZamowien.sk1 = QString("");
    filterZamowien.sk2 = QString("");
    filterZamowien.sk3 = QString("");
    filterZamowien.ha = QString("");
    filterZamowien.snaz = QString("");
    filterZamowien.sprod = QString("");
    filterZamowien.wpr = QString("");
    filterZamowien.rea = QString("");
    filterZamowien.uzyt = QString("");
    filterZamowien.spn = QString("");
    filterKlientow.miasto = QString("");
    filterKlientow.nazwa = QString("");
    filterKlientow.skrot = QString("");
    filterKlientow.nr = QString("");
    filterKlientow.woj = QString("");
    filterKlientow.kraj = QString("");
    filterKlientow.han = QString("");
}

BazaDanychManager::BazaDanychManager() :
    mHandlowce(nullptr),
    mKlienci(nullptr),
    mModele(nullptr),
    mWkladki(nullptr),
    mWzory(nullptr),
    mMatryce(nullptr),
    mSpody(nullptr),
    mKolory(nullptr),
    mSkory(nullptr),
    mOciep(nullptr),
    mZamowienia(nullptr),
    mRozkroje(nullptr),
    mw(nullptr),
    rw(nullptr),
    mKliR(nullptr) {
    lastConnectionError = false;
    firstRun = true;
    db = QSqlDatabase::addDatabase("QMYSQL");
    mSelectZamowienia = NULL;
    idKlienta = -1;
    idHandlowca = -1;
    idMatrycy = -1;
    idModelu = -1;
    idKoloru = -1;
    idSpodu = -1;
    idWzoru = -1;
    idOciep = -1;
    idWkladki = -1;
    idRozkroju = -1;
    idZam = -1;
    idMw = -1;
    sk1= 1;
    sk2= 1;
    sk3= 1;
    clearFilterZam();

    //todo usunac
    user = QString("value");
}

void BazaDanychManager::removeSqlModels() {
    if (mZamowienia) {
        delete mZamowienia;
        mZamowienia = 0;
    }
    if (mWkladki) {
        delete  mWkladki;
        mWkladki = 0;
    }
    if (mKlienci) {
        delete  mKlienci;
        mKlienci = 0;
    }
    if (mHandlowce) {
        delete  mHandlowce;
        mHandlowce = 0;
    }
    if (mModele) {
        delete  mModele;
        mModele = 0;
    }
    if (mMatryce) {
        delete  mMatryce;
        mMatryce = 0;
    }
    if (mSpody) {
        delete  mSpody;
        mSpody = 0;
    }
    if (mSkory) {
        delete  mSkory;
        mSkory = 0;
    }
    if (mKolory) {
        delete  mKolory;
        mKolory = 0;
    }
    if (mWzory) {
        delete  mWzory;
        mWzory = 0;
    }
    if (mOciep) {
        delete  mOciep;
        mOciep = 0;
    }
    if (mRozkroje) {
        delete  mRozkroje;
        mRozkroje = 0;
    }
    if (mw) {
        delete mw;
        mw = 0;
    }
    if (rw) {
        delete rw;
        rw = 0;
    }
    if (mKliR) {
        delete  mKliR;
        mKliR = 0;
    }
}

bool BazaDanychManager::polacz() {
    CSettings s;
    db.setHostName(s.getHost());
    db.setDatabaseName(s.getDatabaseName());
    db.setUserName(s.getUser());
    db.setPassword(s.getPassword());
    if (!db.open()) {
        lastConnectionError = true;
        if (!firstRun) {
            removeSqlModels();
        }
        firstRun = false;
        return false;
    } else {
        lastConnectionError = false;
        //QSqlQuery vStrictMode("SET sql_mode = 'STRICT_ALL_TABLES'", db);
        setZamowienia();
        firstRun = false;
        return true;
    }
}

void BazaDanychManager::setTableWidokZamowienia(QString tabela) {
    mZamowienia->setTable(tabela);
    setHeadersGlowneZamowienia();
    mZamowienia->select();
}

bool BazaDanychManager::copyZamowienieArch(QStandardItemModel *pozycje) {
    int count = pozycje->rowCount();
    db.transaction();
    bool vSuccess = true;

    for (int i = 0; i < count; i++) {
        QSqlQuery qry;
        qry.prepare("INSERT INTO zamowieniaArch SELECT z.* FROM zamowienia z WHERE z.id=:id");
        qry.bindValue(":id", pozycje->data(pozycje->index(i, 0)).toInt());
        if (!qry.exec()) {
            qDebug() << "nie udalo copy";
            qDebug() << qry.lastError().text();
            vSuccess = false;
        }
    }
    if (vSuccess == true) {
        db.commit();
        getModelZamowienia()->select();
        return true;
    } else {
        db.rollback();
        return false;
    }
    return true;
}

void BazaDanychManager::setZamowienia() {
    mZamowienia = new QSqlTableModel();
    setTableWidokZamowienia("vzam");
}

QSqlTableModel *BazaDanychManager::getModelZamowienia() {
    return mZamowienia;
}


QImage BazaDanychManager::getImageZamowienia(int id) {
    QSqlQuery qry2;
    qry2.prepare("select zamowienia.modele_id, modele.wys_zdj from zamowienia join modele on zamowienia.modele_id=modele.id where zamowienia.id=:id");
    qry2.bindValue(":id", id);
    qry2.exec();
    int  idMod = -1;
    int  kt = -1;
    if (qry2.next()) {
        idMod = qry2.value(0).toInt();
        kt = qry2.value(1).toInt();
    }
    QSqlQuery qry;
    QString str = QString("select zdj%1 from modele where id=:idMod").arg(kt);
    qry.prepare(str);
    qry.bindValue(":idMod", idMod);
    if (!qry.exec()) {
        qDebug() << "Błąd przy pobraniu zdjecia";
    }
    if (!qry.next()) {
        return QImage();
    }
    QByteArray array = qry.value(0).toByteArray();
    QBuffer buffer(&array);
    buffer.open(QIODevice::ReadOnly);
    QImageReader reader(&buffer, "JPG");
    QImage image = reader.read();

    return image;
}

QString BazaDanychManager::getKlientSkrot(QString nr_zam) {
    QSqlQuery vQuery(db);
    QString res;
    vQuery.prepare("select klnaz from vzam where nr_zamowienia=:nrZ");
    vQuery.bindValue(":nrZ", nr_zam);
    if (vQuery.exec()) {
        vQuery.next();
        res =  vQuery.value(0).toString();
    }
    return res;
}

QString BazaDanychManager::getHanlSkrot(QString nr_zam) {
    QSqlQuery vQuery(db);
    QString res;
    vQuery.prepare("select skrot from vzam where nr_zamowienia=:nrZ");
    vQuery.bindValue(":nrZ", nr_zam);
    if (vQuery.exec()) {
        vQuery.next();
        res =  vQuery.value(0).toString();
    }
    return res;
}

QSqlTableModel *BazaDanychManager::getModelKlienci() {
    return mKlienci;
}

QSqlTableModel *BazaDanychManager::getModelHandlowce() {
    return mHandlowce;
}

void BazaDanychManager::oznaczDrukowano(int id) {
    QSqlQuery qry2;
    qry2.prepare("update `obuwie_db`.`rozkrojeZam` set DRUKOWANO = DRUKOWANO + 1 where id=:id");
    qry2.bindValue(":id", id);
    if (!qry2.exec()) {
        qDebug() << "Bląd przy aktualizacji drukowano" ;
    }
}

void BazaDanychManager::removeZamowienie(int id) {
    QSqlQuery qry;
    qry.prepare("delete from `obuwie_db`.`zamowienia` where id=:id");
    qry.bindValue(":id", id);
    if (!qry.exec()) {
        qDebug() << "Bląd przy usunieciu rozk" ;
    }
}

void BazaDanychManager::ustawAktualnyModelId(const QModelIndex index) {
    idModelu = mModele->data(mModele->index(index.row(),
                                            0)).toInt();
    idModeluL.append(mModele->data(mModele->index(index.row(),
                                   0)).toInt());
}

int BazaDanychManager::zwrocAktualnyModelIdMw(const QModelIndex index) {
    return mw->data(mw->index(index.row(),
                              1)).toInt();

}

int BazaDanychManager::getIdZamowieniaZTabeli(QModelIndex index) {
    int id = -1;

    id = mZamowienia->data(mZamowienia->index(
                               index.row(),
                               1)).toInt();
    return id;
}

QString BazaDanychManager::getNrRozkrojuDoWskazania(QModelIndex index) {
    return  mZamowienia->data(mZamowienia->index(
                                  index.row(),
                                  48)).toString();
}

void BazaDanychManager::setHeadersGlowneZamowienia() {
    QStringList listaZamowienia;
    listaZamowienia  << "" << "NR ZAM" << "KL SKR" << "KL NR"  << "WZÓR"  << "SPÓD" << "KOL" <<
                     "OCIE" <<
                     "MAT" << "WKŁ" << "36" << "37" << "38" << "39" << "40"    << "41" << "42" << "43"
                     << "44" << "45" << "46" << "47"    << "48" << "49" << "50"
                     << "SUMA"  << "SK1" << "SK2" << "SK3" << "SP NAZWA" <<
                     "SP PROD" << "UŻY" << "HAN" << "DATA WPR" << "DATA WPR"  << "DATA REA" << "REKORD" << "CAŁE ZAM" << "STATUS"
                     << ""
                     << ""  << "" << ""
                     << ""  << "" << ""
                     << ""  << "" << "ROZKRÓJ"
                     << "RÓŻNICA"  << "" << ""
                     << "" << ""  << "" << "";
    setHeaders(listaZamowienia, mZamowienia);
}

QVariant BazaDanychManager::GetFirstValueForQuery(QSqlQuery *aQuery) {
    QVariant vResult;
    aQuery->exec();
    if (aQuery->next()) {
        vResult = aQuery->value(0);
    }

    return vResult;
}

int BazaDanychManager::getNumerOstatniegoZamKomputerowego() {
    QSqlQuery vIdQuery(db);
    vIdQuery.exec("SELECT zam_nr FROM zamnr WHERE zam_nr LIKE 'B%' ORDER BY id DESC LIMIT 1;");
    QVariant vIdAsVariant = GetFirstValueForQuery(&vIdQuery);
    QString numer = vIdAsVariant.isNull() ? QString("B0") :
                    vIdAsVariant.toString();
    int liczba = numer.remove(0, 1).toInt();
    return liczba;
}

int BazaDanychManager::getNumerOstatniegoRozkroju() {
    QSqlQuery vIdQuery(db);
    vIdQuery.exec("SELECT nr_rozkroju FROM rozkroje ORDER BY id DESC LIMIT 1;");

    QVariant vIdAsVariant = GetFirstValueForQuery(&vIdQuery);
    QString numer = vIdAsVariant.isNull() ? QString("R0") :
                    vIdAsVariant.toString();
    int liczba = numer.remove(0, 1).toInt();
    return liczba;
}

int BazaDanychManager::getNumerOstatniegoModeluMw() {
    QSqlQuery vIdQuery(db);
    vIdQuery.exec("SELECT id FROM modele ORDER BY id DESC LIMIT 1;");
    QVariant vIdAsVariant = GetFirstValueForQuery(&vIdQuery);
    QString numer = vIdAsVariant.isNull() ? QString("0") :
                    vIdAsVariant.toString();
    int liczba = numer.toInt();
    return liczba;
}

void BazaDanychManager::stworzSzkieletRozkroju(QString nr) {
    QSqlQuery qry;
    qry.prepare("INSERT INTO `obuwie_db`.`rozkroje` (`nr_rozkroju`, `WPROWADZONO`,"
                " `UZYTKOWNIK`) VALUES (:nr_rozkroju, :WPROWADZONO, :UZYTKOWNIK);");
    qry.bindValue(":nr_rozkroju", nr);
    qry.bindValue(":WPROWADZONO", QDate::currentDate().toString("dd/MM/yyyy"));
    qry.bindValue(":UZYTKOWNIK", user);
    if (!qry.exec()) {
        qDebug() << "Bląd przy stworzSzkieletRozkroju" ;
    }

    QSqlQuery qry2;
    qry2.prepare("SELECT MAX(id) FROM rozkroje;");
    qry2.exec();
    qry2.next();
    idRozkroju = qry2.value(0).toInt();
    nrRozkroju = nr;
}

void BazaDanychManager::stworzSzkieletZam(QString nr) {
    QSqlQuery qry;
    qry.prepare("INSERT INTO `obuwie_db`.`zamnr` (`zam_nr`) VALUES (:nr_zam)");
    qry.bindValue(":nr_zam", nr);
    if (!qry.exec()) {
        qDebug() << "Bląd przy stworzSzkielet zam" ;
    }

    QSqlQuery qry2;
    qry2.prepare("SELECT MAX(id) FROM zamnr;");
    qry2.exec();
    qry2.next();
    idZam = qry2.value(0).toInt();
}

void BazaDanychManager::usunSzkieletRozkroju() {
    QSqlQuery qry;
    qry.prepare("delete from `obuwie_db`.`rozkroje` where id=:id");
    qry.bindValue(":id", idRozkroju);
    if (!qry.exec()) {
        qDebug() << "Bląd przy usunieciu rozk" ;
    }
}

void BazaDanychManager::usunSzkieletZam() {
    QSqlQuery qry;
    qry.prepare("delete from `obuwie_db`.`zamnr` where id=:id");
    qry.bindValue(":id", idZam);
    if (!qry.exec()) {
        qDebug() << "Bląd przy usunieciu zamowienia" ;
        qry.lastError().text();
    }
}

QVector<QString> BazaDanychManager::zwrocListeModel(int id) {
    QVector<QString> rzad;
    QString vQueryText = QString("select * from vmodele where id=%1;").arg(id);
    QSqlQuery vQuery(db);
    vQuery.prepare(vQueryText);
    vQuery.exec();
    if (vQuery.next()) {
        rzad.append(vQuery.value(1).toString());
        rzad.append(vQuery.value(2).toString());
        rzad.append(vQuery.value(3).toString());
        rzad.append(vQuery.value(4).toString());
        rzad.append(vQuery.value(5).toString());
        rzad.append(vQuery.value(6).toString());
    }
    return rzad;
}

QVector<int> BazaDanychManager::zwrocListeIdSkladowychModelu(int id) {
    QVector<int> rzad;
    QString vQueryText = QString("select * from modele where id=%1;").arg(id);
    QSqlQuery vQuery(db);
    vQuery.prepare(vQueryText);
    vQuery.exec();
    if (vQuery.next()) {
        rzad.append(vQuery.value(1).toInt());
        rzad.append(vQuery.value(2).toInt());
        rzad.append(vQuery.value(3).toInt());
        rzad.append(vQuery.value(4).toInt());
        rzad.append(vQuery.value(5).toInt());
        rzad.append(vQuery.value(6).toInt());
        rzad.append(vQuery.value(7).toInt());
    }
    return rzad;
}

QList<QStandardItem *> BazaDanychManager::zwrocWierszModel() {
    QList<QStandardItem *> rzad;
    QString vQueryText = QString("select * from vmodele where id=%1;").arg(idModelu);
    QSqlQuery vQuery(db);
    vQuery.prepare(vQueryText);
    vQuery.exec();
    int nr_wzoru = 0;
    QString matryca;
    QString ocieplenie;
    int spod = 0;
    int kolor = 0;
    QString wkladka;
    if (vQuery.next()) {
        nr_wzoru = vQuery.value(1).toInt();
        spod  = vQuery.value(2).toInt();
        kolor  = vQuery.value(3).toInt();
        ocieplenie = vQuery.value(4).toString();
        matryca = vQuery.value(5).toString();
        wkladka = vQuery.value(6).toString();
    }

    rzad.append(new QStandardItem(QString::number(nr_wzoru)));
    rzad.append(new QStandardItem(QString::number(spod)));
    rzad.append(new QStandardItem(QString::number(kolor)));
    rzad.append(new QStandardItem(matryca));
    rzad.append(new QStandardItem(ocieplenie));
    rzad.append(new QStandardItem(wkladka));
    for (int i = 0; i < 16; i++) {
        rzad.append(new QStandardItem(QString("0")));
    }
    return rzad;
}

QSqlRecord BazaDanychManager::getSqlRecordZModelu(const QAbstractItemModel *aItemModel) {
    QSqlRecord vResult;
    for (int row = 0; row < aItemModel->rowCount(); ++row) {
        for (int column = 0; column < aItemModel->columnCount(); ++column) {
            QSqlField *vField = new QSqlField(
                (aItemModel->headerData(column, Qt::Horizontal)).toString(),
                (aItemModel->data(aItemModel->index(row, column))).type());
            vField->setValue(aItemModel->data(aItemModel->index(row, column)));
            vResult.append(*vField);
        }
    }

    return vResult;
}

QAbstractItemModel *BazaDanychManager::getModelForQuery(QSqlQuery *aQuery) {
    QCoreApplication::processEvents();
    QAbstractItemModel *vResult = NULL;
    QSqlQueryModel *vModel = new QSqlQueryModel();
    aQuery->exec();
    vModel->setQuery(*aQuery);

    while (vModel->canFetchMore()) {
        vModel->fetchMore();
        QCoreApplication::processEvents();
    }
    QCoreApplication::processEvents();
    vResult = vModel;
    return vResult;
}

QStandardItemModel *BazaDanychManager::getDoRozkroju(const std::vector<int> &value) {
    QString queString("select *from vzam where zamowienia_id in ( ");
    QString idki;
    for (int v : value) {
        idki.append(QString("%1 ,").arg(v));
    }
    idki.remove(idki.count() - 1, 1);
    queString += idki;
    qDebug() << idki;
    currentIdZamRozkroje = idki;
    queString += " )";
    QSqlQuery query(queString);
    QAbstractItemModel *abmodel = getModelForQuery(&query);
    QStandardItemModel *stModel = new QStandardItemModel();

    for (int i = 0; i < abmodel->rowCount(); i++) {
        QList<QStandardItem *> rzad;
        for (int j = 0; j < abmodel->columnCount(); j++) {
            rzad.append(new QStandardItem(abmodel->data(abmodel->index(i, j)).toString()));
        }
        stModel->insertRow(i, rzad);
        rzad.clear();
    }

    delete abmodel;
    return  stModel;
}

QSqlQueryModel *BazaDanychManager::getSqlModelForQuery(QSqlQuery *aQuery) {
    QCoreApplication::processEvents();
    QSqlQueryModel *vModel = new QSqlQueryModel();
    aQuery->exec();
    vModel->setQuery(*aQuery);

    while (vModel->canFetchMore()) {
        vModel->fetchMore();
        QCoreApplication::processEvents();
    }
    QCoreApplication::processEvents();

    return vModel;
}

void BazaDanychManager::aktualizujHeaderyKlient(QAbstractItemModel *model) {
    QStringList listaKlienci;
    listaKlienci << "NAZWA FIRMY" << "SKRÓT NAZWY" << "MIASTO" << "KOD" << "ULICA"
                 << "NUMER" << "TELEFON" << "TEL KOM 1" << "TEL KOM 2" << "FAX" << "E-MAIL" << "UWAGI" << "" << "" << "";
    setHeaders(listaKlienci, model);
}

QSqlTableModel *BazaDanychManager::getRw() const {
    return rw;
}

QSqlTableModel *BazaDanychManager::getKliR() const {
    return mKliR;
}

void BazaDanychManager::setIdMatrycy(int value) {
    idMatrycy = value;
}

void BazaDanychManager::setIdModelu(int value) {
    idModelu = value;
}

void BazaDanychManager::setIdOciep(int value) {
    idOciep = value;
}

void BazaDanychManager::setIdWkladki(int value) {
    idWkladki = value;
}

void BazaDanychManager::setIdWzoru(int value) {
    idWzoru = value;
}

void BazaDanychManager::setIdSpodu(int value) {
    idSpodu = value;
}

void BazaDanychManager::setIdKoloru(int value) {
    idKoloru = value;
}

QSqlTableModel *BazaDanychManager::getmw() const {
    return mw;
}

void BazaDanychManager::setmw() {
    if (mw == nullptr) {
        mw = new QSqlTableModel();
        mw->setTable("widokmw");
        QStringList listaModele;
        listaModele << "" << "" << "WZÓR"  << "SPÓD" << "KOLOR" << "OCIEPLENIE" << "MATRYCA" <<
                    "WKŁADKA"  <<  "36" << "37" << "38" << "39" << "40"    << "41" << "42" << "43"
                    << "44" << "45" << "46" << "47"    << "48" << "49" << "50" << "SUMA";
        setHeaders(listaModele, mw);
    }

    mw->select();
}


void BazaDanychManager::setRw() {
    if (rw == nullptr) {
        rw = new QSqlTableModel();
        rw->setTable("widokrw");
        QStringList listaModele;
        listaModele << "" << "" << "WZÓR"  << "SPÓD" << "KOLOR" << "OCIEPLENIE" << "MATRYCA" <<
                    "WKŁADKA"  <<  "36" << "37" << "38" << "39" << "40"    << "41" << "42" << "43"
                    << "44" << "45" << "46" << "47"    << "48" << "49" << "50" << "SUMA" <<  "POBRANO DNIA" << "UŻYTKOWNIK";
        setHeaders(listaModele, rw);
    }

    rw->select();
}


void BazaDanychManager::updateHandl( int idHan, int idKL) {
    QSqlQuery qry2;
    QString qryStr = QString("update `obuwie_db`.`klienci` set handlowce_id=%1 where klienci.id=%2").arg(idHan).arg(idKL);
    qry2.prepare(qryStr);
    if (!qry2.exec()) {
        qDebug() << "Bląd przy aktualizacji kli - handl" ;
    }
}

QSqlTableModel *BazaDanychManager::getRozkroje() const {
    return mRozkroje;
}

void BazaDanychManager::setRozkroje() {
    if (mRozkroje == nullptr) {
        mRozkroje = new QSqlTableModel();
        mRozkroje->setTable("rozkroje");

        mRozkroje->setHeaderData(1, Qt::Horizontal, "NR ROZKROJU");
    }
    mRozkroje->select();
}

void BazaDanychManager::setZamowieniaSzczegolyFilter(QString f) {
    QString ff = QString("nr_zamowienia LIKE '%1%'").arg(f);
    mZamowienia->setFilter(ff);
}

bool BazaDanychManager::sprawdzNr(QString nr) {
    QSqlQuery vQuery(db);
    vQuery.prepare("select nr_zamowienia from zamowienia where nr_zamowienia=:nrZ");
    vQuery.bindValue(":nrZ", nr);
    vQuery.exec();
    if(vQuery.next()) return true;
    else return false;
}

QSqlTableModel *BazaDanychManager::getWkladki() const {
    return mWkladki;
}

void BazaDanychManager::setOciep() {
    if (mOciep == nullptr) {
        mOciep = new QSqlTableModel();
        mOciep->setTable("ocieplenia");
        mOciep->setHeaderData(1, Qt::Horizontal, "RODZAJ");
        mOciep->setHeaderData(2, Qt::Horizontal, "OPIS");
    }

    mOciep->select();
}

QSqlTableModel *BazaDanychManager::getOciep() const {
    return mOciep;
}

QSqlTableModel *BazaDanychManager::getSkory() const {
    return mSkory;
}

void BazaDanychManager::setSkory() {
    if (mSkory == nullptr) {
        mSkory = new QSqlTableModel();
        mSkory->setTable("skora");
        QStringList listaKlienci;
        listaKlienci << "" << "NAZWA" <<  "DOSTAWCA" << "AKTUALNA CENA" << "";
        setHeaders(listaKlienci, mSkory);
    }
    mSkory->select();
}

void BazaDanychManager::zmienHandlZam(QString nrZam, int idh) {
    QSqlQuery qry = getIdsZamowienia(nrZam);

    while (qry.next()) {
        QSqlQuery qry2;
        QString qryS2 =
            QString("update zamowienia set handlowce_id=%1 where zamowienia.id=%2").arg(
                idh).
            arg(qry.value(0).toString());
        qry2.prepare(qryS2) ;
        if (!qry2.exec()) {
            qDebug() << "Bląd update ha" ;
        }
    }

    mZamowienia->select();
}

QString BazaDanychManager::zwrocNazweHandlKlienta() {
    QSqlQuery qry;
    QString qryStr =
        QString("select handlowce_id from klienci where id=%1").arg(idKlienta);
    qry.prepare(qryStr);
    qry.exec();
    if (qry.next()) {
        idHandlowca    = qry.value(0).toInt();
    } else {
        qDebug() << "Blad przy pobraniu nazwy 1" ;
        return QString();
    }
    QSqlQuery qry2;
    QString qryStr2 =
        QString("select skrot from handlowce where id=%1").arg(idHandlowca);
    qry2.prepare(qryStr2);
    qry2.exec();
    if (qry2.next()) {
        return qry2.value(0).toString();
    } else {
        qDebug() << "Blad przy pobraniu nazwy 2" ;
    }
}

int BazaDanychManager::zwrocIdHandlKlienta() {
    QSqlQuery qry;
    QString qryStr =
        QString("select handlowce_id from klienci where id=%1").arg(idKlienta);
    qry.prepare(qryStr);
    qry.exec();
    if (qry.next()) {
        return qry.value(0).toInt();
    } else {
        qDebug() << "Blad przy pobraniu nazwy 1" ;
        return 0;
    }
}

QSqlTableModel *BazaDanychManager::getKolory() const {
    return mKolory;
}

void BazaDanychManager::setKolory() {
    if (mKolory == nullptr) {
        mKolory = new QSqlTableModel();
        mKolory->setTable("vkolory");
        QStringList listaKlienci;
        listaKlienci << "ID " << "KOLOR" <<  "SKÓRA 1" << "DOSTAWCA SK1" << "SKÓRA 2" <<
                     "DOSTAWCA SK2" << "SKÓRA 3" << "DOSTAWCA SK3" << "KOLOR SK DOMIN" << "" << "" << "" << "";
        setHeaders(listaKlienci, mKolory);
    }
    mKolory->select();
}

QSqlTableModel *BazaDanychManager::getSpody() const {
    return mSpody;
}

QString BazaDanychManager::pobierzNazweMatrycy(const QModelIndex index) {
    idMatrycy = mMatryce->data(mMatryce->index(index.row(),
                               0)).toInt();
    return mMatryce->data(mMatryce->index(index.row(),
                                          1)).toString();
}

int BazaDanychManager::pobierzAktualnyKolor(const QModelIndex index) {
    idKoloru = mKolory->data(mKolory->index(index.row(),
                                            0)).toInt();
    return  mKolory->data(mKolory->index(index.row(),
                                         1)).toInt();
}

QString BazaDanychManager::pobierzNazwaSpodu(const QModelIndex index) {
    idSpodu = mSpody->data(mSpody->index(index.row(),
                                         0)).toInt();
    return mSpody->data(mSpody->index(index.row(),
                                      1)).toString();
}

QString BazaDanychManager::pobierzNazweAktualejWkladki(const QModelIndex index) {
    idWkladki = mWkladki->data(mWkladki->index(index.row(),
                               0)).toInt();
    return mWkladki->data(mWkladki->index(index.row(),
                                          1)).toString();
}

QString BazaDanychManager::pobierzAktualnyOciep(const QModelIndex index) {
    idOciep = mOciep->data(mOciep->index(index.row(),
                                         0)).toInt();
    return  mOciep->data(mOciep->index(index.row(),
                                       1)).toString();
}

int BazaDanychManager::getNrWzoru(const QModelIndex index) {
    idWzoru = mWzory->data(mWzory->index(index.row(),
                                         0)).toInt();
    return  mWzory->data(mWzory->index(index.row(),
                                       1)).toInt();
}

int BazaDanychManager::getWysZdj(int id) {
    QSqlQuery qry;
    QString qryStr =
        QString("select wys_zdj from modele where id=%1").arg(id);
    qry.prepare(qryStr);
    qry.exec();
    if (qry.next()) {
        return  qry.value(0).toInt();
    } else {
        qDebug() << "Blad przy pobraniu wys_zdjecia" ;
        return -1;
    }
}

QVector<QString> BazaDanychManager::poberzRodzaje(int id) {
    QSqlQuery qry;
    QVector<QString> res;
    qry.prepare("select `typ`, `rodzaj_montazu`, `rodzaj_buta`, `rodzaj_buta_2`, `rodzaj_buta_3`, `rodzaj_buta_4`, `rodzaj_buta_5`, `rodzaj_buta_6` from modele where id=:id");
    qry.bindValue(":id", id);
    qry.exec();
    while (qry.next()) {
        res.append(qry.value(0).toString());
        res.append(qry.value(1).toString());
        res.append(qry.value(2).toString());
        res.append(qry.value(3).toString());
        res.append(qry.value(4).toString());
        res.append(qry.value(5).toString());
        res.append(qry.value(6).toString());
        res.append(qry.value(7).toString());
    }
    return  res;
}

QString BazaDanychManager::poberzOpis1(int id) {
    QSqlQuery qry;
    qry.prepare("select `opis1` from modele where id=:id");
    qry.bindValue(":id", id);
    qry.exec();
    if (qry.next()) {
        return qry.value(0).toString();
    } else {
        return QString();
    }
}

QString BazaDanychManager::poberzOpis2(int id) {
    QSqlQuery qry;
    qry.prepare("select `opis2` from modele where id=:id");
    qry.bindValue(":id", id);
    qry.exec();
    if (qry.next()) {
        return qry.value(0).toString();
    } else {
        return QString();
    }
}

QString BazaDanychManager::pobierzAktualnaSkore(const QModelIndex index) {
    return  mSkory->data(mSkory->index(index.row(),
                                       1)).toString();
}

int BazaDanychManager::pobierzAktualnaSkoreId(const QModelIndex index) {
    return mSkory->data(mSkory->index(index.row(),
                                      0)).toInt();
}

void BazaDanychManager::zachowajKolor(int kolor, QString s1d,
                                      QString s2d, QString s3d, QString sdomi) {
    QSqlQuery qry;
    qry.prepare("INSERT INTO kolor (`kolor`, `skora_id1`, `skora_id2`, `skora_id3`,`kolor_sk_dominujacy`)"
                " VALUES (:kolor, :skora_id1, :skora_id2, :skora_id3, :kolor_sk_dominujacy)");
    qry.bindValue(":kolor", kolor);
    qry.bindValue(":skora_id1", sk1);
    qry.bindValue(":skora_id2", sk2);
    qry.bindValue(":skora_id3", sk3);
    qry.bindValue(":kolor_sk_dominujacy", sdomi);
    if (!qry.exec()) {
        qDebug() << "Bląd przy zapisie koloru" ;
        qDebug() << qry.lastError().text();
    } else {
        mKolory->select();
    }
}

void BazaDanychManager::zachowajSkore(QString naz, QString dost, double cena) {
    QSqlQuery qry;
    qry.prepare("INSERT INTO skora (`nazwa`, `dostawca`, `aktualna_cena`) VALUES (:nazwa, :dostawca, :aktualna_cena)");
    qry.bindValue(":nazwa", naz);
    qry.bindValue(":dostawca", dost);
    qry.bindValue(":aktualna_cena", cena);

    if (!qry.exec()) {
        qDebug() << "Bląd przy zapisie skory" ;
    } else {
        mSkory->select();
    }
}

QSqlTableModel *BazaDanychManager::getModele() const {
    return mModele;
}

QSqlTableModel *BazaDanychManager::getMatryce() const {
    return mMatryce;
}

void BazaDanychManager::zachowajMatryce(QString naz, QString infonaz) {
    QSqlQuery qry;
    qry.prepare("INSERT INTO matryce (nazwa, info_nazwa) VALUES (:nazwa, :info_nazwa)");
    qry.bindValue(":nazwa", naz);
    qry.bindValue(":info_nazwa", infonaz);
    if (!qry.exec()) {
        qDebug() << "Bląd przy zapisie matrycy" ;
    } else {
        mMatryce->select();
    }
}

void BazaDanychManager::zachowajWkla(QString naz, QString o) {
    QSqlQuery qry;
    qry.prepare("INSERT INTO wkladka (rodzaj, opis) VALUES (:nazwa, :opis)");
    qry.bindValue(":nazwa", naz);
    qry.bindValue(":opis", o);
    if (!qry.exec()) {
        qDebug() << "Bląd przy zapisie wkladka" ;
    } else {
        mWkladki->select();
    }
}

QSqlTableModel *BazaDanychManager::getWzory() const {
    return mWzory;
}

void BazaDanychManager::setUser(const QString &value) {
    user = value;
}

void BazaDanychManager::setHeaders(QStringList lista,
                                   QAbstractItemModel *model) {
    for (int i = 0; i < model->columnCount(); ++i) {
        model->setHeaderData(i, Qt::Horizontal, lista[i]);
    }
}

QString BazaDanychManager::getOstatniSelectZam() const {
    return ostatniSelectZam;
}

void BazaDanychManager::setKlienci() {
    if (mKlienci == nullptr) {
        mKlienci = new QSqlTableModel();
        mKlienci->setTable("kli");
        QStringList listaKlienci;
        listaKlienci << "NUMER KLI" << "NAZWA FIRMY" << "SKRÓT NAZWY" <<"HANDLOWIEC"<< "MIASTO"<< "WOJEWÓD"<< "KRAJ"  << "KOD"  << "ULICA" << "NR MIESZKANIA" << "TELEFON" << "TEL KOM 1"
                     << "TEL KOM 2" << "FAX" << "E-MAIL" << "UWAGI" << "" << "" << "";
        setHeaders(listaKlienci, mKlienci);
    }
    mKlienci->select();
}


void BazaDanychManager::setKliR() {
    if (mKliR == nullptr) {
        mKliR = new QSqlTableModel();
        mKliR->setTable("klienci");
    }
    mKliR->select();
}


void BazaDanychManager::setSpody() {
    if (mSpody == nullptr) {
        mSpody = new QSqlTableModel();
        mSpody->setTable("spody");
        mSpody->setHeaderData(1, Qt::Horizontal, QString("NUMER"));
        mSpody->setHeaderData(2, Qt::Horizontal, QString("NAZWA"));
        mSpody->setHeaderData(3, Qt::Horizontal, QString("PRODUCENT"));
        mSpody->setHeaderData(4, Qt::Horizontal, QString("ROZMIARY"));
        mSpody->setHeaderData(5, Qt::Horizontal, QString("RODZAJ"));
        mSpody->setHeaderData(10, Qt::Horizontal, QString("UWAGI"));
    }
    mSpody->select();
}

void BazaDanychManager::setWzory() {
    if (mWzory == nullptr) {
        mWzory = new QSqlTableModel();
        mWzory->setTable("wzory");
        mWzory->setHeaderData(1, Qt::Horizontal, QString("NUMER WZORU"));
        mWzory->setHeaderData(2, Qt::Horizontal, QString("OPIS"));
    }
    mWzory->select();
}

void BazaDanychManager::setMatryce() {
    if (mMatryce == nullptr) {
        mMatryce = new QSqlTableModel();
        mMatryce->setTable("matryce");
        mMatryce->setHeaderData(1, Qt::Horizontal, QString("NAZWA"));
        mMatryce->setHeaderData(2, Qt::Horizontal, QString("INFO NAZWA"));
    }
    mMatryce->select();
}

void BazaDanychManager::setHandlowce() {
    if (mHandlowce == nullptr) {
        mHandlowce = new QSqlTableModel();
        mHandlowce->setTable("handlowce");
        QStringList listaHandlowce;
        listaHandlowce << "" << "IMIĘ" << "NAZWISKO" << "SKRÓT" <<  "UWAGI" << "" << "";
        setHeaders(listaHandlowce, mHandlowce);
    }
    mHandlowce->select();
}

void BazaDanychManager::setModele() {
    if (mModele == nullptr) {
        mModele = new QSqlTableModel();
        mModele->setTable("vmodele");
        QStringList listaModele;
        listaModele << "" << "WZÓR"  << "SPÓD" << "KOLOR" << "OCIEPLENIE" << "MATRYCA" <<
                    "WKŁADKA"  << "TYP" << "MONTAŻ"  << "RODZ BUTA 1" << "RODZ BUTA 2" << "RODZ BUTA 3" << "RODZ BUTA 4" <<
                    "RODZ BUTA 5" << "RODZ BUTA 6" << "SZWALNIA" << "MONTAŻ" << "" << "";
        setHeaders(listaModele, mModele);
    }

    mModele->select();
}

void BazaDanychManager::setWkladki() {
    if (mWkladki == nullptr) {
        mWkladki = new QSqlTableModel();
        mWkladki->setTable("wkladka");
    }
    mWkladki->setHeaderData(1, Qt::Horizontal, QString("RODZAJ"));
    mWkladki->setHeaderData(2, Qt::Horizontal, "OPIS");

    mWkladki->select();
}

void BazaDanychManager::zachowajKlienta(const Klient &klient) {
    QSqlQuery qry;
    qry.prepare("INSERT INTO klienci (nazwa, nazwa_skrot, miasto, kod_pocztowy, ulica, numer, fax, tel_kom1, tel_kom2, mail, uwagi, tel, wojewodztwo, KRAJ, handlowce_id) "
                "VALUES (:nazwa, :nazwa_skrot, :miasto, :kod_pocztowy, :ulica, :numer, :fax, :tel_kom1, :tel_kom2, :mail, :uwagi, :tel, :woj, :kraj, :h)");
    qry.bindValue(":nazwa", klient.getNazwa());
    qry.bindValue(":nazwa_skrot", klient.getSkrot());
    qry.bindValue(":miasto", klient.getMiasto());
    qry.bindValue(":kod_pocztowy", klient.getKodPocztowy());
    qry.bindValue(":ulica", klient.getUlica());
    qry.bindValue(":numer", klient.getNumerDomu());
    qry.bindValue(":fax", klient.getFax());
    qry.bindValue(":tel_kom1", klient.getTel1());
    qry.bindValue(":tel_kom2", klient.getTel2());
    qry.bindValue(":mail", klient.getMail());
    qry.bindValue(":uwagi", klient.getUwagi());
    qry.bindValue(":tel", klient.getNumerTelefonu());
    qry.bindValue(":woj", klient.getWoj());
    qry.bindValue(":kraj", klient.getKraj());
    qry.bindValue(":h", idHandlowca);
    if (!qry.exec()) {
        qDebug() << "Bląd przy zapisie klienta" ;
    } else {
        setKlienci();
        mKlienci->select();
    }
}

void BazaDanychManager::zachowajHandlowca(QString im, QString nz, QString skr,
        QString uwagi) {
    QSqlQuery qry;
    qry.prepare("INSERT INTO handlowce (imie, nazwisko, skrot, uwagi) "
                "VALUES (:imie, :nazwisko, :skrot, :uwagi)");
    qry.bindValue(":imie", im);
    qry.bindValue(":nazwisko", nz);
    qry.bindValue(":skrot", skr);
    qry.bindValue(":uwagi", uwagi);
    if (!qry.exec()) {
        qDebug() << "Bląd przy zapisie Handlowca" ;
    } else {
        setHandlowce();
        mHandlowce->select();
    }
}

bool BazaDanychManager::zachowajRW() {
    QSqlQuery qry;
    /*R36, R37 ,R38, R39,  R40, "
                        "  R41, R42  ,R43   ,R44,  R45, R46 ,  R47,  R48 ,  R49 , R50,suma, uwagi,wprowadzono, realizacja, status, uzytkownik, modele_id, handlowce_id,  uwagi2) VALUES ("
                        ":nr_zamowienia,:id_klienta, :R36, :R37 ,:R38,:R39, :R40 ,  :R41 ,  :R42 , :R43  ,:R44, :R45 ,  :R46 , :R47  , :R48, :R49,:R50 ,:suma,:uwagi, :wprowadzono ,"*/
    qry.prepare("INSERT INTO rw (`modele_id`,`R36`, wprowadzono, uzytkownik) VALUES (:modele_id, :R36, :wprowadzono, :uzytkownik)");
    qry.bindValue(":modele_id", 4);
    qry.bindValue(":R36", 12);
    qry.bindValue(":wprowadzono", QDate::currentDate());
    qry.bindValue(":uzytkownik", user);
    if (!qry.exec()) {
        qDebug() << "Bląd przy zapisie modelu" ;
        qDebug() << qry.lastError();
        return false;
    } else {
        return true;
    }

//    QVector<int>rozmiary;
//   zam.rozmiary.append(vModel->data(vModel->index(i, 10)).toInt());
//   zam.rozmiary.append(vModel->data(vModel->index(i, 11)).toInt());
//   zam.rozmiary.append(vModel->data(vModel->index(i, 12)).toInt());
//   zam.rozmiary.append(vModel->data(vModel->index(i, 13)).toInt());
//   zam.rozmiary.append(vModel->data(vModel->index(i, 14)).toInt());
//   zam.rozmiary.append(vModel->data(vModel->index(i, 15)).toInt());
//   zam.rozmiary.append(vModel->data(vModel->index(i, 16)).toInt());
//   zam.rozmiary.append(vModel->data(vModel->index(i, 17)).toInt());
//   zam.rozmiary.append(vModel->data(vModel->index(i, 18)).toInt());
//   zam.rozmiary.append(vModel->data(vModel->index(i, 19)).toInt());
//   zam.rozmiary.append(vModel->data(vModel->index(i, 20)).toInt());
//   zam.rozmiary.append(vModel->data(vModel->index(i, 21)).toInt());
//   zam.rozmiary.append(vModel->data(vModel->index(i, 22)).toInt());
//   zam.rozmiary.append(vModel->data(vModel->index(i, 23)).toInt());
//   zam.rozmiary.append(vModel->data(vModel->index(i, 24)).toInt());
//    qry.bindValue(":R36", rzad.at(6)->data(Qt::DisplayRole).toInt());
//    qry.bindValue(":R37", rzad.at(7)->data(Qt::DisplayRole).toInt());
//    qry.bindValue(":R38", rzad.at(8)->data(Qt::DisplayRole).toInt());
//    qry.bindValue(":R39", rzad.at(9)->data(Qt::DisplayRole).toInt());
//    qry.bindValue(":R40", rzad.at(10)->data(Qt::DisplayRole).toInt());
//    qry.bindValue(":R41", rzad.at(11)->data(Qt::DisplayRole).toInt());
//    qry.bindValue(":R42", rzad.at(12)->data(Qt::DisplayRole).toInt());
//    qry.bindValue(":R43", rzad.at(13)->data(Qt::DisplayRole).toInt());
//    qry.bindValue(":R44", rzad.at(14)->data(Qt::DisplayRole).toInt());
//    qry.bindValue(":R45", rzad.at(15)->data(Qt::DisplayRole).toInt());
//    qry.bindValue(":R46", rzad.at(16)->data(Qt::DisplayRole).toInt());
//    qry.bindValue(":R47", rzad.at(17)->data(Qt::DisplayRole).toInt());
//    qry.bindValue(":R48", rzad.at(18)->data(Qt::DisplayRole).toInt());
//    qry.bindValue(":R49", rzad.at(19)->data(Qt::DisplayRole).toInt());
//    qry.bindValue(":R50", rzad.at(20)->data(Qt::DisplayRole).toInt());
//    int suma = 0;
}

bool BazaDanychManager::zachowajModel(QVector<QImage> images,
                                      QString rodzaj_montazu, QString typ, QString rodzaj_buta, QString rodzaj_buta_2,
                                      QString rodzaj_buta_3, QString rodzaj_buta_4, QString rodzaj_buta_5,
                                      QString rodzaj_buta_6, QString opis, QString opis2, int zdj) {
    db.transaction();
    bool vSuccess = true;
    QSqlQuery qry;
    qry.prepare("INSERT INTO modele (`wzory_id`, `matryce_id`, `ocieplenie`, `kolor`, `wkladka`, `spody_id`, "
                "`opis1`, `opis2`,`wys_zdj`, `typ`, `rodzaj_montazu`,`rodzaj_buta`, `rodzaj_buta_2`, `rodzaj_buta_3`, `rodzaj_buta_4`, `rodzaj_buta_5`, `rodzaj_buta_6`, `zdj1`, `zdj2`, `zdj3`, `zdj4`) VALUES (:wzory_id, :matryce_id, :ocieplenie, :kolor, :wkladka, :spody_id, "
                ":opis1, :opis2, :wys_zdj,:typ, :rodzaj_montazu, :rodzaj_buta, :rodzaj_buta_2, :rodzaj_buta_3, :rodzaj_buta_4, :rodzaj_buta_5, :rodzaj_buta_6, :zdj1, :zdj2, :zdj3, :zdj4)");
    qry.bindValue(":wzory_id", idWzoru);
    qry.bindValue(":matryce_id", idMatrycy);
    qry.bindValue(":ocieplenie", idOciep);
    qry.bindValue(":kolor", idKoloru);
    qry.bindValue(":wkladka", idWkladki);
    qry.bindValue(":spody_id", idSpodu);
    qry.bindValue(":opis1", opis);
    qry.bindValue(":opis2", opis2);
    qry.bindValue(":wys_zdj", zdj);
    qry.bindValue(":typ", typ);
    qry.bindValue(":rodzaj_montazu", rodzaj_montazu);
    qry.bindValue(":rodzaj_buta", rodzaj_buta);
    qry.bindValue(":rodzaj_buta_2", rodzaj_buta_2);
    qry.bindValue(":rodzaj_buta_3", rodzaj_buta_3);
    qry.bindValue(":rodzaj_buta_4", rodzaj_buta_4);
    qry.bindValue(":rodzaj_buta_5", rodzaj_buta_5);
    qry.bindValue(":rodzaj_buta_6", rodzaj_buta_6);
    QBuffer buffer;
    QImageWriter writer(&buffer, "JPG");
    writer.write(images[0]);

    qry.bindValue(":zdj1", buffer.data());

    QBuffer buffer2;
    QImageWriter writer2(&buffer2, "JPG");
    writer2.write(images[1]);
    qry.bindValue(":zdj2", buffer2.data());

    QBuffer buffer3;
    QImageWriter writer3(&buffer3, "JPG");
    writer3.write(images[2]);
    qry.bindValue(":zdj3", buffer3.data());

    QBuffer buffer4;
    QImageWriter writer4(&buffer4, "JPG");
    writer4.write(images[3]);
    qry.bindValue(":zdj4", buffer4.data());

    if (!qry.exec()) {
        vSuccess = false;
        qDebug() << "Bląd przy zapisie modelu" ;
        qDebug() << qry.lastError();
    }

    if (vSuccess) {
        QSqlQuery qry2;
        qry2.prepare("INSERT INTO mw (`modele_id`) "
                     " VALUES (:modele_id)");
        int idM = getNumerOstatniegoModeluMw();
        qry2.bindValue(":modele_id", idM);

        if (!qry2.exec()) {
            vSuccess = false;
            qDebug() << "Bląd przy zapisie mw" ;
            qDebug() << qry2.lastError();
        }
    }

    if (vSuccess == true) {
        db.commit();
        mModele->select();
        return true;
    } else {
        db.rollback();
        return false;
    }
}

void BazaDanychManager::aktualizujModel(QVector<QImage> images, QString rodzaj_montazu, QString typ,
                                        QString rodzaj_buta, QString rodzaj_buta_2, QString rodzaj_buta_3, QString rodzaj_buta_4, QString rodzaj_buta_5,
                                        QString rodzaj_buta_6, QString opis, QString opis2, int zdj) {
    updateImage(idModelu, 1, images[0], QString("modele"));
    updateImage(idModelu, 2, images[1], QString("modele"));
    updateImage(idModelu, 3, images[2], QString("modele"));
    updateImage(idModelu, 4, images[3], QString("modele"));
    QSqlQuery qry;
    if(typ.isEmpty())
        typ = "";
    if(rodzaj_montazu.isEmpty())
        rodzaj_montazu = "";
    if(rodzaj_buta.isEmpty())
        rodzaj_buta = "";
    if(rodzaj_buta_2.isEmpty())
        rodzaj_buta_2 = "";
    if(rodzaj_buta_3.isEmpty())
        rodzaj_buta_3 = "";
    if(rodzaj_buta_4.isEmpty())
        rodzaj_buta_4 = "";
    if(rodzaj_buta_5.isEmpty())
        rodzaj_buta_5 = "";
    if(rodzaj_buta_6.isEmpty())
        rodzaj_buta_6 = "";

    qry.prepare("update modele set `wzory_id`=:wzory_id, `matryce_id`=:matryce_id, `ocieplenie`=:ocieplenie, `kolor`=:kolor, `wkladka`=:wkladka, `spody_id`=:spody_id, "
                "`opis1`=:opis1, `opis2`=:opis2,`wys_zdj`=:wys_zdj, `typ`=:typ, `rodzaj_montazu`=:rodzaj_montazu,`rodzaj_buta`=:rodzaj_buta,"
                " `rodzaj_buta_2`=:rodzaj_buta_2, `rodzaj_buta_3`=:rodzaj_buta_3, `rodzaj_buta_4`=:rodzaj_buta_4, `rodzaj_buta_5`=:rodzaj_buta_5, `rodzaj_buta_6`=:rodzaj_buta_6  where id=:id_mod");
    qry.bindValue(":wzory_id", idWzoru);
    qry.bindValue(":matryce_id", idMatrycy);
    qry.bindValue(":ocieplenie", idOciep);
    qry.bindValue(":kolor", idKoloru);
    qry.bindValue(":wkladka", idWkladki);
    qry.bindValue(":spody_id", idSpodu);
    qry.bindValue(":opis1", opis);
    qry.bindValue(":opis2", opis2);
    qry.bindValue(":wys_zdj", zdj);
    qry.bindValue(":typ", typ);
    qry.bindValue(":rodzaj_montazu", rodzaj_montazu);
    qry.bindValue(":rodzaj_buta", rodzaj_buta);
    qry.bindValue(":rodzaj_buta_2", rodzaj_buta_2);
    qry.bindValue(":rodzaj_buta_3", rodzaj_buta_3);
    qry.bindValue(":rodzaj_buta_4", rodzaj_buta_4);
    qry.bindValue(":rodzaj_buta_5", rodzaj_buta_5);
    qry.bindValue(":rodzaj_buta_6", rodzaj_buta_6);
    qry.bindValue(":id_mod", idModelu);

    if (!qry.exec()) {
        qDebug() << "Bląd przy UPDATE modelu" ;
    } else {
        mModele->select();
    }

}

bool BazaDanychManager::zamowienie(QDate zam,
                                   QDate realizacji,
                                   QStringList uwagi1,
                                   QString uwagi2,
                                   QString nr_zam, QStandardItemModel *pozycje) {
    db.transaction();
    bool vSuccess = true;
    int count = pozycje->rowCount();
    for (int i = 0; i < count; i++) {
        QList<QStandardItem *> rzad = pozycje->takeRow(0);
        QSqlQuery qry;
        qry.prepare("INSERT INTO `obuwie_db`.`zamowienia` (nr_zamowienia, id_klienta, R36, R37 ,R38, R39,  R40, "
                    "  R41, R42  ,R43   ,R44,  R45, R46 ,  R47,  R48 ,  R49 , R50,suma, uwagi,wprowadzono, realizacja, status, uzytkownik, modele_id, handlowce_id,  uwagi2) VALUES ("
                    ":nr_zamowienia,:id_klienta, :R36, :R37 ,:R38,:R39, :R40 ,  :R41 ,  :R42 , :R43  ,:R44, :R45 ,  :R46 , :R47  , :R48, :R49,:R50 ,:suma,:uwagi, :wprowadzono ,"
                    " :realizacja, :status, :uzytkownik, :modele_id, :handlowce_id, :uwagi2)");
        QString nr_zamiPoz = QString("%1/%2").arg(nr_zam).arg((i+1));
        qry.bindValue(":nr_zamowienia", nr_zamiPoz);
        qry.bindValue(":id_klienta", idKlienta);
        qry.bindValue(":R36", rzad.at(6)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R37", rzad.at(7)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R38", rzad.at(8)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R39", rzad.at(9)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R40", rzad.at(10)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R41", rzad.at(11)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R42", rzad.at(12)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R43", rzad.at(13)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R44", rzad.at(14)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R45", rzad.at(15)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R46", rzad.at(16)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R47", rzad.at(17)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R48", rzad.at(18)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R49", rzad.at(19)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R50", rzad.at(20)->data(Qt::DisplayRole).toInt());
        int suma = 0;
        for (int i = 6; i < 21; i++) {
            suma += rzad.at(i)->data(Qt::DisplayRole).toInt();
        }
        qry.bindValue(":suma", suma);
        qry.bindValue(":uwagi", uwagi1[i]);
        qry.bindValue(":uwagi2", uwagi2);
        qry.bindValue(":wprowadzono", zam);
        qry.bindValue(":realizacja", realizacji);
        qry.bindValue(":status", QString("WPROWADZONE"));
        qry.bindValue(":uzytkownik", user);
        qry.bindValue(":modele_id", idModeluL[i]);
        qry.bindValue(":handlowce_id", idHandlowca);
        if (!qry.exec()) {
            qDebug() << "Bląd przy zapisie pozycji" ;
            qDebug() << qry.lastError().text();
            vSuccess = false;
            pozycje->appendRow(rzad);
        }
    }
    idModeluL.clear();
    if (vSuccess == true) {
        db.commit();
        mZamowienia->select();
        return true;
    } else {
        db.rollback();
        return false;
    }
}

void BazaDanychManager::insertPozycjazamowienie(QString nr_zam, int idKlienta, int idHandlowca) {
    QSqlQuery qry;
    qry.prepare("INSERT INTO `obuwie_db`.`zamowienia` (nr_zamowienia, id_klienta, wprowadzono, realizacja, status, uzytkownik, modele_id, handlowce_id) VALUES ("
                ":nr_zamowienia,:id_klienta, :wprowadzono ,:realizacja, :status, :uzytkownik, :modele_id, :handlowce_id)");
    qry.bindValue(":nr_zamowienia", nr_zam);
    qry.bindValue(":id_klienta", idKlienta);
    qry.bindValue(":wprowadzono", QDate::currentDate());
    qry.bindValue(":realizacja", QDate::currentDate().addDays(14));
    qry.bindValue(":status", QString("WPROWADZONE"));
    qry.bindValue(":uzytkownik", user);
    qry.bindValue(":modele_id", idModelu);
    qry.bindValue(":handlowce_id", idHandlowca);
    if (!qry.exec()) {
        qDebug() << "Bląd przy insert zam";
    }
}

bool BazaDanychManager::rozkroj(QStandardItemModel *pozycje) {
    db.transaction();
    bool vSuccess = true;
    int count = pozycje->rowCount();
    for (int i = 0; i < count; i++) {
        QList<QStandardItem *> rzad = pozycje->takeRow(0);
        QSqlQuery qry;
        qry.prepare("INSERT INTO `obuwie_db`.`rozkrojeZam` (`nr_zamowieniaR`, `R36`, `R37`, `R38`, `R39`, `R40`, `R41`,"
                    " `R42`, `R43`, `R44`, `R45`, `R46`, `R47`, `R48`, `R49`, `R50`, `suma`,`wprowadzono`,`realizacja`, `uwagi`, `uwagi2`,"
                    " `uzytkownik`, `modele_id`, `klienci_id`, `handlowce_id`, `rozkroje_id`, `pozycja`) VALUES (:nr_zamowieniaR, :R36, :R37 ,:R38,:R39, :R40 ,  :R41 ,  :R42 , :R43  ,:R44, :R45 ,  :R46 , :R47  , :R48, :R49,:R50 ,:suma,:wprowadzono, :realizacja,:uwagi, :uwagi2,"
                    " :uzytkownik, :modele_id, :klienci_id, :handlowce_id, :rozkroje_id, :pozycja);");
        qry.bindValue(":nr_zamowieniaR", rzad.at(1)->data(Qt::DisplayRole).toString());
        qry.bindValue(":klienci_id", rzad.at(3)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R36", rzad.at(10)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R37", rzad.at(11)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R38", rzad.at(12)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R39", rzad.at(13)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R40", rzad.at(14)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R41", rzad.at(15)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R42", rzad.at(16)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R43", rzad.at(17)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R44", rzad.at(18)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R45", rzad.at(19)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R46", rzad.at(20)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R47", rzad.at(21)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R48", rzad.at(22)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R49", rzad.at(23)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":R50", rzad.at(24)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":suma", rzad.at(25)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":uzytkownik", user);
        qry.bindValue(":modele_id", rzad.at(33)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":wprowadzono", rzad.at(34)->data(Qt::DisplayRole).toString());
        qry.bindValue(":realizacja", rzad.at(35)->data(Qt::DisplayRole).toString());
        qry.bindValue(":uwagi", rzad.at(36)->data(Qt::DisplayRole).toString());
        qry.bindValue(":uwagi2", rzad.at(37)->data(Qt::DisplayRole).toString());
        qry.bindValue(":handlowce_id",  rzad.at(47)->data(Qt::DisplayRole).toInt());
        qry.bindValue(":rozkroje_id", idRozkroju);
        QString nrPoz = QString("%1").arg((i+1));
        qry.bindValue(":pozycja", QString("%1/%2").arg(nrRozkroju, nrPoz));
        if (!qry.exec()) {
            qDebug() << "Bląd przy zapisie rozk poz" ;
            qDebug() << qry.lastError().text();
            vSuccess = false;
            pozycje->appendRow(rzad);
        }

    }
    if (vSuccess == true) {
        QSqlQuery qryx;
        QString qryString = QString("UPDATE `obuwie_db`.`zamowienia` SET `status`='ZLEC W PRODUKCJI', `ROZKROJ`='%1' WHERE `id` in ( ").arg(nrRozkroju);
        qryString += currentIdZamRozkroje;
        qryString += " )";
        qryx.prepare(qryString);
        if (!qryx.exec()) {
            qDebug() << "Bląd przy zmiana stat do wys" ;
            vSuccess = false;
        }
    }

    if (vSuccess == true) {
        db.commit();
        setRozkroje();
        mRozkroje->select();
        return true;
    } else {
        db.rollback();
        return false;
    }
}

void BazaDanychManager::zachowajSpod(QString nr, QString getNazwa, QString getProducent,
                                     QVector<QImage> images, QString getRodzaj, QString getRozm,
                                     QString getUwagi) {
    QSqlQuery qry;
    qry.prepare("INSERT INTO spody (nr, nazwa, producent, rodzaj, rozmiary, uwagi, zdj1, zdj2, zdj3, zdj4) "
                "VALUES (:nr, :nazwa, :producent, :rodzaj, :rozmiary, :uwagi, :zdj1, :zdj2, :zdj3, :zdj4)");
    qry.bindValue(":nr", nr.toInt());
    qry.bindValue(":nazwa", getNazwa);
    qry.bindValue(":producent", getProducent);
    qry.bindValue(":rodzaj", getRodzaj);
    qry.bindValue(":rozmiary", getRozm);
    qry.bindValue(":uwagi", getUwagi);

    QBuffer buffer;
    QImageWriter writer(&buffer, "JPG");
    writer.write(images[0]);

    qry.bindValue(":zdj1", buffer.data());

    QBuffer buffer2;
    QImageWriter writer2(&buffer2, "JPG");
    writer2.write(images[1]);
    qry.bindValue(":zdj2", buffer2.data());

    QBuffer buffer3;
    QImageWriter writer3(&buffer3, "JPG");
    writer3.write(images[2]);
    qry.bindValue(":zdj3", buffer3.data());

    QBuffer buffer4;
    QImageWriter writer4(&buffer4, "JPG");
    writer4.write(images[3]);
    qry.bindValue(":zdj4", buffer4.data());

    if (!qry.exec()) {
        qDebug() << "Bląd przy zapisie spodu" ;
        qDebug() << qry.lastError().text();
    } else {
        mSpody->select();
    }
}

QImage BazaDanychManager::getImage(int id, int ktore, QString tab) {
    QSqlQuery qry;
    QString qryStr =
        QString("select zdj%1 from %2 where id=:id;").arg(ktore).arg(tab);
    qry.prepare(qryStr);
    qry.bindValue(":id", id);

    if (!qry.exec()) {
        qDebug() << "Blad przy pobraniu zdjecia" ;
    }

    if (!qry.next()) {
        return QImage();
    }
    QByteArray array = qry.value(0).toByteArray();
    QBuffer buffer(&array);
    buffer.open(QIODevice::ReadOnly);
    QImageReader reader(&buffer, "JPG");
    QImage image = reader.read();

    return image;
}

bool BazaDanychManager::updateImage(int id, int ktore, QImage im, QString tab) {
    QSqlQuery qry;
    QString qryStr =
        QString("UPDATE %1 SET zdj%2=:image where id=:id").arg(tab).arg(ktore);

    qry.prepare(qryStr);
    QBuffer buffer;
    QImageWriter writer(&buffer, "JPG");
    writer.write(im);

    qry.bindValue(":image", buffer.data(), QSql::InOut | QSql::Binary);
    qry.bindValue(":id", id, QSql::InOut | QSql::Binary);
    if (!qry.exec()) {
        qDebug() << "Bląd przy aktualizacji zdj spodu" ;
        return false;
    } else {
        return true;
    }
}

void BazaDanychManager::ustawIdAktualnegoKlienta(const QModelIndex index) {
    idKlienta = mKlienci->data(mKlienci->index(index.row(),
                               0)).toInt();
    nazwaKlienta = mKlienci->data(mKlienci->index(index.row(),
                                  2)).toString();
}

void BazaDanychManager::ustawIdAktualnegoHandl(const QModelIndex index) {
    idHandlowca = mHandlowce->data(mHandlowce->index(
                                       index.row(),
                                       0)).toInt();
    nazwaHandlowca = mHandlowce->data(mHandlowce->index(
                                          index.row(),
                                          3)).toString();
}

QString BazaDanychManager::pobierzNazweAktualnegoKlienta() {
    return nazwaKlienta;
}

QString BazaDanychManager::pobierzNazweAktualnegoHandl() {
    return nazwaHandlowca;
}

void BazaDanychManager::rozlacz() {
    if (db.open()) {
        db.close();
    }
}

QSqlQuery BazaDanychManager::getIdsZamowienia(QString nrzam) {
    QSqlQuery qry;
    QString qryS = QString("select id from zamowienia where nr_zamowienia=:nr");
    qry.prepare(qryS) ;
    qry.bindValue(":nr", nrzam);
    qry.exec();
    return qry;
}

void BazaDanychManager::zmienKlientaZam(QString nrzam) {
    QSqlQuery qry = getIdsZamowienia(nrzam);

    while (qry.next()) {
        QSqlQuery qry2;
        QString qryS2 =
            QString("update zamowienia set id_klienta=%1 where zamowienia.id=%2").arg(
                idKlienta).
            arg(qry.value(0).toString());
        qry2.prepare(qryS2) ;
        if (!qry2.exec()) {
            qDebug() << "Bląd update zam kli" ;
        }
    }

    mZamowienia->select();
}

void BazaDanychManager::zmienHandlZam(QString nrzam) {
    QSqlQuery qry = getIdsZamowienia(nrzam);
    while (qry.next()) {
        QSqlQuery qry2;
        QString qryS2 =
            QString("update zamowienia set handlowce_id=%1 where zamowienia.id=%2").arg(
                idHandlowca).
            arg(qry.value(0).toString());
        qry2.prepare(qryS2) ;
        if (!qry2.exec()) {
            qDebug() << "Bląd update zam han" ;
        }
    }

    mZamowienia->select();
}

int BazaDanychManager::zwrocSumeZamowien() {
    int result = 0;
    for (int i = 0; i < mZamowienia->rowCount(); i++) {
        result += mZamowienia->data(mZamowienia->index(i,
                                    25)).toInt();
    }
    return result;
}

void BazaDanychManager::dodajWzor(int w, QString opis) {
    QSqlQuery qry;
    qry.prepare("INSERT INTO wzory (nr_wzoru, opis) VALUES (:nr, :opis)");
    qry.bindValue(":nr", w);
    qry.bindValue(":opis", opis);
    if (!qry.exec()) {
        qDebug() << "Bląd przy dodaniu wzoru" ;
    }
}

void BazaDanychManager::dodajOciep(QString w, QString o) {
    QSqlQuery qry;
    qry.prepare("INSERT INTO ocieplenia (rodzaj, opis) VALUES (:rodzaj, :opis)");
    qry.bindValue(":rodzaj", w);
    qry.bindValue(":opis", o);
    if (!qry.exec()) {
        qDebug() << "Bląd przy dodaniu ociep" ;
    }
}

bool BazaDanychManager::aktualizujStatus(int id, QString status) {
    QSqlQuery qry;
    qry.prepare("update zamowienia set status=:status where id=:id");
    qry.bindValue(":status", status);
    qry.bindValue(":id", id);
    if (!qry.exec()) {
        qDebug() << "Bląd przy aktualizacji statusu" ;
        return false;
    } else {
        return true;
    }
}

void BazaDanychManager::setZamowieniaFilter() {
    QString f =
        QString("status LIKE '%1%' AND klnr LIKE '%2%' AND nr_zamowienia LIKE '%3%' AND klnaz LIKE '%4%'"
                " AND typ LIKE '%5%' AND rodzaj_montazu LIKE '%6%' AND rodzaj_buta LIKE '%7%'  AND rodzaj_buta_2 LIKE '%8%'  AND rodzaj_buta_3 LIKE '%9%'").arg(
            filterZamowien.status, filterZamowien.klNr, filterZamowien.nrZ,
            filterZamowien.klNaz,
            filterZamowien.typ, filterZamowien.mont, filterZamowien.r1,  filterZamowien.r2,
            filterZamowien.r3);
    f += QString(" AND rodzaj_buta_4 LIKE '%1%'"
                 "  AND rodzaj_buta_5 LIKE '%2%'  AND rodzaj_buta_6 LIKE '%3%' AND wzn LIKE '%4%' AND ocn LIKE '%5%'AND man LIKE '%6%' AND kol LIKE '%7%' AND wklr LIKE '%8%' AND sk1 LIKE '%9%'").
         arg(filterZamowien.r4,  filterZamowien.r5, filterZamowien.r6,
             filterZamowien.wzor,
             filterZamowien.ociep, filterZamowien.mat, filterZamowien.kolor,
             filterZamowien.wkladka, filterZamowien.sk1); //,  );
    f += QString("AND sk2 LIKE '%1%' AND sk3 LIKE '%2%' AND uzytkownik LIKE '%3%' AND skrot LIKE '%4%' AND spnum LIKE '%5%' AND wprowadzono LIKE '%6%'"
                 " AND realizacja LIKE '%7%' AND spn LIKE '%8%' AND spp LIKE '%9%'").
         arg(filterZamowien.sk2, filterZamowien.sk3, filterZamowien.uzyt,
             filterZamowien.ha, filterZamowien.spn, filterZamowien.wpr, filterZamowien.rea,
             filterZamowien.snaz, filterZamowien.sprod);
    mZamowienia->setFilter(f);
}
//`kol`.`sk1` AS `sk1`,
//       `kol`.`sk2` AS `sk2`,
//       `kol`.`sk3` AS `sk3`,
void BazaDanychManager::setKlienciFilter() {
    QString f =
        QString("nazwa_skrot LIKE '%1%' AND nazwa LIKE '%2%' AND miasto LIKE '%3%' AND id LIKE '%4%' AND skrot LIKE '%5%' ").arg(
            filterKlientow.skrot, filterKlientow.nazwa, filterKlientow.miasto, filterKlientow.nr, filterKlientow.han);
    mKlienci->setFilter(f);
}

BazaDanychManager::~BazaDanychManager() {
    rozlacz();
    QSqlDatabase::removeDatabase("obuwie_db");
    removeSqlModels();
}

bool BazaDanychManager::ponowniePolacz() {
    rozlacz();
    if (polacz()) {
        return true;
    } else {
        return false;
    }
}
