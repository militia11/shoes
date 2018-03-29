#include "nowyKlientDialog.h"
#include "ui_nowyKlientDialog.h"
#include <QMessageBox>

void nowyKlientDialog::resetujPrzyciskiWymagane() {
    ui->lineEditNazwa->setStyleSheet("color:black ;background-color: white;");
    ui->lineEditSkrot->setStyleSheet("color:black ;background-color: white;");
    ui->lineEditNrDomu->setStyleSheet("color:black ;background-color: white;");
    ui->lineEditMiasto->setStyleSheet("color:black ;background-color: white;");
    ui->lineEditKodPocztowy->setStyleSheet("color:black ;background-color: white;");
    ui->lineEditUlica->setStyleSheet("color:black ;background-color: white;");
    ui->lineEditW->setStyleSheet("color:black ;background-color: white;");
    ui->lineEditKraj->setStyleSheet("color:black ;background-color: white;");
    ui->labelHandlowiec->setStyleSheet("color:black ;background-color: white;");
}

QString nowyKlientDialog::getKraj() const {
    return kraj;
}

QString nowyKlientDialog::getWoj() const {
    return woj;
}

nowyKlientDialog::nowyKlientDialog(handlowceDialog *wybHandlDialog,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nowyKlientDialog),
    dialogHandl(wybHandlDialog) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    resetujPrzyciskiWymagane();
}

nowyKlientDialog::~nowyKlientDialog() {
    delete ui;
}
void nowyKlientDialog::wyczyscPola() {
    ui->lineEditNazwa->clear();
    ui->lineEditSkrot->clear();
    ui->lineEditNrDomu->clear();
    ui->lineEditMiasto->clear();
    ui->lineEditKodPocztowy->clear();
    ui->lineEditUlica->clear();
    ui->lineEditFax->clear();
    ui->lineEditTel1->clear();
    ui->lineEditTel2->clear();
    ui->lineEditNumerTelefonu->clear();
    ui->lineEditMail->clear();
    ui->lineEditUwagi->clear();
    ui->lineEditW->clear();
    ui->lineEditKraj->clear();
    ui->labelHandlowiec->clear();
}

void nowyKlientDialog::on_buttonBox_accepted() {
    bool wyswietlKomunikat = false;

    resetujPrzyciskiWymagane();
    if (ui->lineEditNrDomu->text().isEmpty()) {
        ui->lineEditNrDomu->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
        wyswietlKomunikat = true;
        ui->lineEditNrDomu->setFocus();
    }
    if (ui->lineEditUlica->text().isEmpty()) {
        ui->lineEditUlica->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
        wyswietlKomunikat = true;
        ui->lineEditUlica->setFocus();
    }
    if (ui->lineEditKodPocztowy->text().isEmpty()) {
        ui->lineEditKodPocztowy->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
        wyswietlKomunikat = true;
        ui->lineEditKodPocztowy->setFocus();
    }
    if (ui->lineEditKraj->text().isEmpty()) {
        ui->lineEditKraj->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
        wyswietlKomunikat = true;
        ui->lineEditKraj->setFocus();
    }
    if (ui->lineEditW->text().isEmpty()) {
        ui->lineEditW->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
        wyswietlKomunikat = true;
        ui->lineEditW->setFocus();
    }
    if (ui->lineEditMiasto->text().isEmpty()) {
        ui->lineEditMiasto->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
        wyswietlKomunikat = true;
        ui->lineEditMiasto->setFocus();
    }
    if (ui->lineEditSkrot->text().isEmpty() ) {
        wyswietlKomunikat = true;
        ui->lineEditSkrot->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
        ui->lineEditSkrot->setFocus();
    }

    if (ui->lineEditNazwa->text().isEmpty() ) {
        ui->lineEditNazwa->setFocus();
        ui->lineEditNazwa->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
        wyswietlKomunikat = true;
    }
    if (ui->labelHandlowiec->text().isEmpty() ) {
        ui->labelHandlowiec->setStyleSheet("color: blue; background-color:  #ff9999;border-style: outset; border-width: 1px; border-color: red;");
        wyswietlKomunikat = true;
    }

    if (wyswietlKomunikat) {
        QMessageBox::warning( this, "BRAK WYMAGANYCH PÓL",
                              " <FONT COLOR='#000080'>Nie można zaakceptować bez podania wymaganych pól. "
                              "<br>Proszę uzupełnić podświetlone na czerwono pola.</FONT>",
                              QMessageBox::Ok);
    } else {
        nazwa = ui->lineEditNazwa->text();
        skrot = ui->lineEditSkrot->text();
        numerDomu = ui->lineEditNrDomu->text();
        miasto = ui->lineEditMiasto->text();
        kodPocztowy = ui->lineEditKodPocztowy->text();
        ulica = ui->lineEditUlica->text();
        fax = ui->lineEditFax->text();
        tel1 = ui->lineEditTel1->text();
        tel2 = ui->lineEditTel2->text();
        numerTelefonu = ui->lineEditNumerTelefonu->text();
        mail = ui->lineEditMail->text();
        uwagi = ui->lineEditUwagi->toPlainText();
        woj = ui->lineEditW->text();
        kraj = ui->lineEditKraj->text();
        accept();
    }
}

void nowyKlientDialog::on_buttonBox_rejected() {
    reject();
}

void nowyKlientDialog::showEvent(QShowEvent *e) {
    wyczyscPola();
    resetujPrzyciskiWymagane();
    ui->lineEditNazwa->setFocus();
}

QString nowyKlientDialog::getNazwa() const {
    return nazwa;
}

QString nowyKlientDialog::getSkrot() const {
    return skrot;
}

QString nowyKlientDialog::getUlica() const {
    return ulica;
}

QString nowyKlientDialog::getNumerDomu() const {
    return numerDomu;
}

QString nowyKlientDialog::getMiasto() const {
    return miasto;
}

QString nowyKlientDialog::getKodPocztowy() const {
    return kodPocztowy;
}

QString nowyKlientDialog::getNumerTelefonu() const {
    return numerTelefonu;
}

QString nowyKlientDialog::getTel1() const {
    return tel1;
}

QString nowyKlientDialog::getTel2() const {
    return tel2;
}

QString nowyKlientDialog::getFax() const {
    return fax;
}

QString nowyKlientDialog::getMail() const {
    return mail;
}

QString nowyKlientDialog::getUwagi() const {
    return uwagi;
}

void nowyKlientDialog::on_pushButton_2_clicked() {
    if (dialogHandl->selectExec() == QDialog::Accepted) {
        ( ui->labelHandlowiec->setText(dialogHandl->getAktualnyHandlNazwa()));
    }
}
