#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QCloseEvent>
#include <QSettings>
#include "nowyKlientDialog.h"
#include "Klient.h"
#include <QMessageBox>
#include "Delegate.h"
#include "delegateKli.h"
#include <unistd.h>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    nrkar = 65;
    kl = 62;
    klnr = 52;
    wz = 52;
    oc = 52;
    ma = 52;
    kol = 52;
    sp = 52;
    wkl = 52;
    s123 = 56;
    uz = 42;
    ha = 42;
    daty = 97;
    spnazproc = 74;
    wysylkaMode = false;
    ui->toolBar->setIconSize(QSize(36, 36));
    dbManager = new BazaDanychManager();
    rwDial = new rwDialog(dbManager, this);
    dialog = new UstawieniaForm(dbManager, this);
    dialogzdj = new ZdjecieDialog(this);
    dialogzdj->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    dialognowyHandl = new NowyHandlowiecDialog(this);
    dialogHandl = new handlowceDialog(dialognowyHandl, dbManager, this);
    dialognowyKlient = new nowyKlientDialog(dialogHandl,this);
    del = new  Delegate(dbManager, this);
    dialogKlienci = new klienciDialog(dialognowyKlient, dbManager, this);
    dialogNowaWkl = new NowaWkladkaDialog(this);
    dialogwkladka = new wkladkaDialog(dialogNowaWkl, dbManager, this);
    dialognskora = new nowaSkoraDialog(this);
    dialogskory = new skoryDialog(dialognskora, dbManager, this);
    dilogNowyKolor = new nowyKolorDialog(dbManager,dialogskory, this);
    dialogkolory = new koloryDialog( dilogNowyKolor, dbManager, this);
    dialognspod = new nowySpodDialog(this);
    dialogspody = new spodyDialog(dialogzdj, dialognspod, dbManager, this);
    dno = new noweociepdialog(this);
    dialogocieplenie = new ocieplenieDialog(dno,dbManager, this);

    nowaMatryca = new NowaMatrycaDialog(this);
    dialogmatryce = new matryceDialog(nowaMatryca, dbManager, this);
    dialonwzor = new nowywzorDialog(this);
    dialogwzory = new wzoryDialog(dialonwzor, dbManager, this);
    dialognowyModel = new owyModelDialog(dialogwkladka,
                                         dialogocieplenie, dialogwzory,
                                         dialogskory, dialogkolory,
                                         dialogspody, dialogmatryce, dbManager,
                                         this);
    dialogmodele = new modeleDialog(dialogzdj, dialognowyModel, dbManager, this);

    rozkroje = new RozkrojeDialog(dbManager, this);
    dorozkroju = new DoRozkrojuDialog(this);
    log = new logowanieDialog(dbManager, this);
    rozmDialo= new    rozmiaryDialog( dbManager, this);
    mw = new mwDialog(rozmDialo,dbManager,  this);
    pz = new pzDialog(rozmDialo,dbManager,  this);
    dialogNoweZamowienie = new noweZamowienieDialog(mw, dialogHandl, dbManager, dialogmodele, dialogKlienci, this);
    proxy = new QSortFilterProxyModel(this);
    archiwumMode = false;
    if (!dbManager->polacz()) {
        ustawieniaBazy();
    }
    while(!logowanie());
    ui->labelPodglad->setFixedHeight(196);
    ui->labelPodglad->setFixedWidth(274);
    ui->labelPodglad->setScaledContents(true);

    ui->tableViewZam->setContextMenuPolicy(Qt::CustomContextMenu);
    podlaczSygnaly();
    createCombos();
    dbManager->filterZamowien.status = QString("WPROWADZONE");
    filtruj();
    connect(dbManager->getModelZamowienia(), SIGNAL(dataChanged(const QModelIndex &,
            const QModelIndex &, const QVector<int> &)), this,
            SLOT(updateZamSum(const QModelIndex &, const QModelIndex &,
                              const QVector<int> &)));
    setSumaZamowien();
    delNoEdit = new NotEditableDelegate(this);
    stadnardDel = new QItemDelegate(this);
    for (int i = 0; i < 10; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, delNoEdit);
    }
    for (int i = 25; i < 33; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, delNoEdit);
    }
    ui->tableViewZam->setItemDelegateForColumn(38, delNoEdit);
    dialogEdycjaZam = new EdycjaZamowieniaDialog(dialogKlienci, dialogHandl, dialogmodele, dbManager, this);
    connect(dialogEdycjaZam, SIGNAL(koniecEdycji()), this, SLOT(ustawIFiltruj()));
    aktualizujTabele();

    QHeaderView *hv = ui->tableViewZam->horizontalHeader();
    hv->setSectionHidden(48, true);

    ui->tableViewZam->sortByColumn(0, Qt::DescendingOrder);

    ui->tableViewZam->installEventFilter(this);
    ui->labelw->setText(QString::number(ui->tableViewZam->model()->rowCount()));
    ui->radioButton_2->setEnabled(false);
    ui->tableViewZam->verticalHeader()->setDefaultSectionSize(ui->tableViewZam->verticalHeader()->minimumSectionSize());
    ui->tableViewZam->setEditTriggers(QAbstractItemView::DoubleClicked);
    on_radioButton_clicked();
    edytuj();
    edytuj();
//    QHeaderView *verticalHeader = myTableView->verticalHeader();
//    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
//    verticalHeader->setDefaultSectionSize(24);

//    dialogKlienci->exec();
//    dialogNoweZamowienie->exec();
//    exit(1);
//    rozkroje->exec();
}

bool MainWindow::logowanie() {
    if (log->exec() == QDialog::Accepted) {
        QString text = log->getUs();
        dbManager->setUser(text);
        QString l = QString("ABIS Manager - %1").arg(text);
        this->setWindowTitle(l);
        return true;
    } else {
        return false;
    }
}

void MainWindow::aktualizujTabele() {
    proxy->setSourceModel(dbManager->getModelZamowienia());
    proxy->setDynamicSortFilter(true);
    ui->tableViewZam->setModel(proxy);
    rozciagnijWiersze();
}

void MainWindow::refreshTable() {
    dbManager->getModelZamowienia()->select();
    setSumaZamowien();
}

void MainWindow::showTable() {
    ui->tableViewZam->show();
}

