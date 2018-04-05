#include "NowyHandlowiecDialog.h"
#include "ui_NowyHandlowiecDialog.h"
#include <QMessageBox>

NowyHandlowiecDialog::NowyHandlowiecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NowyHandlowiecDialog) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
}

NowyHandlowiecDialog::~NowyHandlowiecDialog() {
    delete ui;
}

void NowyHandlowiecDialog::on_buttonBox_accepted() {
    bool wyswietlKomunikat = false;

    if (ui->lineEditSkrot_2->text().isEmpty() ) {
        ui->lineEditSkrot_2->setFocus();
        wyswietlKomunikat = true;
    }
    if (ui->lineEditImie->text().isEmpty() ) {
        ui->lineEditImie->setFocus();
        wyswietlKomunikat = true;
    }
    if (ui->lineEditNazwisko->text().isEmpty() ) {
        ui->lineEditNazwisko->setFocus();
        wyswietlKomunikat = true;
    }
    if (wyswietlKomunikat) {
        QMessageBox::warning(this, "BRAK WYMAGANYCH PÓL",
                             " <FONT COLOR='#000080'>Nie można zaakceptować bez podania wymaganych pól. "
                             "<br>Proszę uzupełnić wymagane pola.</FONT>",
                             QMessageBox::Ok);
    } else {
        imie = ui->lineEditImie->text();
        nazwisko = ui->lineEditNazwisko->text();
        skrot = ui->lineEditSkrot_2->text();
        uwagi = ui->plainTextEdit->toPlainText();
        accept();
    }
}

void NowyHandlowiecDialog::on_buttonBox_rejected() {
    reject();
}

void NowyHandlowiecDialog::showEvent(QShowEvent *e) {
    wyczyscPola();
    ui->lineEditImie->setFocus();
}

void NowyHandlowiecDialog::wyczyscPola() {
    ui->lineEditImie->clear();
    ui->lineEditNazwisko->clear();
    ui->lineEditSkrot_2->clear();
    ui->plainTextEdit->clear();
}

QString NowyHandlowiecDialog::getUwagi() const {
    return uwagi;
}

QString NowyHandlowiecDialog::getSkrot() const {
    return skrot;
}

QString NowyHandlowiecDialog::getNazwisko() const {
    return nazwisko;
}

QString NowyHandlowiecDialog::getImie() const {
    return imie;
}
