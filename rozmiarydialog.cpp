#include "rozmiarydialog.h"
#include "ui_rozmiarydialog.h"
#include <QKeyEvent>
#include <QMessageBox>

rozmiaryDialog::rozmiaryDialog(BazaDanychManager *db, QWidget *parent) :
    QDialog(parent),dbManager(db), stModel(nullptr),
    ui(new Ui::rozmiaryDialog) {
    curId = -1;
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    ui->lineEdit36->installEventFilter(this);
    ui->lineEdit37->installEventFilter(this);
    ui->lineEdit38->installEventFilter(this);
    ui->lineEdit39->installEventFilter(this);
    ui->lineEdit40->installEventFilter(this);
    ui->lineEdit41->installEventFilter(this);
    ui->lineEdit42->installEventFilter(this);
    ui->lineEdit43->installEventFilter(this);
    ui->lineEdit44->installEventFilter(this);
    ui->lineEdit45->installEventFilter(this);
    ui->lineEdit46->installEventFilter(this);
    ui->lineEdit47->installEventFilter(this);
    ui->lineEdit48->installEventFilter(this);
    ui->lineEdit49->installEventFilter(this);
    ui->lineEdit50->installEventFilter(this);
    insertExec = false;
    zrealExec = false;
    zrealCofExec = false;
    connect(ui->buttonBox, SIGNAL(accepted()),this, SLOT(acceptRoz()));
}

rozmiaryDialog::~rozmiaryDialog() {
    delete ui;
}

void rozmiaryDialog::updateCurrentRow() {
    QAbstractItemModel *old = ui->tableViewZam->model();
    if (old) {
        delete old;
        old = 0;
    }

    QString que = QString("select * from widokmw where mid=%1;").arg(curId);
    QSqlQuery q(que);
    QAbstractItemModel *abmodel = dbManager->getModelForQuery(&q);
    stModel = new QStandardItemModel();

    for (int i = 0; i < abmodel->rowCount(); i++) {
        QList<QStandardItem *> rzad;
        for (int j = 0; j < abmodel->columnCount(); j++) {
            rzad.append(new QStandardItem(abmodel->data(abmodel->index(i, j)).toString()));
        }
        stModel->insertRow(i, rzad);
        rzad.clear();
    }

    delete abmodel;
    if (stModel) {
        ui->tableViewZam->setModel(stModel);
        ui->tableViewZam->setColumnHidden(0, true);
        ui->tableViewZam->setColumnHidden(1, true);
        for (int c = 8; c < 23;     c++) {
            ui->tableViewZam->horizontalHeader()->setSectionResizeMode(c,
                    QHeaderView::Fixed);
            ui->tableViewZam->setColumnWidth(c, 30);
        }
        ui->tableViewZam->setColumnWidth(23,59);
        QStringList lista;
        lista << "" << "" << "WZÓR"  << "SPÓD" << "KOLOR" << "OCIEPLENIE" << "MATRYCA" <<
              "WKŁADKA"  <<  "36" << "37" << "38" << "39" << "40"    << "41" << "42" << "43"
              << "44" << "45" << "46" << "47"    << "48" << "49" << "50" << "SUMA";
        for (int i = 0; i < ui->tableViewZam->model()->columnCount(); ++i) {
            ui->tableViewZam->model()->setHeaderData(i, Qt::Horizontal, lista[i]);
        }
        ui->horizontalLayout->update();
    }
    ui->tableViewZam->update();
}