void MainWindow::setSumaZamowien() {
    ui->labelSuma->setText(QString::number(dbManager->zwrocSumeZamowien()));
}

void MainWindow::updateZamSum(const QModelIndex &topLeft, const QModelIndex &bot, const QVector<int> &) {
    if (bot.column() != 46) {
        QTimer::singleShot(100, this, SLOT(refreshTable()));
    }
}

QString MainWindow::getNrZam(QModelIndex idx) {
    QString nr_zam = dbManager->getModelZamowienia()->data(dbManager->getModelZamowienia()->index(idx.row(), 1)).toString();
    int whe = nr_zam.indexOf('/');
    qDebug() << nr_zam.left(whe);
    return nr_zam.left(whe);
}

QString MainWindow::getNrZamWl(QModelIndex idx) {
    return dbManager->getModelZamowienia()->data(dbManager->getModelZamowienia()->index(idx.row(), 1)).toString();
}

int MainWindow::getiDZam(QModelIndex idx) {
    int nr_zam = dbManager->getModelZamowienia()->data(dbManager->getModelZamowienia()->index(idx.row(), 0)).toInt();

    return nr_zam;
}

QString MainWindow::prepareRozkroj() {
    int ostatniNumer = dbManager->getNumerOstatniegoRozkroju();
    int numerRozkrojuNowego = ostatniNumer + 1;
    QString nr = QString("R%1").arg(numerRozkrojuNowego);
    dbManager->stworzSzkieletRozkroju(nr);
    return nr;
}

QString MainWindow::prepareZam() {
    int ostatniNumer = dbManager->getNumerOstatniegoZamKomputerowego();
    int numerZamowieniaNowego = ostatniNumer + 1;
    QString nr = QString("B%1").arg(numerZamowieniaNowego);
    dbManager->stworzSzkieletZam(nr);
    return nr;
}

