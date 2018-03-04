#include "RozkrojeDialog.h"
#include "ui_RozkrojeDialog.h"
#include "NaglowkiZamowienia.h"

RozkrojeDialog::RozkrojeDialog(BazaDanychManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RozkrojeDialog), dbManager(db) {
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    dodanoRozkroj = false;
    wskazRozkroj = false;
    ui->lineEditNr->setFixedWidth(100);
    ui->lineEditUz->setFixedWidth(100);
    ui->lineEditWpr->setFixedWidth(100);
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

void RozkrojeDialog::setWskazRozkroj(bool value)
{
    wskazRozkroj = value;
}

void RozkrojeDialog::setDodanoRozkroj(bool value) {
    dodanoRozkroj = value;
}

void RozkrojeDialog::ustawIFiltruj() {
    dbManager->getRozkroje()->setFilter(QString("nr_rozkroju LIKE '%1%' AND WPROWADZONO LIKE '%2%' AND UZYTKOWNIK LIKE '%3%'").arg(ui->lineEditNr->text(),ui->lineEditWpr->text(),ui->lineEditUz->text()));
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
    ui->tableViewSzczegoly->horizontalHeader()->setMinimumSectionSize(5);
    QHeaderView *hv = ui->tableViewSzczegoly->horizontalHeader();
    NaglowkiZamowienia::ustawNaglowki(ui->tableViewSzczegoly, vModel);
       ui->tableViewSzczegoly->setColumnWidth(35, 80);
       ui->tableViewSzczegoly->setColumnWidth(36, 80);
    hv->setSectionHidden(41, false);
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
    } else if(wskazRozkroj) {
        //dbManager->pobierzIdRozkrojuWskaz(nrRozkrojuWskaz);
    }
    for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c) {
        ui->tableView->horizontalHeader()->setSectionResizeMode(c,
                QHeaderView::Fixed);
    }
    ui->tableView->horizontalHeader()->setDefaultSectionSize(100);
    ustawIFiltruj();

//    QString q = QString("select * from vroz where rozkroje_id=%1").arg(1);
//    QSqlQuery query(q);
//    vModel = dbManager->getSqlModelForQuery(&query);
//    on_pushButtonPrint_clicked();
//    exit(1);
}

