#include "noweZamowienieDialog.h"
#include "ui_noweZamowienieDialog.h"
#include "Delegate.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QDebug>
#include <QModelIndex>
noweZamowienieDialog::noweZamowienieDialog(NowyHandlowiecDialog *nh,
		WybHandlDialog *wybHandlDialog,
		BazaDanychManager *db, WybModelDialog *modeleDialog,
		WybKlientaDialog *dialog,
		nowyKlientDialog *nowyKliDialog,
		QWidget *parent) :
	QDialog(parent),
	dbManager(db),
	idZamowienia(0),
	modeleDialog(modeleDialog),
	dialog(dialog),
	dialogHandl(wybHandlDialog),
	nowyKliDialog(nowyKliDialog),
	nowyHandlDialog(nh),
	ui(new Ui::noweZamowienieDialog),
	zamowienie(0),
	ktoraPozycja(0)
{
	ui->setupUi(this);

	ui->lineEditPapier->setVisible(false);
	ui->lineEditPapier->setText("A");
	ui->checkBox->setChecked(false);

	ui->calendarWidget->setGridVisible(true);
	ui->calendarWidgetRealizacja->setGridVisible(true);
}

noweZamowienieDialog::~noweZamowienieDialog()
{
	delete ui;
}

void noweZamowienieDialog::obliczSume(QStandardItem *it)
{
	int suma = 0;
	int wszystkie = 0;
	int rzad = it->row();
	for (int i = 6; i < 21; i++) {
		suma += zamowienie->data(zamowienie->index(rzad, i),
					 Qt::DisplayRole).toInt();
	}
	zamowienie->setData(zamowienie->index(rzad, 21), QVariant(suma));

	for (int j = 0; j <  zamowienie->rowCount(); j++) {
		wszystkie += zamowienie->data(zamowienie->index(j, 21),
						  Qt::DisplayRole).toInt();
	}
	ui->lcdNumber->display(wszystkie);
}

void noweZamowienieDialog::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape) {
		wyczysc();
	}
	QDialog::keyPressEvent(event);
}

void noweZamowienieDialog::on_pushButton_5_clicked()
{
	if (dialog->exec() == QDialog::Accepted) {
		ui->labelKlient->setText(dialog->getAktualnyKlientNazwa());
	}
}

void noweZamowienieDialog::on_pushButton_6_clicked()
{
	if ( nowyKliDialog->exec() == QDialog::Accepted ) {
		Klient klient(nowyKliDialog->getNazwa(), nowyKliDialog->getSkrot(),
				  nowyKliDialog->getUlica(),
				  nowyKliDialog->getNumerDomu(),
				  nowyKliDialog->getMiasto(), nowyKliDialog->getKodPocztowy(),
				  nowyKliDialog->getTel1(),
				  nowyKliDialog->getTel2(),
				  nowyKliDialog->getFax(), nowyKliDialog->getMail(),
				  nowyKliDialog->getUwagi(),
				  nowyKliDialog->getNumerTelefonu());
		dbManager->zachowajKlienta(klient);
	}
}

void noweZamowienieDialog::wyczysc() {
	ui->calendarWidget->setSelectedDate(QDate::currentDate());
	ui->calendarWidgetRealizacja->setSelectedDate(QDate::currentDate());
	ui->labelKlient->clear();
	ui->labelHandlowiec->clear();
	ui->lineEditPapier->setText("A");
	ui->lineEditPapier->setVisible(false);
	ui->checkBox->setChecked(false);
	if (zamowienie != 0) {
		delete zamowienie;
		zamowienie = 0;
	}
}

