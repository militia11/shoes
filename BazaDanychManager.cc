#include "BazaDanychManager.h"
#include "CSettings.h"
#include <QBuffer>
#include <QImageReader>

BazaDanychManager::BazaDanychManager() {
	lastConnectionError = false;
	firstRun = true;
	db = QSqlDatabase::addDatabase("QMYSQL");
	mSelectZamowienia = NULL;
	idKlienta = -1;
	idHandlowca = -1;
	idModelu = -1;
	idZamowieniaModeleForMainWindow = -1;
	mZamowieniaModele = new QSqlTableModel();
}

void BazaDanychManager::removeSqlModels() {
	if (mZamowienia) {
		delete mZamowienia;
		mZamowienia = 0;
	}
	if (mZamowieniaModele) {
		delete mZamowieniaModele;
		mZamowieniaModele = 0;
	}
	if (mKlienci) {
		delete  mKlienci;
		mKlienci = 0;
	}
	if (mHandlowce) {
		delete  mHandlowce;
		mHandlowce = 0;
	}
	if (mKlienciWybieranie) {
		delete  mKlienciWybieranie;
		mKlienciWybieranie = 0;
	}
	if (mModeleWybieranie) {
		delete  mModeleWybieranie;
		mModeleWybieranie = 0;
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
		QSqlQuery vStrictMode("SET sql_mode = 'STRICT_ALL_TABLES'", db);
		aktualizujTabele();
		firstRun = false;
		return true;
	}
}

void BazaDanychManager::setZamowienia() {
	mZamowienia = new QSqlTableModel();
	mZamowienia->setTable("zamowienia");
	mZamowienia->select();

	setHeadersGlowneZamowienia();
}

void BazaDanychManager::setHeadersForZamowienia(QAbstractItemModel *model) {
	QStringList listaZamowienia;
	listaZamowienia  << "WZÓR" <<  "OCIEPLENIE" << "SPÓD" <<
			 "MATRYCA " << "KOLOR" << "R36" << "R37" << "R38"	<< "R39" << "R40"
			 << "R41" << "R42" << "R43"	<< "R44"
			 << "R45" << "R46" << "R47"	<< "R48" << "R49" << "R50"
			 << "SUMA" << "ZDJECIE" << "SK1" <<	"SK2" <<	"SK3" <<
			 "UWAGI" << "" << "" << ""  ;
	setHeaders(listaZamowienia, model);
}

QSqlTableModel *BazaDanychManager::getModelZamowienia() {
	return mZamowienia;
}

QAbstractItemModel *BazaDanychManager::getModelZamowieniaModele() {
	return mZamowieniaModele;
}

QAbstractItemModel *BazaDanychManager::getModelZamowieniaModeleForMainWindow() {
	QString vQueryText =
		QString("SELECT * FROM zamowienia_modele WHERE zamowienia_id=%1;").arg(
			idZamowieniaModeleForMainWindow);
	QSqlQuery vQuery(db);
	vQuery.prepare(vQueryText);

	QAbstractItemModel *model = getModelForQuery(&vQuery);
	setHeadersForZamowienia(model);

	return model;
}

QImage BazaDanychManager::getImageZamowienia(int id) {
	QSqlQuery qry;
	qry.prepare( "select zdjecie from zamowienia_modele where id=:id;" );
	qry.bindValue( ":id", id );

	if ( !qry.exec() ) {
		qFatal( "Blad przy pobraniu zdjecia" );
	}

	if ( !qry.next() ) {
		return QImage();
	}
	QByteArray array = qry.value(0).toByteArray();
	QBuffer buffer(&array);
	buffer.open( QIODevice::ReadOnly );
	QImageReader reader(&buffer, "JPG");
	QImage image = reader.read();

	return image;
}

QSqlTableModel *BazaDanychManager::getModelKlienci() {
	return mKlienci;
}

QSqlTableModel *BazaDanychManager::getModelHandlowce()
{
	return mHandlowce;
}

QSqlTableModel *BazaDanychManager::getModelKlienciWybieranie()
{
	return  mKlienciWybieranie;
}

