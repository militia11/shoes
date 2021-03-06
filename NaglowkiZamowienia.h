#ifndef NAGLOWKIZAMOWIENIA_H
#define NAGLOWKIZAMOWIENIA_H

#include <QTableView>
#include <QAbstractItemModel>
#include <QHeaderView>

class NaglowkiZamowienia {
public:
    static void ustawNaglowki(QTableView *tableView, QAbstractItemModel *model);
    static void ustawNaglowkiROZ(QTableView *tableView, QAbstractItemModel *model);
    static void ustawNaglowkiWyd(QTableView *tableView, QAbstractItemModel *model);
};

#endif // NAGLOWKIZAMOWIENIA_H