void rozmiaryDialog::updateCurrentRowZreal() {
    QAbstractItemModel *old = ui->tableViewZam->model();
    if (old) {
        delete old;
        old = 0;
    }

    QString que = QString("select * from vzam where zamowienia_id=%1;").arg(curId);
    QSqlQuery q(que);
    QAbstractItemModel *abmodel = dbManager->getModelForQuery(&q);
    stModel = new QStandardItemModel();

    for (int i = 0; i < abmodel->rowCount(); i++) {
        QList<QStandardItem *> rzad;
        for (int j = 0; j < abmodel->columnCount(); j++) {
            rzad.append(new QStandardItem(abmodel->data(abmodel->index(i, j)).toString()));
        }
        stModel->insertRow(i, rzad);
        rzad.clear();
    }

    delete abmodel;
    if (stModel) {
        ui->tableViewZam->setModel(stModel);
        for (int c = 10; c < 25;     c++) {
            ui->tableViewZam->horizontalHeader()->setSectionResizeMode(c,
                    QHeaderView::Fixed);
            ui->tableViewZam->setColumnWidth(c, 30);
        }
        ui->tableViewZam->setColumnWidth(25,59);
        QStringList lista;
        ui->tableViewZam->hideColumn(0);
        ui->tableViewZam->hideColumn(1);
        ui->tableViewZam->hideColumn(2);
        ui->tableViewZam->hideColumn(3);
        for(int i=26; i<50; i++) {
            ui->tableViewZam->hideColumn(i);
        }
        lista  << "" << "NR ZAM" << "KL SKR" << "KL NR"  << "WZÓR"  << "SPÓD" << "KOL" <<
               "OCIE" <<
               "MAT" << "WKŁ" << "36" << "37" << "38" << "39" << "40"    << "41" << "42" << "43"
               << "44" << "45" << "46" << "47"    << "48" << "49" << "50"
               << "SUMA"  << "SK1" << "SK2" << "SK3" << "SP NAZWA" <<
               "SP PROD" << "UŻY" << "HAN" << "DATA WPR" << "DATA WPR"  << "DATA REA" << "REKORD" << "CAŁE ZAM" << "STATUS"  << ""
               << ""  << "" << ""
               << ""  << "" << ""
               << ""  << "" << "ROZKRÓJ"
               << "DRUK"  << "" << ""
               << "" << ""  << "" << "";
        for (int i = 0; i < ui->tableViewZam->model()->columnCount(); ++i) {
            ui->tableViewZam->model()->setHeaderData(i, Qt::Horizontal, lista[i]);
        }
        ui->horizontalLayout->update();
    }
    ui->tableViewZam->update();
}

void rozmiaryDialog::showEvent(QShowEvent *e) {
    wyczyscPola();
    if(zrealExec || zrealCofExec) {
        updateCurrentRowZreal();
    } else {
        updateCurrentRow();
    }
    if(insertExec) {
        ui->labeldOD->setVisible(true);
        ui->labelpOB->setVisible(false);
        ui->labelpRZEN->setVisible(false);
    } else if(zrealExec || zrealCofExec) {
        ui->labeldOD->setVisible(false);
        ui->labelpOB->setVisible(false);
        ui->labelpRZEN->setVisible(true);
    } else {
        ui->labeldOD->setVisible(false);
        ui->labelpOB->setVisible(true);
        ui->labelpRZEN->setVisible(false);
    }

    ui->lineEdit36->setFocus();
}

void rozmiaryDialog::hideEvent(QHideEvent *e) {
    curId = -1;
    insertExec = false;
    zrealExec = false;
    zrealCofExec = false;
}

QList<QStandardItem *> rozmiaryDialog::zwrocWierszModel() {
    QList<QStandardItem *> rzad;
    rzad.append(new QStandardItem(stModel->index(0,2).data(Qt::DisplayRole).toString()));
    rzad.append(new QStandardItem(stModel->index(0,3).data(Qt::DisplayRole).toString()));
    rzad.append(new QStandardItem(stModel->index(0,4).data(Qt::DisplayRole).toString()));
    rzad.append(new QStandardItem(stModel->index(0,5).data(Qt::DisplayRole).toString()));
    rzad.append(new QStandardItem(stModel->index(0,6).data(Qt::DisplayRole).toString()));
    rzad.append(new QStandardItem(stModel->index(0,7).data(Qt::DisplayRole).toString()));

    for (int i = 0; i < 16; i++) {
        rzad.append(new QStandardItem(rozmiaryx.at(i)));
    }
    rzad.append(new QStandardItem("MAGAZYN TOWARÓW"));
    return rzad;
}

int rozmiaryDialog::getCurId() const {
    return curId;
}

void rozmiaryDialog::setCurId(int value) {
    curId = value;
}

