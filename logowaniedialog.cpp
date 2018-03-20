#include "logowaniedialog.h"
#include "ui_logowaniedialog.h"
#include <QSqlQuery>

logowanieDialog::logowanieDialog(BazaDanychManager *db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::logowanieDialog), db(db) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
}

logowanieDialog::~logowanieDialog() {
    delete ui;
}
void logowanieDialog::on_buttonBox_accepted() {
    us = ui->comboBox->currentText();
    if(us != QString(""))
        accept();
}

void logowanieDialog::on_buttonBox_rejected() {
    reject();
}

void logowanieDialog::showEvent(QShowEvent *e) {
    ui->comboBox->clear();
    QSqlQuery query("select * from uzytkownicy");
    QAbstractItemModel *vModel = db->getModelForQuery(&query);
    ui->comboBox->addItem(QString(""), QVariant(0));
    if (vModel) {
        for (int i = 0; i < vModel->rowCount(); ++i) {
            QString vEventName = vModel->data(vModel->index(i, 1)).toString();
            QVariant vEventMnemonic = vModel->data(vModel->index(i, 1));
            ui->comboBox->addItem(
                vEventName,
                vEventMnemonic);
        }
        delete vModel;
    }

}
QString logowanieDialog::getUs() const {
    return us;
}
