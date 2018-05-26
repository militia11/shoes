#include "matryceDialog.h"
#include "ui_matryceDialog.h"
#include <QInputDialog>
#include <QStyle>
#include <QDesktopWidget>


matryceDialog::matryceDialog(NowaMatrycaDialog *nowamat, BazaDanychManager *db,
                             QWidget *parent) :
    QDialog(parent),
    ui(new Ui::matryceDialog), dbManager(db), nowamat(nowamat), proxy(nullptr) {
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    this->setWindowFlags(Qt::Window);
    ui->tableView->verticalHeader()->setDefaultSectionSize(ui->tableView->verticalHeader()->minimumSectionSize());

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );

}

matryceDialog::~matryceDialog() {
    delete ui;
    delete proxy;
}

void matryceDialog::aktualizujTabele() {
    QHeaderView *hv = ui->tableView->horizontalHeader();
    hv->setStretchLastSection(true);
    hv->setSectionHidden(0, true);
    hv->setDefaultAlignment(Qt::AlignLeft);
    ui->tableView->sortByColumn(0, Qt::AscendingOrder);
}

void matryceDialog::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    dbManager->setMatryce();
    proxy->setDynamicSortFilter(true);
    proxy->setSourceModel(dbManager->getMatryce());
    ui->tableView->setModel(proxy);
    for (int c = 0; c < ui->tableView->horizontalHeader()->count(); ++c) {
        ui->tableView->horizontalHeader()->setSectionResizeMode(c,
                QHeaderView::ResizeToContents);
    }
    aktualizujTabele();
}

void matryceDialog::hideEvent(QHideEvent *e) {
    disconnect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
               SLOT(wybranoMatryce(const QModelIndex)));
}

QString matryceDialog::getAktualnaMatrycaNazwa() const {
    return aktualnaMatrycaNazwa;
}

void matryceDialog::on_pushButton_2_clicked() {
    if ( nowamat->exec() == QDialog::Accepted ) {
        dbManager->zachowajMatryce(nowamat->getNazwa(),
                                   nowamat->getInfonazwa());
        aktualizujTabele();
    }
}

void matryceDialog::wybranoMatryce(const QModelIndex index) {
    QModelIndex  idx = proxy->mapToSource(
                           ui->tableView->selectionModel()->currentIndex());
    aktualnaMatrycaNazwa = dbManager->pobierzNazweMatrycy(idx);
    accept();
}

int matryceDialog::selectExec() {
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tableView, SIGNAL(doubleClicked(const QModelIndex)), this,
            SLOT(wybranoMatryce(const QModelIndex)));
    return QDialog::exec();
}

int matryceDialog::exec() {
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    return QDialog::exec();
}