QSqlTableModel *BazaDanychManager::getModelmModeleWybieranie()
{
	return  mModeleWybieranie;
}

void BazaDanychManager::setIdZamowieniaModeleForMainWindow(
	const QModelIndex index, bool selectMode) {
	if (selectMode) {
		idZamowieniaModeleForMainWindow = mSelectZamowienia->data(
				mSelectZamowienia->index(
					index.row(),
					0)).toInt();
	} else {
		idZamowieniaModeleForMainWindow = mZamowienia->data(mZamowienia->index(
				index.row(),
				0)).toInt();
	}
}

int BazaDanychManager::getIdZamowieniaZTabeli(QModelIndex index,
		bool selectMode) {
	int id = -1;
	if (selectMode) {
		id = mSelectZamowienia->data(mSelectZamowienia->index(
							 index.row(),
							 0)).toInt();
	} else {
		id = mZamowienia->data(mZamowienia->index(
						   index.row(),
						   0)).toInt();
	}
	qDebug() << id;
	return id;
}

void BazaDanychManager::ustawAktualnyModelId(const QModelIndex index) {
	idModelu = mModeleWybieranie->data(mModeleWybieranie->index(index.row(),
					   0)).toInt();
}

void BazaDanychManager::setHeadersGlowneZamowienia()
{
	QStringList listaZamowienia;
	listaZamowienia << "NR ZAM" << "KLIENT" << "HANDLOWIEC" <<  "UWAGI 1" <<
			"UWAGI 2" <<
			"DATA WPROWADZENIA" << "DATA REALIZACJI" << "STATUS";
	setHeaders(listaZamowienia, mZamowienia);
}

void BazaDanychManager::setHeadersGlowneSelectZamowienia()
{
	QStringList listaZamowienia;
	listaZamowienia << "NR ZAM" << "KLIENT" << "HANDLOWIEC" <<  "UWAGI 1" <<
			"UWAGI 2" <<
			"DATA WPROWADZENIA" << "DATA REALIZACJI" << "STATUS";
	setHeaders(listaZamowienia, mSelectZamowienia);
}

QVariant BazaDanychManager::GetFirstValueForQuery(QSqlQuery *aQuery) {
	QVariant vResult;
	aQuery->exec();

	if (wystapilBlad(*aQuery)) {
		obsluzSqlError(*aQuery);
	} else if (aQuery->next()) {
		vResult = aQuery->value(0);
	}

	return vResult;
}

int BazaDanychManager::GetIdOfLastInsertedRow()
{
	QSqlQuery vIdQuery(db);
	vIdQuery.exec("SELECT last_insert_id()");

	QVariant vIdAsVariant = GetFirstValueForQuery(&vIdQuery);
	int vId = vIdAsVariant.isNull() ? -1 : vIdAsVariant.toInt();

	return vId;
}

int BazaDanychManager::getIdOstatniegoZam() {
	QSqlQuery vIdQuery(db);
	vIdQuery.exec("SELECT id FROM zamowienia ORDER BY id DESC LIMIT 1;");

	QVariant vIdAsVariant = GetFirstValueForQuery(&vIdQuery);
	int vId = vIdAsVariant.isNull() ? -1 : vIdAsVariant.toInt();

	return vId;
}

int BazaDanychManager::getNumerOstatniegoZamKomputerowego() {
	QSqlQuery vIdQuery(db);
	vIdQuery.exec("SELECT nr_zamowienia FROM zamowienia  WHERE nr_zamowienia LIKE 'B%' ORDER BY id DESC LIMIT 1;");

	QVariant vIdAsVariant = GetFirstValueForQuery(&vIdQuery);
	QString numer = vIdAsVariant.isNull() ? QString("B-1") :
			vIdAsVariant.toString();
	int liczba = numer.remove(0, 1).toInt();
	return liczba;
}

