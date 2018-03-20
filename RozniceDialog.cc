#include "RozniceDialog.h"
#include "ui_RozniceDialog.h"
#include "NaglowkiZamowienia.h"
RozniceDialog::RozniceDialog(BazaDanychManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RozniceDialog), dbManager(db) {
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    ui->lineEditNr->setFixedWidth(110);
    ui->lineEditUz->setFixedWidth(110);
    ui->lineEditWpr->setFixedWidth(110);
    wskazRoznice = false;
    this->setWindowFlags(Qt::Window);
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

void RozniceDialog::ustawIFiltruj() {
    dbManager->getRoznice()->setFilter(QString("nr_rozkroju LIKE '%1%' AND WPROWADZONO LIKE '%2%' AND UZYTKOWNIK LIKE '%3%'").arg(ui->lineEditNr->text(),ui->lineEditWpr->text(),ui->lineEditUz->text()));
}

void RozniceDialog::czysc() {
    ui->lineEditNr->clear();
    ui->lineEditWpr->clear();
    ui->lineEditUz->clear();
}

void RozniceDialog::deleteOldModel() {
    QAbstractItemModel *old = ui->tableViewSzczegoly->model();
    if (old) {
        delete old;
        old = 0;
    }
}

void RozniceDialog::setNrRoznicy(const QString &value) {
    nrRoznicy = value;
}

void RozniceDialog::setWskazRoznice(bool value) {
    wskazRoznice = value;
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
    ui->tableViewSzczegoly->horizontalHeader()->setMinimumSectionSize(5);
    NaglowkiZamowienia::ustawNaglowki(ui->tableViewSzczegoly, vModel);
    ui->tableViewSzczegoly->setColumnWidth(35, 110);
    ui->tableViewSzczegoly->setColumnWidth(36, 110);
    ui->tableViewSzczegoly->update();
}

void RozniceDialog::showEvent(QShowEvent *e) {
    deleteOldModel();
    dbManager->setRoznice();
    proxy->setDynamicSortFilter(true);
    proxy->setSourceModel(dbManager->getRoznice());
    ui->tableView->setModel(proxy);
    ui->tableView->setSortingEnabled(true);
    QHeaderView *hv = ui->tableView->horizontalHeader();
    hv->setStretchLastSection(true);
    hv->setSectionHidden(0, true);
    hv->setDefaultAlignment(Qt::AlignLeft);
    ui->tableView->sortByColumn(0, Qt::DescendingOrder);
    connect(
        ui->tableView->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
        SLOT(SelectionOfTableChanged(
                 const QItemSelection &,
                 const QItemSelection &)));
    for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c) {
        ui->tableView->horizontalHeader()->setSectionResizeMode(c,
                QHeaderView::Fixed);
        ui->tableView->horizontalHeader()->setDefaultSectionSize(110);
    }
    ustawIFiltruj();
    if(wskazRoznice) {
        QAbstractItemModel * model = ui->tableView->model();
        ui->tableView->setFocus();
        for(int i=0; i < model->rowCount(); i++) {
            if(model->data(model->index(i, 1))==nrRoznicy) {
                QModelIndex index = ui->tableView->model()->index(i, 1);
                ui->tableView->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
                on_tableView_clicked(index);
            }
        }
        wskazRoznice = false;
    }
    ui->tableView->sortByColumn(1, Qt::DescendingOrder);
}

void RozniceDialog::hideEvent(QHideEvent *e) {
    czysc();
}

void RozniceDialog::on_pushSzukaj_clicked() {
    ustawIFiltruj();
}