void MainWindow::ShowContextMenu(const QPoint &pos) {
    QPoint globalPos = ui->tableViewZam->mapToGlobal(pos);
    QMenu myMenu;
    QModelIndexList selection = ui->tableViewZam->selectionModel()->selectedRows();
    if (dbManager->filterZamowien.status == QString("WPROWADZONE") && ui->actionEdycja->isChecked()) {
        QIcon icon(":/zasoby/cut.png");
        myMenu.addAction( icon,"KRÓJ");
        if (selection.length() == 1) {
            QIcon iconch(":/zasoby/change.png");
            myMenu.addAction(iconch,"EDYTUJ");
        }
//        QIcon icontr(":/zasoby/trash2.png");
//        myMenu.addAction(icontr,"USUŃ");
    } else if (dbManager->filterZamowien.status == QString("ZLEC W PRODUKCJI") && ui->actionEdycja->isChecked()) {
        if (selection.length() == 1) {
            myMenu.addAction("POKAŻ ROZKRÓJ");
            myMenu.addSeparator();
        }
        QIcon iconup(":/zasoby/arrow.png");
        myMenu.addAction(iconup, "NA MAGAZYN TOWARÓW");

        //  QIcon icontr(":/zasoby/trash2.png");
        //  myMenu.addAction(icontr,"USUŃ");
    } else if (dbManager->filterZamowien.status == QString("MAGAZYN TOWARÓW")) {
        if (selection.length() == 1) {
            myMenu.addAction("ZREALIZUJ CAŁE");
            myMenu.addAction("ZREALIZUJ KONKRETNĄ ILOŚĆ");
            myMenu.addSeparator();
            myMenu.addAction("COFNIJ DO ZLEC W PRODUKCJI");
        }

    } else if (dbManager->filterZamowien.status == QString("ZREALIZOWANO")) {
        // nothing
        QIcon iconup(":/zasoby/reset.png");
        myMenu.addAction(iconup, "COFNIJ REALIZACJĘ");
    }
    QAction *selectedItem = myMenu.exec(globalPos);
    if (selectedItem) {
        QModelIndex idx = proxy->mapToSource(
                              ui->tableViewZam->selectionModel()->currentIndex());
        if (selectedItem->text() == QString("KRÓJ")) {
            std::vector<int> zamowienia;
            int id = 0;
            for (int i = 0; i < selection.count(); i++) {
                QModelIndex index = proxy->mapToSource(selection.at(i));
                id =  dbManager->getIdZamowieniaZTabeli(index);
                zamowienia.push_back(id);
            }
            prepareRozkroj();
            dbManager->copyZamowienieArch(dbManager->getDoRozkroju(zamowienia));
            if (dbManager->rozkroj(dbManager->getDoRozkroju(zamowienia))) {
                dbManager->getModelZamowienia()->select();
                rozkroje->setDodanoRozkroj(true);
                rozkroje->exec();
            } else {
                dbManager->usunSzkieletRozkroju();
                return;
            }
        } else if (selectedItem->text() == QString("EDYTUJ")) {
            QString nr_zam = getNrZam(idx);
            QString nr_zamWlasciwy = getNrZamWl(idx);
            dialogEdycjaZam->setNrZam(nr_zam);
            dialogEdycjaZam->setNrZamWl(nr_zamWlasciwy);
            dialogEdycjaZam->exec();
        } else if(selectedItem->text() == QString("POKAŻ ROZKRÓJ")) {
            rozkroje->setWskazRozkroj(true);
            rozkroje->setNrRozkrojuWskaz(dbManager->getNrRozkrojuDoWskazania(idx));
            rozkroje->exec();
        } else if (selectedItem->text() == QString("USUŃ")) {
            if (QMessageBox::question(this, "USUŃ", "<FONT COLOR='#000080'>Czy napewno usunąć?") == QMessageBox::Yes) {
                int id = 0;
                for (int i = 0; i < selection.count(); i++) {
                    QModelIndex index = selection.at(i);

                    id = dbManager->getIdZamowieniaZTabeli(index);
                    dbManager->removeZamowienie(id);
                }

                dbManager->getModelZamowienia()->select();
                QMessageBox::information(this, "ZAKTUALIZOWANO", QString(" <FONT COLOR='#0f00f0'>Usunięto %1 pozycje.").arg(
                                             QString::number(selection.count())), QMessageBox::Ok);
            }
        } else if (selectedItem->text() == QString("COFNIJ REALIZACJĘ")) {
            int id = 0;
            id = dbManager->getIdZamowieniaZTabeli(idx);
            rozmDialo->setCurId(id);
            rozmDialo->setFixedSize(rozmDialo->size());
            rozmDialo->setZrealExec(true);
            rozmDialo->setWindowTitle("COFNIJ REALIZACJĘ");
            bool sukces = false;
            if(rozmDialo->exec()==QDialog::Accepted) {
                if(dbManager->cofodejmijZrealizuj(rozmDialo->zwrocWierszModel(), id)) {
                    QString zam= dbManager->getNrZamowieniaZTabeli(idx);

                    if(dbManager->cofdodajZrealizuj(rozmDialo->zwrocWierszModel(), zam)) {
                        sukces = true;
                    }
                }
                if(sukces) {
                    QMessageBox::information(this, "REALIZACJA", QString(" <FONT COLOR='#0f00f0'>Cofnięto realizację wskazanych par.")
                                             , QMessageBox::Ok);
                    dbManager->getModelZamowienia()->select();
                } else {
                    QMessageBox::information(this, "NIE ZREALIZOWANO", QString(" <FONT COLOR='#0f00f0'>Nie udało się cofnąć realizacji.")
                                             , QMessageBox::Ok);
                }

            }
        } else if (selectedItem->text() == QString("ZREALIZUJ KONKRETNĄ ILOŚĆ")) {
            int id = 0;
            id = dbManager->getIdZamowieniaZTabeli(idx);
            rozmDialo->setCurId(id);
            rozmDialo->setFixedSize(rozmDialo->size());
            rozmDialo->setZrealExec(true);
            rozmDialo->setWindowTitle("ZREALIZUJ");
            bool sukces = false;
            if(rozmDialo->exec()==QDialog::Accepted) {
                if(dbManager->odejmijZrealizuj(rozmDialo->zwrocWierszModel(), id)) {
                    QString zam= dbManager->getNrZamowieniaZTabeli(idx);
                    if(dbManager->dodajZrealizuj(rozmDialo->zwrocWierszModel(), zam)) {
                        sukces = true;
                    }
                }
                if(sukces) {
                    QMessageBox::information(this, "REALIZACJA", QString(" <FONT COLOR='#0f00f0'>Zrealizowano wskazane pary.")
                                             , QMessageBox::Ok);
                    dbManager->getModelZamowienia()->select();
                } else {
                    QMessageBox::information(this, "NIE ZREALIZOWANO", QString(" <FONT COLOR='#0f00f0'>Nie udało się zrealizować.")
                                             , QMessageBox::Ok);
                }
            }
        } else if (selectedItem->text() == QString("ZREALIZUJ CAŁE")) {
            int id = dbManager->getIdZamowieniaZTabeli(idx);
            QString que = QString("select * from zamowienia where id=%1;").arg(id);

            QSqlQuery q(que);
            QAbstractItemModel *abmodel = dbManager->getModelForQuery(&q);
            QStandardItemModel stModel;
            QList<QStandardItem *> rzad;
            for (int j = 0; j < abmodel->columnCount(); j++) {
                rzad.append(new QStandardItem(abmodel->data(abmodel->index(0, j)).toString()));
            }
            stModel.insertRow(0, rzad);
            delete abmodel;
            QString zam= dbManager->getNrZamowieniaZTabeli(idx);
            if(dbManager->caleZrealizuj(rzad, zam, id)) {
                QMessageBox::information(this, "REALIZACJA", QString(" <FONT COLOR='#0f00f0'>Zrealizowano całe zamówienie.")
                                         , QMessageBox::Ok);
                dbManager->getModelZamowienia()->select();
            } else {
                QMessageBox::information(this, "NIE ZREALIZOWANO", QString(" <FONT COLOR='#0f00f0'>Nie udało się zrealizować.")
                                         , QMessageBox::Ok);
            }
        }  else if (selectedItem->text() == QString("NA MAGAZYN TOWARÓW")) {
            int id = 0;
            id = dbManager->getIdZamowieniaZTabeli(idx);
            rozmDialo->setCurId(id);
            rozmDialo->setFixedSize(rozmDialo->size());
            rozmDialo->setZrealExec(true);
            rozmDialo->setWindowTitle("ZREALIZUJ");
            bool sukces = false;
            if(rozmDialo->exec()==QDialog::Accepted) {
                if(dbManager->odejmijZrealizuj(rozmDialo->zwrocWierszModel(), id)) {
                    QString zam= dbManager->getNrZamowieniaZTabeli(idx);
                    if(dbManager->dodajZrealizuj(rozmDialo->zwrocWierszModel(), zam)) {
                        sukces = true;
                    }
                }
                if(sukces) {
                    QMessageBox::information(this, "REALIZACJA", QString(" <FONT COLOR='#0f00f0'>Przeniesiono na magazyn towarów wskazane pary.")
                                             , QMessageBox::Ok);
                    dbManager->getModelZamowienia()->select();
                } else {
                    QMessageBox::information(this, "NIE ZREALIZOWANO", QString(" <FONT COLOR='#0f00f0'>Nie udało się przenieść na magazyn.")
                                             , QMessageBox::Ok);
                }
            }
        }  else if (selectedItem->text() == QString("COFNIJ DO ZLEC W PRODUKCJI")) {

        }
    }
}

void MainWindow::ustawieniaBazy() {
    if (dialog->exec() == QDialog::Accepted) {
        aktualizujTabele();
    }
}

void MainWindow::podlaczSygnaly() {
    connect(ui->akcjaUstawieniaBazy, SIGNAL(triggered()), this,
            SLOT(ustawieniaBazy()));
    connect(ui->actionDodajZamowienie, SIGNAL(triggered()), this,
            SLOT(dodajZam()));
    connect(ui->tableViewZam, SIGNAL(customContextMenuRequested(const QPoint &)),
            this,
            SLOT(ShowContextMenu(const QPoint &)));
}

void  MainWindow::edytuj() {
    //todo moze tez gdy archiwum jesli bedzie arch i różny od archiwum
    if(dbManager->filterZamowien.status != QString("MAGAZYN TOWARÓW") && dbManager->filterZamowien.status != QString("ZREALIZOWANO") ) {
        if (ui->actionEdycja->isChecked()) {
            ui->actionEdycja->setIcon(QIcon(":/zasoby/unlock.png")) ;
            noblock();
            ui->actionEdycja->setToolTip("Zablokuj edycję zamówień");
        } else {
            ui->actionEdycja->setIcon(QIcon(":/zasoby/lock.png"));
            ui->actionEdycja->setToolTip("Odblokuj edycję zamówień");
            block();
        }
    } else {
        ui->actionEdycja->setChecked(false);
    }
}

