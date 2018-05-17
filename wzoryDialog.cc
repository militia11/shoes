#include "wzoryDialog.h"
#include "ui_wzoryDialog.h"
#include <QStyle>
#include <QDesktopWidget>

wzoryDialog::wzoryDialog(nowywzorDialog * nw,BazaDanychManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wzoryDialog), dbManager(db),nw(nw) {
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    aktualnyWzorNr = -1;
    this->setWindowFlags(Qt::Window);

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );
}

wzoryDialog::~wzoryDialog() {
    delete proxy;
    delete ui;
}

int wzoryDialog::selectExec() {
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
            SLOT(wybranoWzor(const QModelIndex)));
    return QDialog::exec();
}

void wzoryDialog::ustawIFiltruj() {
    dbManager->getWzory()->setFilter(QString("nr_wzoru LIKE '%1%' AND opis LIKE '%2%'").arg(ui->lineEditNr->text(), ui->lineEditSkrot->text()));
}

int wzoryDialog::exec() {
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    return QDialog::exec();
}

void wzoryDialog::aktualizujTabele() {
    QHeaderView *hv = ui->tableView->horizontalHeader();
    hv->setSectionHidden(0, true);
    hv->setDefaultAlignment(Qt::AlignCenter);
    hv->setStretchLastSection(true);
    ui->tableView->sortByColumn(1, Qt::AscendingOrder);
}

void wzoryDialog::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    dbManager->setWzory();
    proxy->setSourceModel(dbManager->getWzory());
    proxy->setDynamicSortFilter(true);
    ui->tableView->setModel(proxy);
    ui->lineEditNr->clear();
    ui->lineEditSkrot->clear();
    aktualizujTabele();
    ustawIFiltruj();
}

void wzoryDialog::hideEvent(QHideEvent *e) {
    disconnect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
               SLOT(wybranoWzor(const QModelIndex)));
}

int wzoryDialog::getAktualnyWzorNr() const {
    return aktualnyWzorNr;
}

void wzoryDialog::on_pushButton_2_clicked() {
    if (nw->exec() == QDialog::Accepted) {
        dbManager->dodajWzor(nw->getWzor(), nw->getOpis());
        dbManager->getWzory()->select();
        aktualizujTabele();
    }
}

void wzoryDialog::wybranoWzor(const QModelIndex index) {
    QModelIndex  idx = proxy->mapToSource(
                           ui->tableView->selectionModel()->currentIndex());
    aktualnyWzorNr = dbManager->getNrWzoru(idx);
    accept();
}

void wzoryDialog::on_pushSzukaj_clicked() {
    ustawIFiltruj();
}
