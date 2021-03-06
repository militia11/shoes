#include "noweZamowienieDialog.h"
#include "ui_noweZamowienieDialog.h"
#include "Delegate.h"
#include <QMessageBox>
#include <QKeyEvent>
#include <QModelIndex>
#include <QMenu>
#include <QInputDialog>
#include <QStyle>
#include <QDesktopWidget>

noweZamowienieDialog::noweZamowienieDialog(mwDialog *roz, handlowceDialog *wybHandlDialog,
        BazaDanychManager *db, modeleDialog *modeleDialog,
        klienciDialog *dialog,
        QWidget *parent) :
    QDialog(parent),
    roz(roz),
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
    delArrow = new DelegateArrows(ui->tableViewZam);
    for (int i = 6; i < 21; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, delArrow);
    }
    ui->tableViewZam->setItemDelegateForColumn(21, del);
    ui->tableViewZam->setItemDelegateForColumn(22, del);

    ui->plainTextEditU1->installEventFilter(this);
    ui->plainTextEditU2->installEventFilter(this);
    ui->tableViewZam->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->setWindowFlags(Qt::Window);
    //this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint| Qt::WindowSystemMenuHint | Qt::WindowMaximizeButtonHint | Qt::WindowMinimizeButtonHint);
    connect(delArrow, SIGNAL(commitData(QWidget*)), this, SLOT(abra(QWidget*)));
    ui->tableViewZam->verticalHeader()->setDefaultSectionSize(ui->tableViewZam->verticalHeader()->minimumSectionSize());

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );
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

void noweZamowienieDialog::sumall() {
    int wszystkie = 0;
    for (int j = 0; j <  zamowienie->rowCount(); j++) {
        wszystkie += zamowienie->data(zamowienie->index(j, 21), Qt::DisplayRole).toInt();
    }
    ui->lcdNumber->setText(QString::number(wszystkie));
}

void noweZamowienieDialog::obliczSume(QStandardItem *it) {
    int suma = 0;
    int rzad = it->row();
    for (int i = 6; i < 21; i++) {
        suma += zamowienie->data(zamowienie->index(rzad, i),
                                 Qt::DisplayRole).toInt();
    }
    zamowienie->setData(zamowienie->index(rzad, 21), QVariant(suma));

    sumall();
}

void noweZamowienieDialog::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        if (QMessageBox::question(this, "WYJŚCIE",
                                  "<FONT COLOR='#000082'>Jesteś w trakcie dodawania zamówienia. Czy na pewno wyjść?") == QMessageBox::Yes) {
            anuluj();
            wyczysc();
            QDialog::keyPressEvent(event);
        } else {
        }
    }
}

void noweZamowienieDialog::closeEvent(QCloseEvent *e) {
    if (QMessageBox::question(this, "WYJŚCIE",
                              "<FONT COLOR='#000082'>Jesteś w trakcie dodawania zamówienia. Czy na pewno wyjść?") == QMessageBox::Yes) {
        anuluj();

        wyczysc();
        e->accept();
    } else {
        e->ignore();
    }
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
    pojemnikIdMW.clear();
    pojemnikRzad.clear();
}

void noweZamowienieDialog::anuluj() {
    if(!pojemnikIdMW.empty()) {
        bool sukces = true;
        for(int x : pojemnikIdMW) {
            if(!dbManager->usunMwDok(x)) {
                sukces = false;
            }
        }
        if(sukces) {
            QMessageBox::information(this, "PRZYWRÓCONO",
                                     " <FONT COLOR='#000082'>Przywrócono towar na magazyn. Usunięto dokumenty Rozchód wewnętrzny.",
                                     QMessageBox::Ok);
        } else {
            QMessageBox::information(this, "NIEPOWODZENIE",
                                     " <FONT COLOR='#000082'>Przywrócenie par na magazyn nie powiodło się. ",
                                     QMessageBox::Ok);
        }
    }
}

void noweZamowienieDialog::setNr(const QString &value) {
    nr = value;
}

