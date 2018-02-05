#include "spodyDialog.h"
#include "ui_spodyDialog.h"
#include "BazaDanychManager.h"
#include "ManagerZdjec.h"

spodyDialog::spodyDialog(ZdjecieDialog *zdj, nowySpodDialog *dialogNSpod,
			 BazaDanychManager *db,
			 QWidget *parent) :
	QDialog(parent),
	ui(new Ui::spodyDialog),
	dialogNSpod(dialogNSpod),
	dialogZdj(zdj), dbManager(db) {
	ui->setupUi(this);
	label1 = new clickableLabel(this);
	ui->horizontalLay1_2->addWidget(label1);
	label2 = new clickableLabel(this);
	ui->horizontalLay1_3->addWidget(label2);
	label3 = new clickableLabel(this);
	ui->horizontalLay1_4->addWidget(label3);
	label4 = new clickableLabel(this);
	ui->horizontalLay1_5->addWidget(label4);
	label1->setScaledContents(true);
	label2->setScaledContents(true);
	label3->setScaledContents(true);
	label4->setScaledContents(true);
	connect(label1, &clickableLabel::clicked, this, &spodyDialog::zdj1);
	connect(label2, &clickableLabel::clicked, this, &spodyDialog::zdj2);
	connect(label3, &clickableLabel::clicked, this, &spodyDialog::zdj3);
	connect(label4, &clickableLabel::clicked, this, &spodyDialog::zdj4);
	proxy = new QSortFilterProxyModel(this);
}

spodyDialog::~spodyDialog() {
	delete proxy;
	delete ui;
}

int spodyDialog::selectExec() {
	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
		SLOT(wybranoSpod(const QModelIndex)));
	ui->pushButton_3->hide();
	ui->pushButton_4->hide();
	ui->pushButton_6->hide();
	ui->pushButton_7->hide();
	return QDialog::exec();
}

int spodyDialog::exec() {
	ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
	ui->pushButton_3->show();
	ui->pushButton_4->show();
	ui->pushButton_6->show();
	ui->pushButton_7->show();
	return QDialog::exec();
}

void spodyDialog::wybranoSpod(const QModelIndex index)
{
	QModelIndex  idx = proxy->mapToSource(
				   ui->tableView->selectionModel()->currentIndex());
	aktualnySpodNazwa = dbManager->pobierzNazwaSpodu(idx);
	accept();
}

void spodyDialog::showPhoto(QImage im) {
	dialogZdj->setLabel(im);
	dialogZdj->exec();
}

void spodyDialog::zdj1() {
	if (!image1.isNull()) {
		label1->setPixmap(QPixmap::fromImage(image1));
		showPhoto(image1);
	}
}

void spodyDialog::zdj2() {
	if (!image2.isNull()) {
		label2->setPixmap(QPixmap::fromImage(image2));
		showPhoto(image2);
	}
}

void spodyDialog::zdj3()
{	if (!image3.isNull()) {
		label3->setPixmap(QPixmap::fromImage(image3));
		showPhoto(image3);
	}
}

void spodyDialog::zdj4()
{	if (!image4.isNull()) {
		label4->setPixmap(QPixmap::fromImage(image4));
		showPhoto(image4);
	}
}

void spodyDialog::showEvent(QShowEvent *e) {
	Q_UNUSED(e);
	dbManager->setSpody();
	proxy->setSourceModel(dbManager->getSpody());
	proxy->setDynamicSortFilter(true);
	ui->tableView->setModel(proxy);
	QHeaderView *hv = ui->tableView->horizontalHeader();
	hv->setSectionHidden(0, true);
	hv->setSectionHidden(5, true);
	hv->setSectionHidden(6, true);
	hv->setSectionHidden(7, true);
	hv->setSectionHidden(8, true);
	hv->setSectionHidden(9, true);
	hv->setDefaultAlignment(Qt::AlignCenter);
	hv->setStretchLastSection(true);
	//ui->tableView->sortByColumn(1, Qt::AscendingOrder);
}

void spodyDialog::hideEvent(QHideEvent *e)
{
	label1->clear();
	label2->clear();
	label3->clear();
	label4->clear();
	image1 = QImage();
	image2 = QImage();
	image3 = QImage();
	image4 = QImage();
	disconnect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
		   SLOT(wybranoSpod(const QModelIndex)));
}

QString spodyDialog::getAktualnySpodNazwa() const
{
	return aktualnySpodNazwa;
}

void spodyDialog::on_pushButton_2_clicked() {
	dialogNSpod->setFixedSize(dialogNSpod->size());
	if (dialogNSpod->exec() == QDialog::Accepted ) {
		dbManager->zachowajSpod(dialogNSpod->getNazwa(), dialogNSpod->getProducent(),
					dialogNSpod->getImages(), dialogNSpod->getRodzaj(), dialogNSpod->getRozm(),
					dialogNSpod->getUwagi());
	}
}

void spodyDialog::on_pushButton_3_clicked() {
	image1 = ManagerZdjec::getImage(this);
	if (!image1.isNull()) {
		int id = getId();
		if (dbManager->updateImage(id, 1, image1, QString("spody"))) {
			label1->setPixmap(QPixmap::fromImage(image1));
		}
	}
}

void spodyDialog::on_pushButton_4_clicked() {
	image2 = ManagerZdjec::getImage(this);
	if (!image2.isNull()) {
		int id = getId();
		if (dbManager->updateImage(id, 2, image2, QString("spody"))) {
			label2->setPixmap(QPixmap::fromImage(image2));
		}
	}
}

void spodyDialog::on_pushButton_6_clicked() {
	image3 = ManagerZdjec::getImage(this);
	if (!image3.isNull()) {
		int id = getId();
		if (dbManager->updateImage(id, 3, image3, QString("spody"))) {
			label3->setPixmap(QPixmap::fromImage(image3));
		}
	}
}

void spodyDialog::on_pushButton_7_clicked() {
	image4 = ManagerZdjec::getImage(this);
	if (!image4.isNull()) {
		int id = getId();
		if (dbManager->updateImage(id, 4, image4, QString("spody"))) {
			label4->setPixmap(QPixmap::fromImage(image4));
		}
	}
}

int spodyDialog::getId()
{
	QModelIndex  idx = proxy->mapToSource(
				   ui->tableView->selectionModel()->currentIndex());
	return  dbManager->getSpody()->data(
			dbManager->getSpody()->index(idx.row(),
					0)).toInt();
}

void spodyDialog::on_tableView_clicked(const QModelIndex &index) {
	label1->clear();
	label2->clear();
	label3->clear();
	label4->clear();
	int id = getId();
	image1 = dbManager->getImage(id, 1, QString("spody"));
	image2 = dbManager->getImage(id, 2, QString("spody"));
	image3 = dbManager->getImage(id, 3, QString("spody"));
	image4 = dbManager->getImage(id, 4, QString("spody"));

	label1->setPixmap(QPixmap::fromImage(image1));
	label2->setPixmap(QPixmap::fromImage(image2));
	label3->setPixmap(QPixmap::fromImage(image3));
	label4->setPixmap(QPixmap::fromImage(image4));
}

void spodyDialog::on_buttonBox_accepted()
{
	accept();
}

void spodyDialog::on_buttonBox_rejected()
{
	reject();
}
