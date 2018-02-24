#include "RozkrojeDialog.h"
#include "ui_RozkrojeDialog.h"
#include "NaglowkiZamowienia.h"
RozkrojeDialog::RozkrojeDialog(BazaDanychManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RozkrojeDialog), dbManager(db), vModel(nullptr) {
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    dodanoRozkroj = false;
}

RozkrojeDialog::~RozkrojeDialog() {
    delete ui;
    delete proxy;
    if (vModel)
        delete vModel;
}

void RozkrojeDialog::deleteOldModel() {
    QAbstractItemModel *old = ui->tableViewSzczegoly->model();
    if (old) {
        delete old;
        old = 0;
    }
}

void RozkrojeDialog::setDodanoRozkroj(bool value) {
    dodanoRozkroj = value;
}

void RozkrojeDialog::on_tableView_clicked(const QModelIndex &index) {
    deleteOldModel();
    QModelIndex  idx = proxy->mapToSource(
                           ui->tableView->selectionModel()->currentIndex());
    int id = dbManager->getRozkroje()->data(
                 dbManager->getRozkroje()->index(idx.row(),
                         0)).toInt();
    QString q = QString("select *from vroz where rozkroje_id=%1").arg(id);
    QSqlQuery query(q);
    vModel = dbManager->getSqlModelForQuery(&query);
    if (vModel) {
        ui->tableViewSzczegoly->setModel(vModel);
    }
    ui->tableViewSzczegoly->hideColumn(0);
    NaglowkiZamowienia::ustawNaglowki(ui->tableViewSzczegoly, vModel);
    connect(
        ui->tableViewSzczegoly->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
        SLOT(SelectionOfTableChangedSzczegoly(
                 const QItemSelection &,
                 const QItemSelection &)));
    ui->pushButtonPrint_2->setEnabled(false);
}

void RozkrojeDialog::showEvent(QShowEvent *e) {
    deleteOldModel();
    ui->pushButtonPrint->setEnabled(false);
    ui->pushButtonPrint_2->setEnabled(false);
    dbManager->setRozkroje();
    proxy->setDynamicSortFilter(true);
    proxy->setSourceModel(dbManager->getRozkroje());
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
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);
    connect(
        ui->tableView->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
        SLOT(SelectionOfTableChanged(
                 const QItemSelection &,
                 const QItemSelection &)));
    if (dodanoRozkroj) {
        int row = ui->tableView->model()->rowCount();
        QModelIndex index = ui->tableView->model()->index(row - 1, 1);
        ui->tableView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
        on_tableView_clicked(index);
        dodanoRozkroj = false;
    }
    QString q = QString("select *from vroz where rozkroje_id=%1").arg(1);
    QSqlQuery query(q);
    vModel = dbManager->getSqlModelForQuery(&query);
    on_pushButtonPrint_clicked();
    exit(1);
//  ui->lineEdit->clear();
    //  ustawIFiltruj();
}

void RozkrojeDialog::hideEvent(QHideEvent *e) {
    setDodanoRozkroj(false);
}

void RozkrojeDialog::on_pushButtonPrint_clicked() {
    stworzListeCaleZamowienie();
    drukuj();
}

void RozkrojeDialog::SelectionOfTableChanged(const QItemSelection &aSelected, const QItemSelection &aDeselected) {
    bool vIsAnyItemSelected = aSelected.count() > 0;
    ui->pushButtonPrint->setEnabled(vIsAnyItemSelected);
    if (!vIsAnyItemSelected) {
        deleteOldModel();
        ui->pushButtonPrint_2->setEnabled(false);
    }
}

void RozkrojeDialog::SelectionOfTableChangedSzczegoly(const QItemSelection &aSelected, const QItemSelection &aDeselected) {
    bool vIsAnyItemSelected = aSelected.count() > 0;
    ui->pushButtonPrint_2->setEnabled(vIsAnyItemSelected);
}

void RozkrojeDialog::drukuj() {
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

    //  } else {
    //    qDebug() << "anulowane";
    //  }
    zamowieniaDruk.clear();
    idDrukowanychZam.clear();
}

bool RozkrojeDialog::pageSetup(QPrinter *printer) {
    QPageSetupDialog psd(printer);
    if (psd.exec() == QDialog::Accepted) {
        return true;
    } else {
        return false;
    }
}

void RozkrojeDialog::printDocument(QPrinter *printer) {
    QTextDocument document;
    dodajZamowieniaDoHtml(&document);
    document.print(printer);
}

void RozkrojeDialog::wyczyscListy() {
    zamowieniaDruk.clear();
    idDrukowanychZam.clear();
}

