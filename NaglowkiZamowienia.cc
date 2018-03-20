#include "NaglowkiZamowienia.h"

void NaglowkiZamowienia::ustawNaglowki(QTableView *tableView, QAbstractItemModel *model) {
    QHeaderView *hv = tableView->horizontalHeader();
    hv->setSectionHidden(0, true);
    hv->setStretchLastSection(true);
    for (int i = 37; i < 48; i++) {
        hv->setSectionHidden(i, true);
    }
    hv->setDefaultAlignment(Qt::AlignLeft);
    for (int c = 9; c < 25;         ++c) {
        tableView->setColumnWidth(c, 30);
    }


    tableView->setColumnWidth(25, 51); // suma
    tableView->setColumnWidth(1, 65);
    tableView->setColumnWidth(2, 68);
    tableView->setColumnWidth(3, 52);
    tableView->setColumnWidth(4, 52);
    tableView->setColumnWidth(5, 52);
    tableView->setColumnWidth(6, 52);
    tableView->setColumnWidth(7, 52);
    tableView->setColumnWidth(8, 52);
    tableView->setColumnWidth(9, 52);
    tableView->setColumnWidth(26, 59);// sk1
    tableView->setColumnWidth(27, 59);
    tableView->setColumnWidth(28, 59);
    tableView->setColumnWidth(29, 60);
    tableView->setColumnWidth(30, 60);
    tableView->setColumnWidth(31, 56);
    tableView->setColumnWidth(32, 56);

    tableView->setColumnWidth(33, 88);
    tableView->setColumnWidth(34, 88);
    tableView->setColumnWidth(37, 25);
    QStringList listaZamowienia;
    listaZamowienia  << "" << "NR ZAM" << "KL SKR" << "KL NR"  << "WZÓR"  << "SPÓD" << "KOL" <<
                     "OCIE" <<
                     "MAT" << "WKŁ" << "36" << "37" << "38" << "39" << "40" << "41" << "42" << "43"
                     << "44" << "45" << "46" << "47"    << "48" << "49" << "50"
                     << "SUMA"  << "SK1" << "SK2" <<    "SK3" << "SP NAZWA" <<
                     "SP PROD" << "UŻY" << "HAN" << "DATA WPR" << "DATA REA" << "UWAGI 1" << "UWAGI 2" << ""
                     << "" << "" << ""  << "DRUK" << ""                    << ""  << "" << ""    << ""  << "" << ""
                     << ""  << "" << ""    << ""  << ""<< ""  << "" << ""    << ""  << ""                     << "" << ""  << "" << "";
    for (int i = 0; i < model->columnCount(); ++i) {
        model->setHeaderData(i, Qt::Horizontal, listaZamowienia[i]);
    }
}
