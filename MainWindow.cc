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
#include "Delegate.h"
#include <unistd.h>
#include <QTimer>

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
	nrkar = 58;
	kl = 84;
	klnr = 48;
	wz = 50;
	oc = 50;
	ma = 50;
	kol = 46;
	sp = 46;
	wkl = 52;
	s123 = 56;
	uz = 87;
	ha = 80;
	daty = 88;
	spnazproc = 74;

	//ui->tableViewZam->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->toolBar->setIconSize(QSize(36, 36));
	dbManager = new BazaDanychManager();
	dialog = new UstawieniaForm(dbManager, this);
	dialogzdj = new ZdjecieDialog(this);
	dialogzdj->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
	dialognowyKlient = new nowyKlientDialog(this);
	dialognowyHandl = new NowyHandlowiecDialog(this);
	dialogKlienci = new klienciDialog(dialognowyKlient, dbManager, this);
	dialogHandl = new handlowceDialog(dialognowyHandl, dbManager, this);
	dialogwkladka = new wkladkaDialog(dbManager, this);
	dialognskora = new nowaSkoraDialog(this);
	dialogskory = new skoryDialog(dialognskora, dbManager, this);
	dilogNowyKolor = new nowyKolorDialog(this);
	dialogkolory = new koloryDialog(dilogNowyKolor, dbManager, this);
	dialognspod = new nowySpodDialog(this);
	dialogspody = new spodyDialog(dialogzdj, dialognspod, dbManager, this);
	dialogocieplenie = new ocieplenieDialog (dbManager, this);

	nowaMatryca = new NowaMatrycaDialog(this);
	dialogmatryce = new matryceDialog(nowaMatryca, dbManager, this);
	dialonwzor = new nowywzorDialog(this);
	dialogwzory = new wzoryDialog(dialonwzor, dbManager, this);
	dialognowyModel = new NowyModelDialog(dialogwkladka,
						  dialogocieplenie, dialogwzory,
						  dialogskory, dialogkolory,
						  dialogspody, dialogmatryce, dbManager ,
						  this);
	dialogmodele = new modeleDialog(dialogzdj, dialognowyModel, dbManager, this);

	dialogNoweZamowienie = new noweZamowienieDialog(dialogHandl, dbManager, dialogmodele, dialogKlienci, this);
	rozkroje = new RozkrojeDialog(this);
	dorozkroku = new DoRozkrojuDialog(this);

	proxy = new QSortFilterProxyModel(this);
	//logowanie();

	if (!dbManager->polacz()) {
		ustawieniaBazy();
	}

	ui->actionDrukuj_zam_wienia->setEnabled(false);
	ui->tableViewZam->setContextMenuPolicy(Qt::CustomContextMenu);
	podlaczSygnaly();
	a();
	aktualizujTabele();
	createCombos();
	//dbManager->filterZamowien.status = QString("KRÓJ");
	dbManager->filterZamowien.status = QString("WPROWADZONE");
	filtruj();
	connect(dbManager->getModelZamowienia(), SIGNAL(dataChanged(const QModelIndex &,
			const QModelIndex &, const QVector<int> &)), this,
		SLOT(updateZamSum(const QModelIndex &, const QModelIndex &,
				  const QVector<int> &)));
	connect(dbManager->getModelZamowienia(), SIGNAL(beforeUpdate(int,
			QSqlRecord &)), this,
		SLOT(beforeupdate(int, QSqlRecord &)));

	setSumaZamowien();

	//ui->tableViewZam->selectRow(2);
	//on_actionDrukuj_zam_wienia_triggered();
	//exit(1);
}

void MainWindow::aktualizujTabele() {
	proxy->setSourceModel(dbManager->getModelZamowienia());
	proxy->setDynamicSortFilter(true);
	ui->tableViewZam->setModel(proxy);
	rozciagnijWiersze();
}

void MainWindow::a() {
	//if (	dialogmodele->exec() == QDialog::Accepted) {
	//		if (	dialognowyModel->exec() == QDialog::Accepted) {
	//}
	//dialogNoweZamowienie->exec();
}

