#include "koloryDialog.h"
#include "ui_koloryDialog.h"

koloryDialog::koloryDialog(nowyKolorDialog *dilogNowyKolor,
                           BazaDanychManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::koloryDialog), dbManager(db), nowyKolor(dilogNowyKolor) {
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    aktualnyKolor = -1;
    this->setWindowFlags(Qt::Window);
}

koloryDialog::~koloryDialog() {
    delete ui;
    delete proxy;
}

void koloryDialog::ustawIFiltruj() {
    dbManager->getKolory()->setFilter(QString("kolor LIKE '%1%' and dost_sk1 like '%2%' and dost_sk2 like '%3%' and dost_sk3 "
                                      "like '%4%' and sk1 like '%5%' and sk2 like '%6%' and sk3 like '%7%' ").arg(ui->lineEdit->text(),
                                              ui->lineEditd1->text(), ui->lineEditd2->text(),ui->lineEditd3->text(),
                                              ui->lineEdits1->text(),ui->lineEdits2->text(),ui->lineEdits3->text()));
}

int koloryDialog::selectExec() {
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
            SLOT(wybranoKolor(const QModelIndex)));
    return QDialog::exec();
}



void koloryDialog::aktualHeader() {
    QHeaderView *hv = ui->tableView->horizontalHeader();
    hv->setStretchLastSection(true);
    hv->setDefaultAlignment(Qt::AlignLeft);
    ui->tableView->sortByColumn(1, Qt::AscendingOrder);
}

void koloryDialog::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    dbManager->setKolory();
    proxy->setDynamicSortFilter(true);
    proxy->setSourceModel(dbManager->getKolory());
    ui->tableView->setModel(proxy);
    ui->tableView->setSortingEnabled(true);
    for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c) {
        ui->tableView->horizontalHeader()->setSectionResizeMode(c,
                QHeaderView::Stretch);
    }

    aktualHeader();
    ui->tableView->hideColumn(0);
    ustawIFiltruj();
}

void koloryDialog::czysc() {
    ui->lineEdit->clear();
    ui->lineEditd1->clear();
    ui->lineEditd2->clear();
    ui->lineEditd3->clear();
    ui->lineEdits1->clear();
    ui->lineEdits2->clear();
    ui->lineEdits3->clear();
}

void koloryDialog::hideEvent(QHideEvent *e) {
    czysc();
    disconnect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
               SLOT(wybranoKolor(const QModelIndex)));
}

void koloryDialog::on_pushButton_2_clicked() {
    if (nowyKolor->exec() == QDialog::Accepted) {
        dbManager->zachowajKolor(nowyKolor->getAktualnyKolor(), nowyKolor->getSk1(),
                                 nowyKolor->getSk1d(),
                                 nowyKolor->getSk2(), nowyKolor->getSk2d(), nowyKolor->getSk3(),
                                 nowyKolor->getSk3d(), nowyKolor->getSkdomi());
        aktualHeader();
    }
}

void koloryDialog::wybranoKolor(const QModelIndex index) {
    QModelIndex  idx = proxy->mapToSource(
                           ui->tableView->selectionModel()->currentIndex());
    aktualnyKolor = dbManager->pobierzAktualnyKolor(idx);
    accept();
}

int koloryDialog::exec() {
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    return QDialog::exec();
}

int koloryDialog::getAktualnyKolor() const {
    return aktualnyKolor;
}

void koloryDialog::on_pushSzukaj_clicked() {
    ustawIFiltruj();
}

void koloryDialog::on_pushButton_clicked() {
    czysc();
    ustawIFiltruj();
}
