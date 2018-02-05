#include "wkladkaDialog.h"
#include "ui_wkladkaDialog.h"
#include <QInputDialog>
#include <QMessageBox>
wkladkaDialog::wkladkaDialog(BazaDanychManager *db, QWidget *parent) :
	QDialog(parent), dbManager(db),
	ui(new Ui::wkladkaDialog)
{
	ui->setupUi(this);	proxy = new QSortFilterProxyModel(this);
}

wkladkaDialog::~wkladkaDialog()
{
		delete ui;delete proxy;
	}

int wkladkaDialog::selectExec()
	{	ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
			SLOT(wybranoWkl(const QModelIndex)));
		return QDialog::exec();

	}

int wkladkaDialog::exec()
	{
		ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
		return QDialog::exec();

	}

void wkladkaDialog::wybranoWkl(const QModelIndex index)
	{
		QModelIndex  idx = proxy->mapToSource(
					   ui->tableView->selectionModel()->currentIndex());
		aktualnaWkladkaNazwa = dbManager->pobierzNazweAktualejWkladki(idx);
		accept();
	}

void wkladkaDialog::showEvent(QShowEvent *e)
{
	Q_UNUSED(e);
	dbManager->setWkladki();aktualizujTabele();
	ui->tableView->sortByColumn(0, Qt::AscendingOrder);
	}

void wkladkaDialog::hideEvent(QHideEvent *e)
	{
		disconnect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
			   SLOT(wybranoWkl(const QModelIndex)));
	}


QString wkladkaDialog::getAktualnaWkladkaNazwa() const{
		return aktualnaWkladkaNazwa;
}

void wkladkaDialog::aktualizujTabele() {
		proxy->setDynamicSortFilter(true);
		proxy->setSourceModel(dbManager->getWkladki());
		ui->tableView->setModel(proxy);
		ui->tableView->setSortingEnabled(true);
		for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c) {
			ui->tableView->horizontalHeader()->setSectionResizeMode(c,
					QHeaderView::ResizeToContents);
		}
		QHeaderView *hv = ui->tableView->horizontalHeader();
		hv->setStretchLastSection(true);
		hv->setSectionHidden(0, true);
		hv->setDefaultAlignment(Qt::AlignLeft);
	}

void wkladkaDialog::on_buttonBox_accepted()
{
accept();
}

void wkladkaDialog::on_buttonBox_rejected()
{
reject();
}

void wkladkaDialog::on_pushButton_2_clicked()
{
		QString text = QInputDialog::getText(this, tr("Dodaj wkładkę"),
											 tr("Podaj rodzaj wkładki"), QLineEdit::Normal, QString(""));

		if (text != QString("")) {
				dbManager->zachowajWkla(text);
			} else {
				QMessageBox::warning( this, "BRAK WYMAGANYCH PÓL",
							  " <FONT COLOR='#000080'>Nie można dodać wkładki bez podania rodzaju. ",
							  QMessageBox::Ok);
			}
}
