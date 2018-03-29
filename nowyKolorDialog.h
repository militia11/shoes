#ifndef NOWYKOLORDIALOG_H
#define NOWYKOLORDIALOG_H

#include <QtWidgets/QDialog>
#include <QKeyEvent>
#include "skoryDialog.h"
#include "BazaDanychManager.h"
namespace Ui {
class nowyKolorDialog;
}

class nowyKolorDialog : public QDialog {
    Q_OBJECT

public:
    explicit nowyKolorDialog(BazaDanychManager *dbManager,skoryDialog *s,QWidget *parent = 0);
    ~nowyKolorDialog();
    void keyPressEvent(QKeyEvent *event) {
        if (event->key() == Qt::Key_Escape) {
            wyczyscPola();
        }
        QDialog::keyPressEvent(event);
    }
    void wyczyscPola();
    int getAktualnyKolor() const;

    QString getSk1d() const;


    QString getSk2d() const;


    QString getSk3d() const;

    QString getSkdomi() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    void showEvent(QShowEvent *e);
    Ui::nowyKolorDialog *ui;
    int aktKolor;
    QString sk1d;
    QString sk2d;
    QString sk3d;
    QString skdomin;
    skoryDialog * s;
    BazaDanychManager *dbManager;
};

#endif // NOWYKOLORDIALOG_H