void rozmiaryDialog::acceptRoz() {
    if(insertExec) {
        if(ui->lineEditsuma->text()!="0") {
            if(!ui->lineEdit36->text().isEmpty()) {
                rozmiaryx.append(ui->lineEdit36->text());
            } else rozmiaryx.append("0");
            if(!ui->lineEdit37->text().isEmpty()) {
                rozmiaryx.append(ui->lineEdit37->text());
            } else rozmiaryx.append("0");
            if(!ui->lineEdit38->text().isEmpty()) {
                rozmiaryx.append(ui->lineEdit38->text());
            } else rozmiaryx.append("0");
            if(!ui->lineEdit39->text().isEmpty()) {
                rozmiaryx.append(ui->lineEdit39->text());
            } else rozmiaryx.append("0");
            if(!ui->lineEdit40->text().isEmpty()) {
                rozmiaryx.append(ui->lineEdit40->text());
            } else rozmiaryx.append("0");
            if(!ui->lineEdit41->text().isEmpty()) {
                rozmiaryx.append(ui->lineEdit41->text());
            } else rozmiaryx.append("0");
            if(!ui->lineEdit42->text().isEmpty()) {
                rozmiaryx.append(ui->lineEdit42->text());
            } else rozmiaryx.append("0");
            if(!ui->lineEdit43->text().isEmpty()) {
                rozmiaryx.append(ui->lineEdit43->text());
            } else rozmiaryx.append("0");
            if(!ui->lineEdit44->text().isEmpty()) {
                rozmiaryx.append(ui->lineEdit44->text());
            } else rozmiaryx.append("0");
            if(!ui->lineEdit45->text().isEmpty()) {
                rozmiaryx.append(ui->lineEdit45->text());
            } else rozmiaryx.append("0");
            if(!ui->lineEdit46->text().isEmpty()) {
                rozmiaryx.append(ui->lineEdit46->text());
            } else rozmiaryx.append("0");
            if(!ui->lineEdit47->text().isEmpty()) {
                rozmiaryx.append(ui->lineEdit47->text());
            } else rozmiaryx.append("0");
            if(!ui->lineEdit48->text().isEmpty()) {
                rozmiaryx.append(ui->lineEdit48->text());
            } else rozmiaryx.append("0");
            if(!ui->lineEdit49->text().isEmpty()) {
                rozmiaryx.append(ui->lineEdit49->text());
            } else rozmiaryx.append("0");
            if(!ui->lineEdit50->text().isEmpty()) {
                rozmiaryx.append(ui->lineEdit50->text());
            } else rozmiaryx.append("0");
            rozmiaryx.append(ui->lineEditsuma->text());

            QList<QStandardItem *> rzad = zwrocWierszModel();

            dbManager->ustawAktualnyModelMWId(curId);
            if(dbManager->insPz(rzad)) {
                dbManager->dodajdoMW(rzad, curId);
                dbManager->getmw()->select();
                accept();
                insertExec = false;
            } else {
                QMessageBox::information(this, "BŁĄD", " <FONT COLOR='#0f00f0'>Nie dodano do magazynu. Proszę sprawdzić pozycje.", QMessageBox::Ok);
            }
        } else {
            QMessageBox::information(this, "NIEPOPRAWNA ILOŚĆ", " <FONT COLOR='#0f00f0'>Nie dodano żadnej ilości. Proszę sprawdzić pozycje.", QMessageBox::Ok);
        }
    } else if(zrealExec || zrealCofExec) {
        bool wysKomunikat = false;

        if(!ui->lineEdit36->text().isEmpty()) {
            if(ui->lineEdit36->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,10)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit36->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEdit37->text().isEmpty()) {
            if(ui->lineEdit37->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,11)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit37->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEdit38->text().isEmpty()) {
            if(ui->lineEdit38->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,12)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit38->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEdit39->text().isEmpty()) {
            if(ui->lineEdit39->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,13)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit39->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEdit40->text().isEmpty()) {
            if(ui->lineEdit40->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,14)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit40->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEdit41->text().isEmpty()) {
            if(ui->lineEdit41->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,15)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit41->text());
            }
        } else rozmiaryx.append("0");


        if(!ui->lineEdit42->text().isEmpty()) {
            if(ui->lineEdit42->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,16)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit42->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEdit43->text().isEmpty()) {
            if(ui->lineEdit43->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,17)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit43->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEdit44->text().isEmpty()) {
            if(ui->lineEdit44->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,18)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit44->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEdit45->text().isEmpty()) {
            if(ui->lineEdit45->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,19)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit45->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEdit46->text().isEmpty()) {
            if(ui->lineEdit46->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,20)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit46->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEdit47->text().isEmpty()) {
            if(ui->lineEdit47->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,21)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit47->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEdit48->text().isEmpty()) {
            if(ui->lineEdit48->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,22)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit48->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEdit49->text().isEmpty()) {
            if(ui->lineEdit49->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,23)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit49->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEdit50->text().isEmpty()) {
            if(ui->lineEdit50->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,24)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit50->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEditsuma->text().isEmpty() && !wysKomunikat)
            rozmiaryx.append(ui->lineEditsuma->text());
        rozmiaryx.append("0");

        if(wysKomunikat) {
            rozmiaryx.clear();
            QMessageBox::information(this, "NIEPOPRAWNA ILOŚĆ", " <FONT COLOR='#0f00f0'>W zamówieniu nie ma podanej ilości par. Proszę sprawdzić pozycje.", QMessageBox::Ok);
        } else {
            if(ui->lineEditsuma->text()!="0")
                accept();
            else {
                QMessageBox::information(this, "NIEPOPRAWNA ILOŚĆ", " <FONT COLOR='#0f00f0'>Nie wskazano par do realizacji. Proszę sprawdzić pozycje.", QMessageBox::Ok);
            }
        }



    } else {
        bool wysKomunikat = false;

        if(!ui->lineEdit36->text().isEmpty() && !wysKomunikat) {
            if(ui->lineEdit36->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,8)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit36->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEdit37->text().isEmpty() && !wysKomunikat) {
            if(ui->lineEdit37->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,9)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit37->text());
            }
        } else rozmiaryx.append("0");
        if(!ui->lineEdit38->text().isEmpty()) {
            if(ui->lineEdit38->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,10)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit38->text());
            }
        } else rozmiaryx.append("0");
        if(!ui->lineEdit39->text().isEmpty() && !wysKomunikat) {
            if(ui->lineEdit39->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,11)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit39->text());
            }
        } else rozmiaryx.append("0");
        if(!ui->lineEdit40->text().isEmpty() && !wysKomunikat) {
            if(ui->lineEdit40->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,12)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit40->text());
            }
        } else rozmiaryx.append("0");
        if(!ui->lineEdit41->text().isEmpty() && !wysKomunikat) {
            if(ui->lineEdit41->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,13)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit41->text());
            }
        }

        else rozmiaryx.append("0");
        if(!ui->lineEdit42->text().isEmpty() && !wysKomunikat) {
            if(ui->lineEdit42->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,14)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit42->text());
            }
        }

        else rozmiaryx.append("0");
        if(!ui->lineEdit43->text().isEmpty() && !wysKomunikat) {
            if(ui->lineEdit43->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,15)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit43->text());
            }
        }

        else rozmiaryx.append("0");

        if(!ui->lineEdit44->text().isEmpty() && !wysKomunikat) {
            if(ui->lineEdit44->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,16)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit44->text());
            }
        }

        else rozmiaryx.append("0");
        if(!ui->lineEdit45->text().isEmpty() && !wysKomunikat) {
            if(ui->lineEdit45->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,17)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit45->text());
            }

        }   else rozmiaryx.append("0");
        if(!ui->lineEdit46->text().isEmpty() && !wysKomunikat) {
            if(ui->lineEdit46->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,18)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit46->text());
            }

        }   else rozmiaryx.append("0");
        if(!ui->lineEdit47->text().isEmpty() && !wysKomunikat) {
            if(ui->lineEdit47->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,19)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit47->text());
            }
        }   else rozmiaryx.append("0");
        if(!ui->lineEdit48->text().isEmpty() && !wysKomunikat) {
            if(ui->lineEdit48->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,20)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit48->text());
            }

        }  else rozmiaryx.append("0");

        if(!ui->lineEdit49->text().isEmpty() && !wysKomunikat) {
            if(ui->lineEdit49->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,21)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit49->text());
            }
        } else rozmiaryx.append("0");
        if(!ui->lineEdit50->text().isEmpty() && !wysKomunikat) {
            if(ui->lineEdit50->text().toInt() > ui->tableViewZam->model()->data(ui->tableViewZam->model()->index(0,22)).toInt()) {
                wysKomunikat = true;
            } else {
                rozmiaryx.append(ui->lineEdit50->text());
            }
        } else rozmiaryx.append("0");

        if(!ui->lineEditsuma->text().isEmpty() && !wysKomunikat)
            rozmiaryx.append(ui->lineEditsuma->text());
        rozmiaryx.append("0");

        if(wysKomunikat) {
            rozmiaryx.clear();
            QMessageBox::information(this, "NIEPOPRAWNA ILOŚĆ", " <FONT COLOR='#0f00f0'>Na magazynie nie jest dostępna podana ilość towaru. Proszę sprawdzić pozycje.", QMessageBox::Ok);
        } else {
            if(ui->lineEditsuma->text()!="0")
                accept();
            else {
                QMessageBox::information(this, "NIEPOPRAWNA ILOŚĆ", " <FONT COLOR='#0f00f0'>Nie pobrano żadnej ilości z magazynu. Proszę sprawdzić pozycje.", QMessageBox::Ok);
            }
        }
    }
}

