#include "noweZamowienieDialog.h"
#include "ui_noweZamowienieDialog.h"
#include "Delegate.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QModelIndex>
#include "DelegateArrows.h"

noweZamowienieDialog::noweZamowienieDialog(handlowceDialog *wybHandlDialog,
        BazaDanychManager *db, modeleDialog *modeleDialog,
        klienciDialog *dialog,
        QWidget *parent) :
    QDialog(parent),
    dbManager(db),
    idZamowienia(0),
    modelDialog(modeleDialog),
    dialog(dialog),
    dialogHandl(wybHandlDialog),
    ui(new Ui::noweZamowienieDialog),
    zamowienie(0),
    ktoraPozycja(0) {
    ui->setupUi(this);
    ui->checkBox->setChecked(false);

    ui->calendarWidget->setGridVisible(true);
    ui->calendarWidgetRealizacja->setGridVisible(true);
    setPlainTextEnabled(false);
    ui->calendarWidget->setSelectedDate(QDate::currentDate());
    ui->calendarWidgetRealizacja->setSelectedDate(QDate::currentDate().addDays(14));
    NotEditableDelegate *del = new NotEditableDelegate(this);
    for (int i = 0; i < 6; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, del);
    }
    DelegateArrows *delArrow = new DelegateArrows(this);
    for (int i = 6; i < 21; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, delArrow);
    }
    ui->tableViewZam->setItemDelegateForColumn(21, del);

}

noweZamowienieDialog::~noweZamowienieDialog() {
    delete ui;
}

void noweZamowienieDialog::obliczSume(QStandardItem *it) {
    int suma = 0;
    int wszystkie = 0;
    int rzad = it->row();
    for (int i = 6; i < 21; i++) {
        suma += zamowienie->data(zamowienie->index(rzad, i),
                                 Qt::DisplayRole).toInt();
    }
    zamowienie->setData(zamowienie->index(rzad, 21), QVariant(suma));

    for (int j = 0; j <  zamowienie->rowCount(); j++) {
        wszystkie += zamowienie->data(zamowienie->index(j, 21),
                                      Qt::DisplayRole).toInt();
    }
    ui->lcdNumber->setText(QString::number(wszystkie));
}

void noweZamowienieDialog::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        wyczysc();
    }
    QDialog::keyPressEvent(event);
}

void noweZamowienieDialog::on_pushButton_5_clicked() {
    if (dialog->selectExec() == QDialog::Accepted) {
        ui->labelKlient->setText(dialog->getAktualnyKlientNazwa());
    }
}

void noweZamowienieDialog::wyczysc() {
    ui->calendarWidget->setSelectedDate(QDate::currentDate());
    ui->calendarWidgetRealizacja->setSelectedDate(QDate::currentDate().addDays(14));
    ui->labelKlient->clear();
    ui->labelHandlowiec->clear();
    ui->lineEditPapier->clear();
    ui->checkBox->setChecked(false);
    if (zamowienie != 0) {
        delete zamowienie;
        zamowienie = 0;
    }
    ui->tableViewZam->update();
    uwagi.clear();
    ui->plainTextEditU1->clear();
    ui->plainTextEditU2->clear();
}

void noweZamowienieDialog::setNr(const QString &value)
{
    nr = value;
}

void noweZamowienieDialog::on_buttonBox_accepted() {
    if (ui->labelKlient->text().isEmpty()) {
        QMessageBox::warning(this, "BRAK WYMAGANYCH PÓL",
                             " <FONT COLOR='#000080'>Nie można zaakceptować bez wskazania klienta. ",
                             QMessageBox::Ok);
    } else if (ui->labelHandlowiec->text().isEmpty()) {
        QMessageBox::warning(this, "BRAK WYMAGANYCH PÓL",
                             " <FONT COLOR='#000080'>Nie można zaakceptować bez wskazania handlowca. ",
                             QMessageBox::Ok);
    } else {
        if (dbManager->zamowienie(ui->calendarWidget->selectedDate(),
                                  ui->calendarWidgetRealizacja->selectedDate(),
                                  uwagi, ui->plainTextEditU2->toPlainText(), ui->lineEditPapier->text(), zamowienie)) {
            wyczysc();
            accept();
        } else {
            QMessageBox::warning(this, "NIEPOWODZENIE",
                                 " <FONT COLOR='#000080'>Dodanie zamówienia nie powiodło się. ",
                                 QMessageBox::Ok);
        }
    }
}

void noweZamowienieDialog::on_buttonBox_rejected() {
    wyczysc();
    reject();
}

void noweZamowienieDialog::on_pushButton_9_clicked() {
    if (dialogHandl->selectExec() == QDialog::Accepted) {
        ui->labelHandlowiec->setText(dialogHandl->getAktualnyHandlNazwa());
    }
}