void noweZamowienieDialog::on_buttonBox_accepted() {
    QString firstLetterZamm = ui->lineEditPapier->text().left(1);
    QString zam = ui->lineEditPapier->text();
    int x = QString::compare(firstLetterZamm, "A", Qt::CaseSensitive);
    int y = QString::compare(firstLetterZamm, "B", Qt::CaseSensitive);
    if (ui->labelKlient->text().isEmpty()) {
        QMessageBox::warning(this, "BRAK WYMAGANYCH PÓL",
                             " <FONT COLOR='#000082'>Nie można zaakceptować bez wskazania klienta. ",
                             QMessageBox::Ok);
    } else if (ui->labelHandlowiec->text().isEmpty()) {
        QMessageBox::warning(this, "BRAK WYMAGANYCH PÓL",
                             " <FONT COLOR='#000082'>Nie można zaakceptować bez wskazania handlowca. ",
                             QMessageBox::Ok);
    } else if (x != 0 && y != 0) {
        QMessageBox::warning(this, "NIEPOPRAWNE ZAMÓWIENIE",
                             " <FONT COLOR='#000082'>Zamówienie papierowe zaczynamy A, natomiast komputerowe B",
                             QMessageBox::Ok);
    }  else if (zam.count() < 2) {
        QMessageBox::warning(this, "NIEPOPRAWNE ZAMÓWIENIE",
                             " <FONT COLOR='#000082'>Uzupełnij numer zamówienia.",
                             QMessageBox::Ok);
    }  else if (dbManager->sprawdzNr(ui->lineEditPapier->text())) {
        QMessageBox::warning(this, "NIEPOPRAWNE ZAMÓWIENIE",
                             " <FONT COLOR='#000082'>Zamówienie o podanym numerze istnieje w bazie.",
                             QMessageBox::Ok);
    }  else if (ui->tableViewZam->model()->rowCount() == 0) {
        QMessageBox::warning(this, "NIEPOPRAWNE ZAMÓWIENIE",
                             " <FONT COLOR='#000082'>Dodaj pozycje do zamówienia.",
                             QMessageBox::Ok);
    }   else {
        if (dbManager->zamowienie(ui->calendarWidget->selectedDate(),
                                  ui->calendarWidgetRealizacja->selectedDate(),
                                  uwagi, ui->plainTextEditU2->toPlainText(), ui->lineEditPapier->text(), zamowienie)) {
            if(firstLetterZamm == QString("A")) {
                dbManager->usunSzkieletZam();
            }
            wyczysc();
            accept();
        } else {
            QMessageBox::warning(this, "NIEPOWODZENIE",
                                 " <FONT COLOR='#000082'>Dodanie zamówienia nie powiodło się. ",
                                 QMessageBox::Ok);
        }
    }
}

void noweZamowienieDialog::on_buttonBox_rejected() {
    if (QMessageBox::question(this, "WYJŚCIE", "<FONT COLOR='#000082'>Jesteś w trakcie dodawania zamówienia. Czy na pewno wyjść?") == QMessageBox::Yes) {
        anuluj();

        wyczysc();
        reject();
    } else {
    }
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

void noweZamowienieDialog::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    ui->lineEditPapier->setText("A");
    ui->lineEditPapier->setReadOnly(false);
    ktoraPozycja = 0;
    if (zamowienie == 0) {
        zamowienie = new QStandardItemModel();
        ui->tableViewZam->setModel(zamowienie);
        connect(zamowienie, SIGNAL(itemChanged(QStandardItem *)), this,
                SLOT(obliczSume(QStandardItem *)));
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
            if (QMessageBox::question(this, "USUŃ", "<FONT COLOR='#000082'>Czy napewno usunąć?") == QMessageBox::Yes) {
                if (zamowienie->rowCount() != 0) {
                    if (ui->tableViewZam->selectionModel()->hasSelection()) {
                        if(zamowienie->data(zamowienie->index(row, 22)).toString() == QString("MAGAZYN TOWARÓW")) {
                            int modelMWId = pojemnikRzad[row+1];
                            if(dbManager->usunMwDok(modelMWId)) {
                                pojemnikIdMW.remove(modelMWId);
                                uwagi.removeAt(row);
                                zamowienie->removeRow(row);
                                ktoraPozycja--;

                                ui->tableViewZam->update();
                                qDebug() << pojemnikIdMW.empty();
                                sumall();
                                QMessageBox::information(this, "ZAKTUALIZOWANO", " <FONT COLOR='#0f00f0'>Przywrócono towar na magazyn. Usunięto dokument Rozchód wewnętrzny.", QMessageBox::Ok);
                            } else {
                                QMessageBox::information(this, "NIEPOWODZENIE", " <FONT COLOR='#0f00f0'>Nie udało się usunąć pozycji.", QMessageBox::Ok);
                            }
                        } else {
                            uwagi.removeAt(row);
                            zamowienie->removeRow(row);
                            ktoraPozycja--;
                            ui->tableViewZam->update();
                            sumall();
                            QMessageBox::information(this, "ZAKTUALIZOWANO", " <FONT COLOR='#0f00f0'>Usunięto pozycję.", QMessageBox::Ok);
                        }
                    }
                }
            }
        } else if(selectedItem->text() == QString("KOPIUJ")) {
            bool ok;
            int ile = QInputDialog::getInt(this, "KOPIE", "Proszę o podanie ilości kopii.", 1, 1, 1000, 1, &ok);
            if (ok) {
                int row = ui->tableViewZam->currentIndex().row();
                int modelId = dbManager->idModeluL[row];
                for(int i=0; i<ile; i++) {
                    QList<QStandardItem *> list;
                    for (int column = 0; column < zamowienie->columnCount() -1; ++column) {
                        QStandardItem * itm= zamowienie->item(row, column);
                        list.append(itm->clone());
                    }
                    list.append(new QStandardItem("WPROWADZONE"));
                    zamowienie->insertRow(ktoraPozycja,list);
                    QString x =ui->plainTextEditU1->toPlainText();
                    uwagi.append(x);
                    dbManager->idModeluL.append(modelId);
                    ktoraPozycja++;
                }
            }
            int wszystkie = 0;
            for (int j = 0; j < zamowienie->rowCount(); j++) {
                wszystkie += zamowienie->data(zamowienie->index(j, 21), Qt::DisplayRole).toInt();
            }
            ui->lcdNumber->setText(QString::number(wszystkie));
        }
    }
}

