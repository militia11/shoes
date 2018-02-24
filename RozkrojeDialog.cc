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
}

QString RozkrojeDialog::zamowienieTabelka(zamowienieZRozmiaramiStruct zamowienie) {
    QString wynik = QString("<TABLE border=1  WIDTH=317 CELLPADDING=4 CELLSPACING=0 style=\"border-width: 1px; border-collapse: collapse;\">	"
                            "<COL WIDTH=42>	<COL WIDTH=62>	<COL WIDTH=45>	<COL WIDTH=37>	<COL WIDTH=22>	<COL WIDTH=3>	<COL WIDTH=48>	<TR VALIGN=TOP>		"
                            "<TD WIDTH=42 STYLE=\"border-top: 1px solid #000000; border-bottom: 1px solid #000000; border-left: 1px solid #000000; "
                            "border-right: none; padding-top: 0.04in; padding-bottom: 0.04in; padding-left: 0.04in; "
                            "padding-right: 0in\">			<P><FONT SIZE=2>DATA:</FONT></P><P><BR>"
                            "</P></TD><TD WIDTH=62 STYLE=\"border-top: 1px solid #000000; border-bottom: "
                            "1px solid #000000; border-left: 1px solid #000000; border-right: none; "
                            "padding-top: 0.04in; padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0in\">"
                            "<P><FONT SIZE=2>KLIENT:</FONT></P></TD><TD WIDTH=45 STYLE=\"border-top: 1px solid #000000;"
                            "border-bottom: 1px solid #000000; border-left: 1px solid #000000; border-right: none;"
                            " padding-top: 0.04in; padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0in\">	"
                            "<P><FONT SIZE=2>NR ZAM:</FONT></P>		</TD>		<TD COLSPAN=2 WIDTH=67 STYLE=\"border-top:"
                            "1px solid #000000; border-bottom: 1px solid #000000; border-left: 1px solid #000000;"
                            " border-right: none; padding-top: 0.04in; padding-bottom: 0.04in; padding-left: 0.04in;"
                            "padding-right: 0in\">			<P><FONT SIZE=2>NR ROZKROJU</FONT></P>"
                            "</TD>		<TD COLSPAN=2 WIDTH=59 STYLE=\"border: 1px solid #000000; padding: 0.04in\">"
                            "<P><FONT SIZE=2>ZLECAJĄCY</FONT></P>		</TD>	</TR>	<TR VALIGN=TOP>"
                            "<TD WIDTH=42 STYLE=\"border-top: none; border-bottom: 1px solid #000000; border-left: 1px solid #000000; "
                            "border-right: none; padding-top: 0in; padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0in\">"
                            "<P><FONT SIZE=2>WZÓR</FONT></P>	</TD><TD WIDTH=62 STYLE=\"border-top: none; border-bottom: 1px solid #000000; "
                            "border-left: 1px solid #000000; border-right: none; padding-top: 0in; padding-bottom: 0.04in; padding-left: 0.04in; "
                            "padding-right: 0in\"><P><FONT SIZE=2>Spód</FONT></P>		</TD>		<TD WIDTH=45 STYLE=\"border-top: none; border-bottom: 1px "
                            "solid #000000; border-left: 1px solid #000000; border-right: none; padding-top: 0in; padding-bottom: 0.04in; padding-left: 0.04in; "
                            "padding-right: 0in\">			<P><FONT SIZE=2>KOLOR</FONT></P>		</TD>		<TD WIDTH=37 STYLE=\"border-top: none; border-bottom: 1px "
                            "solid #000000; border-left: 1px solid #000000; border-right: none; padding-top: 0in; padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0in\">"
                            "<P><FONT SIZE=2>OCIE</FONT></P>		</TD>		<TD COLSPAN=2  WIDTH=33 STYLE=\"border-top: none; border-bottom: 1px solid #000000; border-left: 1px solid"
                            " #000000; border-right: none; padding-top: 0in; padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0in\">			<P><FONT SIZE=2>MAT</FONT></P>		"
                            "</TD>		<TD WIDTH=48 STYLE=\"border-top: none; border-bottom: 1px solid #000000; border-left: 1px solid #000000; border-right: 1px solid #000000; padding-top: 0in; "
                            "padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0.04in\">			<P><FONT SIZE=2>WKŁ</FONT></P>		</TD>	</TR>	<TR VALIGN=TOP>		<TD ROWSPAN=3 COLSPAN=4"
                            " WIDTH=210 STYLE=\"border-top: none; border-bottom: 1px solid #000000; border-left: 1px solid #000000; border-right: none; padding-top: 0in; padding-bottom: 0.04in;"
                            " padding-left: 0.04in; padding-right: 0in\">			<P><BR>			</P>		</TD>		<TD ROWSPAN=3 COLSPAN=2 WIDTH=33 STYLE=\"border-top: none; "
                            "border-bottom: 1px solid #000000; border-left: 1px solid #000000; border-right: none; padding-top: 0in; padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0in\">"
                            "<P><FONT SIZE=2>SUMA</FONT></P>		</TD>		<TD WIDTH=48 STYLE=\"border-top: none; border-bottom: 1px solid #000000; border-left: 1px solid #000000; border-right: 1px"
                            " solid #000000; padding-top: 0in; padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0.04in\">			<P><FONT SIZE=2>KROJ</FONT></P>		</TD>	</TR>	<TR VALIGN=TOP>		"
                            "<TD WIDTH=48 STYLE=\"border-top: none; border-bottom: 1px solid #000000; border-left: 1px solid #000000; border-right: 1px solid #000000; padding-top: 0in; padding-bottom: 0.04in; padding-left: 0.04in; padding-right:"
                            " 0.04in\">			<P><FONT SIZE=2>SZWALNIA</FONT></P>		</TD>	</TR>	<TR VALIGN=TOP>		<TD WIDTH=48 STYLE=\"border-top: none; border-bottom: 1px solid #000000; border-left: 1px"
                            " solid #000000; border-right: 1px solid #000000; padding-top: 0in; padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0.04in\">			<P><FONT SIZE=2>MONTAŻ</FONT></P>"
                            "</TD>	</TR>	<TR>		<TD COLSPAN=7 WIDTH=307 VALIGN=TOP STYLE=\"border-top: none; border-bottom: 1px solid #000000; border-left: 1px solid #000000; border-right: 1px solid "
                            "#000000; padding-top: 0in; padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0.04in\">			<P><FONT SIZE=2>U1</FONT></P>		</TD>	</TR>	<TR>		<TD COLSPAN=7"
                            " WIDTH=307 VALIGN=TOP STYLE=\"border-top: none; border-bottom: 1px solid #000000; border-left: 1px solid #000000; border-right: 1px solid #000000; padding-top: 0in; "
                            "padding-bottom: 0.04in; padding-left: 0.04in; padding-right: 0.04in\">"
                            "			<P><FONT SIZE=2>U2</FONT></P>		</TD>	</TR></TABLE>"
                            "");


//        QString("<td><table border=1 cellpadding=0 cellspacing=-1 style=\"border-width: 1px; border-collapse: collapse;font-family:'Times New Roman', serif;font-size: 10px;\">"
//                "<tr valign=top>"
//                "<td width=81 height=84 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\"><p  >DATA:</p>"
//                "<p style=\"font-size: 13px;\">%1&nbsp;&nbsp;&nbsp;&nbsp;%2</p>"
//                "</td>"
//                "<td colspan=2 width=193 height=84 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\"><p >ZAM&#211;WIENIE:</p><p style=\"font-size: 13px;\">%3</p>"
//                "</td>"
//                "<td width=118 height=84 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px;\"><p >ZLECAJ&#260;CY:</p><p style=\"font-size: 13px;\">%4</p>"
//                "</td>"
//                "</tr>"
//                "<tr valign=top>"
//                "<td width=81 height=84 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\"><p >WZ&#211;R:</p><p style=\" font-size: 13px;\">%5</p>"
//                "</td>"
//                "<td width=54 height=84 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px;  border-right: none;\"><p>SPODY:</p><p style=\"font-size: 13px;\">%6</p>"
//                "</td>"
//                "<td width=68 height=84 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-right: none;\"><p >KOLOR SK&#211;RA</p><p style=\"font-size: 13px;\">%7</p>"
//                "</td>"
//                "<td width=81 height=84 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px;\"><p >SZARFIARZ:</p><p style=\";font-size: 13px;\"></p></span></p>"
//                "</td>"
//                "</tr>").arg(zamowienie.wpr.toHtmlEscaped(), zamowienie.rea.toHtmlEscaped(), zamowienie.nrZ.toHtmlEscaped(),
//                             zamowienie.klNaz.toHtmlEscaped(), zamowienie.wzor.toHtmlEscaped(), zamowienie.snaz.toHtmlEscaped(),
//                             zamowienie.kolor.toHtmlEscaped());

//    QMap<QString, int> rozm;
//    int suma = zamowienie.rozmiary[15];
//    for (int i = 0; i < 15; i++) {
//        int id = 36 + i;
//        rozm.insert(QString("R %1").arg(id),
//                    zamowienie.rozmiary[i]);
//    }

//    for (QMap<QString, int>::iterator it = rozm.begin(); it != rozm.end();) {
//        if ((*it) == 0) {
//            rozm.erase(it++);
//        } else {
//            ++it;
//        }
//    }

//    for (QMap<QString, int>::iterator it = rozm.begin(); it != rozm.end(); it++) {
//        //  qDebug() << it.key() << it.value();
//    }

    //wynik += QString (
    //        < / td > ");
    //QString zamowienm,,ieStr = QString(% 1").arg(suma);
//    wynik += QString("<tr valign=top>"
//                     "<td colspan=2 rowspan=2 width=174 height=29 valign=top style=\"border-width : 0px; border-color: #000000; border-style: solid; padding: 0px; border-top: none; border-right: none;\">"
//                     "<table border=1 cellpadding=9 cellspacing=-1 style=\"border-collapse: collapse;font-family:'Times New Roman', serif;font-size: 14px;\">"
//                     "<tr>"
//                     "<td ><u>R36</u><br>1</td>"
//                     " <td><u>R37</u></u><br>8</td><td><p><u>R38</u><br>21</p></td><td><p><u>R39</u><br>10</p></td>"
//                     " <td border=1 style=\"border-width: 3px; border-color: #000000; border-style: solid; \"><u>R43</u></u><br>8</td><td><p><u>R46</u><br>21</p></td><td><p><u>R47</u><br>10</p></td>"
//                     " <td border=1  style=\"border-width : 3px; border-color: #000000; border-style: solid; \"><u>R48</u><br>18</td></tr>"

//                     "<tr>"
//                     "<td><u>R49</u><br>1</td>"
//                     " <td><u>R50</u></u><br>8</td>"
//                     "</tr>"

//                     "</table>"

//                     "</td>"
//                     "<td rowspan=2 valign=top style=\"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-top: none; border-right: none;\">SUMA:</td>"
//                     "<td width = 128 height = 48 valign = top style = \"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-top: none;\"><p>PRZYJMUJ&#260;CY:</p><p style=\"font-size: 13px;\"></p>"
//                     " </td> </tr> "
//                     "<tr valign = top>"
//                     "<td width = 128 height = 48 valign = top style = \"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-top: none;\"><p>MONTA&#379;:</p><p style=\"font-size: 13px;\"></p>"
//                     " </td> </tr> "
//                     "<tr valign = top>"
//                     "<td colspan = 4 width = 530 height = 54 valign = top style = \"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-top: none;\"><p>UWAGI 1: < / p > <p style = \"font-size: 13px;\">jakies uwagi < / p > "
//                     " </td > </tr> "
//                     "<tr>"
//                     "<td colspan = 4 width = 530 height = 54 valign = top style = \"border-width : 1px; border-color: #000000; border-style: solid; padding: 1px; border-top: none;\"><p>UWAGI 2: < / p > <p style = \"font-size: 13px;\">jakies uwagi < / p > "
//                     " </td > </tr></table ></td >").arg(zamowienie.nrZ.toHtmlEscaped(),
//                             zamowienie.klNaz.toHtmlEscaped());

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