QList<QStandardItem *> BazaDanychManager::zwrocWierszModel() {
	QList<QStandardItem *> rzad;

	QString vQueryText =
		QString("select nr_wzoru,matryca,ocieplenie,spod,kolor from modele where id=%1;").arg(
			idModelu);
	QSqlQuery vQuery(db);
	vQuery.prepare(vQueryText);
	vQuery.exec();

	int nr_wzoru = 0;
	QString matryca;
	QString ocieplenie;
	int spod = 0;
	int kolor = 0;
	if (wystapilBlad(vQuery)) {
		obsluzSqlError(vQuery);
	} else if (vQuery.next()) {
		nr_wzoru = vQuery.value(0).toInt();
		matryca = vQuery.value(1).toString();
		ocieplenie = vQuery.value(2).toString();
		spod = vQuery.value(3).toInt();
		kolor = vQuery.value(4).toInt();
	}

	rzad.append(new QStandardItem(QString::number(nr_wzoru)));
	rzad.append(new QStandardItem(matryca));
	rzad.append(new QStandardItem(ocieplenie));
	rzad.append(new QStandardItem(QString::number(spod)));
	rzad.append(new QStandardItem(QString::number(kolor)));
	for (int i = 0; i < 15; i++) {
		rzad.append(new QStandardItem(QString("0")));
	}
	rzad.append(new QStandardItem(QString("")));
	return rzad;
}

QSqlRecord BazaDanychManager::getSqlRecordZModelu(const QAbstractItemModel
		*aItemModel) {
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

	if (wystapilBlad(*aQuery)) {
		obsluzSqlError(*aQuery);
		delete vModel;
	}  else {
		vResult = vModel;
	}

	return vResult;
}

bool BazaDanychManager::wystapilBlad(const QSqlQuery &aQuery)
{
	QSqlError vError = aQuery.lastError();
	bool vOccured = (!aQuery.isActive() || vError.type() > 0);

	return vOccured;
}

void BazaDanychManager::obsluzSqlError(const QSqlQuery &aQuery)
{
	QSqlError vError = aQuery.lastError();
	if (vError.type() > 0) {
		QString vErrorText = QString("%1: %2").
					 arg(aQuery.executedQuery()).arg(vError.text());
		qDebug() << vError;
	}

	if (!aQuery.isActive()) {
		QString vErrorText =
			QString("%1: Problem z połączeniem (query )").
			arg(aQuery.lastQuery());
		qDebug() << vErrorText;
	}

	db.close();
	qDebug() << "stan bazy zmienił się na zerwany";
}

void BazaDanychManager::aktualizujHeaderyKlient(QAbstractItemModel *model)
{
	QStringList listaKlienci;
	listaKlienci << "NAZWA FIRMY" << "SKRÓT NAZWY" << "MIASTO" << "KOD" << "ULICA"
			 << "NUMER" << "TELEFON" << "TEL KOM 1"
			 << "TEL KOM 2" << "FAX" << "E-MAIL" << "UWAGI" << "ZAMÓWIONE" << "ODEBRANE" <<
			 "NIEODEBRANE";
	setHeaders(listaKlienci, model);
}

void BazaDanychManager::updateZamowieniaModele() {
	//setZamowieniaModeleHeaders();
}

QAbstractItemModel *BazaDanychManager::wyszukajKlientowPoNazwie(QString nazwa) {
	QString vQueryText =
		QString("SELECT * FROM klienci WHERE nazwa LIKE '%1%'").arg(
			nazwa);
	QSqlQuery vQuery(db);
	vQuery.prepare(vQueryText);

	QAbstractItemModel *model = getModelForQuery(&vQuery);
	aktualizujHeaderyKlient(model);

	return model;
}

QAbstractItemModel *BazaDanychManager::wyszukajKlientowPoSkrocie(
	QString nazwa) {
	QString vQueryText =
		QString("SELECT * FROM klienci WHERE nazwa_skrot LIKE '%1%'").arg(
			nazwa);

	QSqlQuery vQuery(db);
	vQuery.prepare(vQueryText);
	QAbstractItemModel *model = getModelForQuery(&vQuery);
	aktualizujHeaderyKlient(model);

	return model;
}

