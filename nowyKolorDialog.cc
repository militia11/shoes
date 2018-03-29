#include "nowyKolorDialog.h"
#include "ui_nowyKolorDialog.h"
#include <QMessageBox>
nowyKolorDialog::nowyKolorDialog(BazaDanychManager *dbManager, skoryDialog *s, QWidget *parent) :
    QDialog(parent), s(s), dbManager(dbManager),
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
    ui->lineEditSk2->clear();
    ui->lineEditSk3->clear();
    ui->lineEditSkDominujacy->clear();
    dbManager->sk1 = 1;
    dbManager->sk2 = 1;
    dbManager->sk3 = 1;
    ui->lineEditSk1->setText("BRAK");
    ui->lineEditSk2->setText("BRAK");
    ui->lineEditSk3->setText("BRAK");
}

void nowyKolorDialog::on_buttonBox_accepted() {
    if (!ui->spinBox->text().isEmpty()) {
        aktKolor = ui->spinBox->text().toInt();
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


int nowyKolorDialog::getAktualnyKolor() const {
    return aktKolor;
}

QString nowyKolorDialog::getSk1d() const {
    return  sk1d;
}

QString nowyKolorDialog::getSk2d() const {
    return  sk2d;
}


QString nowyKolorDialog::getSk3d() const {
    return sk3d;
}

QString nowyKolorDialog::getSkdomi() const {
    return  skdomin;
}

void nowyKolorDialog::on_pushButton_2_clicked() {
    dbManager->setSkory();
    if (s->selectExec() == QDialog::Accepted) {
        dbManager->sk1 = s->getIdsk();
        ui->lineEditSk1->setText(s->getAktualnaSkoraNazwa());
    }
}

void nowyKolorDialog::on_pushButton_3_clicked() {
    if (s->selectExec() == QDialog::Accepted) {
        dbManager->sk2 = s->getIdsk();
        ui->lineEditSk2->setText(s->getAktualnaSkoraNazwa());
    }
}

void nowyKolorDialog::on_pushButton_4_clicked() {
    if (s->selectExec() == QDialog::Accepted) {
        dbManager->sk3 = s->getIdsk();
        ui->lineEditSk3->setText(s->getAktualnaSkoraNazwa());
    }
}
