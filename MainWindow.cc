#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QCloseEvent>
#include <QSettings>
#include <QDesktopWidget>
#include <QPainter>
#include "nowyKlientDialog.h"
#include "Klient.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);

	dbManager = new BazaDanychManager();
	dialog = new UstawieniaForm(dbManager, this);
	dialogWybKlienta = new WybKlientaDialog(dbManager, this);
	dialogWybHandl = new WybHandlDialog(dbManager, this);
	dialogWybModel = new WybModelDialog(dbManager, this);
	dialognowyKlient = new nowyKlientDialog(this);
	dialognowyHandl = new NowyHandlowiecDialog(this);
	dialogNoweZamowienie = new noweZamowienieDialog(dialognowyHandl, dialogWybHandl,
			dbManager,
			dialogWybModel, dialogWybKlienta,
			dialognowyKlient, this);
	if (!dbManager->polacz()) {
		ustawieniaBazy();
	}

	ui->comboBox->addItem(QString("WPROWADZANIE"));
	ui->comboBox->addItem(QString("DO ROZKROJU"));
	ui->comboBox->addItem(QString("KRAJALNIA"));
	ui->comboBox->addItem(QString("SZWALNIA 1"));
	ui->comboBox->addItem(QString("SZWALNIE ZEWNĘTRZNE"));
	ui->comboBox->addItem(QString("SPODY"));
	ui->comboBox->addItem(QString("MONTAŻ"));
	ui->comboBox->addItem( QString("WYSŁANO"));
	ui->comboBox->addItem(QString("KOSZ"));
	ui->comboBox->setCurrentText(QString(""));

	podlaczSygnaly();
	aktualizujTabele();
	selectMode = false;
	a();
}

void MainWindow::aktualizujTabele() {
	ui->tableViewZam->setModel(dbManager->getModelZamowienia());
	ui->tableViewKlienci->setModel(dbManager->getModelKlienci());
	ui->tableViewHandlowce->setModel(dbManager->getModelHandlowce());
	rozciagnijWiersze(ui->tableViewKlienci);
	rozciagnijWiersze(ui->tableViewHandlowce);
	rozciagnijWiersze(ui->tableViewZam);
	dialogWybKlienta->aktualizujTabele();
	dialogWybHandl->aktualizujTabele();
	dialogWybModel->aktualizujTabele();
	ui->tableViewKlienci->setColumnWidth(1, 200);
	ui->tableViewKlienci->setColumnWidth(2, 135);
}

void MainWindow::a()
{
	//dialogNoweZamowienie->exec();
}

void MainWindow::ustawieniaBazy() {
	if (dialog->exec() == QDialog::Accepted) {
		aktualizujTabele();
	}
}

void MainWindow::podlaczSygnaly() {
	connect(ui->akcjaUstawieniaBazy, SIGNAL(triggered()), this,
		SLOT(ustawieniaBazy()));
}

void MainWindow::on_pushButton_2_clicked() {
	dodajKlienta();
}

void MainWindow::dodajZam() {
	if ( dialogNoweZamowienie->exec() == QDialog::Accepted ) {
		QMessageBox::information(this, "POWODZENIE",
					 " <FONT COLOR='#000080'>Dodano zamówienie. ",
					 QMessageBox::Ok);
	}
}

void MainWindow::on_pushButton_clicked() {
	dodajZam();
}