QAbstractItemModel *BazaDanychManager::wyszukajKlientow(QString nazwa,
		QString skrot) {
	QString vQueryText =
		QString("SELECT * FROM klienci WHERE nazwa LIKE '%1%' and nazwa_skrot LIKE '%2%'").arg(
			nazwa, skrot);
	QSqlQuery vQuery(db);
	vQuery.prepare(vQueryText);

	QAbstractItemModel *model = getModelForQuery(&vQuery);
	aktualizujHeaderyKlient(model);

	return model;
}

QAbstractItemModel *BazaDanychManager::selectZamowieniaWgStatusu(
	QString status) {
	QString vQueryText =
		QString("SELECT * FROM zamowienia WHERE status='%1';").arg(
			status);
	QSqlQuery vQuery(db);
	vQuery.prepare(vQueryText);

	if (mSelectZamowienia) {
		delete  mSelectZamowienia;
		mSelectZamowienia = 0;
	}
	ostatniSelectZam = status;
	mSelectZamowienia = getModelForQuery(&vQuery);

	return mSelectZamowienia;
}

void BazaDanychManager::aktualizujTabele() {
	//setHeadersForZamowienia(mZamowieniaModele);
	setZamowienia();
	setKlienci();
	setHandlowce();
	setKlienciWybieranie();
	setModeleWybieranie();
}

void BazaDanychManager::setHeaders(QStringList lista,
				   QAbstractItemModel *model) {
	for (int i = 1; i < model->columnCount(); ++i) {
		model->setHeaderData(i, Qt::Horizontal, lista[i - 1]);
	}
}

QString BazaDanychManager::getOstatniSelectZam() const
{
	return ostatniSelectZam;
}

void BazaDanychManager::setKlienci() {
	mKlienci = new QSqlTableModel();
	mKlienci->setTable("klienci");
	mKlienci->select();
	QStringList listaKlienci;
	listaKlienci << "NAZWA FIRMY" << "SKRÓT NAZWY" << "MIASTO" << "KOD" << "ULICA"
			 << "NUMER" << "TELEFON" << "TEL KOM 1"
			 << "TEL KOM 2" << "FAX" << "E-MAIL" << "UWAGI" << "ZAMÓWIONE" << "ODEBRANE" <<
			 "NIEODEBRANE";
	setHeaders(listaKlienci, mKlienci);
}

void BazaDanychManager::setHandlowce() {
	mHandlowce = new QSqlTableModel();
	mHandlowce->setTable("handlowce");
	mHandlowce->select();
	QStringList listaHandlowce;
	listaHandlowce << "IMIĘ" << "NAZWISKO" << "SKRÓT" <<  "UWAGI";
	setHeaders(listaHandlowce, mHandlowce);
}

void BazaDanychManager::setKlienciWybieranie() {
	mKlienciWybieranie = new QSqlTableModel();
	mKlienciWybieranie->setTable("klienci");
	mKlienciWybieranie->select();
	QStringList listaKlienci;
	listaKlienci << "NAZWA FIRMY" << "SKRÓT NAZWY" << "MIASTO" << "KOD" << "ULICA"
			 << "NUMER" << "TELEFON" << "TEL KOM 1"
			 << "TEL KOM 2" << "FAX" << "E-MAIL" << "UWAGI" << "ZAMÓWIONE" << "ODEBRANE" <<
			 "NIEODEBRANE";
	setHeaders(listaKlienci, mKlienciWybieranie);
}

void BazaDanychManager::setModeleWybieranie() {
	mModeleWybieranie = new QSqlTableModel();
	mModeleWybieranie->setTable("modele");
	mModeleWybieranie->select();
	QStringList
	listaModele;//NR MODELU WZÓR	MATRYCA	OCIEPLENIE	SPOD	KOLOR	WKŁADKA	ZDJECIE1	ZDJECIE2	ZDJECIE3	ZDJECIE4	OPIS1	OPIS2
	listaModele << "NR MODELU" << "WZÓR" << "MATRYCA" << "OCIEPLENIE" << "SPÓD" <<
			"KOLOR" << "WKŁADKA" << "OPIS1" << "OPIS2" << "" << ""  << "" << "" << "" << ""
			<< "" << "";
	setHeaders(listaModele, mModeleWybieranie);
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
		qDebug() << "Bląd przy zapisie klienta" ;
	}
	else {
		mKlienci->select();
	}
}

