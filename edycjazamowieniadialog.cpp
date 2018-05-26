#include "edycjazamowieniadialog.h"
#include "ui_edycjazamowieniadialog.h"
#include <QTimer>
#include "NaglowkiZamowienia.h"
#include "Delegate.h"
#include <QStyle>
#include <QDesktopWidget>

EdycjaZamowieniaDialog::EdycjaZamowieniaDialog(mwDialog *rz, klienciDialog * dialogKlienci, handlowceDialog * dialogHandl, modeleDialog * dialogmodele, BazaDanychManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EdycjaZamowieniaDialog), dbManager(db), dialogKlienci(dialogKlienci), dialogHandl(dialogHandl), dialogmodele(dialogmodele), roz(rz) {
    ui->setupUi(this);
    ui->pushButton_10->setEnabled(false);

    ui->tableViewZam->setModel(dbManager->getModelZamowienia());
    connect(dbManager->getModelZamowienia(), SIGNAL(dataChanged(const QModelIndex &,
            const QModelIndex &, const QVector<int> &)), this,
            SLOT(updateZamSum(const QModelIndex &, const QModelIndex &,
                              const QVector<int> &)));

    idKli = -1;
    this->setWindowFlags(Qt::Window);
    ui->tableViewZam->verticalHeader()->setDefaultSectionSize(ui->tableViewZam->verticalHeader()->minimumSectionSize());
    delNoEdit = new NotEditableDelegate(ui->tableViewZam);
    delArrow = new EdycjaZamDelegat(ui->tableViewZam);
    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );

}

EdycjaZamowieniaDialog::~EdycjaZamowieniaDialog() {
    delete ui;
}

void EdycjaZamowieniaDialog::setNrZam(QString nrZami) {
    nrZam = nrZami;
    ui->lineEditPapier->setText(nrZam);
    QString nrzkres = nrZam;
    nrzkres +="/";
    dbManager->setZamowieniaSzczegolyFilter(nrzkres);
}

void EdycjaZamowieniaDialog::setNrZamWl(QString nrZami) {
    nrZamwl = nrZami;
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

void EdycjaZamowieniaDialog::on_pushButton_10_clicked() {
    if (QMessageBox::question(this, "USUŃ", "<FONT COLOR='#000080'>Czy napewno usunąć?") == QMessageBox::Yes) {
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
}

void EdycjaZamowieniaDialog::showEvent(QShowEvent *e) {
    setSumaZamowien();
    ui->tableViewZam->hideColumn(2);
    ui->tableViewZam->hideColumn(3);
    ui->tableViewZam->hideColumn(48);
    ui->tableViewZam->hideColumn(49);
    ui->labelKlient->setText(dbManager->getKlientSkrot(nrZamwl));
    ui->labelHandlowiec->setText(dbManager->getHanlSkrot(nrZamwl));
    ui->tableViewZam->horizontalHeader()->setMinimumSectionSize(5);
    NaglowkiZamowienia::ustawNaglowki(ui->tableViewZam, dbManager->getModelZamowienia());
    ui->tableViewZam->sortByColumn(0, Qt::AscendingOrder);
    ui->tableViewZam->horizontalHeader()->setSectionHidden(38,false);
    dbManager->EZustawIdAktualnegoKLiHandl();
    connect(
        ui->tableViewZam->selectionModel(),
        SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
        SLOT(SelectionOfTableChanged(
                 const QItemSelection &,
                 const QItemSelection &)));
    ui->tableViewZam->setItemDelegateForColumn(37, delNoEdit);
    ui->tableViewZam->setItemDelegateForColumn(38, delNoEdit);

    for (int i = 0; i < 10; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, delNoEdit);
    }
    for (int i = 25; i < 33; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, delNoEdit);
    }

    for (int i = 10; i < 25; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, delArrow);
    }
    ui->tableViewZam->hideColumn(50);
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
        int idHa = dbManager->zwrocIdHandlKlienta();
        dbManager->zmienHandlZam(nrZam, idHa);
        ui->labelHandlowiec->setText(dbManager->zwrocNazweHandlKlienta());
    }
}

