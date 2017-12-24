#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QCloseEvent>
#include <QSettings>
#include <QDesktopWidget>
#include <QPainter>
#include "nowyKlientDialog.h"
#include "Klient.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QSqlRelationalDelegate>

void MainWindow::logowanie() {
	QString text("");
	while (text == QString("")) {
		text = QInputDialog::getText(this, tr("Logowanie"),
						 tr("Nazwa użytkownika"), QLineEdit::Normal, QString(""));
	}
	dbManager->setUser(text);
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);
	nrkar = 67;
	kl = 138;
	klnr = 55;
	wz = 49;
	oc = 74;
	sp = 42;
	ma = 73;
	kol = 53;
	wkl = 76;
	s123 = 56;
	uz = 118;
	ha = 103;
	daty = 88;
	spnazproc = 89;
	ui->tableViewZam->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->toolBar->setIconSize(QSize(36, 36));
	dbManager = new BazaDanychManager();
	dialog = new UstawieniaForm(dbManager, this);
	dialogWybKlienta = new WybKlientaDialog(dbManager, this);
	dialogWybHandl = new WybHandlDialog(dbManager, this);
	dialogWybModel = new WybModelDialog(dbManager, this);
	dialognowyKlient = new nowyKlientDialog(this);
	dialognowyHandl = new NowyHandlowiecDialog(this);
	dialognowyModel = new nowyModelDialog(this);
	dialogNoweZamowienie = new noweZamowienieDialog(dialognowyHandl, dialogWybHandl,
			dbManager,
			dialogWybModel, dialogWybKlienta,
			dialognowyKlient, this);
	dialogKlienci = new klienciDialog(dialognowyKlient, dbManager, this);
	dialogHandl = new handlowceDialog(dialognowyHandl, dbManager, this);
	dialogwkladka = new wkladkaDialog(dbManager, this);
	dialogmodele = new modeleDialog(dialognowyModel, dbManager, this);
	dialogskory = new skoryDialog(dbManager, this);
	dialogkolory = new koloryDialog(dbManager, this);
	dialogspody = new spodyDialog(dbManager, this);
	dialogocieplenie = new ocieplenieDialog (dbManager, this);
	dialogmatryce = new matryceDialog(dbManager, this);
	dialogwzory = new wzoryDialog(dbManager, this);
	proxy = new QSortFilterProxyModel(this);
	proxy->setDynamicSortFilter(true);
	//logowanie();

	if (!dbManager->polacz()) {
		ustawieniaBazy();
	}

	//ui->comboBox->addItem(QString("KRAJALNIA"));
	//ui->comboBox->addItem(QString("SZWALNIA 1"));
	//ui->comboBox->addItem(QString("SZWALNIE ZEWNĘTRZNE"));
	//ui->comboBox->addItem(QString("SPODY"));
	//ui->comboBox->addItem(QString("MONTAŻ"));
	//ui->comboBox->addItem(QString("KOSZ"));

	ui->tableViewZam->setContextMenuPolicy(Qt::CustomContextMenu);
	podlaczSygnaly();
	aktualizujTabele();
	a();
	//ui->tableViewZam->setItemDelegate(new QSqlRelationalDelegate(ui->tableViewZam));
}

void MainWindow::aktualizujTabele() {
	proxy->setSourceModel(dbManager->getModelZamowienia());
	ui->tableViewZam->setModel(dbManager->getModelZamowienia());
	rozciagnijWiersze();
}

void MainWindow::a()
{
	//dialogNoweZamowienie->exec();
}

void MainWindow::stionResized(int logicalIndex, int oldSize, int newSize)
{
	switch (logicalIndex) {
		case 1:
		{	nrkar = newSize;
			ui->lineEditNrKarta->setFixedWidth(nrkar);
			break;
		}
		case 2:
			kl = newSize;
			ui->lineEditKlient->setFixedWidth(kl);
			break;
		case 3:
		{	klnr = newSize;
			ui->lineEditKlientN->setFixedWidth(klnr);
			break;
		}
		case 4:
			klnr = newSize;
			ui->lineEditKlientN->setFixedWidth(klnr);
			break;

		default:
			break;
	}
	this->repaint();
}