void BazaDanychManager::zachowajHandlowca(QString im, QString nz, QString skr) {
	QSqlQuery qry;
	qry.prepare( "INSERT INTO handlowce (imie, nazwisko, skrot) "
			 "VALUES (:imie, :nazwisko, :skrot)" );
	qry.bindValue( ":imie", im);
	qry.bindValue( ":nazwisko", nz);
	qry.bindValue( ":skrot", skr);
	if ( !qry.exec() ) {
		qDebug() << "Bląd przy zapisie Handlowca" ;
	}
	else {
		mHandlowce->select();
	}
}

bool BazaDanychManager::zamowienie(QString klientNazwa, QString handlNazwa,
				   QDate zam,
				   QDate realizacji, QStandardItemModel *pozycje,
				   QString papierowe) {
	db.transaction();
	bool vSuccess = true;
	int ostatniNumer = getNumerOstatniegoZamKomputerowego();
	int numerZamowieniaNowego = ostatniNumer + 1;
	QSqlQuery qry;
	qry.prepare("INSERT INTO `obuwie_db`.`zamowienia` (`nr_zamowienia`, `nazwa_klienta`, `nazwa_handlowca`, `wprowadzono`, `realizacja`, `status`) VALUES (:nr_zamowienia, :nazwa_klienta, :nazwa_handlowca, :wprowadzono , :realizacja, :status)");
	if (papierowe == QString("")) {
		qry.bindValue( ":nr_zamowienia", QString("B%1").arg(numerZamowieniaNowego));
	} else {
		qry.bindValue( ":nr_zamowienia", papierowe);
	}

	qry.bindValue( ":nazwa_klienta", klientNazwa);
	qry.bindValue( ":nazwa_handlowca", handlNazwa);
	qry.bindValue( ":wprowadzono", zam);
	qry.bindValue( ":realizacja", realizacji);
	qry.bindValue( ":status", QString("WPROWADZANIE"));
	if ( !qry.exec() ) {
		qDebug() << "Bląd przy zapisie zamówienia" ;
		vSuccess = false;
	}
	else {
		vSuccess = true;

	}
	int sumaKlient = 0;

	if (vSuccess == true) { //dodaj aktualne pozycje
		int idZamowieniaNowego = GetIdOfLastInsertedRow();
		int count = pozycje->rowCount();
		for (int i = 0; i < count; i++) {
			QList<QStandardItem *> rzad = pozycje->takeRow(0);
			QSqlQuery qry;
			//"ZDJECIE" << "SK1" <<	"SK2" <<"SK3"
			qry.prepare("INSERT INTO zamowienia_modele (wzor, matryca, ocieplenie, spod, kolor, R36, R37 ,R38, R39,  R40,   R41, R42  ,R43   ,R44,  R45, R46 ,  R47,  R48 ,  R49 , R50,"
					"suma, uwagi, zamowienia_id,modele_id) VALUES (:nr_wzoru ,:matryca , :ocieplenie, :spod,:kolor, :R36, :R37 ,:R38,:R39, :R40 ,  :R41 ,  :R42 , :R43  ,:R44, :R45 ,  :R46 , :R47  , :R48, :R49,:R50 ,:suma,:uwagi,:zamowienia_id, :modele_id)");
			qry.bindValue( ":nr_wzoru", rzad.at(0)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":matryca", rzad.at(1)->data(Qt::DisplayRole).toString());
			qry.bindValue( ":ocieplenie", rzad.at(2)->data(Qt::DisplayRole).toString());
			qry.bindValue( ":spod", rzad.at(3)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":kolor", rzad.at(4)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":R36", rzad.at(5)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":R37", rzad.at(6)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":R38", rzad.at(7)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":R39", rzad.at(8)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":R40", rzad.at(9)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":R41", rzad.at(10)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":R42", rzad.at(11)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":R43", rzad.at(12)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":R44", rzad.at(13)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":R45", rzad.at(14)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":R46", rzad.at(15)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":R47", rzad.at(16)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":R48", rzad.at(17)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":R49", rzad.at(18)->data(Qt::DisplayRole).toInt());
			qry.bindValue( ":R50", rzad.at(19)->data(Qt::DisplayRole).toInt());
			int suma = 0;
			for (int i = 5; i < 20; i++) {
				suma += rzad.at(i)->data(Qt::DisplayRole).toInt();
			}
			sumaKlient += suma;
			qry.bindValue( ":suma", suma);
			qry.bindValue( ":uwagi", rzad.at(20)->data(Qt::DisplayRole).toString());
			qry.bindValue( ":zamowienia_id", idZamowieniaNowego);
			qry.bindValue( ":modele_id", idModelu);
			if ( !qry.exec() ) {
				qDebug() << "Bląd przy zapisie pozycji" ;
				qDebug() << qry.lastQuery();
				qDebug () << qry.lastError().text();
				vSuccess = false;
				pozycje->insertRow(i, rzad);
			}
			else {
				mZamowienia->select();
			}
		}
	}

	if (vSuccess == true) {
			int zamowione = 0;
			int nieodebrane = 0;
			QSqlQuery qry;
			qry.prepare( "select zamowione, nieodebrane from klienci where id=:id");
			qry.bindValue( ":id", idKlienta);

			qry.exec();

			if (wystapilBlad(qry)) {
				obsluzSqlError(qry);
			} else if (qry.next()) {
				zamowione = qry.value(0).toInt();
				nieodebrane = qry.value(1).toInt();
			}
			zamowione += sumaKlient;
			nieodebrane += sumaKlient;
			QSqlQuery qry2;
			qry2.prepare( "update klienci set zamowione=:zamowione, nieodebrane=:nieodebrane where id=:id");
			qry2.bindValue( ":zamowione", zamowione);
			qry2.bindValue( ":nieodebrane", nieodebrane);
			qry2.bindValue( ":id", idKlienta);
			if ( !qry2.exec() ) {
				qDebug() << "Bląd przy aktualizacji sumy zamowień klienta" ;vSuccess = false;
			}
			else {
				mKlienci->select();
				mKlienciWybieranie->select();
			}
	}

	if (vSuccess == true) {
		db.commit();
		mZamowienia->select();
		return true;
	} else {
		db.rollback();
		mZamowienia->select();
		return false;
	}
}

