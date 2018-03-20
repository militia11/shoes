#include "klienciDialog.h"
#include "ui_klienciDialog.h"

klienciDialog::klienciDialog(nowyKlientDialog *nowyKliDialog,
                             BazaDanychManager *db, QWidget *parent) :
    QDialog(parent), ui(new Ui::klienciDialog), dbManager(db),
    nowyKliDialog(nowyKliDialog), proxy(nullptr) {
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    this->setWindowFlags(Qt::Window);
}

klienciDialog::~klienciDialog() {
    delete ui;
    delete proxy;
}

int klienciDialog::selectExec() {
    ui->tableViewKlienci->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tableViewKlienci, SIGNAL(doubleClicked(const QModelIndex)), this,
            SLOT(wybranoKli(const QModelIndex)));
    return QDialog::exec();
}

int klienciDialog::exec() {
    ui->tableViewKlienci->setEditTriggers(QAbstractItemView::DoubleClicked);
    return QDialog::exec();
}

void klienciDialog::wybranoKli(const QModelIndex index) {
    QModelIndex  idx = proxy->mapToSource(
                           ui->tableViewKlienci->selectionModel()->currentIndex());
    dbManager->ustawIdAktualnegoKlienta(idx);
    aktualnyKlientNazwa = dbManager->pobierzNazweAktualnegoKlienta();
    accept();
}

void klienciDialog::aktualizujHeader() {
    QHeaderView *hv = ui->tableViewKlienci->horizontalHeader();
    hv->setStretchLastSection(true);
    hv->setDefaultAlignment(Qt::AlignLeft);
    ui->lineEditMi->setFixedWidth(132);
    ui->lineEditNr->setFixedWidth(132);
    ui->lineEditNazwaSkrot->setFixedWidth(132);
    ui->lineEditSkrot->setFixedWidth(125);
    ui->tableViewKlienci->sortByColumn(0, Qt::AscendingOrder);
    ui->tableViewKlienci->horizontalHeader()->setDefaultSectionSize(132);
}

void klienciDialog::aktualizujTabele() {
    proxy->setDynamicSortFilter(true);
    proxy->setSourceModel(dbManager->getModelKlienci());
    ui->tableViewKlienci->setModel(proxy);
    ui->tableViewKlienci->setSortingEnabled(true);
    for (int c = 0; c < ui->tableViewKlienci->horizontalHeader()->count(); ++c) {
        ui->tableViewKlienci->horizontalHeader()->setSectionResizeMode(c,
                QHeaderView::Fixed);
    }
    aktualizujHeader();
}

void klienciDialog::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    dbManager->setKlienci();
    aktualizujTabele();
    ui->lineEditNazwaSkrot->clear();
    ui->lineEditSkrot->clear();
    ui->lineEditMi->clear();
    ui->lineEditNr->clear();
    ustawIFiltruj();
}

void klienciDialog::hideEvent(QHideEvent *e) {
    disconnect(ui->tableViewKlienci, SIGNAL(doubleClicked(const QModelIndex)), this,
               SLOT(wybranoKli(const QModelIndex)));
}

QString klienciDialog::getAktualnyKlientNazwa() const {
    return aktualnyKlientNazwa;
}

void klienciDialog::ustawIFiltruj() {
    dbManager->filterKlientow.miasto = ui->lineEditMi->text();
    dbManager->filterKlientow.nazwa = ui->lineEditSkrot->text();
    dbManager->filterKlientow.skrot = ui->lineEditNazwaSkrot->text();
    dbManager->filterKlientow.nr = ui->lineEditNr->text();
    dbManager->setKlienciFilter();
}

void klienciDialog::on_pushButton_2_clicked() {
    if ( nowyKliDialog->exec() == QDialog::Accepted ) {
        Klient klient(nowyKliDialog->getNazwa(), nowyKliDialog->getSkrot(),
                      nowyKliDialog->getUlica(),
                      nowyKliDialog->getNumerDomu(),
                      nowyKliDialog->getMiasto(), nowyKliDialog->getKodPocztowy(),
                      nowyKliDialog->getTel1(),
                      nowyKliDialog->getTel2(),
                      nowyKliDialog->getFax(), nowyKliDialog->getMail(),
                      nowyKliDialog->getUwagi(),
                      nowyKliDialog->getNumerTelefonu(),
                      nowyKliDialog->getWoj(),
                      nowyKliDialog->getKraj());
        dbManager->zachowajKlienta(klient);
        aktualizujHeader();
    }
}

void klienciDialog::on_pushSzukaj_clicked() {
    ustawIFiltruj();
}

void klienciDialog::on_pushButton_clicked() {
    ui->lineEditNr->clear();
    ui->lineEditNazwaSkrot->setText("");
    ui->lineEditSkrot->setText("");
    ui->lineEditMi->setText("");
    ui->lineEditWoj->setText("");
    ui->lineEditKr->setText("");
    ui->tableViewKlienci->setModel(dbManager->getModelKlienci());
}