void MainWindow::ShowContextMenu(const QPoint &pos) {
	if (ui->actionEdycja->isChecked()) {
		QPoint globalPos = ui->tableViewZam->mapToGlobal(pos);
		// for QAbstractScrollArea and derived classes you would use:
		// QPoint globalPos = myWidget->viewport()->mapToGlobal(pos);
		QMenu myMenu;
		myMenu.addAction("WPROWADZONE");
		myMenu.addAction("DO ROZKROJU");
		myMenu.addAction("WYSŁANO");
		QAction *selectedItem = myMenu.exec(globalPos);
		if (selectedItem) {
			QModelIndexList selection = ui->tableViewZam->selectionModel()->selectedRows();
			int id = 0;
			bool sukces = true;
			for (int i = 0; i < selection.count(); i++)
			{
				QModelIndex index = selection.at(i);
				id = dbManager->getIdZamowieniaZTabeli(index);
				if (dbManager->aktualizujStatus(id, selectedItem->text()) == false) {
					sukces = false;
				}
			}
			if (sukces) {
				QMessageBox::information(this, "ZAKTUALIZOWANO",
							 QString(" <FONT COLOR='#000080'>Zmieniono na status %1.").arg(
								 selectedItem->text().toLower()),
							 QMessageBox::Ok);
				dbManager->getModelZamowienia()->select();
			}
		}
	}
}

void MainWindow::ustawieniaBazy() {
	if (dialog->exec() == QDialog::Accepted) {
		aktualizujTabele();
	}
}

void MainWindow::podlaczSygnaly() {
	connect(ui->akcjaUstawieniaBazy, SIGNAL(triggered()), this,
		SLOT(ustawieniaBazy()));
	connect(ui->actionDodajZamowienie , SIGNAL(triggered()), this,
		SLOT(dodajZam()));
	connect(ui->actionEdycja , SIGNAL(triggered()), this,
		SLOT(edytuj()));
	connect(ui->actionDrukuj_zam_wienia , SIGNAL(triggered()), this,
		SLOT(drukuj()));
	connect(ui->tableViewZam, SIGNAL(customContextMenuRequested(const QPoint &)),
		this,
		SLOT(ShowContextMenu(const QPoint &)));
	//connect((ui->radioButton, SIGNAL())
}

