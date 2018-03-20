#include "handlowceDialog.h"
#include "ui_handlowceDialog.h"

handlowceDialog::handlowceDialog(NowyHandlowiecDialog *nowyKliDialog,
                                 BazaDanychManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::handlowceDialog), dbManager(db), nowyKliDialog(nowyKliDialog),
    proxy(nullptr) {
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    this->setWindowFlags(Qt::Window);
}

handlowceDialog::~handlowceDialog() {
    delete proxy;
    delete ui;
}

int handlowceDialog::selectExec() {
    ui->tableViewHandlowce->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tableViewHandlowce, SIGNAL(doubleClicked(const QModelIndex)), this,
            SLOT(wybranoHandl(const QModelIndex)));
    return QDialog::exec();
}

QString handlowceDialog::getAktualnyHandlNazwa() {
    return  aktualnyHandlNazwa;
}

int handlowceDialog::exec() {
    ui->tableViewHandlowce->setEditTriggers(QAbstractItemView::DoubleClicked);
    return QDialog::exec();
}

void handlowceDialog::wybranoHandl(const QModelIndex index) {
    QModelIndex  idx = proxy->mapToSource(
                           ui->tableViewHandlowce->selectionModel()->currentIndex());
    dbManager->ustawIdAktualnegoHandl(idx);
    aktualnyHandlNazwa = dbManager->pobierzNazweAktualnegoHandl();
    accept();
}

void handlowceDialog::aktualizujTabele() {
    QHeaderView *hv = ui->tableViewHandlowce->horizontalHeader();
    hv->setStretchLastSection(true);
    hv->setSectionHidden(0, true);
    hv->setSectionHidden(5, true);
    hv->setDefaultAlignment(Qt::AlignLeft);
    ui->tableViewHandlowce->sortByColumn(0, Qt::AscendingOrder);
}

void handlowceDialog::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    dbManager->setHandlowce();
    proxy->setDynamicSortFilter(true);
    proxy->setSourceModel(dbManager->getModelHandlowce());
    ui->tableViewHandlowce->setModel(proxy);
    ui->tableViewHandlowce->setSortingEnabled(true);
    for (int c = 0; c < ui->tableViewHandlowce->horizontalHeader()->count(); ++c) {
        ui->tableViewHandlowce->horizontalHeader()->setSectionResizeMode(c,
                QHeaderView::ResizeToContents);
    }
    aktualizujTabele();
}

void handlowceDialog::hideEvent(QHideEvent *e) {
    disconnect(ui->tableViewHandlowce, SIGNAL(doubleClicked(const QModelIndex)),
               this,
               SLOT(wybranoHandl(const QModelIndex)));
}

void handlowceDialog::on_pushButton_3_clicked() {
    if (nowyKliDialog->exec() == QDialog::Accepted ) {
        dbManager->zachowajHandlowca(nowyKliDialog->getImie(),
                                     nowyKliDialog->getNazwisko(), nowyKliDialog->getSkrot(),
                                     nowyKliDialog->getUwagi());
        aktualizujTabele();
    }
}