void noweZamowienieDialog::ustawTabeleHeaders() {
    if (ktoraPozycja == 0) {
        QHeaderView *hv = ui->tableViewZam->horizontalHeader();
        hv->setMinimumSectionSize(2);
        for (int c = 0; c < ui->tableViewZam->horizontalHeader()->count(); ++c) {
            ui->tableViewZam->horizontalHeader()->setSectionResizeMode(c,
                    QHeaderView::ResizeToContents);
        }
        hv->setDefaultAlignment(Qt::AlignLeft);
        hv->setStretchLastSection(true);
    }
}

void noweZamowienieDialog::on_pushButtonModel_clicked() {
    modelDialog->setFixedSize(modelDialog->size());
    if (modelDialog->selectExec() == QDialog::Accepted) {
        QList<QStandardItem *> rzad = dbManager->zwrocWierszModel();
        zamowienie->insertRow(ktoraPozycja, rzad);
        ustawTabeleHeaders();
        QStringList listaZamowienia;
        listaZamowienia << "WZÓR" << "SPÓD" << "KOLOR" <<
                        "MATRYCA " << "OCIEP" << "WKŁADKA" << "R36" << "R37"
                        << "R38"    <<
                        "R39" << "R40"
                        << "R41" << "R42" << "R43"  << "R44"
                        << "R45" << "R46" << "R47"  << "R48" << "R49" << "R50"
                        << "SUMA" << "" ;
        for (int i = 0; i < zamowienie->columnCount(); ++i) {
            zamowienie->setHeaderData(i, Qt::Horizontal, listaZamowienia[i]);
        }
        uwagi.append(QString(""));

        QModelIndex index = ui->tableViewZam->model()->index(ktoraPozycja, 10);

        ui->tableViewZam->selectionModel()->clearSelection();
        ui->tableViewZam->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
        ktoraPozycja++;
        ustawTabeleHeaders();
    }
}

void noweZamowienieDialog::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    ui->pushButton_10->setEnabled(false);
    ui->lineEditPapier->setText(nr);
    ui->lineEditPapier->setReadOnly(true);
    ktoraPozycja = 0;
    if (zamowienie == 0) {
        zamowienie = new QStandardItemModel();
        connect(zamowienie, SIGNAL(itemChanged(QStandardItem *)), this,
                SLOT(obliczSume(QStandardItem *)));
        ui->tableViewZam->setModel(zamowienie);
        connect(
            ui->tableViewZam->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            SLOT(SelectionOfTableChanged(
                     const QItemSelection &,
                     const QItemSelection &)));
    }
    ui->pushButton_5->setFocus();
}

void noweZamowienieDialog::hideEvent(QHideEvent *e) {
    QObject::disconnect(zamowienie, SIGNAL(itemChanged(QStandardItem *)), this,
                        SLOT(obliczSume(QStandardItem *)));
    ui->tableViewZam->setModel(zamowienie);
}

void noweZamowienieDialog::on_checkBox_stateChanged(int arg1) {
    if (arg1 == 0) {
        ui->lineEditPapier->setText(nr);
        ui->lineEditPapier->setReadOnly(true);
    } else {
        ui->lineEditPapier->setText(QString("A"));
        ui->lineEditPapier->setReadOnly(false);
    }
}

void noweZamowienieDialog::setPlainTextEnabled(bool aEnable) {
    ui->plainTextEditU1->setEnabled(aEnable);
}

void noweZamowienieDialog::on_pushButton_10_clicked() {
    if (zamowienie->rowCount() != 0) {
        if (ui->tableViewZam->selectionModel()->hasSelection()) {
            int row = ui->tableViewZam->selectionModel()->currentIndex().row();
            uwagi.removeAt(row);
            zamowienie->removeRow(row);
            ktoraPozycja--;
            ui->tableViewZam->update();
        }
    }
}

void noweZamowienieDialog::on_tableViewZam_clicked(const QModelIndex &index) {
    ui->plainTextEditU1->setPlainText(uwagi[index.row()]);
}

void noweZamowienieDialog::on_plainTextEditU1_textChanged() {
    if (zamowienie && zamowienie->rowCount() != 0) {
        int row = ui->tableViewZam->selectionModel()->currentIndex().row();
        if (row != -1) {
            uwagi[row] = ui->plainTextEditU1->toPlainText();
        }
    }
}

void noweZamowienieDialog::SelectionOfTableChanged(const QItemSelection &aSelected, const QItemSelection &aDeselected) {
    Q_UNUSED(aDeselected);
    bool vIsAnyItemSelected = aSelected.count() > 0;
    setPlainTextEnabled(vIsAnyItemSelected);
    ui->pushButton_10->setEnabled(vIsAnyItemSelected);
}