void MainWindow::dodajZam() {
    QString nr = prepareZam();
    dialogNoweZamowienie->setNr(nr);
    dialogNoweZamowienie->setFixedSize(dialogNoweZamowienie->size());
    if (dialogNoweZamowienie->exec() == QDialog::Accepted) {
        ui->tableViewZam->sortByColumn(0, Qt::DescendingOrder);
        QMessageBox::information(this, "ZATWIERDZONO", "<FONT COLOR='#000080'>Dodano zamówienie. ", QMessageBox::Ok);
    } else {
        dbManager->usunSzkieletZam();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_akcjaZamknij_triggered() {
    dbManager->rozlacz();
    close();
}

void MainWindow::on_tableViewZam_clicked(const QModelIndex &index) {
    ui->labelPodglad->clear();
    QModelIndex  idx = proxy->mapToSource(
                           ui->tableViewZam->selectionModel()->currentIndex());
    qDebug() << idx.row();
    int id =  dbManager->getModelZamowienia()->data(
                  dbManager->getModelZamowienia()->index(idx.row(),
                          0)).toInt();
    ui->labelPodglad->setScaledContents(true);
    ui->labelPodglad->setPixmap(QPixmap::fromImage(
                                    dbManager->getImageZamowienia(id)));
    ui->labelPodglad->setFixedHeight(196);
    ui->labelPodglad->setFixedWidth(274);
    ui->labelPodglad->setScaledContents(true);
}

void MainWindow::dodajKlienta() {
    if (dialognowyKlient->exec() == QDialog::Accepted) {
        Klient klient(
            dialognowyKlient->getNazwa(),
            dialognowyKlient->getSkrot(),
            dialognowyKlient->getUlica(),
            dialognowyKlient->getNumerDomu(),
            dialognowyKlient->getMiasto(), dialognowyKlient->getKodPocztowy(),
            dialognowyKlient->getTel1(),
            dialognowyKlient->getTel2(),
            dialognowyKlient->getFax(), dialognowyKlient->getMail(),
            dialognowyKlient->getUwagi(),
            dialognowyKlient->getNumerTelefonu(),
            dialognowyKlient->getWoj(),
            dialognowyKlient->getKraj());
        dbManager->zachowajKlienta(klient);
    }
}

void MainWindow::dodajHandlowca() {
    if (dialognowyHandl->exec() == QDialog::Accepted) {
        dbManager->zachowajHandlowca(dialognowyHandl->getImie(),
                                     dialognowyHandl->getNazwisko(), dialognowyHandl->getSkrot(),
                                     dialognowyHandl->getUwagi());
    }
}

void MainWindow::ustawCombo(QString tabela, QComboBox *com) {
    com->clear();
    QString q = QString("select * from %1").arg(tabela);
    QSqlQuery query(q);
    QAbstractItemModel *vModel = dbManager->getModelForQuery(&query);
    com->addItem(QString(""), QVariant(0));
    if (vModel) {
        for (int i = 0; i < vModel->rowCount(); ++i) {
            QString vEventName = vModel->data(vModel->index(i, 1)).toString();
            QVariant vEventMnemonic = vModel->data(vModel->index(i, 0));
            com->addItem(
                vEventName,
                vEventMnemonic);
        }
        delete vModel;
    }
}

void MainWindow::createCombos() {
    ustawCombo("rodzaj_montazu", ui->comboBoxmont);
    ustawCombo("typ", ui->comboBoxtyp);
    ustawCombo("rodzaj_buta", ui->comboBoxb1);
    ustawCombo("rodzaj_buta_2", ui->comboBoxb2);
    ustawCombo("rodzaj_buta_3", ui->comboBoxb3);
    ustawCombo("rodzaj_buta_4", ui->comboBoxb4);
    ustawCombo("rodzaj_buta_5", ui->comboBoxb5);
    ustawCombo("rodzaj_buta_6", ui->comboBoxb6);
}

void MainWindow::on_actionKlienci_triggered() {
    dialogKlienci->setFixedSize(dialogKlienci->size());
    if (dialogKlienci->exec() == QDialog::Accepted) {
    }
}

void MainWindow::on_actionModele_triggered() {
    dialogmodele->setFixedSize(dialogmodele->size());
    ui->labelPodglad->clear();
    ui->tableViewZam->clearSelection();
    if (dialogmodele->exec() == QDialog::Accepted) {
    }
}

void MainWindow::on_pushButtonSzukaj_clicked() {
    ustawIFiltruj();
}

void MainWindow::filtruj() {
    dbManager->setZamowieniaFilter();
    setSumaZamowien();
}

void MainWindow::on_radioButton_clicked() {
    QHeaderView *hv = ui->tableViewZam->horizontalHeader();
    if (archiwumMode) {
        ui->tableViewZam->setVisible(false);
        ui->centralWidget->layout()->setAlignment(ui->horizontalLayout_2,Qt::AlignTop);
        dbManager->setTableWidokZamowienia("vzam");
        archiwumMode = false;
        wait ww;
        ww.setWindowTitle("                    Zamykam archiwum ...");
        ww.show();
        rozciagnijWiersze();
        ww.hide();
        showTable();

        if(ui->actionEdycja->isChecked())
            noblock();

    } else if(wysylkaMode) {
        ui->tableViewZam->setColumnWidth(35, 97);
        hv->setSectionHidden(48, true);

    }
    ui->tableViewZam->setColumnWidth(34, 97);
    ui->tableViewZam->setColumnWidth(35, 97);
    ui->tableViewZam->setColumnWidth(36, 136);
    ui->tableViewZam->setColumnWidth(37, 128);
    dbManager->filterZamowien.status = QString("WPROWADZONE");
    dbManager->filterZamowien.druk = -1;
    dbManager->filterZamowien.sumaNot0 = false;
    filtruj();
    ui->labelw->setText(QString::number(ui->tableViewZam->model()->rowCount()));
    ui->labelPodglad->clear();
    ui->tableViewZam->horizontalHeader()->setSectionHidden(38,true);
    hv->setSectionHidden(49, true);
    ui->pushButtondruk1->setVisible(false);
    ui->pushButtondruk2->setVisible(false);
}

void MainWindow::on_radioButton_3_clicked() {
    if (archiwumMode) {
        ui->tableViewZam->setVisible(false);
        ui->centralWidget->layout()->setAlignment(ui->horizontalLayout_2,Qt::AlignTop);

        dbManager->setTableWidokZamowienia("vzam");
        archiwumMode = false;
        wait ww;
        ww.setWindowTitle("                    Zamykam archiwum ...");
        ww.show();
        rozciagnijWiersze();
        ww.hide();
        showTable();
        if(ui->actionEdycja->isChecked())
            noblock();
        //todo we wszystkich radiobutton zrobic tez ikona zamek gdy archiwum
    }
    ui->tableViewZam->setColumnWidth(34, 97);
    ui->tableViewZam->setColumnWidth(35, 97);
    ui->tableViewZam->setColumnWidth(36, 83);
    ui->tableViewZam->setColumnWidth(37, 83);
    ui->tableViewZam->setColumnWidth(48, 69);
    ui->tableViewZam->setColumnWidth(49, 40);
    QHeaderView *hv = ui->tableViewZam->horizontalHeader();
    hv->setSectionHidden(48, false);
    hv->setSectionHidden(49, false);
    dbManager->filterZamowien.status = QString("ZLEC W PRODUKCJI");
    ui->labelPodglad->clear();
    dbManager->filterZamowien.sumaNot0 = false;
    filtruj();
    ui->labelw->setText(QString::number(ui->tableViewZam->model()->rowCount()));
    wysylkaMode = true;
    ui->tableViewZam->horizontalHeader()->setSectionHidden(38,true);
    ui->tableViewZam->horizontalHeader()->setSectionHidden(49,false);
//    dbManager->filterZamowien.druk = -1;

    ui->pushButtondruk1->setVisible(true);
    ui->pushButtondruk1->setChecked(false);
    ui->pushButtondruk2->setVisible(true);
    ui->pushButtondruk2->setChecked(false);
}

void MainWindow::on_radioButton_6_clicked() {
    if (archiwumMode) {
        ui->tableViewZam->setVisible(false);
        ui->centralWidget->layout()->setAlignment(ui->horizontalLayout_2,Qt::AlignTop);

        dbManager->setTableWidokZamowienia("vzam");
        archiwumMode = false;
        wait ww;
        ww.setWindowTitle("                    Zamykam archiwum ...");
        ww.show();
        rozciagnijWiersze();
        ww.hide();
        showTable();
        if(ui->actionEdycja->isChecked())
            noblock();
    } else if(wysylkaMode) {


        QHeaderView *hv = ui->tableViewZam->horizontalHeader();
        hv->setSectionHidden(48, true);
    }
    if(ui->actionEdycja->isChecked()) {
        ui->actionEdycja->setChecked(false);
        ui->actionEdycja->setIcon(QIcon(":/zasoby/lock.png"));
        ui->actionEdycja->setToolTip("Odblokuj edycję zamówień");
        block();
    }
    dbManager->filterZamowien.status = QString("MAGAZYN TOWARÓW");
    dbManager->filterZamowien.druk = -1;
    dbManager->filterZamowien.sumaNot0 = true;
    ui->labelPodglad->clear();
    filtruj();
    ui->labelw->setText(QString::number(ui->tableViewZam->model()->rowCount()));
    ui->tableViewZam->horizontalHeader()->setSectionHidden(38,true);
    ui->tableViewZam->setColumnWidth(36, 136);
    ui->tableViewZam->setColumnWidth(37, 128);
    ui->tableViewZam->setColumnWidth(34, 97);
    ui->tableViewZam->setColumnWidth(35,97);
    ui->tableViewZam->horizontalHeader()->setSectionHidden(49,true);
    ui->pushButtondruk1->setVisible(false);
    ui->pushButtondruk2->setVisible(false);
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Return) {
        ustawIFiltruj();
    }
    QMainWindow::keyPressEvent(event);
}

void MainWindow::on_radioButton_4_clicked() {
    if (archiwumMode) {
        ui->tableViewZam->setVisible(false);
        ui->centralWidget->layout()->setAlignment(ui->horizontalLayout_2,Qt::AlignTop);

        dbManager->setTableWidokZamowienia("vzam");
        wait ww;
        ww.setWindowTitle("                    Zamykam archiwum ...");
        ww.show();
        rozciagnijWiersze();
        ww.hide();
        showTable();
        archiwumMode = false;
        if(ui->actionEdycja->isChecked())
            noblock();
    } else if(wysylkaMode) {
        QHeaderView *hv = ui->tableViewZam->horizontalHeader();
        hv->setSectionHidden(48, true);

    }
    dbManager->filterZamowien.status = QString("");
    dbManager->filterZamowien.druk = -1;
    dbManager->filterZamowien.sumaNot0 = true;
    ui->labelPodglad->clear();
    ui->tableViewZam->setColumnWidth(36, 90);
    ui->tableViewZam->setColumnWidth(37, 90);
    filtruj();
    ui->labelw->setText(QString::number(ui->tableViewZam->model()->rowCount()));
    ui->tableViewZam->horizontalHeader()->setSectionHidden(38,false);
    ui->tableViewZam->horizontalHeader()->setSectionHidden(49,true);
    ui->pushButtondruk1->setVisible(false);
    ui->pushButtondruk2->setVisible(false);
}

void MainWindow::on_radioButton_5_clicked() {
    if (archiwumMode) {
        ui->tableViewZam->setVisible(false);
        ui->centralWidget->layout()->setAlignment(ui->horizontalLayout_2,Qt::AlignTop);

        dbManager->setTableWidokZamowienia("vzam");
        archiwumMode = false;
        wait ww;
        ww.setWindowTitle("                    Zamykam archiwum ...");
        ww.show();
        rozciagnijWiersze();
        ww.hide();
        showTable();
        if(ui->actionEdycja->isChecked())
            noblock();
    } else if(wysylkaMode) {
        ui->tableViewZam->setColumnWidth(35, 97);
        QHeaderView *hv = ui->tableViewZam->horizontalHeader();
        hv->setSectionHidden(48, true);

    }
    if(ui->actionEdycja->isChecked()) {
        ui->actionEdycja->setChecked(false);
        ui->actionEdycja->setIcon(QIcon(":/zasoby/lock.png"));
        ui->actionEdycja->setToolTip("Odblokuj edycję zamówień");
        block();
    }
    dbManager->filterZamowien.status = QString("ZREALIZOWANO");
    dbManager->filterZamowien.druk = -1;
    dbManager->filterZamowien.sumaNot0 = true;

    ui->labelPodglad->clear();
    filtruj();
    ui->labelw->setText(QString::number(ui->tableViewZam->model()->rowCount()));
    ui->tableViewZam->horizontalHeader()->setSectionHidden(38,true);
    ui->tableViewZam->horizontalHeader()->setSectionHidden(49,true);
    ui->pushButtondruk1->setVisible(false);
    ui->pushButtondruk2->setVisible(false);
}

void MainWindow::on_actionWzory_triggered() {
    dialogwzory->setFixedSize(dialogwzory->size());
    dialogwzory->exec();
}

void MainWindow::on_actionMatryce_triggered() {
    dialogmatryce->exec();
}

void MainWindow::on_actionHandlowce_triggered() {
    dialogHandl->exec();
}

void MainWindow::on_actionSk_ry_triggered() {
    dialogskory->exec();
}

void MainWindow::on_actionSpody_triggered() {
    dialogspody->setFixedSize(dialogspody->size());
    dialogspody->exec();
}

void MainWindow::on_actionKolory_triggered() {
    dialogkolory->setFixedSize(dialogkolory->size());
    dialogkolory->exec();
}

void MainWindow::on_actionWk_adki_triggered() {
    dialogwkladka->exec();
}

void MainWindow::on_comboBoxtyp_activated(const QString &arg1) {
    dbManager->filterZamowien.typ = ui->comboBoxtyp->currentText();
    filtruj();
}

void MainWindow::on_comboBoxmont_activated(const QString &arg1) {
    dbManager->filterZamowien.mont = ui->comboBoxmont->currentText();
    filtruj();
}

void MainWindow::on_comboBoxb1_activated(const QString &arg1) {
    dbManager->filterZamowien.r1 = ui->comboBoxb1->currentText();
    filtruj();
}

void MainWindow::on_comboBoxb2_activated(const QString &arg1) {
    dbManager->filterZamowien.r2 = ui->comboBoxb2->currentText();
    filtruj();
}

void MainWindow::on_comboBoxb3_activated(const QString &arg1) {
    dbManager->filterZamowien.r3 = ui->comboBoxb3->currentText();
    filtruj();
}

void MainWindow::on_comboBoxb4_activated(const QString &arg1) {
    dbManager->filterZamowien.r4 = ui->comboBoxb4->currentText();
    filtruj();

}

void MainWindow::on_comboBoxb5_activated(const QString &arg1) {
    dbManager->filterZamowien.r5 = ui->comboBoxb5->currentText();
    filtruj();
}

void MainWindow::on_comboBoxb6_activated(const QString &arg1) {
    dbManager->filterZamowien.r6 = ui->comboBoxb6->currentText();
    filtruj();
}

void MainWindow::on_pushButton_clicked() {
    ui->lineEditNrKarta->clear();
    ui->lineEditWzor->clear();
    ui->lineEditO->clear();
    ui->lineEditKlientN->clear();
    ui->lineEditKlient->clear();
    ui->lineEditMa->clear();
    ui->lineEditKol->clear();
    ui->lineEditWkl->clear();
    ui->lineEdits1->clear();
    ui->lineEdits2->clear();
    ui->lineEdits3->clear();
    ui->lineEditUzy->clear();
    ui->lineEditHan->clear();
    ui->lineEditwpr->clear();
    ui->lineEditzre->clear();
    ui->lineEditS->clear();
    ui->lineEditsnaz->clear();
    ui->lineEditsprod->clear();
    dbManager->filterZamowien.r1 = QString("");
    dbManager->filterZamowien.r2 = QString("");
    dbManager->filterZamowien.r3 = QString("");
    dbManager->filterZamowien.r4 = QString("");
    dbManager->filterZamowien.r5 = QString("");
    dbManager->filterZamowien.r6 = QString("");
    dbManager->filterZamowien.mont = QString("");
    dbManager->filterZamowien.typ = QString("");
    ui->comboBoxtyp->setCurrentIndex(0);
    ui->comboBoxmont->setCurrentIndex(0);
    ui->comboBoxb1->setCurrentIndex(0);
    ui->comboBoxb2->setCurrentIndex(0);
    ui->comboBoxb3->setCurrentIndex(0);
    ui->comboBoxb4->setCurrentIndex(0);
    ui->comboBoxb5->setCurrentIndex(0);
    ui->comboBoxb6->setCurrentIndex(0);
    ustawIFiltruj();
    ui->tableViewZam->sortByColumn(0, Qt::DescendingOrder);
}

void MainWindow::on_actionOcieplenia_triggered() {
    dialogocieplenie->exec();
}

void MainWindow::on_actionRozkroje_triggered() {
    rozkroje->exec();
}

void MainWindow::stionResized(int logicalIndex, int oldSize, int newSize) {
    switch (logicalIndex) {
    case 1: {
        nrkar = newSize;
        ui->lineEditNrKarta->setFixedWidth(nrkar);
        break;
    }
    case 2:
        kl = newSize;
        ui->lineEditKlientN->setFixedWidth(kl);
        break;
    case 3: {
        klnr = newSize;
        ui->lineEditKlient->setFixedWidth(klnr);
        break;
    }
    case 4:
        wz = newSize;
        ui->lineEditWzor->setFixedWidth(wz);
        break;
    case 5:
        sp = newSize;
        ui->lineEditS->setFixedWidth(sp);
        break;
    case 6:
        kol = newSize;
        ui->lineEditKol->setFixedWidth(kol);
        break;
    case 7:
        oc = newSize;
        ui->lineEditO->setFixedWidth(oc);
        break;
    case 8:
        ma = newSize;
        ui->lineEditMa->setFixedWidth(ma);
        break;
    case 9:
        wkl = newSize;
        ui->lineEditWkl->setFixedWidth(wkl);
        break;
    case 26:
        ui->lineEdits1->setFixedWidth(newSize);
        break;
    case 27:
        ui->lineEdits2->setFixedWidth(newSize);
        break;
    case 28:
        ui->lineEdits3->setFixedWidth(newSize);
        break;
    case 29:
        ui->lineEditsnaz->setFixedWidth(newSize);
        break;
    case 30:
        ui->lineEditsprod->setFixedWidth(newSize);
        break;
    case 31:
        ui->lineEditUzy->setFixedWidth(newSize);
        break;
    case 32:
        ui->lineEditHan->setFixedWidth(newSize);
        break;
    case 34:
        ui->lineEditwpr->setFixedWidth(newSize);
        break;
    case 35:
        ui->lineEditzre->setFixedWidth(newSize);
        break;
    default:
        break;
    }
    this->repaint();
}

void MainWindow::ustawIFiltruj() {
    dbManager->filterZamowien.nrZ = ui->lineEditNrKarta->text();
    dbManager->filterZamowien.klNaz = ui->lineEditKlientN->text();
    dbManager->filterZamowien.klNr = ui->lineEditKlient ->text();
    dbManager->filterZamowien.ociep = ui->lineEditO->text();
    dbManager->filterZamowien.wzor = ui->lineEditWzor->text();
    dbManager->filterZamowien.kolor = ui->lineEditKol->text();
    dbManager->filterZamowien.mat = ui->lineEditMa->text();
    dbManager->filterZamowien.wkladka = ui->lineEditWkl ->text();
    dbManager->filterZamowien.uzyt = ui->lineEditUzy->text();
    dbManager->filterZamowien.sk1 = ui->lineEdits1 ->text();
    dbManager->filterZamowien.sk2 = ui->lineEdits2 ->text();
    dbManager->filterZamowien.sk3 = ui->lineEdits3 ->text();
    dbManager->filterZamowien.ha = ui->lineEditHan ->text();
    dbManager->filterZamowien.snaz = ui->lineEditsnaz ->text();
    dbManager->filterZamowien.sprod = ui->lineEditsprod ->text();
    dbManager->filterZamowien.wpr = ui->lineEditwpr ->text();
    dbManager->filterZamowien.rea = ui->lineEditzre ->text();
    dbManager->filterZamowien.spn = ui->lineEditS->text();
    filtruj();
}

void MainWindow::on_radioButton_2_clicked() {
    if(wysylkaMode) {
        ui->tableViewZam->setColumnWidth(35, 97);
        QHeaderView *hv = ui->tableViewZam->horizontalHeader();
        hv->setSectionHidden(48, true);

    }

    wait ww;
    ww.setWindowTitle("                    Wczytuję archiwum ...");
    ww.show();

    dbManager->setTableWidokZamowienia("vZamArch");
    ui->tableViewZam->setVisible(false);
    ui->centralWidget->layout()->setAlignment(ui->horizontalLayout_2,Qt::AlignTop);
    rozciagnijWiersze();

    ww.hide();

    ui->tableViewZam->setVisible(true);
    archiwumMode = true;
    dbManager->filterZamowien.status = QString("");
    dbManager->filterZamowien.druk = -1;
    dbManager->filterZamowien.sumaNot0 = false;
    filtruj();
    block();
    ui->labelPodglad->clear();
    ui->labelw->setText(QString::number(ui->tableViewZam->model()->rowCount()));
    ui->tableViewZam->horizontalHeader()->setSectionHidden(49,true);
    ui->pushButtondruk1->setVisible(false);
    ui->pushButtondruk2->setVisible(false);

}

void MainWindow::on_actionWyloguj_triggered() {
    logowanie();
}

void MainWindow::on_actionEdycja_triggered() {
    edytuj();
}

void MainWindow::upButtonUpdateZdj() {
    int id = getIdUp();
    updateZdj(id);
}

void MainWindow::downButtonUpdateZdj() {
    int id = getIdDown();
    updateZdj(id);
}

int MainWindow::getIdUp() {
    QModelIndex idx =
        ui->tableViewZam->selectionModel()->currentIndex();

    if(idx.row()==0) {
        QModelIndex idxProxy = proxy->mapToSource(ui->tableViewZam->model()->index(idx.row(), 0));
        return dbManager->getModelZamowienia()->data(
                   dbManager->getModelZamowienia()->index(idxProxy.row(),
                           0)).toInt();
    } else {
        QModelIndex idxProxy = proxy->mapToSource(ui->tableViewZam->model()->index(idx.row()-1, 0));
        return dbManager->getModelZamowienia()->data(
                   dbManager->getModelZamowienia()->index(idxProxy.row(),
                           0)).toInt();
    }
}

int MainWindow::getIdDown() {
    QModelIndex idx =
        ui->tableViewZam->selectionModel()->currentIndex();

    if(idx.row()==ui->tableViewZam->model()->rowCount()-1) {
        QModelIndex idxProxy = proxy->mapToSource(ui->tableViewZam->model()->index(idx.row(), 0));
        return dbManager->getModelZamowienia()->data(
                   dbManager->getModelZamowienia()->index(idxProxy.row(),
                           0)).toInt();
    } else {
        QModelIndex idxProxy = proxy->mapToSource(ui->tableViewZam->model()->index(idx.row()+1, 0));
        return dbManager->getModelZamowienia()->data(
                   dbManager->getModelZamowienia()->index(idxProxy.row(),
                           0)).toInt();
    }
}

void MainWindow::block() {
    for (int i = 10; i < 25; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, delNoEdit);
    }
}