void rozmiaryDialog::setZrealCofExec(bool value) {
    zrealCofExec = value;
}

void rozmiaryDialog::setZrealExec(bool value) {
    zrealExec = value;
}

void rozmiaryDialog::setInsertExec(bool value) {
    insertExec = value;
}

void rozmiaryDialog::wyczyscPola() {
    rozmiaryx.clear();
    ui->lineEdit36->clear();
    ui->lineEdit37->clear();
    ui->lineEdit38->clear();
    ui->lineEdit39->clear();
    ui->lineEdit40->clear();
    ui->lineEdit41->clear();
    ui->lineEdit42->clear();
    ui->lineEdit43->clear();
    ui->lineEdit44->clear();
    ui->lineEdit45->clear();
    ui->lineEdit46->clear();
    ui->lineEdit47->clear();
    ui->lineEdit48->clear();
    ui->lineEdit49->clear();
    ui->lineEdit50->clear();
    ui->lineEditsuma->clear();
}

void rozmiaryDialog::obliczSume() {
    int suma = ui->lineEdit36->text().toInt() +  ui->lineEdit37->text().toInt() +  ui->lineEdit38->text().toInt() +  ui->lineEdit39->text().toInt() +  ui->lineEdit40->text().toInt() +
               ui->lineEdit41->text().toInt() +  ui->lineEdit42->text().toInt() +  ui->lineEdit43->text().toInt() +  ui->lineEdit44->text().toInt() +  ui->lineEdit45->text().toInt() +
               ui->lineEdit46->text().toInt() +  ui->lineEdit47->text().toInt() +  ui->lineEdit48->text().toInt() +  ui->lineEdit49->text().toInt() +  ui->lineEdit50->text().toInt();
    ui->lineEditsuma->setText(QString::number(suma));
}

