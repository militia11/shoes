#include "rozmiarydialog.h"
#include "ui_rozmiarydialog.h"
#include <QKeyEvent>

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
              << "44" << "45" << "46" << "47"    << "48" << "49" << "50" << "";
        for (int i = 0; i < ui->tableViewZam->model()->columnCount(); ++i) {
            ui->tableViewZam->model()->setHeaderData(i, Qt::Horizontal, lista[i]);
        }
        ui->horizontalLayout->update();
    }
    ui->tableViewZam->update();
}

void rozmiaryDialog::showEvent(QShowEvent *e) {
    wyczyscPola();
    updateCurrentRow();
}

void rozmiaryDialog::hideEvent(QHideEvent *e) {
    curId = -1;
}

int rozmiaryDialog::getCurId() const {
    return curId;
}

void rozmiaryDialog::setCurId(int value) {
    curId = value;
}

void rozmiaryDialog::acceptRoz() {
    dbManager->zachowajRW();
    accept();
}

void rozmiaryDialog::wyczyscPola() {
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
//Stream na sport.tvp.pl. Portal sport.se.pl
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
