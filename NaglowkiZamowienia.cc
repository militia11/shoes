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
    tableView->setColumnWidth(25, 43); // suma
    tableView->setColumnWidth(1, 58);
    tableView->setColumnWidth(2, 84);
    tableView->setColumnWidth(3, 48);
    tableView->setColumnWidth(4, 50);
    tableView->setColumnWidth(5, 46);
    tableView->setColumnWidth(6, 46);
    tableView->setColumnWidth(7, 50);
    tableView->setColumnWidth(8, 50);
    tableView->setColumnWidth(9, 52);
    tableView->setColumnWidth(26, 56);// sk1
    tableView->setColumnWidth(27, 56);
    tableView->setColumnWidth(28, 56);
    tableView->setColumnWidth(29, 70);
    tableView->setColumnWidth(30, 70);
    tableView->setColumnWidth(31, 85);
    tableView->setColumnWidth(32, 80);

    tableView->setColumnWidth(33, 88);
    tableView->setColumnWidth(34, 88);
    tableView->setColumnWidth(37, 25);
    QStringList listaZamowienia;
    listaZamowienia  << "" << "NR ZAM" << "KLI SKRÓT" << "KLI NR"  << "WZÓR"  << "SPÓD" << "KOL" <<
                     "OCIEP" <<
                     "MAT" << "WKŁ" << "R36" << "R37" << "R38" << "R39" << "R40" << "R41" << "R42" << "R43"
                     << "R44" << "R45" << "R46" << "R47"    << "R48" << "R49" << "R50"
                     << "SUMA"  << "SK1" << "SK2" <<    "SK3" << "SP NAZWA" <<
                     "SP PROD" << "UŻYTKOWNIK" << "HANDLOWIEC" << "DATA WPR" << "DATA REALIZ" << "UWAGI 1" << "UWAGI 2" << ""
                     << "" << ""
                     << ""  << "" << ""
                     << ""  << "" << ""
                     << ""  << "" << ""
                     << ""  << "" << ""
                     << ""  << "" << ""
                     << "" << ""  << "" << "";
    for (int i = 0; i < model->columnCount(); ++i) {
        model->setHeaderData(i, Qt::Horizontal, listaZamowienia[i]);
    }
}

#include "NaglowkiZamowienia.h"