void RozkrojeDialog::stworzListeCaleZamowienie() {
    wyczyscListy();
    int count = vModel->rowCount();
    for (int i = 0; i < count; i++) {
        zamowienieZRozmiaramiStruct zam;
        zam.nrZ = vModel->data(vModel->index(i, 1)).toString();
        zam.klNaz = vModel->data(vModel->index(i, 2)).toString();
        zam.klNr = vModel->data(vModel->index(i, 3)).toString();
        zam.wzor = vModel->data(vModel->index(i, 4)).toString();
        zam.spn = vModel->data(vModel->index(i, 5)).toString();
        zam.kolor = vModel->data(vModel->index(i, 6)).toString();
        zam.ociep = vModel->data(vModel->index(i, 7)).toString();
        zam.mat = vModel->data(vModel->index(i, 8)).toString();
        zam.wkladka = vModel->data(vModel->index(i, 9)).toString();
        zam.rozmiary.append(vModel->data(vModel->index(i, 10)).toInt());
        zam.rozmiary.append(vModel->data(vModel->index(i, 11)).toInt());
        zam.rozmiary.append(vModel->data(vModel->index(i, 12)).toInt());
        zam.rozmiary.append(vModel->data(vModel->index(i, 13)).toInt());
        zam.rozmiary.append(vModel->data(vModel->index(i, 14)).toInt());
        zam.rozmiary.append(vModel->data(vModel->index(i, 15)).toInt());
        zam.rozmiary.append(vModel->data(vModel->index(i, 16)).toInt());
        zam.rozmiary.append(vModel->data(vModel->index(i, 17)).toInt());
        zam.rozmiary.append(vModel->data(vModel->index(i, 18)).toInt());
        zam.rozmiary.append(vModel->data(vModel->index(i, 19)).toInt());
        zam.rozmiary.append(vModel->data(vModel->index(i, 20)).toInt());
        zam.rozmiary.append(vModel->data(vModel->index(i, 21)).toInt());
        zam.rozmiary.append(vModel->data(vModel->index(i, 22)).toInt());
        zam.rozmiary.append(vModel->data(vModel->index(i, 23)).toInt());
        zam.rozmiary.append(vModel->data(vModel->index(i, 24)).toInt());
        zam.rozmiary.append(vModel->data(vModel->index(i, 25)).toInt());
        zam.uzyt = vModel->data(vModel->index(i, 32)).toString();
        zam.wpr = vModel->data(vModel->index(i, 33)).toString();
        zam.rea = vModel->data(vModel->index(i, 34)).toString();
        zam.uwagi = vModel->data(vModel->index(i, 35)).toString();
        zam.uwagi2 = vModel->data(vModel->index(i, 36)).toString();
        zam.rozkrojNr = vModel->data(vModel->index(i, 49)).toString();
        zamowieniaDruk.append(zam);
        idDrukowanychZam.append(vModel->data(vModel->index(i, 0)).toInt());
    }
}

void RozkrojeDialog::stworzListeZamowienSzczegoly() {
    wyczyscListy();
    QModelIndexList selection = ui->tableViewSzczegoly->selectionModel()->selectedRows();
    std::vector<zamowienieZRozmiaramiStruct> zamowienia;
    int id = 0;
    for (int i = 0; i < selection.count(); i++) {
        QModelIndex index = proxy->mapToSource(selection.at(i));
        id = ui->tableViewSzczegoly->model()->data(ui->tableViewSzczegoly->model()->index(
                    index.row(),
                    0)).toInt();
        zamowieniaDruk.append(dbManager->stworzZamowienieZBazy(id));
        idDrukowanychZam.append(id);
    }
}

void RozkrojeDialog::dodajZamowieniaDoHtml(QTextDocument *document) {
    QString html("<html><head><meta content=\"text/html\"><style type=\"text/css\"></style></head><body><div>"
                 "    <table><tr>"
                );
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
    html +=
        "</table>"
        "<P STYLE=\"margin-right: -0.51in; margin-bottom: 0in; background: transparent; line-height: 100%; page-break-before: auto\"><BR></P> "
        " </body> </html > ";

    //            "</table>"
    //            "<p><span class = rvts3><br> </span > </p > "

    document->setHtml(html);

    // ///////////////
//    QString html("<html><head><meta content=\"text/html\"><style type=\"text/css\"></style></head><body><div>"
//                 "    <table>"
//                 "<tr>");
//    int counter = 0;
//    for (zamowienieZRozmiaramiStruct zamowienie : zamowieniaDruk) {
//        if (counter % 2 == 0) {
//            html += "<tr>\n";
//        }
//        if (!zamowienie.rozmiary.isEmpty()) {
//            html += zamowienieTabelka(zamowienie);
//        }
//        if (counter % 2 != 0) {
//            html += " < / tr > \n";
//        }
//        counter++;
//    }

//    html += "</table></div > "
//            "<p><span class = rvts3><br> </span > </p > "
//            " </body> </html > ";
//    document->setHtml(html);</td >
    // /////
}


