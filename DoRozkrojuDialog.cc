#include "DoRozkrojuDialog.h"
#include "ui_DoRozkrojuDialog.h"
#include "Delegate.h"
#include "DelegateArrows.h"
#include <QKeyEvent>
#include "NaglowkiZamowienia.h"
DoRozkrojuDialog::DoRozkrojuDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DoRozkrojuDialog), model(nullptr), bazowyModel(nullptr) {
    ui->setupUi(this);
    NotEditableDelegate *del = new NotEditableDelegate(this);
    for (int i = 0; i < 10; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, del);
    }
    for (int i = 25; i < 33; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, del);
    }
    ui->tableViewZam->setItemDelegateForColumn(37, del);
    DelegateArrows *delArrow = new DelegateArrows(this);
    for (int i = 10; i < 25; i++) {
        ui->tableViewZam->setItemDelegateForColumn(i, delArrow);
    }
    bazowyModel = new QStandardItemModel();
}

DoRozkrojuDialog::~DoRozkrojuDialog() {
    delete ui;
    if (model) {
        delete model;
    }
    if (bazowyModel) {
        delete bazowyModel;
    }
}

void DoRozkrojuDialog::on_buttonBox_accepted() {

    accept();
}

void DoRozkrojuDialog::on_buttonBox_rejected() {
    reject();
}

void DoRozkrojuDialog::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        return;
        // wyczysc();
    }
    QDialog::keyPressEvent(event);
}

void DoRozkrojuDialog::showEvent(QShowEvent *e) {
    Q_UNUSED(e);
    ui->lineEditPapier->setText(nr);
    QAbstractItemModel *old = ui->tableViewZam->model();
    if (old) {
        delete old;
        old = 0;
    }
    ui->tableViewZam->setModel(model);
    NaglowkiZamowienia::ustawNaglowki(ui->tableViewZam, model);

    bazowyModel->clear();
    for (int i = 0; i < model->rowCount(); i++) {
        QList<QStandardItem *> rzad;
        for (int j = 0; j < model->columnCount(); j++) {
            rzad.append(new QStandardItem(model->data(model->index(i, j)).toString()));
        }
        bazowyModel->insertRow(i, rzad);
        rzad.clear();
    }
}

QStandardItemModel *DoRozkrojuDialog::getBazowyModel() const {
    return bazowyModel;
}

void DoRozkrojuDialog::setNr(const QString &value) {
    nr = value;
}

QStandardItemModel *DoRozkrojuDialog::getModel() const {
    return model;
}

void DoRozkrojuDialog::setModel(QStandardItemModel *value) {
    if (model) {
        delete model;
    }
    model = value;
}

void DoRozkrojuDialog::setZamowienia(const std::vector<int> &value) {
    zamowienia.clear();
    zamowienia = value;
}