void MainWindow::rozciagnijWiersze(QTableView *m) {
	for (int c = 0; c < m->horizontalHeader()->count(); ++c) {
		m->horizontalHeader()->setSectionResizeMode(c, QHeaderView::ResizeToContents);
	}
	QHeaderView *hv = m->horizontalHeader();
	hv->setStretchLastSection(true);
	hv->setSectionHidden(0, true);
	hv->setDefaultAlignment(Qt::AlignLeft);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_akcjaZamknij_triggered()
{
	dbManager->rozlacz();
	close();
}

void MainWindow::on_tableViewZam_clicked(const QModelIndex &index) {
	dbManager->setIdZamowieniaModeleForMainWindow(index, selectMode);
	ui->tableViewZamMod->setModel(
		dbManager->getModelZamowieniaModeleForMainWindow());
	QHeaderView *hv = ui->tableViewZamMod->horizontalHeader();
	for (int c = 0; c < ui->tableViewZamMod->horizontalHeader()->count(); ++c) {
		ui->tableViewZamMod->horizontalHeader()->setSectionResizeMode(c,
				QHeaderView::ResizeToContents);
	}
	hv->setStretchLastSection(true);
	hv->setSectionHidden(0, true);
	hv->setSectionHidden(22, true);
	hv->setSectionHidden(27, true);
	hv->setSectionHidden(28, true);
	hv->setDefaultAlignment(Qt::AlignLeft);
	ui->labelPodglad->clear();
}

void MainWindow::on_pushButton_3_clicked() {
	dodajHandlowca();
}

void MainWindow::on_tableViewZamMod_clicked(const QModelIndex &index)
{	ui->labelPodglad->clear();
	QAbstractItemModel *model = ui->tableViewZamMod->model();
	int id = model->data(model->index(
					 index.row(),
					 0)).toInt();
	ui->labelPodglad->setPixmap(QPixmap::fromImage(
						dbManager->getImageZamowienia(id)));
}

void MainWindow::dodajKlienta() {
	if ( dialognowyKlient->exec() == QDialog::Accepted ) {
		Klient klient(
			dialognowyKlient->getNazwa(),
			dialognowyKlient->getSkrot(),
			dialognowyKlient->getUlica(),
			dialognowyKlient->getNumerDomu(),
			dialognowyKlient->getMiasto(), dialognowyKlient->getKodPocztowy(),
			dialognowyKlient->getTel1(),
			dialognowyKlient->getTel2(),
			dialognowyKlient->getFax(), dialognowyKlient->getMail(),
			dialognowyKlient->getUwagi(),
			dialognowyKlient->getNumerTelefonu());

		dbManager->zachowajKlienta(klient);
	}
}

void MainWindow::dodajHandlowca()
{
	if ( dialognowyHandl->exec() == QDialog::Accepted ) {
		dbManager->zachowajHandlowca(dialognowyHandl->getImie(),
						 dialognowyHandl->getNazwisko(), dialognowyHandl->getSkrot());
	}
}

void MainWindow::on_actionDodaj_klienta_triggered()
{
	dodajKlienta();
}

void MainWindow::on_actionDodaj_handlowca_2_triggered()
{
	dodajHandlowca();
}

void MainWindow::on_actionDodaj_zam_wienie_2_triggered()
{
	dodajZam();
}

bool MainWindow::pageSetup(QPrinter *printer) {
	QPageSetupDialog psd(printer);
	if (psd.exec() == QDialog::Accepted) {
		return true;
	} else {
		return false;
	}
}

void MainWindow::printDocument(QPrinter *printer)
{	QTextDocument document;
	populateDocument(&document);
	document.print(printer);
}

void MainWindow::populateDocument(QTextDocument *document) {
	DokumentDoDruku tworzacyDokument;
	OnePage page;
	page.title = QString("title");
	page.filenames << "/home/mmichniewski/001.jpg" << "/home/mmichniewski/001.jpg"
			   << "/home/mmichniewski/001.jpg" << "/home/mmichniewski/001.jpg";
	page.captions << "111ddddd" << "222dd" << "111ddddd" << "222dd";
	page.descriptionHtml = QString("opis");
	tworzacyDokument.dodajStrone(page);

	tworzacyDokument.populateDocumentUsingHtml(document);
}

void MainWindow::on_pushButton_5_clicked() {
	QPrinter printer; //printer.setResolution(QPrinter::HighResolution);

	QMarginsF ma;
	//ma.setTop(5.5);
	//ma.setLeft(2.7);//0,95
	printer.setPageMargins(ma);
	printer.setPageOrientation(QPageLayout::Landscape);//QPageLayout::Portrait
	//if (pageSetup(&printer)) {
	printDocument(&printer);
	//}
}

void MainWindow::on_pushButton_4_clicked() {
	QModelIndexList selection = ui->tableViewZam->selectionModel()->selectedRows();

	int id = 0;
	for (int i = 0; i < selection.count(); i++)
	{
		QModelIndex index = selection.at(i);
		id = dbManager->getIdZamowieniaZTabeli(index, selectMode);
		dbManager->aktualizujStatus(id, ui->comboBox->currentText());

		if (selectMode) {
			ui->tableViewZam->setModel(dbManager->selectZamowieniaWgStatusu(
							   dbManager->getOstatniSelectZam()));
			dbManager->setHeadersGlowneSelectZamowienia();
		}
	}
}

void MainWindow::on_pushButton_7_clicked() {
	ui->tableViewZam->setModel(dbManager->selectZamowieniaWgStatusu(
					   ui->comboBox->currentText()));
	dbManager->setHeadersGlowneSelectZamowienia();
	selectMode = true;
}

void MainWindow::on_pushButton_6_clicked() {// reset selected  zamowienia
	ui->tableViewZam->setModel(dbManager->getModelZamowienia());
	rozciagnijWiersze(ui->tableViewZam);
	selectMode = false;
}