void BazaDanychManager::ustawIdAktualnegoKlienta(const QModelIndex index) {

	idKlienta = mKlienciWybieranie->data(mKlienciWybieranie->index(index.row(),
						 0)).toLongLong();
	nazwaKlienta = mKlienciWybieranie->data(mKlienciWybieranie->index(index.row(),
						2)).toString();
}

void BazaDanychManager::ustawIdAktualnegoHandl(const QModelIndex index) {
	idHandlowca = mHandlowce->data(mHandlowce->index(index.row(),
					   0)).toLongLong();
	nazwaHandlowca = mHandlowce->data(mHandlowce->index(index.row(),
					  3)).toString();
}

QString BazaDanychManager::pobierzNazweAktualnegoKlienta() {
	return nazwaKlienta;
}

QString BazaDanychManager::pobierzNazweAktualnegoHandl() {
	return  nazwaHandlowca;
}

void BazaDanychManager::rozlacz() {
	if (db.open()) {
		db.close();
	}
}

void BazaDanychManager::aktualizujStatus(int id, QString status) {
	QSqlQuery qry;
	qry.prepare( "update zamowienia set status=:status where id=:id");
	qry.bindValue( ":status", status);
	qry.bindValue( ":id", id);
	if ( !qry.exec() ) {
		qDebug() << "Bląd przy aktualizacji statusu" ;
	}
	else {
		mZamowienia->select();
	}
}

BazaDanychManager::~BazaDanychManager() {
	rozlacz();
	QSqlDatabase::removeDatabase("obuwie_db");
}

bool BazaDanychManager::ponowniePolacz() {
	rozlacz();
	if (polacz()) {
		return true;
	} else {
		return false;
	}
}
