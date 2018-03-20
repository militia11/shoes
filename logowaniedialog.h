#ifndef LOGOWANIEDIALOG_H
#define LOGOWANIEDIALOG_H

#include <QDialog>
#include "BazaDanychManager.h"
namespace Ui {
class logowanieDialog;
}

class logowanieDialog : public QDialog {
    Q_OBJECT

public:
    explicit logowanieDialog(BazaDanychManager *db, QWidget *parent = 0);
    ~logowanieDialog();

    QString getUs() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    void showEvent(QShowEvent *e);
    QString us;
    Ui::logowanieDialog *ui;
    BazaDanychManager *db;
};

#endif // LOGOWANIEDIALOG_H
