#include "mwdialog.h"
#include "ui_mwdialog.h"

int mwDialog::selectExec() {
    ui->pushButtonPu->setVisible(true);
    ui->pushButtonZw->setVisible(true);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    return QDialog::exec();
}

mwDialog::mwDialog(rozmiaryDialog *roz, BazaDanychManager *db, QWidget *parent) :
    QDialog(parent), dbManager(db), roz(roz),
    ui(new Ui::mwDialog) {
    ui->setupUi(this);
    proxy = new QSortFilterProxyModel(this);
    this->setWindowFlags(Qt::Window);
    actualLastId = -1;
    zmagazynu = true;
}

mwDialog::~mwDialog() {
    delete ui;
    delete proxy;
}

int mwDialog::exec() {
    ui->pushButtonPu->setVisible(false);
    ui->pushButtonZw->setVisible(false);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    return QDialog::exec();
}

void mwDialog::ustawIFiltruj() {
    QString f = QString("nr_wzoru LIKE '%1%' AND spnaz LIKE '%2%' AND kolor LIKE '%3%' AND rodzaj LIKE '%4%'"
                        "AND nazwa LIKE '%5%' AND wkrodzaj LIKE '%6%'").arg(
                    ui->lineEditwz->text(),ui->lineEditsp->text(), ui->lineEditkol->text(), ui->lineEditoc->text(),ui->lineEditma->text(),
                    ui->lineEditwkl->text());

    dbManager->getmw()->setFilter(f);
}

QList<QStandardItem *> mwDialog::zwrocWierszModel() {
    return roz->zwrocWierszModel();
}

void mwDialog::showEvent(QShowEvent *e) {
    ui->pushButtonZw->setEnabled(false);
    ui->pushButtonPu->setEnabled(false);
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
    czysc();
    ustawIFiltruj();
    zmagazynu = true;
    connect(
        ui->tableView->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
        SLOT(SelectionOfTableChanged(
                 const QItemSelection &,
                 const QItemSelection &)));
    dbManager->setPz();
}

void mwDialog::hideEvent(QHideEvent *e) {

}

void mwDialog::on_pushButtonZw_clicked() {
    QModelIndex idx = proxy->mapToSource(
                          ui->tableView->selectionModel()->currentIndex());
    int id = dbManager->zwrocAktualnyModelIdMw(idx);
    actualLastId = id;
    roz->setCurId(id);
    roz->setFixedSize(roz->size());
    roz->setWindowTitle("Pobierz z magazynu wolne");
    if(roz->exec()==QDialog::Accepted) {
        zmagazynu = true;
        accept();
    }
}

void mwDialog::on_pushButtonPu_clicked() {
    zmagazynu = false;
    QModelIndex idx = proxy->mapToSource(
                          ui->tableView->selectionModel()->currentIndex());
    int id = dbManager->zwrocAktualnyModelIdMw(idx);
    dbManager->ustawAktualnyModelMWId(id);

    accept();
}

void mwDialog::on_pushButtonSzukaj_clicked() {
    ustawIFiltruj();
}

void mwDialog::czysc() {
    ui->lineEditwz->clear();
    ui->lineEditkol->clear();
    ui->lineEditma->clear();
    ui->lineEditoc->clear();
    ui->lineEditsp->clear();
    ui->lineEditwkl->clear();
}

void mwDialog::on_pushButton_clicked() {
    czysc();
    ustawIFiltruj();
}

bool mwDialog::getZmagazynu() const {
    return zmagazynu;
}

void mwDialog::SelectionOfTableChanged(const QItemSelection &aSelected, const QItemSelection &aDeselected) {
    bool vIsAnyItemSelected = aSelected.count() > 0;
    ui->pushButtonZw->setEnabled(vIsAnyItemSelected);
    ui->pushButtonPu->setEnabled(vIsAnyItemSelected);
}

int mwDialog::getActualLastId() const {
    return actualLastId;
}

void mwDialog::on_pushButton_2_clicked() {
    QModelIndex idx = proxy->mapToSource(
                          ui->tableView->selectionModel()->currentIndex());
    int id = dbManager->zwrocAktualnyModelIdMw(idx);
    actualLastId = id;
    roz->setCurId(id);
    roz->setInsertExec(true);
    roz->setFixedSize(roz->size());
    roz->setWindowTitle("Pobranie z magazynu wolne");
    roz->exec();
}
