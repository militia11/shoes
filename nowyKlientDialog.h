#ifndef NOWYKLIENTDIALOG_H
#define NOWYKLIENTDIALOG_H

#include <QtWidgets/QDialog>
#include <QKeyEvent>

namespace Ui {
class nowyKlientDialog;
}

class nowyKlientDialog : public QDialog {
    Q_OBJECT

public:
    explicit nowyKlientDialog(QWidget *parent = 0);
    ~nowyKlientDialog();

    QString getNazwa() const;

    QString getSkrot() const;

    QString getNumerTelefonu() const;

    QString getUlica() const;

    QString getNumerDomu() const;

    QString getMiasto() const;

    QString getKodPocztowy() const;

    QString getTel1() const;

    QString getTel2() const;

    QString getFax() const;

    QString getMail() const;

    QString getUwagi() const;

    QString getWoj() const;

    QString getKraj() const;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    void keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Escape) {
            wyczyscPola();
            resetujPrzyciskiWymagane();
        }
        QDialog::keyPressEvent(event);
    }
    void showEvent(QShowEvent *e);
    void wyczyscPola();
    void resetujPrzyciskiWymagane();

    Ui::nowyKlientDialog *ui;
    QString nazwa;
    QString skrot;
    QString numerTelefonu;
    QString numerDomu;
    QString miasto;
    QString woj;
    QString kodPocztowy;
    QString ulica;
    QString tel1;
    QString tel2;
    QString fax;
    QString mail;
    QString uwagi;
    QString kraj;
};

#endif // NOWYKLIENTDIALOG_H