void  MainWindow::edytuj() {
	if (ui->actionEdycja->isChecked()) {
		ui->actionEdycja->setIcon(QIcon(":/zasoby/unlock.png"));
		ui->actionEdycja->setToolTip("Zablokuj edycję zamówień");
		ui->tableViewZam->setEditTriggers(QAbstractItemView::DoubleClicked);

	} else {
		ui->actionEdycja->setIcon(QIcon(":/zasoby/lock.png")) ;
		ui->actionEdycja->setToolTip("Odblokuj edycję zamówień");
		ui->tableViewZam->setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
}

void MainWindow::dodajZam() {
	if ( dialogNoweZamowienie->exec() == QDialog::Accepted ) {
		QMessageBox::information(this, "POWODZENIE",
					 " <FONT COLOR='#000080'>Dodano zamówienie. ",
					 QMessageBox::Ok);
	}
}

void MainWindow::rozciagnijWiersze() {
	for (int c = 10; c < 25;			++c) {
		ui->tableViewZam->setColumnWidth(c, 30);
	}

	ui->tableViewZam->setColumnWidth(1, nrkar);
	ui->lineEditNrKarta->setFixedWidth(nrkar);
	ui->tableViewZam->setColumnWidth(2, kl);
	ui->lineEditKlient->setFixedWidth(kl);

	ui->tableViewZam->setColumnWidth(3, klnr);
	ui->lineEditKlientN->setFixedWidth(klnr);

	ui->tableViewZam->setColumnWidth(4, wz);
	ui->tableViewZam->setColumnWidth(5, oc);
	ui->tableViewZam->setColumnWidth(6, sp);
	ui->tableViewZam->setColumnWidth(7, ma);
	ui->tableViewZam->setColumnWidth(8, kol);
	ui->tableViewZam->setColumnWidth(9, wkl);
	ui->tableViewZam->setColumnWidth(25, 46);// suma
	ui->lineEditWzor->setFixedWidth(wz);
	ui->lineEditO->setFixedWidth(oc);
	ui->lineEditSpod->setFixedWidth(sp);
	ui->lineEditMa->setFixedWidth(ma);
	ui->lineEditKol->setFixedWidth(kol);
	ui->lineEditWkl->setFixedWidth(wkl);
	ui->lineEdits1->setFixedWidth(s123);
	ui->lineEdits2->setFixedWidth(s123);
	ui->lineEdits3->setFixedWidth(s123);
	ui->lineEditUzy->setFixedWidth(uz);
	ui->lineEditHan->setFixedWidth(ha);
	ui->lineEditwpr->setFixedWidth(daty);
	ui->lineEditzre->setFixedWidth(daty);
	QHeaderView *hv = ui->tableViewZam->horizontalHeader();
	hv->setStretchLastSection(true);
	hv->setSectionHidden(0, true);
	hv->setSectionHidden(26, true);
	hv->setSectionHidden(34, true);
	hv->setSectionHidden(36, true);
	hv->setDefaultAlignment(Qt::AlignLeft);

	ui->tableViewZam->setColumnWidth(27, s123);// sk1
	ui->tableViewZam->setColumnWidth(28, s123);
	ui->tableViewZam->setColumnWidth(29, s123);
	ui->tableViewZam->setColumnWidth(30, spnazproc);
	ui->tableViewZam->setColumnWidth(31, spnazproc);
	ui->lineEditsnaz->setFixedWidth(spnazproc);
	ui->lineEditsprod->setFixedWidth(spnazproc);
	ui->tableViewZam->setColumnWidth(32, daty);
	ui->tableViewZam->setColumnWidth(33, daty);
	ui->tableViewZam->setColumnWidth(35, 70);
	ui->tableViewZam->setColumnWidth(36, uz);
	ui->tableViewZam->setColumnWidth(37, 62);
	ui->tableViewZam->setColumnWidth(38, ha);
	connect(hv, SIGNAL(sectionResized (int , int , int)), this,
		SLOT(stionResized (int ,
				   int , int)));
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_akcjaZamknij_triggered() {
	dbManager->rozlacz();
	close();
}

void MainWindow::on_tableViewZam_clicked(const QModelIndex &index) {
	dbManager->setIdZamowieniaModeleForMainWindow(index);

	ui->labelPodglad->clear();
	QSqlRelationalTableModel *model = dbManager->getModelZamowienia();
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

void MainWindow::dodajHandlowca() {
	if ( dialognowyHandl->exec() == QDialog::Accepted ) {
		dbManager->zachowajHandlowca(dialognowyHandl->getImie(),
						 dialognowyHandl->getNazwisko(), dialognowyHandl->getSkrot());
	}
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
	ZamowieniaDruk zamowienia;
	zamowienia.captions << "1" << "2" << "3" << "4";
	tworzacyDokument.dodajZamowienia(zamowienia);
	tworzacyDokument.populateDocumentUsingHtml(document);
}

void MainWindow::drukuj() {
	QPrinter printer;

	QMarginsF ma;
	//	ma.setTop(5.5);
	//	ma.setLeft(2.7);//0,95
	//printer.setPageMargins(ma);
	//if (pageSetup(&printer)) {
	printDocument(&printer);
}

void MainWindow::on_actionKlienci_triggered() {
	if (dialogKlienci->exec() == QDialog::Accepted ) {
	}
}

void MainWindow::on_actionModele_triggered() {
	if (dialogmodele->exec() == QDialog::Accepted ) {
	}
}

void MainWindow::ustawIFiltruj()
{
	dbManager->filterZamowien.nrZ = ui->lineEditNrKarta->text();
	dbManager->filterZamowien.mat = ui->lineEditMa->text();
	filtruj();
}

void MainWindow::on_pushButtonSzukaj_clicked() {
	ustawIFiltruj();
}

void MainWindow::filtruj() {
	dbManager->setZamowieniaFilter();
}

void MainWindow::on_radioButton_clicked() {
	dbManager->filterZamowien.status = QString("WPROWADZONE");
	filtruj();
}

void MainWindow::on_radioButton_2_clicked()
{
	dbManager->filterZamowien.status = QString("DO ROZKROJU");

	filtruj();
}

void MainWindow::on_radioButton_3_clicked()
{
	dbManager->filterZamowien.status = QString("WYSŁANO");
	filtruj();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Return) {
		ustawIFiltruj();
	}
	QMainWindow::keyPressEvent(event);
}

void MainWindow::on_actionDrukuj_zam_wienia_triggered()
{
	drukuj();
}

void MainWindow::on_radioButton_4_clicked() {
	dbManager->filterZamowien.status = QString("");
	filtruj();
}

void MainWindow::on_actionWzory_triggered()
{
	dialogwzory->exec();
}
