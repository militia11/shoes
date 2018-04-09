#include "pzdialog.h"
#include "ui_pzdialog.h"

pzDialog::pzDialog(rozmiaryDialog *roz, BazaDanychManager *db, QWidget *parent) :
    QDialog(parent), dbManager(db),roz(roz),
    ui(new Ui::pzDialog) {
    ui->setupUi(this);
    actualLastId = -1;
    proxy = new QSortFilterProxyModel(this);
    this->setWindowFlags(Qt::Window);
}

pzDialog::~pzDialog() {
    delete ui;
    delete proxy;
}

void pzDialog::ustawIFiltruj() {
    QString f = QString("nr_wzoru LIKE '%1%' AND spnaz LIKE '%2%' AND kolor LIKE '%3%' AND rodzaj LIKE '%4%'"
                        "AND nazwa LIKE '%5%' AND wkrodzaj LIKE '%6%'").arg(
                    ui->lineEditwz->text(),ui->lineEditsp->text(), ui->lineEditkol->text(), ui->lineEditoc->text(),ui->lineEditma->text(),
                    ui->lineEditwkl->text());

    dbManager->getPz()->setFilter(f);
}

int pzDialog::getActualLastId() const {
    return actualLastId;
}

void pzDialog::czysc() {
    ui->lineEditwz->clear();
    ui->lineEditkol->clear();
    ui->lineEditma->clear();
    ui->lineEditoc->clear();
    ui->lineEditsp->clear();
    ui->lineEditwkl->clear();
}

void pzDialog::showEvent(QShowEvent *e) {
    dbManager->setPz();
    proxy->setDynamicSortFilter(true);
    proxy->setSourceModel(dbManager->getPz());
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
    czysc();
    ustawIFiltruj();
//        connect(
//            ui->tableView->selectionModel(),
//            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
//            SLOT(SelectionOfTableChanged(
//                     const QItemSelection &,
//                     const QItemSelection &)));
}

void pzDialog::hideEvent(QHideEvent *e) {

}

void pzDialog::on_pushButtonSzukaj_clicked() {
    ustawIFiltruj();
}

void pzDialog::on_pushButton_clicked() {
    czysc();
    ustawIFiltruj();
}

//void pzDialog::on_pushButton_3_clicked() {
//    roz->setInsertExec(true);
//    roz->setFixedSize(roz->size());
//    roz->setWindowTitle("Pobranie z magazynu wolne");
//    roz->exec();
//}
