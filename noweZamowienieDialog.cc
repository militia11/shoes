#include "noweZamowienieDialog.h"
#include "ui_noweZamowienieDialog.h"
#include "Delegate.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QModelIndex>
#include <QMenu>
#include <QInputDialog>
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
    ui->checkBox->setChecked(true);

    ui->calendarWidget->setGridVisible(true);
    ui->calendarWidgetRealizacja->setGridVisible(true);
    setPlainTextEnabled(false);
    ui->calendarWidget->setSelectedDate(QDate::currentDate());
    ui->calendarWidgetRealizacja->setSelectedDate(QDate::currentDate().addDays(14));
    NotEditableDelegate *del = new NotEditableDelegate(this);
    for (int i = 0; i < 6; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, del);
    }
    DelegateArrows *delArrow = new DelegateArrows(ui->tableViewZam);
    for (int i = 6; i < 21; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, delArrow);
    }
    ui->tableViewZam->setItemDelegateForColumn(21, del);

    ui->plainTextEditU1->installEventFilter(this);
    ui->plainTextEditU2->installEventFilter(this);
    ui->tableViewZam->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setWindowFlags(Qt::Window);
    connect(delArrow, SIGNAL(commitData(QWidget*)), this, SLOT(abra(QWidget*)));
}

bool noweZamowienieDialog::eventFilter(QObject *object, QEvent *event) {
    if (object == ui->plainTextEditU2 || object == ui->plainTextEditU1) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Return) {
                return true;
            } else {
                return QDialog::eventFilter(object, event);
            }
        } else {
            return QDialog::eventFilter(object, event);
        }
    } else {
        return QDialog::eventFilter(object, event);
    }
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
        wszystkie += zamowienie->data(zamowienie->index(j, 21), Qt::DisplayRole).toInt();
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
        ui->labelHandlowiec->setText(dbManager->zwrocNazweHandlKlienta());
    }
}

void noweZamowienieDialog::wyczysc() {
    ui->calendarWidget->setSelectedDate(QDate::currentDate());
    ui->calendarWidgetRealizacja->setSelectedDate(QDate::currentDate().addDays(14));
    ui->labelKlient->clear();
    ui->labelHandlowiec->clear();
    ui->lineEditPapier->clear();
    ui->checkBox->setChecked(true);
    if (zamowienie != 0) {
        delete zamowienie;
        zamowienie = 0;
    }
    ui->tableViewZam->update();
    uwagi.clear();
    ui->plainTextEditU1->clear();
    ui->plainTextEditU2->clear();
}

void noweZamowienieDialog::setNr(const QString &value) {
    nr = value;
}