void noweZamowienieDialog::on_buttonBox_accepted()
{
	if (ui->labelKlient->text().isEmpty()) {
		QMessageBox::warning( this, "BRAK WYMAGANYCH PÓL",
					  " <FONT COLOR='#000080'>Nie można zaakceptować bez wskazania klienta. ",
					  QMessageBox::Ok);
	} else if (ui->labelHandlowiec->text().isEmpty()) {
		QMessageBox::warning( this, "BRAK WYMAGANYCH PÓL",
					  " <FONT COLOR='#000080'>Nie można zaakceptować bez wskazania handlowca. ",
					  QMessageBox::Ok);
	} else {

		if (ui->checkBox->checkState() == Qt::Checked) {
			if (dbManager->zamowienie(ui->labelKlient->text(), ui->labelHandlowiec->text(),
						  ui->calendarWidget->selectedDate(),
						  ui->calendarWidgetRealizacja->selectedDate(), zamowienie,
						  ui->lineEditPapier->text())) {
				wyczysc();
				accept();
			}
			else {
				QMessageBox::warning( this, "NIEPOWODZENIE",
							  " <FONT COLOR='#000080'>Dodanie zamówienia nie powiodło się. ",
							  QMessageBox::Ok);
			}
		} else {
			if (dbManager->zamowienie(ui->labelKlient->text(), ui->labelHandlowiec->text(),
						  ui->calendarWidget->selectedDate(),
						  ui->calendarWidgetRealizacja->selectedDate(), zamowienie)) {
				wyczysc();
				accept();
			}
			else {
				QMessageBox::warning( this, "NIEPOWODZENIE",
							  " <FONT COLOR='#000080'>Dodanie zamówienia nie powiodło się. ",
							  QMessageBox::Ok);
			}
		}
	}
}

void noweZamowienieDialog::on_buttonBox_rejected() {
	wyczysc();
	reject();
}

void noweZamowienieDialog::on_pushButton_9_clicked() {
	if (dialogHandl->exec() == QDialog::Accepted) {
		ui->labelHandlowiec->setText(dialogHandl->getAktualnyHandlNazwa());
	}
}

void noweZamowienieDialog::ustawTabeleHeaders() {
	if (ktoraPozycja == 0) {
		for (int c = 0; c < ui->tableViewZam->horizontalHeader()->count(); ++c) {
			ui->tableViewZam->horizontalHeader()->setSectionResizeMode(c,
					QHeaderView::ResizeToContents);
		}
		QHeaderView *hv = ui->tableViewZam->horizontalHeader();
		hv->setStretchLastSection(true);
		for (int i = 0; i < 5; i++) {
			ui->tableViewZam->setItemDelegateForColumn(i,
					new NotEditableDelegate(ui->tableViewZam));
		}
		hv->setDefaultAlignment(Qt::AlignLeft);
	}
}

void noweZamowienieDialog::on_pushButtonModel_clicked() {
	if (modeleDialog->exec() == QDialog::Accepted) {
		QList<QStandardItem *> rzad = dbManager->zwrocWierszModel();
		zamowienie->insertRow(ktoraPozycja, rzad);
		ui->tableViewZam->setModel(zamowienie);
		ustawTabeleHeaders();
		ktoraPozycja++;
		QStringList listaZamowienia;
		listaZamowienia << "WZÓR" <<
				"MATRYCA " << "OCIEPLENIE" << "SPÓD" << "KOLOR" << "WKŁADKA" << "R36" << "R37"
				<< "R38"	<<
				"R39" << "R40"
				<< "R41" << "R42" << "R43"	<< "R44"
				<< "R45" << "R46" << "R47"	<< "R48" << "R49" << "R50"
				<< "SUMA" << "SK1" <<	"SK2" << "SK3" << "UWAGI" ;
		for (int i = 0; i < zamowienie->columnCount(); ++i) {
			zamowienie->setHeaderData(i, Qt::Horizontal, listaZamowienia[i]);
		}
	}
}

void noweZamowienieDialog::showEvent(QShowEvent *e) {
	Q_UNUSED(e);
	ktoraPozycja = 0;
	if (zamowienie == 0) {
		zamowienie = new QStandardItemModel();
		QObject::connect(zamowienie, SIGNAL(itemChanged(QStandardItem *)), this,
				 SLOT(obliczSume(QStandardItem *)));
	}
}

void noweZamowienieDialog::on_pushButton_7_clicked()
{
	if ( nowyHandlDialog->exec() == QDialog::Accepted ) {
		dbManager->zachowajHandlowca(nowyHandlDialog->getImie(),
						 nowyHandlDialog->getNazwisko(), nowyHandlDialog->getSkrot());
	}
}

void noweZamowienieDialog::on_checkBox_stateChanged(int arg1)
{
	if (arg1 == 0) {
		ui->lineEditPapier->setVisible(false);
	} else {
		ui->lineEditPapier->setVisible(true);
	}
}
