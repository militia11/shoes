#include "skoryDialog.h"
#include "ui_skoryDialog.h"
#include <QSqlQuery>
#include <QStyle>
#include <QDesktopWidget>
skoryDialog::skoryDialog(nowaSkoraDialog *ns, BazaDanychManager *db,
                         QWidget *parent) :
    QDialog(parent),
    ui(new Ui::skoryDialog), dbManager(db), ns(ns), m(nullptr) {
    ui->setupUi(this);
    idsk = -1;
    proxy = new QSortFilterProxyModel(this);
    this->setWindowFlags(Qt::Window);
    ui->tableViewCeny->verticalHeader()->setDefaultSectionSize(ui->tableViewCeny->verticalHeader()->minimumSectionSize());
    ui->tableViewKlienci->verticalHeader()->setDefaultSectionSize(ui->tableViewKlienci->verticalHeader()->minimumSectionSize());

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );

}

skoryDialog::~skoryDialog() {
    delete ui;
    delete proxy;
    if (m) {
        delete m;
    }
}

int skoryDialog::selectExec() {
    ui->tableViewKlienci->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tableViewKlienci, SIGNAL(doubleClicked(const QModelIndex)), this,
            SLOT(wybranoSkore(const QModelIndex)));
    return QDialog::exec();
}

int skoryDialog::exec() {
    ui->tableViewKlienci->setEditTriggers(QAbstractItemView::DoubleClicked);
    return QDialog::exec();
}

void skoryDialog::wybranoSkore(const QModelIndex index) {
    QModelIndex  idx = proxy->mapToSource(ui->tableViewKlienci->selectionModel()->currentIndex());
    aktualnaSkoraNazwa = dbManager->pobierzAktualnaSkore(idx);
    idsk = dbManager->pobierzAktualnaSkoreId(idx);
    accept();
}

void skoryDialog::updateZamSum(const QModelIndex &, const QModelIndex &, const QVector<int> &) {
    getceny();
}

void skoryDialog::aktualizujTabele() {
    QHeaderView *hv = ui->tableViewKlienci->horizontalHeader();
    hv->setStretchLastSection(true);
    hv->setSectionHidden(0, true);
    hv->setDefaultAlignment(Qt::AlignLeft);
    ui->tableViewKlienci->sortByColumn(0, Qt::AscendingOrder);
}

void skoryDialog::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    dbManager->setSkory();
    connect(dbManager->getSkory(), SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
            this, SLOT(updateZamSum(const QModelIndex &, const QModelIndex &, const QVector<int> &)));

    proxy->setDynamicSortFilter(true);
    proxy->setSourceModel(dbManager->getSkory());
    ui->tableViewKlienci->setModel(proxy);
    ui->tableViewKlienci->setSortingEnabled(true);
    for (int c = 0; c < ui->tableViewKlienci->horizontalHeader()->count(); ++c) {
        ui->tableViewKlienci->horizontalHeader()->setSectionResizeMode(c,
                QHeaderView::ResizeToContents);
    }
    aktualizujTabele();
}

void skoryDialog::hideEvent(QHideEvent *e) {
    disconnect(ui->tableViewKlienci, SIGNAL(doubleClicked(const QModelIndex)), this,
               SLOT(wybranoSkore(const QModelIndex)));
    disconnect(dbManager->getSkory(), SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &, const QVector<int> &)),
               this, SLOT(updateZamSum(const QModelIndex &, const QModelIndex &, const QVector<int> &)));

}

int skoryDialog::getIdsk() const {
    return idsk;
}

QString skoryDialog::getAktualnaSkoraNazwa() const {
    return aktualnaSkoraNazwa;
}

void skoryDialog::on_pushButton_2_clicked() {
    if ( ns->exec() == QDialog::Accepted ) {
        dbManager->zachowajSkore(ns->getNaz(), ns->getDos(), ns->getCena());
        aktualizujTabele();
    }
}

void skoryDialog::getceny() {
    QAbstractItemModel *old = ui->tableViewCeny->model();
    if (old) {
        delete old;
        old = 0;
    }
    QModelIndex idx = proxy->mapToSource(
                          ui->tableViewKlienci->selectionModel()->currentIndex());
    int id =  dbManager->getSkory()->data(
                  dbManager->getSkory()->index(idx.row(), 0)).toInt();
    QString que = QString("select * from cena where skora_id=%1;").arg(id);
    QSqlQuery q(que);
    m = dbManager->getSqlModelForQuery(&q);
    if (m) {
        ui->tableViewCeny->setModel(m);
        m->setHeaderData(1, Qt::Horizontal, QString("CENA"));
        m->setHeaderData(2, Qt::Horizontal, QString("DATA"));
    }
    ui->tableViewCeny->hideColumn(0);
    ui->tableViewCeny->hideColumn(3);
    ui->tableViewCeny->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->tableViewCeny->update();
}

void skoryDialog::on_tableViewKlienci_clicked(const QModelIndex &index) {
    getceny();
}
