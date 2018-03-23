#include "edycjazamowieniadialog.h"
#include "ui_edycjazamowieniadialog.h"
#include <QTimer>
#include "NaglowkiZamowienia.h"
#include "Delegate.h"
EdycjaZamowieniaDialog::EdycjaZamowieniaDialog(klienciDialog * dialogKlienci, handlowceDialog * dialogHandl, modeleDialog * dialogmodele, BazaDanychManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EdycjaZamowieniaDialog), dbManager(db), dialogKlienci(dialogKlienci), dialogHandl(dialogHandl), dialogmodele(dialogmodele) {
    ui->setupUi(this);
    ui->pushButton_10->setEnabled(false);

    ui->tableViewZam->setModel(dbManager->getModelZamowienia());
    connect(dbManager->getModelZamowienia(), SIGNAL(dataChanged(const QModelIndex &,
            const QModelIndex &, const QVector<int> &)), this,
            SLOT(updateZamSum(const QModelIndex &, const QModelIndex &,
                              const QVector<int> &)));

    connect(
        ui->tableViewZam->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
        SLOT(SelectionOfTableChanged(
                 const QItemSelection &,
                 const QItemSelection &)));
    NotEditableDelegate *del = new NotEditableDelegate(this);
    for (int i = 0; i < 10; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, del);
    }
    for (int i = 25; i < 33; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, del);
    }

    ui->tableViewZam->setItemDelegateForColumn(37, del);
    idKli = -1;
    this->setWindowFlags(Qt::Window);
}

EdycjaZamowieniaDialog::~EdycjaZamowieniaDialog() {
    delete ui;
}

void EdycjaZamowieniaDialog::setNrZam(QString nrZami) {
    nrZam = nrZami;
    ui->lineEditPapier->setText(nrZam);
    dbManager->setZamowieniaSzczegolyFilter(nrZam);

}

void EdycjaZamowieniaDialog::refreshTable() {
    dbManager->getModelZamowienia()->select();
    setSumaZamowien();
}

void EdycjaZamowieniaDialog::updateZamSum(const QModelIndex &topLeft, const QModelIndex &bot, const QVector<int> &) {
    if (bot.column() != 46) {
        QTimer::singleShot(100, this, SLOT(refreshTable()));
    }
}

void EdycjaZamowieniaDialog::on_pushButtonModel_clicked() {
    dialogmodele->setFixedSize(dialogmodele->size());
    if (dialogmodele->selectExec() == QDialog::Accepted) {
        QModelIndex index = ui->tableViewZam->model()->index(0, 3);
        int kli = ui->tableViewZam->model()->data(index, Qt::DisplayRole).toInt();
        QModelIndex index2 = ui->tableViewZam->model()->index(0, 46);
        int handl =  ui->tableViewZam->model()->data(index2, Qt::DisplayRole).toInt();
        dbManager->insertPozycjazamowienie(nrZam, kli, handl);
        dbManager->getModelZamowienia()->select();
        ui->tableViewZam->sortByColumn(0, Qt::AscendingOrder);
    }
}

void EdycjaZamowieniaDialog::on_pushButton_10_clicked() {
    if (ui->tableViewZam->model()->rowCount() != 0) {
        if (ui->tableViewZam->selectionModel()->hasSelection()) {
            int row = ui->tableViewZam->selectionModel()->currentIndex().row();
            QModelIndex index = ui->tableViewZam->model()->index(row, 0);
            int id = ui->tableViewZam->model()->data(index, Qt::DisplayRole).toInt();
            dbManager->removeZamowienie(id);
            dbManager->getModelZamowienia()->select();
        }
    }
}

void EdycjaZamowieniaDialog::showEvent(QShowEvent *e) {
    ui->tableViewZam->horizontalHeader()->setMinimumSectionSize(5);
    NaglowkiZamowienia::ustawNaglowki(ui->tableViewZam, dbManager->getModelZamowienia());
    ui->tableViewZam->sortByColumn(0, Qt::AscendingOrder);
    setSumaZamowien();
    ui->tableViewZam->hideColumn(2);
    ui->tableViewZam->hideColumn(3);
    ui->tableViewZam->hideColumn(48);
    ui->tableViewZam->hideColumn(49);
    ui->labelKlient->setText(dbManager->getKlientSkrot(nrZam));
    ui->tableViewZam->sortByColumn(0);
}

void EdycjaZamowieniaDialog::hideEvent(QHideEvent *e) {
    czysc();
    dbManager->setHeadersGlowneZamowienia();
    emit koniecEdycji();
}

void EdycjaZamowieniaDialog::on_pushButton_6_clicked() {
    if (dialogKlienci->selectExec() == QDialog::Accepted) {
        dbManager->zmienKlientaZam(nrZam);
        ui->labelKlient->setText(dialogKlienci->getAktualnyKlientNazwa());
        int idHa  =dbManager->zwrocIdHandlKlienta();
        dbManager->zmienHandlZam(nrZam, idHa);
    }
}

void EdycjaZamowieniaDialog::SelectionOfTableChanged(const QItemSelection &aSelected, const QItemSelection &aDeselected) {
    Q_UNUSED(aDeselected);
    bool vIsAnyItemSelected = aSelected.count() > 0;
    ui->pushButton_10->setEnabled(vIsAnyItemSelected);
}

void EdycjaZamowieniaDialog::czysc() {
    ui->labelKlient->clear();
}

void EdycjaZamowieniaDialog::setSumaZamowien() {
    ui->lcdNumber->setText(QString::number(dbManager->zwrocSumeZamowien()));
}
