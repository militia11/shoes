#include "rwdialog.h"
#include "ui_rwdialog.h"

rwDialog::rwDialog(BazaDanychManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::rwDialog),dbManager(db)  {
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    this->setWindowFlags(Qt::Window);
    ui->tableView->verticalHeader()->setDefaultSectionSize(ui->tableView->verticalHeader()->minimumSectionSize());
}

rwDialog::~rwDialog() {
    delete ui;
    delete proxy;
}

void rwDialog::ustawIFiltruj() {
    QString f = QString("nr_wzoru LIKE '%1%' AND spnaz LIKE '%2%' AND kolor LIKE '%3%' AND rodzaj LIKE '%4%'"
                        "AND nazwa LIKE '%5%' AND wkrodzaj LIKE '%6%'").arg(
                    ui->lineEditwz->text(),ui->lineEditsp->text(), ui->lineEditkol->text(), ui->lineEditoc->text(),ui->lineEditma->text(),
                    ui->lineEditwkl->text());

    dbManager->getRw()->setFilter(f);
}

void rwDialog::showEvent(QShowEvent *e) {
    dbManager->setRw();
    proxy->setDynamicSortFilter(true);
    proxy->setSourceModel(dbManager->getRw());
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

    ui->tableView->sortByColumn(0, Qt::DescendingOrder);
    czysc();
    ustawIFiltruj();
}

void rwDialog::hideEvent(QHideEvent *e) {

}

void rwDialog::on_pushButtonSzukaj_clicked() {
    ustawIFiltruj();
}

void rwDialog::czysc() {
    ui->lineEditwz->clear();
    ui->lineEditkol->clear();
    ui->lineEditma->clear();
    ui->lineEditoc->clear();
    ui->lineEditsp->clear();
    ui->lineEditwkl->clear();
}

void rwDialog::on_pushButton_clicked() {
    czysc();
    ustawIFiltruj();
}
