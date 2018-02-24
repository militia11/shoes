#include "edycjazamowieniadialog.h"
#include "ui_edycjazamowieniadialog.h"
#include "Delegate.h"
#include <QTimer>

EdycjaZamowieniaDialog::EdycjaZamowieniaDialog(klienciDialog * dialogKlienci, handlowceDialog * dialogHandl, modeleDialog * dialogmodele, BazaDanychManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EdycjaZamowieniaDialog), dbManager(db), dialogKlienci(dialogKlienci), dialogHandl(dialogHandl), dialogmodele(dialogmodele) {
    ui->setupUi(this);
    ktoraPozycja = 0;

    ui->pushButton_10->setEnabled(false);

    ui->tableViewZam->setModel(dbManager->getModelZamowienia());

    QHeaderView *hv = ui->tableViewZam->horizontalHeader();
    hv->setSectionHidden(0, true);
    hv->setSectionHidden(1, true);
    hv->setSectionHidden(2, true);
    hv->setSectionHidden(3, true);
    hv->setSectionHidden(32, true);
    hv->setStretchLastSection(true);
    for (int i = 38; i < 47; i++) {
        hv->setSectionHidden(i, true);
    }
    hv->setDefaultAlignment(Qt::AlignLeft);
    for (int c = 9; c < 25; ++c) {
        ui->tableViewZam->setColumnWidth(c, 30);
    }
    ui->tableViewZam->setColumnWidth(25, 43); // suma
    ui->tableViewZam->setColumnWidth(1, 58);
    ui->tableViewZam->setColumnWidth(2, 84);
    ui->tableViewZam->setColumnWidth(3, 48);
    ui->tableViewZam->setColumnWidth(4, 50);
    ui->tableViewZam->setColumnWidth(5, 46);
    ui->tableViewZam->setColumnWidth(6, 46);
    ui->tableViewZam->setColumnWidth(7, 50);
    ui->tableViewZam->setColumnWidth(8, 50);
    ui->tableViewZam->setColumnWidth(9, 52);
    ui->tableViewZam->setColumnWidth(26, 56);// sk1
    ui->tableViewZam->setColumnWidth(27, 56);
    ui->tableViewZam->setColumnWidth(28, 56);
    ui->tableViewZam->setColumnWidth(29, 70);
    ui->tableViewZam->setColumnWidth(30, 70);
    ui->tableViewZam->setColumnWidth(31, 85);
    ui->tableViewZam->setColumnWidth(32, 80);

    ui->tableViewZam->setColumnWidth(33, 88);
    ui->tableViewZam->setColumnWidth(34, 88);
    ui->tableViewZam->setColumnWidth(37, 25);

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
//        QList<QStandardItem *> rzad = dbManager->zwrocWierszModel();
//        dbManager->getZamowieniaSzczegoly()->insertRow(ktoraPozycja, rzad);

//        QModelIndex index = ui->tableViewZam->model()->index(ktoraPozycja, 10);
//        ui->tableViewZam->selectionModel()->clearSelection();
//        ui->tableViewZam->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
        ktoraPozycja++;
    }
}

void EdycjaZamowieniaDialog::on_pushButton_10_clicked() {
    if (ui->tableViewZam->model()->rowCount() != 0) {
        if (ui->tableViewZam->selectionModel()->hasSelection()) {
            int row = ui->tableViewZam->selectionModel()->currentIndex().row();
            ui->tableViewZam->model()->removeRow(row);
            ktoraPozycja--;
            ui->tableViewZam->update();
        }
    }
}

void EdycjaZamowieniaDialog::showEvent(QShowEvent *e) {
    ktoraPozycja = ui->tableViewZam->model()->rowCount();
    QStringList listaZamowienia;
    listaZamowienia  << "" << "KLI SKRÓT" << "KLI NR" << ""  << "WZÓR"  << "SPÓD" << "KOL" <<
                     "OCIEP" <<
                     "MAT" << "WKŁ" << "R36" << "R37" << "R38" << "R39" << "R40"  << "R41" << "R42" << "R43"
                     << "R44" << "R45" << "R46" << "R47"  << "R48" << "R49" << "R50"
                     << "SUMA"  << "SK1" << "SK2" <<  "SK3" << "SP NAZWA" <<
                     "SP PROD" << "UŻYTKOWNIK" << "HANDLOWIEC" << "DATA WPR" << "DATA REALIZ" << "UWAGI 1" << "UWAGI 2" << "DRUK" << ""
                     << "" << ""
                     << ""  << "" << ""
                     << ""  << "" << ""
                     << ""  << "" << ""
                     << ""  << "" << ""
                     << ""  << "" << ""
                     << "" << ""  << "" << "";
    for (int i = 0; i < ui->tableViewZam->model()->columnCount(); ++i) {
        ui->tableViewZam->model()->setHeaderData(i, Qt::Horizontal, listaZamowienia[i]);
    }

    setSumaZamowien();
}

void EdycjaZamowieniaDialog::hideEvent(QHideEvent *e) {
    emit koniecEdycji();
    dbManager->setHeadersGlowneZamowienia();
}

void EdycjaZamowieniaDialog::on_pushButton_6_clicked() {
    if (dialogKlienci->selectExec() == QDialog::Accepted) {
        dbManager->zmienKlientaZam(nrZam);
    }
}

void EdycjaZamowieniaDialog::on_pushButton_11_clicked() {
    if (dialogHandl->selectExec() == QDialog::Accepted) {
        dbManager->zmienHandlZam(nrZam);
    }
}

void EdycjaZamowieniaDialog::SelectionOfTableChanged(const QItemSelection &aSelected, const QItemSelection &aDeselected) {
    Q_UNUSED(aDeselected);
    bool vIsAnyItemSelected = aSelected.count() > 0;
    ui->pushButton_10->setEnabled(vIsAnyItemSelected);
}

void EdycjaZamowieniaDialog::setSumaZamowien() {
    ui->lcdNumber->setText(QString::number(dbManager->zwrocSumeZamowien()));
}