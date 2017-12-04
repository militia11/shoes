#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QCloseEvent>
#include <QSettings>

#include "nowyKlientDialog.h"
#include "Klient.h"
#include "noweZamowienieDialog.h"

void MainWindow::setTables()
{
	podlaczSygnaly();
	ui->tableViewZam->setModel(dbManager->getModelZamowienia());
	ui->tableViewKlienci->setModel(dbManager->getModelKlienci());
	rozciagnijWiersze(ui->tableViewKlienci);
	rozciagnijWiersze(ui->tableViewZam);
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow) {
	ui->setupUi(this);
	dbManager = new BazaDanychManager();
	dialog = new UstawieniaForm(dbManager, this);
	if (!dbManager->ponowniePolacz()) {
		ustawieniaBazy();
	}
	setTables();
}

void MainWindow::ustawieniaBazy() {
	if ( dialog->exec() == QDialog::Accepted ) {
		podlaczSygnaly();
		ui->tableViewZam->setModel(dbManager->getModelZamowienia());
		ui->tableViewKlienci->setModel(dbManager->getModelKlienci());
		rozciagnijWiersze(ui->tableViewKlienci);
		rozciagnijWiersze(ui->tableViewZam);
	}//dialog->exec();
}

void MainWindow::podlaczSygnaly() {
	connect(ui->akcjaUstawieniaBazy, SIGNAL(triggered()), this,
		SLOT(ustawieniaBazy()));
}

void MainWindow::on_pushButton_2_clicked() {
	nowyKlientDialog dialog(this);
	if ( dialog.exec() == QDialog::Accepted ) {
		Klient klient(dialog.getNazwa(), dialog.getSkrot(), dialog.getUlica(),
			      dialog.getNumerDomu(),
			      dialog.getMiasto(), dialog.getKodPocztowy(), dialog.getTel1(), dialog.getTel2(),
			      dialog.getFax(), dialog.getMail(), dialog.getUwagi(),
			      dialog.getNumerTelefonu());
		dbManager->zachowajKlienta(klient);
	}
}
void MainWindow::on_pushButton_clicked() {
	noweZamowienieDialog dialog(this);
	if ( dialog.exec() == QDialog::Accepted ) {
		dbManager->zamowienie();//dialog.getKlient()
	}
}

void MainWindow::rozciagnijWiersze(QTableView *m) {
	//	for (int c = 0; c < m->horizontalHeader()->count(); ++c) {
	//		m->horizontalHeader()->setSectionResizeMode(c, QHeaderView::ResizeToContents);
	//	}
	//	QHeaderView* hv = m->horizontalHeader();
	//	hv->setStretchLastSection(true);
	//	hv->setSectionHidden(0, true);
	//	hv->setDefaultAlignment(Qt::AlignLeft);

	// raczej gorsze
	//	for (int c = 0; c < m->horizontalHeader()->count(); ++c) {
	//		m->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
	//	}
	//	QHeaderView* hv = m->horizontalHeader();
	//	hv->setStretchLastSection(true);
	//	hv->setSectionHidden(0, true);
	//	hv->setDefaultAlignment(Qt::AlignLeft);

	//	for (int c = 0; c < m->horizontalHeader()->count(); ++c) {
	//		m->horizontalHeader()->setSectionResizeMode(c, QHeaderView::Stretch);
	//	}
	QHeaderView *hv = m->horizontalHeader();
	hv->setStretchLastSection(true);
	hv->setSectionHidden(0, true);
	hv->setDefaultAlignment(Qt::AlignLeft);

	// hv->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow() {
	delete ui;
}


void MainWindow::on_akcjaZamknij_triggered()
{
	dbManager->rozlacz();
	close();
}