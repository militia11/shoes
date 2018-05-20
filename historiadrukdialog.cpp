#include "historiadrukdialog.h"
#include "ui_historiadrukdialog.h"
#include "NaglowkiZamowienia.h"

historiaDrukDialog::historiaDrukDialog(BazaDanychManager * dbManager,QWidget *parent) :
    QDialog(parent),dbManager(dbManager),
    ui(new Ui::historiaDrukDialog) {
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    this->setWindowFlags(Qt::Window);
    ui->tableView->verticalHeader()->setDefaultSectionSize(ui->tableView->verticalHeader()->minimumSectionSize());

}

historiaDrukDialog::~historiaDrukDialog() {
    delete ui;
    delete proxy;
}

void historiaDrukDialog::showEvent(QShowEvent *e) {
    dbManager->setWydruki();
    proxy->setDynamicSortFilter(true);
    proxy->setSourceModel(dbManager->getWydruki());
    ui->tableView->setModel(proxy);
    ui->tableView->setSortingEnabled(true);
    QHeaderView *hv = ui->tableView->horizontalHeader();
    hv->setStretchLastSection(true);
    hv->setSectionHidden(0, true);
    hv->setDefaultAlignment(Qt::AlignLeft);
    ui->tableView->sortByColumn(0, Qt::DescendingOrder);
    NaglowkiZamowienia::ustawNaglowkiWyd(ui->tableView, dbManager->getWydruki());
    for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c) {
        ui->tableView->horizontalHeader()->setSectionResizeMode(c,
                QHeaderView::Fixed);
    }

    ui->tableView->setColumnWidth(1, 110);
    ui->tableView->setColumnWidth(2, 110);
    ui->tableView->setColumnWidth(3, 110);
    ui->tableView->setColumnWidth(4, 110);
    ui->tableView->setColumnWidth(5, 110);
    ui->tableView->setColumnWidth(6, 110);
    ui->tableView->setColumnWidth(7, 110);
    ui->tableView->setColumnWidth(8, 110);
    ui->tableView->setColumnWidth(9, 110);
    ui->tableView->setColumnWidth(10, 110);
    for (int c = 11; c < 26;     c++) {
        ui->tableView->horizontalHeader()->setSectionResizeMode(c,
                QHeaderView::Fixed);
        ui->tableView->setColumnWidth(c, 28);
    }
    czysc();
    ustawIFiltruj();
}


void historiaDrukDialog::czysc() {
    ui->lineEditroz->clear();
    ui->lineEditnr->clear();
    ui->lineEditKlnr->clear();
    ui->lineEditKlSk->clear();
    ui->lineEditwz->clear();
    ui->lineEditkol->clear();
    ui->lineEditma->clear();
    ui->lineEditoc->clear();
    ui->lineEditsp->clear();
    ui->lineEditwkl->clear();
}

void historiaDrukDialog::ustawIFiltruj() {
    QString f = QString("wzn LIKE '%1%' AND spnum LIKE '%2%' AND kol LIKE '%3%' AND ocn LIKE '%4%'"
                        "AND man LIKE '%5%' AND wklr LIKE '%6%' and pozycja like '%7%' and nr_zamowienia like '%8%' and klnaz like '%9%' ").arg(
                    ui->lineEditwz->text(),ui->lineEditsp->text(), ui->lineEditkol->text(), ui->lineEditoc->text(),ui->lineEditma->text(),
                    ui->lineEditwkl->text(),ui->lineEditroz->text(),ui->lineEditnr->text(),ui->lineEditKlSk->text());
    f += QString(" and klnr like '%1%'").arg(ui->lineEditKlnr->text());
    dbManager->getWydruki()->setFilter(f);
}

void historiaDrukDialog::on_pushButtonSzukaj_clicked() {
    ustawIFiltruj();
}

void historiaDrukDialog::on_pushButton_clicked() {
    czysc();
    ustawIFiltruj();
}