void RozkrojeDialog::hideEvent(QHideEvent *e) {
    czysc();
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
    if (pageSetup(&printer)) {
    printDocument(&printer);
    oznaczDrukowano();

      } else {
        qDebug() << "anulowane";
      }
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


void RozkrojeDialog::stworzListeZamowienSzczegoly() {
    wyczyscListy();
    QModelIndexList selection = ui->tableViewSzczegoly->selectionModel()->selectedRows();
    std::vector<zamowienieZRozmiaramiStruct> zamowienia;
    int id = 0;
    for (int i = 0; i < selection.count(); i++) {
        int row = selection.at(i).row();
        zamowieniaDruk.append(prepareZamowienieDruk(row));
        idDrukowanychZam.append(vModel->data(vModel->index(row, 0)).toInt());
    }
}

zamowienieZRozmiaramiStruct RozkrojeDialog::prepareZamowienieDruk(int i) {
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
    zam.suma = vModel->data(vModel->index(i, 25)).toString();
    zam.uzyt = vModel->data(vModel->index(i, 31)).toString();
    zam.wpr = vModel->data(vModel->index(i, 33)).toString();
    zam.rea = vModel->data(vModel->index(i, 34)).toString();
    zam.uwagi = vModel->data(vModel->index(i, 35)).toString();
    zam.uwagi2 = vModel->data(vModel->index(i, 36)).toString();
    zam.rozkrojNr = vModel->data(vModel->index(i, 40)).toString();

    return zam;
}

void RozkrojeDialog::stworzListeCaleZamowienie() {
    wyczyscListy();
    int count = vModel->rowCount();
    for (int i = 0; i < count; i++) {
        zamowieniaDruk.append(prepareZamowienieDruk(i));
        idDrukowanychZam.append(vModel->data(vModel->index(i, 0)).toInt());
    }
}

void RozkrojeDialog::dodajZamowieniaDoHtml(QTextDocument *document) {
    QString html("<html><head><meta content=\"text/html\"><style type=\"text/css\"></style></head><body><div><table><tr>");
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

    html += "</table></div><p><span class = rvts3><br></span ></p></body></html>";
    document->setHtml(html);
}


QString RozkrojeDialog::zamowienieTabelka(zamowienieZRozmiaramiStruct zamowienie) {
    QString wynik =
        QString("<td><TABLE border=1 WIDTH=460 CELLPADDING=0 CELLSPACING=-1 style=\"border-width: 1px; border-collapse: collapse;font-family:'Times New Roman', serif;font-size: 13px;\">"
                "<TR VALIGN=TOP><TD WIDTH=63>"
                "<p style=\"font-size: 13px;margin: 3;\">%1</p><p style=\"font-size: 13px;margin: 3;line-height:22px;\">%2</p>"
                "</TD><TD WIDTH=74>"
                "<P style=\"margin: 3;\">KLI &nbsp;&nbsp;&nbsp;<b>%3</b></P><P align=\"center\" style=\"font-size:17px;margin: 3;line-height:23px;\"><b>%4</b></P></TD>"
                "<TD WIDTH=69>"
                "<p style=\"margin: 3;\">NR ZAM</p>"
                "<P align=\"center\" style=\"font-size:20px;margin: 3;\"><b>%5</b></P></TD>"
                "<TD COLSPAN=2 WIDTH=112>"
                "<P style=\"margin: 3;\">NR ROZKROJU</P><P align=\"center\" style=\"font-size:20px;margin: 3;\"><b>%6</b></P></TD>"
                "<TD WIDTH=78>"
                "<P style=\"margin: 3;\">ZLECAJĄCY</P><P align=\"center\" style=\"font-size:19px;margin: 3;\"><b>%7</b></P></TD></TR>"
                "<TR VALIGN=TOP>"
                "<TD WIDTH=65>"
                "<P style=\"margin: 3;\">WZÓR</P><P align=\"center\" style=\"font-size:20px;margin: 3;\"><b>%8</b></P></TD>"
                "<TD WIDTH=65 >"
                "<P style=\"margin: 3;\">SPÓD</P>	<P align=\"center\" style=\"font-size:20px;margin: 3;\"><b>%9</b></P></TD>").
        arg(zamowienie.wpr.toHtmlEscaped(), zamowienie.rea.toHtmlEscaped(), zamowienie.klNr,
            zamowienie.klNaz.toHtmlEscaped(), zamowienie.nrZ.toHtmlEscaped(), zamowienie.rozkrojNr.toHtmlEscaped(), zamowienie.uzyt.toHtmlEscaped(),
            zamowienie.wzor.toHtmlEscaped(), zamowienie.spn.toHtmlEscaped());
    wynik += QString("<TD WIDTH = 68>"
                "<P style=\"margin: 3;\">KOLOR</P><P align=\"center\" style=\"font-size:20px;margin: 3;\"><b>%1</b></P></TD>"
                "<TD WIDTH=58 >"
                "<P style=\"margin: 3;\">OCIE</P><P align=\"center\" style=\"font-size:20px;margin: 3;\"><b>%2</b></P></TD>"
                "<TD WIDTH=69 >"
                "<P style=\"margin: 3;\">MAT</P><P align=\"center\" style=\"font-size:20px;margin: 3;\"><b>%3</b></P></TD>"
                "<TD WIDTH=70 >"
                "<P style=\"margin: 3;\">WKŁ</P><P align=\"center\" style=\"font-size:20px;margin: 3;\"><b>%4</b></P></TD></TR>"
               ).arg(zamowienie.kolor.toHtmlEscaped(), zamowienie.ociep.toHtmlEscaped(), zamowienie.mat.toHtmlEscaped(), zamowienie.wkladka.toHtmlEscaped());

    QMap<QString, int> rozm;
    for (int i = 0; i < 15; i++) {
        int id = 36 + i;
        rozm.insert(QString("R%1").arg(id),
                    zamowienie.rozmiary[i]);
    }

    for (QMap<QString, int>::iterator it = rozm.begin(); it != rozm.end();) {
        if ((*it) == 0) {
            rozm.erase(it++);
        } else {
            ++it;
        }
    }

    wynik += "<TR VALIGN=TOP><TD ROWSPAN=3 COLSPAN=4 WIDTH=220>"
                     "<table border=1 cellpadding=4 cellspacing=-1 style=\"border-collapse: none;font-family:'Times New Roman', serif;font-size: 15px;\"><tr>";
    int counter =1;
    for (QMap<QString, int>::iterator it = rozm.begin(); it != rozm.end(); it++) {
        wynik += QString("<td align=\"center\"><p><u>%1</u></p><p>%2</p></td>").arg(it.key()).arg(it.value());
       if(counter==8) {
           wynik +="<tr>";
       }
       counter++;
    }
    if(counter<8) {
       wynik += "<tr><td align=\"center\"><p>&nbsp;&nbsp;&nbsp;</p><p>&nbsp;&nbsp;&nbsp;</p></td>";
    }
    wynik += QString("</tr></table></TD>"
                     "<TD ROWSPAN=3 WIDTH=57>"
                     "<P>SUMA</P><P style=\"font-size:26px;font-family:'Times New Roman'\"><b><center>%1</center></b></P></TD>"
                     "<TD WIDTH=80>"
                     "<P>KROJ <br></br></P></TD></TR>"
                     "<TR VALIGN=TOP>"
                     "<TD WIDTH=80>"
                     "<P>SZWALNIA <br></br></P></TD></TR>"
                     "<TR VALIGN=TOP>"
                     "<TD WIDTH=80>"
                     "<P>MONTAŻ <br></br></P></TD></TR><TR>"
                     "<TD COLSPAN=6 WIDTH=360 VALIGN=TOP>"
                     "<P style=\"font-family:'Times New Roman'\">UWAGI 1</P><P>%2</P></TD></TR><TR>"
                     "<TD COLSPAN=6 WIDTH=360 VALIGN=TOP>"
                     "<P style=\"font-family:'Times New Roman'\">UWAGI 2</P><P>%3</P></TD></TR></TABLE></td>"
                    ).arg(zamowienie.suma.toHtmlEscaped(), zamowienie.uwagi.toHtmlEscaped(), zamowienie.uwagi2.toHtmlEscaped());

    return wynik;
}

void RozkrojeDialog::setNrRozkrojuWskaz(const QString &value)
{
    nrRozkrojuWskaz = value;
}

void RozkrojeDialog::oznaczDrukowano() {
    for (int i : idDrukowanychZam) {
        dbManager->oznaczDrukowano(i);
    }
}

void RozkrojeDialog::on_pushButtonPrint_2_clicked() {
    stworzListeZamowienSzczegoly();
    drukuj();
}

void RozkrojeDialog::czysc() {
      ui->lineEditNr->clear();
      ui->lineEditWpr->clear();
      ui->lineEditUz->clear();
}

void RozkrojeDialog::on_pushSzukaj_clicked()
{
    ustawIFiltruj();
}