void rozmiaryDialog::obliczSumeGora() {
    int suma = 0;
    if(stModel) {
        for (int i = 8; i < 23; i++) {
            suma += stModel->data(stModel->index(0, i),
                                  Qt::DisplayRole).toInt();
        }
        stModel->setData(stModel->index(0, 23), QVariant(suma));
    }
}

bool rozmiaryDialog::eventFilter(QObject *object, QEvent *event) {
    if (object == ui->lineEdit36 || object == ui->lineEdit37 || object == ui->lineEdit38  || object == ui->lineEdit39  || object == ui->lineEdit40  || object == ui->lineEdit41
            || object == ui->lineEdit42 || object == ui->lineEdit43 || object == ui->lineEdit44 || object == ui->lineEdit45 || object == ui->lineEdit46 || object == ui->lineEdit47 || object == ui->lineEdit48 || object == ui->lineEdit49 || object == ui->lineEdit50) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

            if (keyEvent->key() == Qt::Key_Left) {
                if(object->objectName() != "lineEdit36") {
//                    if(object->objectName() == "lineEdit39") {
//                        stModel->setData(stModel->index(0, 23), QVariant(33));
//                    }
                    int last = object->objectName().right(2).toInt();
                    QString neww("lineEdit");
                    last--;
                    neww += QString::number(last);
                    QObject * parent  = object->parent();
                    QObject *child = parent->findChild<QLineEdit *>(neww);
                    QLineEdit *le = qobject_cast<QLineEdit *>(child);
                    le->setFocus();

                }
                obliczSume();
                return QDialog::eventFilter(object, event);

            } else if (keyEvent->key() == Qt::Key_Right) {
                if(object->objectName() != "lineEdit50") {
                    int last = object->objectName().right(2).toInt();
                    QString neww("lineEdit");
                    last++;
                    neww += QString::number(last);
                    QObject * parent  = object->parent();
                    QObject *child = parent->findChild<QLineEdit *>(neww);
                    QLineEdit *le = qobject_cast<QLineEdit *>(child);
                    le->setFocus();
                }
                obliczSume();
                return QDialog::eventFilter(object, event);
            } else {
                obliczSume();
                return QDialog::eventFilter(object, event);
            }
        } else {
            obliczSume();
            return QDialog::eventFilter(object, event);
        }
    } else {
        return QDialog::eventFilter(object, event);
    }
}