void noweZamowienieDialog::abra(QWidget *) {
    ui->plainTextEditU1->setPlainText(uwagi[ui->tableViewZam->currentIndex().row()]);
}

void noweZamowienieDialog::on_pushButtonModel_2_clicked() {
    roz->setFixedSize(roz->size());
    if(roz->selectExec() == QDialog::Accepted) {
        if(roz->getZmagazynu()) {
            QList<QStandardItem *> rzad = roz->zwrocWierszModel();
            dbManager->ustawAktualnyModelMWId(roz->getActualLastId());
            zamowienie->insertRow(ktoraPozycja, rzad);
            ustawTabeleHeaders();
            QStringList listaZamowienia;
            listaZamowienia << "WZÓR" << "SPÓD" << "KOLOR" << "MATRYCA " << "OCIEPLEN" << "WKŁADKA" << "36" << "37" << "38" << "39" << "40" << "41" << "42" << "43"  << "44"
                            << "45" << "46" << "47"  << "48" << "49" << "50" << "SUMA" << "STATUS" ;
            for (int i = 0; i < zamowienie->columnCount(); ++i) {
                zamowienie->setHeaderData(i, Qt::Horizontal, listaZamowienia[i]);
            }
            uwagi.append(QString(""));
            if(ktoraPozycja==0) {
                ustawTabeleHeaders();
                ui->tableViewZam->setContextMenuPolicy(Qt::CustomContextMenu);
                connect(ui->tableViewZam, SIGNAL(customContextMenuRequested(const QPoint &)),
                        this,
                        SLOT(ShowContextMenu(const QPoint &)));
            }
            ktoraPozycja++;
            ui->plainTextEditU1->clear();
            sumall();
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
            pojemnikIdMW.push_back(dbManager->getOstRwID());
            pojemnikRzad.insert(ktoraPozycja,dbManager->getOstRwID());
        } else {
            QList<QStandardItem *> rzad = dbManager->zwrocWierszModel();
            zamowienie->insertRow(ktoraPozycja, rzad);
            ustawTabeleHeaders();
            QStringList listaZamowienia;
            listaZamowienia << "WZÓR" << "SPÓD" << "KOLOR" << "MATRYCA " << "OCIEPLEN" << "WKŁADKA" << "36" << "37" << "38" << "39" << "40" << "41" << "42" << "43"  << "44"
                            << "45" << "46" << "47"  << "48" << "49" << "50" << "SUMA" << "STATUS" ;
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
        }
    }
}
