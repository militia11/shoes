#ifndef ZMIENPARYZAMDIALOG_H
#define ZMIENPARYZAMDIALOG_H

#include <QDialog>
#include "BazaDanychManager.h"
namespace Ui {
class zmienParyZamDialog;
}

class zmienParyZamDialog : public QDialog {
    Q_OBJECT

public:
    explicit zmienParyZamDialog(BazaDanychManager *dbmanager, QWidget *parent = 0);
    ~zmienParyZamDialog();

private:
    Ui::zmienParyZamDialog *ui;
    BazaDanychManager *dbmanager;
};

#endif // ZMIENPARYZAMDIALOG_H
