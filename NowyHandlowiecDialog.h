#ifndef NOWYHANDLOWIECDIALOG_H
#define NOWYHANDLOWIECDIALOG_H
#include <QtWidgets/QDialog>
#include <QKeyEvent>
namespace Ui {
class NowyHandlowiecDialog;
}

class NowyHandlowiecDialog : public QDialog {
    Q_OBJECT

public:
    explicit NowyHandlowiecDialog(QWidget *parent = 0);
    ~NowyHandlowiecDialog();

    QString getImie() const;

    QString getNazwisko() const;

    QString getSkrot() const;

    QString getUwagi() const;

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    void keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Escape) {
            wyczyscPola();

        }
        QDialog::keyPressEvent(event);
    }
    void showEvent(QShowEvent *e);
    void wyczyscPola();


    QString imie;
    QString nazwisko;
    QString skrot;
    QString uwagi;
    Ui::NowyHandlowiecDialog *ui;
};

#endif // NOWYHANDLOWIECDIALOG_H
