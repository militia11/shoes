#include "NaglowkiZamowienia.h"

void NaglowkiZamowienia::ustawNaglowki(QTableView *tableView, QAbstractItemModel *model) {
    QHeaderView *hv = tableView->horizontalHeader();
    hv->setSectionHidden(0, true);
    hv->setStretchLastSection(true);
    for (int i = 36; i < 48; i++) {
        hv->setSectionHidden(i, true);
    }
    hv->setDefaultAlignment(Qt::AlignLeft);
    for (int c = 9; c < 25;         ++c) {
        tableView->setColumnWidth(c, 30);
    }
    hv->setSectionHidden(33,true);

    tableView->setColumnWidth(25, 51); // suma
    tableView->setColumnWidth(1, 88);
    tableView->setColumnWidth(2, 88);
    tableView->setColumnWidth(3, 52);
    tableView->setColumnWidth(4, 52);
    tableView->setColumnWidth(5, 52);
    tableView->setColumnWidth(6, 52);
    tableView->setColumnWidth(7, 52);
    tableView->setColumnWidth(8, 52);
    tableView->setColumnWidth(9, 52);
    tableView->setColumnWidth(26, 69);// sk1
    tableView->setColumnWidth(27, 69);
    tableView->setColumnWidth(28, 69);
    tableView->setColumnWidth(29, 70);
    tableView->setColumnWidth(30, 70);
    tableView->setColumnWidth(31, 56);
    tableView->setColumnWidth(32, 56);

    tableView->setColumnWidth(33, 110);
    tableView->setColumnWidth(34, 110);
    //  tableView->setColumnWidth(37, 25);
    QStringList listaZamowienia;
    listaZamowienia  << ""  << "NR ZAM" << "KL SK" << "KL NR"  << "WZÓR"  << "SPÓD" << "KOL" <<
                     "OCIE" <<
                     "MAT" << "WKŁ" << "36" << "37" << "38" << "39" << "40" << "41" << "42" << "43"
                     << "44" << "45" << "46" << "47"    << "48" << "49" << "50"
                     << "SUMA"  << "SK1" << "SK2" <<    "SK3" << "SP NAZW" <<
                     "SP PROD" << "UŻY" << "HAN" << "DATA WPROW" << "DATA WPR" << "DATA REALIZACJI" << "REKORD" << "CAŁE ZAM" << ""
                     << "" << "" << ""  << "LICZBA WYDRUKÓW" << ""                    << ""  << "" << ""    << ""  << "" << ""
                     << ""  << "" << ""    << ""  << ""<< ""  << "" << ""    << ""  << ""                     << "" << ""  << "" << "";
    for (int i = 0; i < model->columnCount(); ++i) {
        model->setHeaderData(i, Qt::Horizontal, listaZamowienia[i]);
    }
}

void NaglowkiZamowienia::ustawNaglowkiROZ(QTableView *tableView, QAbstractItemModel *model) {
    QHeaderView *hv = tableView->horizontalHeader();
    hv->setSectionHidden(0, true);
    hv->setStretchLastSection(true);
    for (int i = 36; i < 42; i++) {
        hv->setSectionHidden(i, true);
    }
    hv->setDefaultAlignment(Qt::AlignLeft);
    for (int c = 9; c < 26;         ++c) {
        tableView->setColumnWidth(c, 30);
    }
    hv->setSectionHidden(33,true);

    tableView->setColumnWidth(26, 51); // suma
    tableView->setColumnWidth(1, 88);
    tableView->setColumnWidth(2, 88);
    tableView->setColumnWidth(3, 52);
    tableView->setColumnWidth(4, 52);
    tableView->setColumnWidth(5, 52);
    tableView->setColumnWidth(6, 52);
    tableView->setColumnWidth(7, 52);
    tableView->setColumnWidth(8, 52);
    tableView->setColumnWidth(9, 52);
    tableView->setColumnWidth(10, 52);
    tableView->setColumnWidth(27, 69);// sk1
    tableView->setColumnWidth(28, 69);
    tableView->setColumnWidth(29, 69);
    tableView->setColumnWidth(30, 70);
    tableView->setColumnWidth(31, 70);
    tableView->setColumnWidth(32, 56);

    tableView->setColumnWidth(34, 110);
    tableView->setColumnWidth(35, 110);
    tableView->setColumnWidth(36, 110);
    QStringList listaZamowienia;
    listaZamowienia  << ""  << "ROZ/POZ" << "NR ZAM"  <<"KL SK" << "KL NR"  << "WZÓR"  << "SPÓD" << "KOL" <<
                     "OCIE" << "MAT" << "WKŁ" << "36" << "37" << "38" << "39" << "40" << "41" << "42" << "43"
                     << "44" << "45" << "46" << "47"    << "48" << "49" << "50"
                     << "SUMA"  << "SK1" << "SK2" <<    "SK3" << "SP NAZWA" <<
                     "SP PROD" << "UŻY" << "HAN" << "DATA WPROWADZ" << "DATA REAlIZA" << "" << "REKORD" << "CAŁE ZAM" <<
                     "LICZBA WYDRUKÓW"  << "LICZBA WYDRUKÓW"  << "LICZBA WYDRUKÓW" << "LICZBA WYDRUKÓW"    <<"LICZBA WYDRUKÓW"  << "LICZBA WYDRUKÓW"  << "LICZBA WYDRUKÓW" << "LICZBA WYDRUKÓW"    <<"LICZBA WYDRUKÓW"  << "LICZBA WYDRUKÓW"  << "LICZBA WYDRUKÓW" << "LICZBA WYDRUKÓW"    <<"LICZBA WYDRUKÓW"  << "LICZBA WYDRUKÓW"  << "LICZBA WYDRUKÓW" << "LICZBA WYDRUKÓW"    <<"LICZBA WYDRUKÓW"  << "LICZBA WYDRUKÓW"  << "LICZBA WYDRUKÓW" << "LICZBA WYDRUKÓW";
    for (int i = 0; i < model->columnCount(); ++i) {
        model->setHeaderData(i, Qt::Horizontal, listaZamowienia[i]);
    }
}