void MainWindow::refreshTable() {
	dbManager->getModelZamowienia()->select();
	dbManager->updateKlientZamOde();
	setSumaZamowien();
}

void MainWindow::beforeupdate(int row, QSqlRecord &record) {
	dbManager->updateRozmSuma = record.value(25).toInt();
	dbManager->updateRozmIdKli = record.value(3).toInt();
	dbManager->updateRozmIdZam = record.value(0).toInt();
}

void MainWindow::setSumaZamowien() {
	ui->labelSuma->setText(QString::number(dbManager->zwrocSumeZamowien()));
}

void MainWindow::updateZamSum(const QModelIndex &topLeft, const QModelIndex &bot,
				  const QVector<int> &) {
	if (bot.column() != 46) {
		QTimer::singleShot(100, this, SLOT(refreshTable()));
	}
}

void MainWindow::stionResized(int logicalIndex, int oldSize, int newSize) {
	switch (logicalIndex) {
		case 1:
		{	nrkar = newSize;
			ui->lineEditNrKarta->setFixedWidth(nrkar);
			break;
		}
		case 2:
			kl = newSize;
			ui->lineEditKlientN->setFixedWidth(kl);
			break;
		case 3:
		{	klnr = newSize;
			ui->lineEditKlient->setFixedWidth(klnr);
			break;
		}
		case 4:
			wz = newSize;
			ui->lineEditWzor->setFixedWidth(wz);
			break;
		case 5:
			sp = newSize;
			ui->lineEditS->setFixedWidth(sp);
			break;
		case 6:
			kol = newSize;
			ui->lineEditKol->setFixedWidth(kol);
			break;
		case 7:
			oc = newSize;
			ui->lineEditO->setFixedWidth(oc);
			break;
		case 8:
			ma = newSize;
			ui->lineEditMa->setFixedWidth(ma);
			break;
		case 9:
			wkl = newSize;
			ui->lineEditWkl->setFixedWidth(wkl);
			break;
		case 26:
			ui->lineEdits1->setFixedWidth(newSize);
			break;
		case 27:
			ui->lineEdits2->setFixedWidth(newSize);
			break;
		case 28:
			ui->lineEdits3->setFixedWidth(newSize);
			break;
		case 29:
			ui->lineEditsnaz->setFixedWidth(newSize);
			break;
		case 30:
			ui->lineEditsprod->setFixedWidth(newSize);
			break;
		case 31:
			ui->lineEditUzy->setFixedWidth(newSize);
			break;
		case 32:
			ui->lineEditHan->setFixedWidth(newSize);
			break;
		case 33:
			ui->lineEditwpr->setFixedWidth(newSize);
			break;
		case 34:
			ui->lineEditzre->setFixedWidth(newSize);
			break;
		default:
			break;
	}
	this->repaint();
}

