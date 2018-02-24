#include "RozniceDialog.h"
#include "ui_RozniceDialog.h"
#include "NaglowkiZamowienia.h"
RozniceDialog::RozniceDialog(BazaDanychManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RozniceDialog), dbManager(db) {
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
}

RozniceDialog::~RozniceDialog() {
    delete ui;
    delete proxy;
}

void RozniceDialog::SelectionOfTableChanged(const QItemSelection &aSelected, const QItemSelection &aDeselected) {
    bool vIsAnyItemSelected = aSelected.count() > 0;
    if (!vIsAnyItemSelected) {
        deleteOldModel();
    }
}

void RozniceDialog::deleteOldModel() {
    QAbstractItemModel *old = ui->tableViewSzczegoly->model();
    if (old) {
        delete old;
        old = 0;
    }
}

void RozniceDialog::on_tableView_clicked(const QModelIndex &index) {
    deleteOldModel();
    QModelIndex  idx = proxy->mapToSource(
                           ui->tableView->selectionModel()->currentIndex());
    int id = dbManager->getRoznice()->data(
                 dbManager->getRoznice()->index(idx.row(),
                         0)).toInt();
    QString q = QString("select *from vroznice where roznice_id=%1").arg(id);
    QSqlQuery query(q);
    QSqlQueryModel *vModel = dbManager->getSqlModelForQuery(&query);
    if (vModel) {
        ui->tableViewSzczegoly->setModel(vModel);
    }
    ui->tableViewSzczegoly->hideColumn(0);
    NaglowkiZamowienia::ustawNaglowki(ui->tableViewSzczegoly, vModel);
    ui->tableViewSzczegoly->update();
}

void RozniceDialog::showEvent(QShowEvent *e) {
    deleteOldModel();
    dbManager->setRoznice();
    proxy->setDynamicSortFilter(true);
    proxy->setSourceModel(dbManager->getRoznice());
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
//  ui->lineEdit->clear();
//  ustawIFiltruj();
}
