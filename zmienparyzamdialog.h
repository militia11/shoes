#ifndef ZMIENPARYZAMDIALOG_H
#define ZMIENPARYZAMDIALOG_H

#include <QDialog>
#include "BazaDanychManager.h"
#include "klienciDialog.h"
namespace Ui {
class zmienParyZamDialog;
}

class zmienParyZamDialog : public QDialog {
    Q_OBJECT

public:
    explicit zmienParyZamDialog(klienciDialog *dialog, BazaDanychManager *dbmanager, QWidget *parent = 0);
    ~zmienParyZamDialog();

    int getCurId() const;
    void setCurId(int value);
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    QList<QStandardItem *> zwrocWierszModel();

    int getIdModelu() const;

private slots:
    void on_pushButtonModel_2_clicked();
    void acceptRoz();

private:
    QVector<QString>rozmiaryx;
    Ui::zmienParyZamDialog *ui;
    BazaDanychManager *dbmanager;
    int curId;
    void wyczyscPola();
    void obliczSume();
    void obliczSumeGora();
    bool eventFilter(QObject *object, QEvent *event);
    QStandardItemModel *stModel;
    klienciDialog *dialog;
    int idModelu;
};

#endif // ZMIENPARYZAMDIALOG_H