void MainWindow::ShowContextMenu(const QPoint &pos) {
	if (!ui->actionEdycja->isChecked()) {
		QPoint globalPos = ui->tableViewZam->mapToGlobal(pos);
		QMenu myMenu;
		if (dbManager->filterZamowien.status == QString("WPROWADZONE")) {
			myMenu.addAction("KRÓJ");
			myMenu.addAction("DO WYSYŁKI");
		} else if (dbManager->filterZamowien.status == QString("DO WYSYŁKI")) {
			myMenu.addAction("ZREALIZUJ");
			myMenu.addAction("USUŃ");
		}
		myMenu.addSeparator();
		myMenu.addAction("ZMIEŃ MODEL");
		myMenu.addAction("ZMIEŃ KLIENTA");
		myMenu.addAction("ZMIEŃ HANDLOWCA");

		QAction *selectedItem = myMenu.exec(globalPos);
		if (selectedItem) {
			QModelIndexList selection = ui->tableViewZam->selectionModel()->selectedRows();
			QModelIndex  idx = proxy->mapToSource(
						   ui->tableViewZam->selectionModel()->currentIndex());
			if ( selectedItem->text() == QString("ZMIEŃ KLIENTA")) {
				if (dialogKlienci->selectExec() == QDialog::Accepted) {
					QString nr_zam =  dbManager->getModelZamowienia()->data(
								  dbManager->getModelZamowienia()->index(idx.row(),
										  1)).toString();
					dbManager->zmienKlientaZam(nr_zam);
				}
			} else if (selectedItem->text() == QString("ZMIEŃ MODEL")) {
				if (dialogmodele->selectExec() == QDialog::Accepted) {
					int id = dbManager->getModelZamowienia()->data(
							 dbManager->getModelZamowienia()->index(idx.row(),
									 0)).toInt();
					dbManager->zmienModellZam(id);
				}
			} else if (selectedItem->text() == QString("ZMIEŃ HANDLOWCA")) {
				if (dialogHandl->selectExec() == QDialog::Accepted) {
					QString nr_zam =  dbManager->getModelZamowienia()->data(
								  dbManager->getModelZamowienia()->index(idx.row(),
										  1)).toString();
					dbManager->zmienHandlZam(nr_zam);
				}
			} else if (selectedItem->text() == QString("KRÓJ")) {
				if (QMessageBox::question(this, "ZMODYFIKOWAĆ?",
							  " <FONT COLOR='#000080'>Czy pomniejszyć o stany magazynowe?") == QMessageBox::Yes) {
					QModelIndexList selection = ui->tableViewZam->selectionModel()->selectedRows();
					std::vector<int> zamowienia;
					int id = 0;
					for (int i = 0; i < selection.count(); i++) {
						QModelIndex index = proxy->mapToSource(selection.at(i));
						id = dbManager->getIdZamowieniaZTabeli(index);
						zamowienia.push_back(id);
					}
					QAbstractItemModel *mod = dynamic_cast<QAbstractItemModel *>(dbManager->getDoRozkroju(zamowienia));
					dorozkroku->setModel(mod);
					//dorozkroku->setZamowienia(zamowienia);
					dorozkroku->exec();
				} else {

				}
			} else	{
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
								 QString(" <FONT COLOR='#000080'>Przeniesiono %1 pozycji do <FONT COLOR='#0f00f0'><b>%2.").arg(
									 QString::number(selection.count()), selectedItem->text().toLower()),
								 QMessageBox::Ok);
					dbManager->getModelZamowienia()->select();
				}
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
	connect(ui->actionEdycja, SIGNAL(triggered()), this,
		SLOT(edytuj()));
	connect(ui->tableViewZam, SIGNAL(customContextMenuRequested(const QPoint &)),
		this,
		SLOT(ShowContextMenu(const QPoint &)));
}

void  MainWindow::edytuj() {
	if (ui->actionEdycja->isChecked()) {
		ui->actionEdycja->setIcon(QIcon(":/zasoby/unlock.png")) ;
		ui->tableViewZam->setEditTriggers(QAbstractItemView::DoubleClicked);
		ui->actionEdycja->setToolTip("Zablokuj edycję zamówień");
	} else {
		ui->actionEdycja->setIcon(QIcon(":/zasoby/lock.png"));
		ui->actionEdycja->setToolTip("Odblokuj edycję zamówień");
		ui->tableViewZam->setEditTriggers(QAbstractItemView::NoEditTriggers);
	}
}

void MainWindow::dodajZam() {
	dialogNoweZamowienie->setFixedSize(dialogNoweZamowienie->size());
	if ( dialogNoweZamowienie->exec() == QDialog::Accepted ) {
		ui->tableViewZam->sortByColumn(0, Qt::DescendingOrder);
		QMessageBox::information(this, "POWODZENIE",
					 " <FONT COLOR='#000080'>Dodano zamówienie. ",
					 QMessageBox::Ok);
	}
}

void MainWindow::rozciagnijWiersze() {
	for (int c = 9; c < 25;			++c) {
		ui->tableViewZam->setColumnWidth(c, 30);
	}

	ui->tableViewZam->setColumnWidth(1, nrkar);
	ui->lineEditNrKarta->setFixedWidth(nrkar);

	ui->tableViewZam->setColumnWidth(2, kl);
	ui->lineEditKlient->setFixedWidth(kl);

	ui->tableViewZam->setColumnWidth(3, klnr);
	ui->lineEditKlientN->setFixedWidth(klnr);

	ui->tableViewZam->setColumnWidth(4, wz);
	ui->tableViewZam->setColumnWidth(5, sp);
	ui->tableViewZam->setColumnWidth(6, kol);
	ui->tableViewZam->setColumnWidth(7, oc);
	ui->tableViewZam->setColumnWidth(8, ma);
	ui->tableViewZam->setColumnWidth(9, wkl);

	ui->tableViewZam->setColumnWidth(25, 43); // suma
	ui->lineEditWzor->setFixedWidth(wz);
	ui->lineEditO->setFixedWidth(oc);
	ui->lineEditMa->setFixedWidth(ma);
	ui->lineEditKol->setFixedWidth(kol);
	ui->lineEditNrKarta->setFixedWidth(nrkar);
	ui->lineEditKlient->setFixedWidth(klnr);
	ui->lineEditKlientN->setFixedWidth(kl);
	ui->lineEditWkl->setFixedWidth(wkl);
	ui->lineEditS->setFixedWidth(sp);
	ui->lineEdits1->setFixedWidth(s123);
	ui->lineEdits2->setFixedWidth(s123);
	ui->lineEdits3->setFixedWidth(s123);
	ui->lineEditUzy->setFixedWidth(uz);
	ui->lineEditHan->setFixedWidth(ha);
	ui->lineEditwpr->setFixedWidth(daty);
	ui->lineEditzre->setFixedWidth(daty);
	QHeaderView *hv = ui->tableViewZam->horizontalHeader();
	hv->setSectionHidden(0, true);
	hv->setStretchLastSection(true);
	for (int i = 38; i < 47; i++) {
		hv->setSectionHidden(i, true);
	}
	hv->setDefaultAlignment(Qt::AlignLeft);
	ui->tableViewZam->setColumnWidth(26, s123);// sk1
	ui->tableViewZam->setColumnWidth(27, s123);
	ui->tableViewZam->setColumnWidth(28, s123);
	ui->tableViewZam->setColumnWidth(29, spnazproc);
	ui->tableViewZam->setColumnWidth(30, spnazproc);
	ui->tableViewZam->setColumnWidth(31, uz);
	ui->tableViewZam->setColumnWidth(32, ha);
	ui->lineEditsnaz->setFixedWidth(spnazproc);
	ui->lineEditsprod->setFixedWidth(spnazproc);
	ui->tableViewZam->setColumnWidth(33, daty);
	ui->tableViewZam->setColumnWidth(34, daty);
	ui->tableViewZam->setColumnWidth(37, 25);
	connect(hv, SIGNAL(sectionResized (int , int , int)), this,
		SLOT(stionResized (int ,
				   int , int)));
	NotEditableDelegate *del = new NotEditableDelegate(this);
	for (int i = 0; i < 10; i++) {
		ui->tableViewZam->setItemDelegateForColumn(i, del);
	}
	for (int i = 25; i < 33; i++) {
		ui->tableViewZam->setItemDelegateForColumn(i, del);
	}
	ui->tableViewZam->setItemDelegateForColumn(37, del);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::on_akcjaZamknij_triggered() {
	dbManager->rozlacz();
	close();
}

void MainWindow::on_tableViewZam_clicked(const QModelIndex &index) {
	ui->labelPodglad->clear();
	QModelIndex  idx = proxy->mapToSource(
				   ui->tableViewZam->selectionModel()->currentIndex());
	int id =  dbManager->getModelZamowienia()->data(
			  dbManager->getModelZamowienia()->index(idx.row(),
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
						 dialognowyHandl->getNazwisko(), dialognowyHandl->getSkrot(),
						 dialognowyHandl->getUwagi());
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

void MainWindow::printDocument(QPrinter *printer) {
	QTextDocument document;
	dodajZamowieniaDoHtml(&document);
	document.print(printer);
}

QString MainWindow::zamowienieTabelka(zamowienieZRozmiaramiStruct zamowienie) {
	QString wynik =
		QString("<td><table border=1 cellpadding=0 cellspacing=-1 style=\"border-width: 1px; border-collapse: collapse;font-family:'Times New Roman', serif;font-size: 10px;\">"
			"<tr valign=top>"
			"<td width=81 height=84 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\"><p  >DATA:</p>"
			"<p style=\"font-size: 13px;\">%1&nbsp;&nbsp;&nbsp;&nbsp;%2</p>"
			"</td>"
			"<td colspan=2 width=193 height=84 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\"><p >ZAM&#211;WIENIE:</p><p style=\"font-size: 13px;\">%3</p>"
			"</td>"
			"<td width=118 height=84 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px;\"><p >ZLECAJ&#260;CY:</p><p style=\"font-size: 13px;\">%4</p>"
			"</td>"
			"</tr>"
			"<tr valign=top>"
			"<td width=81 height=84 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\"><p >WZ&#211;R:</p><p style=\" font-size: 13px;\">%5</p>"
			"</td>"
			"<td width=54 height=84 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px;  border-right: none;\"><p>SPODY:</p><p style=\"font-size: 13px;\">%6</p>"
			"</td>"
			"<td width=68 height=84 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\"><p >KOLOR SK&#211;RA</p><p style=\"font-size: 13px;\">%7</p>"
			"</td>"
			"<td width=81 height=84 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px;\"><p >SZARFIARZ:</p><p style=\";font-size: 13px;\"></p></span></p>"
			"</td>"
			"</tr>").arg(zamowienie.wpr.toHtmlEscaped(), zamowienie.rea.toHtmlEscaped(), zamowienie.nrZ.toHtmlEscaped(),
					 zamowienie.klNaz.toHtmlEscaped(), zamowienie.wzor.toHtmlEscaped(), zamowienie.snaz.toHtmlEscaped(),
					 zamowienie.kolor.toHtmlEscaped());

	QMap<QString, int> rozm;
	int suma = zamowienie.rozmiary[15];
	for (int i = 0; i < 15; i++) {
		int id = 36 + i;
		rozm.insert(QString("R %1").arg(id),
				zamowienie.rozmiary[i]);
	}

	for (QMap<QString, int>::iterator it = rozm.begin(); it != rozm.end(); ) {
		if ((*it) == 0) {
			rozm.erase(it++);
		} else {
			++it;
		}
	}

	for (QMap<QString, int>::iterator it = rozm.begin(); it != rozm.end(); it++) {
		qDebug() << it.key() << it.value();
	}

	//wynik += QString (
	//			  < / td > ");
	//QString zamowienieStr = QString(% 1").arg(suma);
	wynik += QString("<tr valign=top>"
			 "<td colspan=2 rowspan=2 width=174 height=29 valign=top style=\"border-width : 0px; border-color: #000000; border-style: solid; padding: 0px; border-top: none; border-right: none;\">"
			 "<table border=1 cellpadding=9 cellspacing=-1 style=\"border-collapse: collapse;font-family:'Times New Roman', serif;font-size: 14px;\">"
			 "<tr>"
			 "<td ><u>R36</u><br>1</td>"
			 " <td><u>R37</u></u><br>8</td><td><p><u>R38</u><br>21</p></td><td><p><u>R39</u><br>10</p></td>"
			 " <td border=1 style=\"border-width: 3px; border-color: #000000; border-style: solid; \"><u>R43</u></u><br>8</td><td><p><u>R46</u><br>21</p></td><td><p><u>R47</u><br>10</p></td>"
			 " <td border=1  style=\"border-width : 3px; border-color: #000000; border-style: solid; \"><u>R48</u><br>18</td></tr>"

			 "<tr>"
			 "<td><u>R49</u><br>1</td>"
			 " <td><u>R50</u></u><br>8</td>"
			 "</tr>"

			 "</table>"

			 "</td>"
			 "<td rowspan=2 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-top: none; border-right: none;\">SUMA:</td>"
			 "<td width = 128 height = 48 valign = top style = \"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-top: none;\"><p>PRZYJMUJ&#260;CY:</p><p style=\"font-size: 13px;\"></p>"
			 " </td> </tr> "
			 "<tr valign = top>"
			 "<td width = 128 height = 48 valign = top style = \"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-top: none;\"><p>MONTA&#379;:</p><p style=\"font-size: 13px;\"></p>"
			 " </td> </tr> "
			 "<tr valign = top>"
			 "<td colspan = 4 width = 530 height = 54 valign = top style = \"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-top: none;\"><p>UWAGI 1: < / p > <p style = \"font-size: 13px;\">jakies uwagi < / p > "
			 " </td > </tr> "
			 "<tr>"
			 "<td colspan = 4 width = 530 height = 54 valign = top style = \"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-top: none;\"><p>UWAGI 2: < / p > <p style = \"font-size: 13px;\">jakies uwagi < / p > "
			 " </td > </tr></table ></td >").arg(zamowienie.nrZ.toHtmlEscaped(),
					 zamowienie.klNaz.toHtmlEscaped());

	return wynik;
}

void MainWindow::dodajZamowieniaDoHtml(QTextDocument *document) {
	QString html("<html><head><meta content=\"text/html\"><style type=\"text/css\"></style></head><body><div>"
			 "	<table>"
			 "<tr>");
	int counter = 0;
	for (zamowienieZRozmiaramiStruct zamowienie : zamowieniaDruk) {
		if (counter % 2 == 0) {
			html += "<tr>\n";
		}
		if (!zamowienie.rozmiary.isEmpty()) {
			html += zamowienieTabelka(zamowienie);
		}
		if (counter % 2 != 0) {
			html += " < / tr > \n";
		}
		counter++;
	}

	html += "</table></div > "
		"<p><span class = rvts3><br> </span > </p > "
		" </body> </html > ";
	document->setHtml(html);
}

void MainWindow::oznaczDrukowano() {
	for (int i : idDrukowanychZam) {
		dbManager->oznaczDrukowano(i);
	}
	dbManager->getModelZamowienia()->select();
}

void MainWindow::ustawCombo(QString tabela, QComboBox *com) {
	com->clear();
	QString q = QString("select * from %1").arg(tabela);
	QSqlQuery query (q);
	QAbstractItemModel *vModel = dbManager->getModelForQuery(&query);
	com->addItem(QString(""), QVariant(0));
	if (vModel) {
		for (int i = 0; i < vModel->rowCount(); ++i) {
			QString vEventName = vModel->data(vModel->index(i, 1)).toString();
			QVariant vEventMnemonic = vModel->data(vModel->index(i, 0));
			com->addItem(
				vEventName,
				vEventMnemonic);
		}
		delete vModel;
	}
}

void MainWindow::createCombos() {
	ustawCombo("rodzaj_montazu", ui->comboBoxmont);
	ustawCombo("typ", ui->comboBoxtyp);
	ustawCombo("rodzaj_buta", ui->comboBoxb1);
	ustawCombo("rodzaj_buta_2", ui->comboBoxb2);
	ustawCombo("rodzaj_buta_3", ui->comboBoxb3);
	ustawCombo("rodzaj_buta_4", ui->comboBoxb4);
	ustawCombo("rodzaj_buta_5", ui->comboBoxb5);
	ustawCombo("rodzaj_buta_6", ui->comboBoxb6);
}

void MainWindow::drukuj() {
	QPrinter printer;
	QMarginsF ma;
	ma.setTop(0);
	ma.setLeft(0);
	ma.setBottom(0);
	ma.setRight(0);
	printer.setPageMargins(ma);
	printer.setFullPage(true);
	//if (pageSetup(&printer)) {
	printDocument(&printer);
	oznaczDrukowano();

	//	} else {
	//		qDebug() << "anulowane";
	//	}
	zamowieniaDruk.clear();
	idDrukowanychZam.clear();
}

void MainWindow::on_actionKlienci_triggered() {
	dialogKlienci->setFixedSize(dialogKlienci->size());
	if (dialogKlienci->exec() == QDialog::Accepted ) {
	}
}

void MainWindow::on_actionModele_triggered() {
	dialogmodele->setFixedSize(dialogmodele->size());
	if (dialogmodele->exec() == QDialog::Accepted ) {
	}
}

void MainWindow::ustawIFiltruj() {
	dbManager->filterZamowien.nrZ = ui->lineEditNrKarta->text();
	dbManager->filterZamowien.klNaz = ui->lineEditKlientN->text();
	dbManager->filterZamowien.klNr = ui->lineEditKlient ->text();
	dbManager->filterZamowien.ociep = ui->lineEditO->text();
	dbManager->filterZamowien.wzor = ui->lineEditWzor->text();
	dbManager->filterZamowien.kolor = ui->lineEditKol->text();
	dbManager->filterZamowien.mat = ui->lineEditMa->text();
	dbManager->filterZamowien.wkladka = ui->lineEditWkl ->text();
	dbManager->filterZamowien.uzyt = ui->lineEditUzy->text();
	dbManager->filterZamowien.sk1 = ui->lineEdits1 ->text();
	dbManager->filterZamowien.sk2 = ui->lineEdits2 ->text();
	dbManager->filterZamowien.sk3 = ui->lineEdits3 ->text();
	dbManager->filterZamowien.ha = ui->lineEditHan ->text();
	dbManager->filterZamowien.snaz = ui->lineEditsnaz ->text();
	dbManager->filterZamowien.sprod = ui->lineEditsprod ->text();
	dbManager->filterZamowien.wpr = ui->lineEditwpr ->text();
	dbManager->filterZamowien.rea = ui->lineEditzre ->text();
	dbManager->filterZamowien.spn = ui->lineEditS->text();
	filtruj();

}

void MainWindow::on_pushButtonSzukaj_clicked() {
	ustawIFiltruj();
}


void MainWindow::filtruj() {
	dbManager->setZamowieniaFilter();
	setSumaZamowien();
}

void MainWindow::on_radioButton_clicked() {
	dbManager->filterZamowien.status = QString("WPROWADZONE");
	ui->actionDrukuj_zam_wienia->setEnabled(false);
	filtruj();
}

void MainWindow::on_radioButton_3_clicked() {
	dbManager->filterZamowien.status = QString("DO WYSYŁKI");
	ui->actionDrukuj_zam_wienia->setEnabled(false);
	filtruj();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Return) {
		ustawIFiltruj();
	}
	QMainWindow::keyPressEvent(event);
}

void MainWindow::stworzListeZamowien() {
	QModelIndexList selection = ui->tableViewZam->selectionModel()->selectedRows();
	std::vector<zamowienieZRozmiaramiStruct> zamowienia;
	int id = 0;
	for (int i = 0; i < selection.count(); i++) {
		QModelIndex index = proxy->mapToSource(selection.at(i));
		id = dbManager->getIdZamowieniaZTabeli(index);
		zamowieniaDruk.append(dbManager->stworzZamowienieZBazy(id));
		idDrukowanychZam.append(id);
	}
}

void MainWindow::on_actionDrukuj_zam_wienia_triggered() {
	stworzListeZamowien();
	drukuj();
}

void MainWindow::on_radioButton_4_clicked() {
	//	dbManager->filterZamowien.status = QString("");
	//	ui->actionDrukuj_zam_wienia->setEnabled(false);
	filtruj();
}

void MainWindow::on_actionWzory_triggered() {
	dialogwzory->exec();
}

void MainWindow::on_actionMatryce_triggered() {
	dialogmatryce->exec();
}

void MainWindow::on_actionHandlowce_triggered() {
	dialogHandl->exec();
}

void MainWindow::on_actionSk_ry_triggered() {
	dialogskory->exec();
}

void MainWindow::on_actionSpody_triggered() {
	dialogspody->setFixedSize(dialogspody->size());
	dialogspody->exec();
}

void MainWindow::on_actionKolory_triggered()
{
	dialogkolory->exec();
}

void MainWindow::on_actionWk_adki_triggered()
{
	dialogwkladka->exec();
}

void MainWindow::on_comboBoxtyp_activated(const QString &arg1) {
	dbManager->filterZamowien.typ = ui->comboBoxtyp->currentText();
	filtruj();
}

void MainWindow::on_comboBoxmont_activated(const QString &arg1) {
	dbManager->filterZamowien.mont = ui->comboBoxmont->currentText();
	filtruj();
}

void MainWindow::on_comboBoxb1_activated(const QString &arg1)
{
	dbManager->filterZamowien.r1 = ui->comboBoxb1->currentText();
	filtruj();
}

void MainWindow::on_comboBoxb2_activated(const QString &arg1) {
	dbManager->filterZamowien.r2 = ui->comboBoxb2->currentText();
	filtruj();
}

void MainWindow::on_comboBoxb3_activated(const QString &arg1) {
	dbManager->filterZamowien.r3 = ui->comboBoxb3->currentText();
	filtruj();

}

void MainWindow::on_comboBoxb4_activated(const QString &arg1) {
	dbManager->filterZamowien.r4 = ui->comboBoxb4->currentText();
	filtruj();

}

void MainWindow::on_comboBoxb5_activated(const QString &arg1) {
	dbManager->filterZamowien.r5 = ui->comboBoxb5->currentText();
	filtruj();
}

void MainWindow::on_comboBoxb6_activated(const QString &arg1) {
	dbManager->filterZamowien.r6 = ui->comboBoxb6->currentText();
	filtruj();
}

void MainWindow::on_pushButton_clicked() {
	ui->lineEditNrKarta->clear();
	ui->lineEditWzor->clear();
	ui->lineEditO->clear();
	ui->lineEditKlientN->clear();
	ui->lineEditKlient->clear();
	ui->lineEditMa->clear();
	ui->lineEditKol->clear();
	ui->lineEditWkl->clear();
	ui->lineEdits1->clear();
	ui->lineEdits2->clear();
	ui->lineEdits3->clear();
	ui->lineEditUzy->clear();
	ui->lineEditHan->clear();
	ui->lineEditwpr->clear();
	ui->lineEditzre->clear();
	ui->lineEditS->clear();
	ui->lineEditsnaz->clear();
	ui->lineEditsprod->clear();
	dbManager->filterZamowien.r1 = QString("");
	dbManager->filterZamowien.r2 = QString("");
	dbManager->filterZamowien.r3 = QString("");
	dbManager->filterZamowien.r4 = QString("");
	dbManager->filterZamowien.r5 = QString("");
	dbManager->filterZamowien.r6 = QString("");
	dbManager->filterZamowien.mont = QString("");
	dbManager->filterZamowien.typ = QString("");
	ui->comboBoxtyp->setCurrentIndex(0);
	ui->comboBoxmont->setCurrentIndex(0);
	ui->comboBoxb1->setCurrentIndex(0);
	ui->comboBoxb2->setCurrentIndex(0);
	ui->comboBoxb3->setCurrentIndex(0);
	ui->comboBoxb4->setCurrentIndex(0);
	ui->comboBoxb5->setCurrentIndex(0);
	ui->comboBoxb6->setCurrentIndex(0);
	ustawIFiltruj();
}

void MainWindow::on_actionOcieplenia_triggered() {
	dialogocieplenie->exec();
}

void MainWindow::on_radioButton_5_clicked()
{
	dbManager->filterZamowien.status = QString("ZREALIZUJ");
	ui->actionDrukuj_zam_wienia->setEnabled(false);
	filtruj();
}