void noweZamowienieDialog::on_buttonBox_accepted() {
    QString firstLetterZamm = ui->lineEditPapier->text().left(1);
    int x = QString::compare(firstLetterZamm, "A", Qt::CaseSensitive);
    int y = QString::compare(firstLetterZamm, "B", Qt::CaseSensitive);
    if (ui->labelKlient->text().isEmpty()) {
        QMessageBox::warning(this, "BRAK WYMAGANYCH PÓL",
                             " <FONT COLOR='#000080'>Nie można zaakceptować bez wskazania klienta. ",
                             QMessageBox::Ok);
    } else if (ui->labelHandlowiec->text().isEmpty()) {
        QMessageBox::warning(this, "BRAK WYMAGANYCH PÓL",
                             " <FONT COLOR='#000080'>Nie można zaakceptować bez wskazania handlowca. ",
                             QMessageBox::Ok);
    } else if (x != 0 && y != 0) {
        QMessageBox::warning(this, "NIEPOPRAWNE ZAMÓWIENIE",
                             " <FONT COLOR='#000080'>Zamówienie papierowe zaczynamy A, natomiast komputerowe B",
                             QMessageBox::Ok);
    } else if (dbManager->sprawdzNr(ui->lineEditPapier->text())) {
        QMessageBox::warning(this, "NIEPOPRAWNE ZAMÓWIENIE",
                             " <FONT COLOR='#000080'>Zamówienie o podanym numerze istnieje w bazie.",
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

void noweZamowienieDialog::ustawTabeleHeaders() {
    QHeaderView *hv = ui->tableViewZam->horizontalHeader();
    hv->setMinimumSectionSize(2);
    for (int c = 0; c < ui->tableViewZam->horizontalHeader()->count(); ++c) {
        ui->tableViewZam->horizontalHeader()->setSectionResizeMode(c,
                QHeaderView::ResizeToContents);
    }
    hv->setDefaultAlignment(Qt::AlignLeft);
    hv->setStretchLastSection(true);
}

void noweZamowienieDialog::on_pushButtonModel_clicked() {
    modelDialog->setFixedSize(modelDialog->size());
    if (modelDialog->selectExec() == QDialog::Accepted) {
        QList<QStandardItem *> rzad = dbManager->zwrocWierszModel();
        zamowienie->insertRow(ktoraPozycja, rzad);
        ustawTabeleHeaders();
        QStringList listaZamowienia;
        listaZamowienia << "WZÓR" << "SPÓD" << "KOLOR" << "MATRYCA " << "OCIEP" << "WKŁADKA" << "36" << "37" << "38" << "39" << "40" << "41" << "42" << "43"  << "44"
                        << "45" << "46" << "47"  << "48" << "49" << "50" << "SUMA" << "" ;
        for (int i = 0; i < zamowienie->columnCount(); ++i) {
            zamowienie->setHeaderData(i, Qt::Horizontal, listaZamowienia[i]);
        }
        uwagi.append(QString(""));

        QModelIndex index = ui->tableViewZam->model()->index(ktoraPozycja, 10);

        ui->tableViewZam->selectionModel()->clearSelection();
        ui->tableViewZam->selectionModel()->setCurrentIndex(index, QItemSelectionModel::Select);
        if(ktoraPozycja==0) {
            ustawTabeleHeaders();
            ui->tableViewZam->setContextMenuPolicy(Qt::CustomContextMenu);
            connect(ui->tableViewZam, SIGNAL(customContextMenuRequested(const QPoint &)),
                    this,
                    SLOT(ShowContextMenu(const QPoint &)));
        }
        ktoraPozycja++;
        ui->plainTextEditU1->clear();
    }
}

void noweZamowienieDialog::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    ui->lineEditPapier->setText("A");
    ui->lineEditPapier->setReadOnly(false);
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
    wyczysc();
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
}

void noweZamowienieDialog::ShowContextMenu(const QPoint &pos) {
    QPoint globalPos = ui->tableViewZam->mapToGlobal(pos);
    QMenu myMenu;
    QIcon icon1(":/zasoby/copy.png");
    myMenu.addAction( icon1,"KOPIUJ");
    QIcon icon(":/zasoby/trash2.png");
    myMenu.addAction( icon,"USUŃ");
    QAction *selectedItem = myMenu.exec(globalPos);
    if (selectedItem) {
        int row = ui->tableViewZam->selectionModel()->currentIndex().row();
        if(selectedItem->text() == QString("USUŃ")) {
            //todo usunac tez z
//            int row = ui->tableViewZam->currentIndex().row();
//           int modelId = dbManager->idModeluL[row];
            if (QMessageBox::question(this, "USUŃ", "<FONT COLOR='#000080'>Czy napewno usunąć?") == QMessageBox::Yes) {
                if (zamowienie->rowCount() != 0) {
                    if (ui->tableViewZam->selectionModel()->hasSelection()) {
                        uwagi.removeAt(row);
                        zamowienie->removeRow(row);
                        ktoraPozycja--;
                        ui->tableViewZam->update();
                    }
                }
                QMessageBox::information(this, "ZAKTUALIZOWANO", " <FONT COLOR='#0f00f0'>Usunięto pozycję.", QMessageBox::Ok);
            }
        } else if(selectedItem->text() == QString("KOPIUJ")) {
            bool ok;
            int ile = QInputDialog::getInt(this,"KOPIOWANIE", "Proszę o podanie ilości kopi.",1,1,1000,1,&ok);
            if(ok) {
                int row = ui->tableViewZam->currentIndex().row();
                int modelId = dbManager->idModeluL[row];

                for(int i=0; i<ile; i++) {
                    QList<QStandardItem *> list;
                    for (int column = 0; column < zamowienie->columnCount(); ++column) {
                        QStandardItem * itm= zamowienie->item(row, column);
                        list.append(itm->clone());
                    }
                    zamowienie->insertRow(ktoraPozycja,list);
                    QString x =ui->plainTextEditU1->toPlainText();
                    uwagi.append(x);
                    dbManager->idModeluL.append(modelId);
                    ktoraPozycja++;
                }
            }
            int wszystkie = 0;
            for (int j = 0; j <  zamowienie->rowCount(); j++) {
                wszystkie += zamowienie->data(zamowienie->index(j, 21), Qt::DisplayRole).toInt();
            }
            ui->lcdNumber->setText(QString::number(wszystkie));
        }
    }
}

void noweZamowienieDialog::abra(QWidget *) {
    ui->plainTextEditU1->setPlainText(uwagi[ui->tableViewZam->currentIndex().row()]);
}