QString RozkrojeDialog::zamowienieTabelka(zamowienieZRozmiaramiStruct zamowienie) {
//padding-top: 0in; padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0in\"
    QString wynik =
        QString("<td><TABLE border=1  WIDTH=340 CELLPADDING=0 CELLSPACING=-1 style=\"border-width: 1px; border-collapse: collapse;font-family:'Times New Roman', serif;font-size: 9px;\">"
                "<COL WIDTH=52>	<COL WIDTH=45>	<COL WIDTH=48>	<COL WIDTH=38>	<COL WIDTH=37>	<COL WIDTH=70>	<TR VALIGN=TOP>		"
                "<TD WIDTH=52 STYLE=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\">"
                "<P>DATA:</P>"
                " <p style=\"font-size: 9px;\">20-02-1986%1</p>"
                " <p style=\"font-size: 9px;\">%220-02-1986</p>"

                "<P><BR></P></TD><TD WIDTH=45 STYLE=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\">"
                "<P>KLIENT:</P>"
                "</TD>		"

                "<TD WIDTH=53 STYLE=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px;  border-right: none;\"><p>NR ZAM:</p>"
                "<P>NR ZAMxxxxxxxxxx:</P>		</TD>		"

                "<TD COLSPAN=2 WIDTH=83 STYLE=\"border-top: 1px solid #000000; border-bottom: 1px solid #000000; "
                "border-left: 1px solid #000000; border-right: none; padding-top: 0.04in; padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0in\">	"
                "		<P>NR ROZKROJU</P>		</TD>		<TD WIDTH=70 STYLE=\"border: 1px solid #000000; padding: 0.04in\">			"
                "<P>ZLECAJĄCY</P>		</TD>	</TR>"


                "	<TR VALIGN=TOP>		"
                "<TD WIDTH=52 STYLE=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\""
                "<P>WZÓR</P><P>xxx</P></TD>		"

                "<TD WIDTH=45 STYLE=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\">"
                "<P>SPÓD</P>	<P>SPÓDx</P>	</TD>	"

                "	<TD WIDTH=48 STYLE=\"border-top: none; border-bottom: 1px solid #000000; border-left: 1px solid #000000; border-right: none; padding-top: 0in; padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0in\">"
                "	<P>KOLOR</P>	<P>KOLORx</P>	</TD>		"

                "<TD WIDTH=38 STYLE=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\">"
                "<P>OCIE</P>	<P>OCIEx</P>	</TD>		"

                "<TD WIDTH=37 STYLE=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\">			<P>MAT</P>		<P>MATx</P>	</TD>		"

                "<TD WIDTH=70 STYLE=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\">			<P>WKŁ</P>	<P>WKŁx</P>	</TD>	</TR>"



                "<TR VALIGN=TOP>		"
                "<TD ROWSPAN=3 COLSPAN=4 WIDTH=207 STYLE=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\">	"
                "<P><BR></P></TD>		"

                "<TD ROWSPAN=3 WIDTH=37 STYLE=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\">	"
                "<P>SUMA</P>	<P>SUMAxx</P>	</TD>	"


                "<TD WIDTH=70 STYLE=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\">			"
                "<P>KROJ</P>		</TD>	</TR>"


                "<TR VALIGN=TOP>	"
                "	<TD WIDTH=70 STYLE=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\">			<P>SZWALNIA</P>		</TD>	</TR>	"



                "<TR VALIGN=TOP>	"
                "<TD WIDTH=70 STYLE=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\">			<P>MONTAŻ</P>		</TD>	</TR>	<TR>"

                "<TD COLSPAN=6 WIDTH=330 VALIGN=TOP STYLE=\"border-top: none;"
                " border-bottom: 1px solid #000000; border-left: 1px solid #000000; border-right: 1px solid #000000; padding-top: 0in; padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0.04in\">	"
                "<P>U1</P>	<P>U1xxxxxx</P>	</TD>	</TR>	<TR>		"

                "<TD COLSPAN=6 WIDTH=330 VALIGN=TOP STYLE=\"border-top: none; border-bottom: 1px solid #000000; border-left: 1px solid"
                " #000000; border-right: 1px solid #000000; padding-top: 0in; padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0.04in\">			<P>U2</P><P>U2xxxxxxxxxxx</P>		</TD>	</TR></TABLE></td>"
               );

    return wynik;
}

void RozkrojeDialog::oznaczDrukowano() {
    for (int i : idDrukowanychZam) {
        dbManager->oznaczDrukowano(i);
    }
    dbManager->getModelZamowienia()->select();
}

void RozkrojeDialog::on_pushButtonPrint_2_clicked() {
    stworzListeZamowienSzczegoly();
    drukuj();
}
