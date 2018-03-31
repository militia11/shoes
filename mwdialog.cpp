#include "mwdialog.h"
#include "ui_mwdialog.h"

int mwDialog::selectExec() {
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    return QDialog::exec();
}

mwDialog::mwDialog(rozmiaryDialog *roz, BazaDanychManager *db, QWidget *parent) :
    QDialog(parent), dbManager(db),roz(roz),
    ui(new Ui::mwDialog) {
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    this->setWindowFlags(Qt::Window);
}

mwDialog::~mwDialog() {
    delete ui;
    delete proxy;
}

int mwDialog::exec() {
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    return QDialog::exec();
}

void mwDialog::ustawIFiltruj() {
//    QString f = QString("nr_wzoru LIKE '%1%' AND nazwa LIKE '%2%' AND rodzaj LIKE '%3%' AND kolor LIKE '%4%'"
//                        "AND spnaz LIKE '%5%' AND wkrodzaj LIKE '%6%' AND typ LIKE '%7%' AND rodzaj_montazu LIKE '%8%'").arg(
//                    ui->lineEditwz->text(), ui->lineEditma->text(), ui->lineEditoc->text(), ui->lineEditkol->text(),
//                    ui->lineEditwkl->text(),);

//    dbManager->getmw()->setFilter(f);
}

void mwDialog::showEvent(QShowEvent *e) {
    dbManager->setmw();
    proxy->setDynamicSortFilter(true);
    proxy->setSourceModel(dbManager->getmw());
    ui->tableView->setModel(proxy);
    ui->tableView->setSortingEnabled(true);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setColumnHidden(1,true);
    for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c) {
        ui->tableView->horizontalHeader()->setSectionResizeMode(c,
                QHeaderView::Fixed);
    }

    ui->tableView->setColumnWidth(2, 124);
    ui->tableView->setColumnWidth(3, 124);
    ui->tableView->setColumnWidth(4, 124);
    ui->tableView->setColumnWidth(5, 124);
    ui->tableView->setColumnWidth(6, 124);
    ui->tableView->setColumnWidth(7, 124);
    ui->tableView->setColumnWidth(8, 52);
    ui->tableView->setColumnWidth(9, 52);
    for (int c = 8; c < 23;     c++) {
        ui->tableView->horizontalHeader()->setSectionResizeMode(c,
                QHeaderView::Fixed);
        ui->tableView->setColumnWidth(c, 30);
    }
    QHeaderView *hv = ui->tableView->horizontalHeader();
    hv->setStretchLastSection(true);
    hv->setDefaultAlignment(Qt::AlignLeft);
    ui->tableView->setColumnWidth(23,59);

    ui->tableView->sortByColumn(0, Qt::AscendingOrder);
    ustawIFiltruj();
}

void mwDialog::hideEvent(QHideEvent *e) {

}

void mwDialog::on_pushButtonZw_clicked() {
    QModelIndex idx = proxy->mapToSource(
                          ui->tableView->selectionModel()->currentIndex());
    int id = dbManager->zwrocAktualnyModelIdMw(idx);
    roz->setCurId(id);
    roz->setFixedSize(roz->size());
    roz->exec();
}

void mwDialog::on_pushButtonPu_clicked() {

}

void mwDialog::on_pushButtonSzukaj_clicked() {
    ustawIFiltruj();
}

void mwDialog::on_pushButton_clicked() {
    ui->lineEditwz->clear();
    ui->lineEditkol->clear();
    ui->lineEditma->clear();
    ui->lineEditoc->clear();
    ui->lineEditsp->clear();
    ui->lineEditwkl->clear();
    ustawIFiltruj();
}