void MainWindow::noblock() {
    for (int i = 10; i < 25; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, stadnardDel);
    }
}

void MainWindow::updateZdj(int id) {
    ui->labelPodglad->clear();
    ui->labelPodglad->setScaledContents(true);
    ui->labelPodglad->setPixmap(QPixmap::fromImage(
                                    dbManager->getImageZamowienia(id)));

    ui->labelPodglad->setFixedHeight(196);
    ui->labelPodglad->setFixedWidth(274);
    ui->labelPodglad->setScaledContents(true);
}

bool MainWindow::eventFilter(QObject *object, QEvent *event) {
    if (object == ui->tableViewZam) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Up) {
                upButtonUpdateZdj();
                return   QMainWindow::eventFilter(object, event);
            } else if (keyEvent->key() == Qt::Key_Down) {
                downButtonUpdateZdj();
                return QMainWindow::eventFilter(object, event);
            } else {
                return QMainWindow::eventFilter(object, event);
            }
        } else {
            return QMainWindow::eventFilter(object, event);
        }
    } else {
        return QMainWindow::eventFilter(object, event);
    }
}

void MainWindow::on_actionMagazyn_wolne_triggered() {
    mw->setFixedSize(mw->size());
    mw->exec();
}

void MainWindow::rozciagnijWiersze() {
    ui->tableViewZam->horizontalHeader()->setMinimumSectionSize(15);
    ui->tableViewZam->setColumnWidth(1, nrkar);
    ui->lineEditNrKarta->setFixedWidth(nrkar);

    ui->tableViewZam->setColumnWidth(2, kl);
    ui->lineEditKlient->setFixedWidth(kl);

    ui->tableViewZam->setColumnWidth(3, klnr);
    ui->lineEditKlientN->setFixedWidth(klnr);

    ui->lineEditWzor->setFixedWidth(wz);
    ui->tableViewZam->setColumnWidth(4, wz);
    ui->tableViewZam->setColumnWidth(5, sp);
    ui->tableViewZam->setColumnWidth(6, kol);
    ui->tableViewZam->setColumnWidth(7, oc);
    ui->tableViewZam->setColumnWidth(8, ma);
    ui->tableViewZam->setColumnWidth(9, wkl);

    ui->tableViewZam->setColumnWidth(25, 51); // suma
    ui->lineEditO->setFixedWidth(oc);
    ui->lineEditMa->setFixedWidth(ma);
    ui->lineEditKol->setFixedWidth(kol);
    ui->lineEditNrKarta->setFixedWidth(nrkar);
    ui->lineEditKlient->setFixedWidth(klnr);
    ui->lineEditKlientN->setFixedWidth(kl);
    ui->lineEditWkl->setFixedWidth(wkl);
    ui->lineEditS->setFixedWidth(sp);
    ui->lineEdits1->setFixedWidth(s123);
    ui->lineEdits2->setFixedWidth(s123);
    ui->lineEdits3->setFixedWidth(s123);
    ui->lineEditUzy->setFixedWidth(uz);
    ui->lineEditHan->setFixedWidth(ha);
    ui->lineEditwpr->setFixedWidth(daty);
    ui->lineEditzre->setFixedWidth(daty);
    QHeaderView *hv = ui->tableViewZam->horizontalHeader();
    hv->setSectionHidden(0, true);
    hv->setStretchLastSection(true);
    for (int i = 39; i < 48; i++) {
        hv->setSectionHidden(i, true);
    }

    hv->setDefaultAlignment(Qt::AlignLeft);
    ui->tableViewZam->setColumnWidth(26, s123);// sk1
    ui->tableViewZam->setColumnWidth(27, s123);
    ui->tableViewZam->setColumnWidth(28, s123);
    ui->tableViewZam->setColumnWidth(29, spnazproc);
    ui->tableViewZam->setColumnWidth(30, spnazproc);
    ui->tableViewZam->setColumnWidth(31, uz);
    ui->tableViewZam->setColumnWidth(32, ha);
    ui->lineEditsnaz->setFixedWidth(spnazproc);
    ui->lineEditsprod->setFixedWidth(spnazproc);

    ui->tableViewZam->setColumnWidth(34, daty);
    ui->tableViewZam->setColumnWidth(35, daty);

    ui->tableViewZam->setColumnWidth(37, 25);
    connect(hv, SIGNAL(sectionResized(int, int, int)), this,
            SLOT(stionResized(int,
                              int, int)));
    for (int c = 10; c < 25;     c++) {
        ui->tableViewZam->horizontalHeader()->setSectionResizeMode(c,
                QHeaderView::Fixed);
        ui->tableViewZam->setColumnWidth(c, 30);
    }
    hv->setSectionHidden(33,true);
}

