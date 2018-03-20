#include "nowyKolorDialog.h"
#include "ui_nowyKolorDialog.h"
#include <QMessageBox>
nowyKolorDialog::nowyKolorDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nowyKolorDialog) {
    ui->setupUi(this);
    aktKolor = 0;
    this->setWindowFlags(Qt::Window);
}

nowyKolorDialog::~nowyKolorDialog() {
    delete ui;
}

void nowyKolorDialog::wyczyscPola() {
    ui->spinBox->clear();
    ui->lineEditSk1->clear();
    ui->lineEditSk1d->clear();
    ui->lineEditSk2->clear();
    ui->lineEditSk2d->clear();
    ui->lineEditSk3->clear();
    ui->lineEditSk3d->clear();
    ui->lineEditSkDominujacy->clear();
}

void nowyKolorDialog::on_buttonBox_accepted() {
    if (!ui->spinBox->text().isEmpty()) {
        aktKolor = ui->spinBox->text().toInt();
        sk1 = ui->lineEditSk1->text();
        sk1d = ui->lineEditSk1d->text();
        sk2 = ui->lineEditSk2->text();
        sk2d = ui->lineEditSk2d->text();
        sk3 = ui->lineEditSk3->text();
        sk3d = ui->lineEditSk3d->text();
        skdomin = ui->lineEditSkDominujacy->text();
        accept();
    } else {
        QMessageBox::warning(this, "BRAK NUMERU KOLORU",
                             QString(" <FONT COLOR='#000080'>Podaj wartość koloru."),
                             QMessageBox::Ok);
    }
}

void nowyKolorDialog::on_buttonBox_rejected() {
    reject();
}

void nowyKolorDialog::showEvent(QShowEvent *e) {
    wyczyscPola();
    ui->spinBox->setFocus();
}

QString nowyKolorDialog::getSk1() const {
    return sk1;
}

void nowyKolorDialog::setSk1(const QString &value) {
    sk1 = value;
}

int nowyKolorDialog::getAktualnyKolor() const {
    return aktKolor;
}

QString nowyKolorDialog::getSk1d() const {
    return  sk1d;
}

QString nowyKolorDialog::getSk2() const {
    return  sk2;
}

QString nowyKolorDialog::getSk2d() const {
    return  sk2d;
}

QString nowyKolorDialog::getSk3() const {
    return sk3;
}

QString nowyKolorDialog::getSk3d() const {
    return sk3d;
}

QString nowyKolorDialog::getSkdomi() const {
    return  skdomin;
}
