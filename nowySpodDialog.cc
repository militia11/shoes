#include "nowySpodDialog.h"
#include "ui_nowySpodDialog.h"
nowySpodDialog::nowySpodDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nowySpodDialog) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    resetujPrzyciskiWymagane();
}

nowySpodDialog::~nowySpodDialog() {
    delete ui;
}

void nowySpodDialog::on_pushButton_14_clicked() {
    images[0] = ManagerZdjec::getImage(this);
    if (!images[0].isNull()) {
        ui->labelPodglad1->setPixmap(QPixmap::fromImage(images[0]));
    }
}

void nowySpodDialog::on_pushButton_15_clicked() {
    images[1] = ManagerZdjec::getImage(this);
    if (!images[1].isNull()) {
        ui->labelPodglad2->setPixmap(QPixmap::fromImage(images[1]));
    }
}

void nowySpodDialog::on_pushButton_16_clicked() {
    images[2] = ManagerZdjec::getImage(this);
    if (!images[2].isNull()) {
        ui->labelPodglad3->setPixmap(QPixmap::fromImage(images[2]));
    }
}

void nowySpodDialog::on_pushButton_17_clicked() {
    images[3] = ManagerZdjec::getImage(this);
    if (!images[3].isNull()) {
        ui->labelPodglad4->setPixmap(QPixmap::fromImage(images[3]));
    }
}

void nowySpodDialog::on_buttonBox_accepted() {
    bool wyswietlKomunikat = false;

    resetujPrzyciskiWymagane();
    if(ui->lineEditNr->text().isEmpty() ) {
        ui->lineEditNr->setFocus();
        wyswietlKomunikat = true;
    }
    if (ui->lineEditNaz->text().isEmpty() ) {
        ui->lineEditNaz->setFocus();
        wyswietlKomunikat = true;
    }
    if (ui->lineEditProd->text().isEmpty() ) {
        ui->lineEditProd->setFocus();
        wyswietlKomunikat = true;
    }

    if (wyswietlKomunikat) {
        QMessageBox::warning( this, "BRAK WYMAGANYCH PÓL",
                              " <FONT COLOR='#000080'>Nie można zaakceptować bez podania wymaganych pól. "
                              "<br>Proszę uzupełnić wymagane pola.</FONT>",
                              QMessageBox::Ok);
    } else {
        nr = ui->lineEditNr->text();
        nazwa = ui->lineEditNaz->text();
        producent = ui->lineEditProd->text();
        rodzaj = ui->lineEditRodz->text();
        uwagi = ui->plainTextEdit->toPlainText();
        rozm = ui->lineEditRozm->text();
        accept();
    }
}

void nowySpodDialog::on_buttonBox_rejected() {
    reject();
}

void nowySpodDialog::showEvent(QShowEvent *e) {
    images.clear();
    for (int i = 0; i < 4; i++) {
        images.append(QImage());
    }
    wyczyscPola();
    resetujPrzyciskiWymagane();
    ui->lineEditNr->setFocus();
}

void nowySpodDialog::wyczyscPola() {
    ui->lineEditNaz->clear();
    ui->lineEditNr->clear();
    ui->lineEditProd->clear();
    ui->lineEditRodz->clear();
    ui->plainTextEdit->clear();
    ui->lineEditRozm->clear();
    ui->labelPodglad1->clear();
    ui->labelPodglad2->clear();
    ui->labelPodglad3->clear();
    ui->labelPodglad4->clear();
}

void nowySpodDialog::resetujPrzyciskiWymagane() {
}

QString nowySpodDialog::getNr() const {
    return nr;
}

QVector<QImage> nowySpodDialog::getImages() const {
    return images;
}

QString nowySpodDialog::getRozm() const {
    return rozm;
}

QString nowySpodDialog::getUwagi() const {
    return uwagi;
}

QString nowySpodDialog::getRodzaj() const {
    return rodzaj;
}

QString nowySpodDialog::getProducent() const {
    return producent;
}

QString nowySpodDialog::getNazwa() const {
    return nazwa;
}