void MainWindow::on_actionRozch_d_wewn_trzny_triggered() {
    rwDial->setFixedSize(rwDial->size());
    rwDial->exec();
}

void MainWindow::on_actionPrzyj_cie_zewn_trzne_triggered() {
    pz->setFixedSize(pz->size());
    pz->exec();
}

void MainWindow::on_actionEksport_do_Excela_triggered() {
    QAbstractItemModel *model = ui->tableViewZam->model();

    QString linki =  QFileDialog::getSaveFileName(this, tr("Export do Excela"),  QDir::homePath(), tr("Zapisz plik CSV (*.csv)"));
    int x = 0;
    QString exportdata;

    int counthidden=0, jint = 0;

    while (jint < model->columnCount()) {
        counthidden+=ui->tableViewZam->isColumnHidden(jint);
        jint++;
    }

    int w = 1;
    while (x < model->columnCount()) {

        if (!ui->tableViewZam->isColumnHidden(x)) {

            exportdata.append(model->headerData(x,Qt::Horizontal,Qt::DisplayRole).toString());

            if (model->columnCount() - w > counthidden)
                exportdata.append(";");
            else {
                exportdata.append("\n");

            }
            w++;
        }
        x++;

    }

    int z = 0;

    w = 1;
    while (z < model->rowCount()) {

        x = 0;

        w = 1;
        while (x < model->columnCount()) {
            if (!ui->tableViewZam->isColumnHidden(x)) {


                exportdata.append(model->data(model->index(z,x),Qt::DisplayRole).toString());

                if (model->columnCount() - w > counthidden)
                    exportdata.append(";");
                else
                    exportdata.append("\n");

                w++;
            }
            x++;

        }

        z++;
    }

    QFile plik(linki);
    plik.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);

    QTextStream stream(&plik);
    stream << exportdata;

    plik.close();
}

void MainWindow::on_pushButtondruk1_toggled(bool checked) {
    if(checked) {
        ui->pushButtondruk2->setChecked(false);
        dbManager->filterZamowien.druk = 1;
        filtruj();
    } else {
        dbManager->filterZamowien.druk = -1;
        filtruj();
    }
}

void MainWindow::on_pushButtondruk2_toggled(bool checked) {
    if(checked) {
        ui->pushButtondruk1->setChecked(false);
        dbManager->filterZamowien.druk = 0;
        filtruj();
    } else {
        dbManager->filterZamowien.druk = -1;
        filtruj();
    }
}