void EdycjaZamowieniaDialog::SelectionOfTableChanged(const QItemSelection &aSelected, const QItemSelection &aDeselected) {
    Q_UNUSED(aDeselected);
    bool vIsAnyItemSelected = aSelected.count() > 0;
    ui->pushButton_10->setEnabled(vIsAnyItemSelected);
    ui->pushButton_6->setEnabled(vIsAnyItemSelected);
}

void EdycjaZamowieniaDialog::czysc() {
    ui->labelKlient->clear();
}

void EdycjaZamowieniaDialog::setSumaZamowien() {
    ui->lcdNumber->setText(QString::number(dbManager->zwrocSumeZamowien()));
}

void EdycjaZamowieniaDialog::on_pushButtonModel_2_clicked() {
    roz->setFixedSize(roz->size());
    if(roz->selectExec() == QDialog::Accepted) {
        if(roz->getZmagazynu()) {
            QList<QStandardItem *> rzad = roz->zwrocWierszModel();
            int idWMwModelu = roz->getActualLastId();

            dbManager->setZamowieniaSzczegolyFilterZZerami(nrZam);
            int ileWierszyMinJeden = ui->tableViewZam->model()->rowCount() - 1;
            QString pozycjaOst = dbManager->getNrOstatniejPozycjiZamowieniaZTabeli(ileWierszyMinJeden);
            int whe = pozycjaOst.indexOf('/');
            QString poz = pozycjaOst.mid(whe+1, (pozycjaOst.length()-1)- whe);

            int aPos = poz.toInt();
            int nextPos = aPos+1;
            QString nrZZam = nrZam;
            nrZZam += "/";
            QString alfa = QString::number(nextPos);
            nrZZam += alfa;
            dbManager->ustawAktualnyModelMWId(idWMwModelu);
            dbManager->utworzZamowienieZMagPobrane(rzad, idWMwModelu, nrZZam);

            if(dbManager->zachowajRW(rzad)) {
                dbManager->odejmijzMW(roz->zwrocWierszModel(), roz->getActualLastId());
            }
            for (int c = 0; c < ui->tableViewZam->horizontalHeader()->count(); ++c) {
                ui->tableViewZam->horizontalHeader()->setSectionResizeMode(c,
                        QHeaderView::Fixed);
            }

            ui->tableViewZam->setColumnWidth(0, 82);
            ui->tableViewZam->setColumnWidth(1, 82);
            ui->tableViewZam->setColumnWidth(2, 82);
            ui->tableViewZam->setColumnWidth(3, 82);
            ui->tableViewZam->setColumnWidth(4, 82);
            ui->tableViewZam->setColumnWidth(5, 82);
            for (int c = 6; c < 21;  c++) {
                ui->tableViewZam->horizontalHeader()->setSectionResizeMode(c,
                        QHeaderView::Fixed);
                ui->tableViewZam->setColumnWidth(c, 30);
            }
            QHeaderView *hv = ui->tableViewZam->horizontalHeader();
            hv->setStretchLastSection(true);
            dbManager->getModelZamowienia()->select();
            ui->tableViewZam->sortByColumn(0, Qt::AscendingOrder);
            ui->pushButtondruk1->setChecked(true);
        } else {
            dbManager->setZamowieniaSzczegolyFilterZZerami(nrZam);
            int ileWierszyMinJeden = ui->tableViewZam->model()->rowCount() - 1;
            QString pozycjaOst = dbManager->getNrOstatniejPozycjiZamowieniaZTabeli(ileWierszyMinJeden);
            int whe = pozycjaOst.indexOf('/');
            QString poz = pozycjaOst.mid(whe+1, (pozycjaOst.length()-1)- whe);

            int aPos = poz.toInt();
            int nextPos = aPos+1;
            QString nrZZam = nrZam;
            nrZZam += "/";
            QString alfa = QString::number(nextPos);
            nrZZam += alfa;
            dbManager->insertPozycjazamowienie(nrZZam);
            dbManager->getModelZamowienia()->select();
            ui->tableViewZam->sortByColumn(0, Qt::AscendingOrder);
            ui->pushButtondruk1->setChecked(true);
        }
    }
}

void EdycjaZamowieniaDialog::on_pushButtondruk1_clicked() {
    if(ui->pushButtondruk1->isChecked()) {
        dbManager->setZamowieniaSzczegolyFilterZZerami(nrZam);
    } else {
        dbManager->setZamowieniaSzczegolyFilter(nrZam);
    }
}
