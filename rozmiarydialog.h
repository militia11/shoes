#ifndef ROZMIARYDIALOG_H
#define ROZMIARYDIALOG_H

#include <QDialog>
#include "BazaDanychManager.h"

namespace Ui {
class rozmiaryDialog;
}

class rozmiaryDialog : public QDialog {
    Q_OBJECT

public:
    rozmiaryDialog(BazaDanychManager *db,QWidget *parent = 0);
    ~rozmiaryDialog();
    void updateCurrentRow();
    void showEvent(QShowEvent *e);
    void hideEvent(QHideEvent *e);
    QList<QStandardItem *> zwrocWierszModel();
    int getCurId() const;

    void setCurId(int value);

    void setInsertExec(bool value);

private slots:
    int insertexec();
    void acceptRoz();

private:
    QVector<QString>rozmiaryx;
    bool insertExec;
    void wyczyscPola();
    void obliczSume();
    void obliczSumeGora();
    bool eventFilter(QObject *object, QEvent *event);
    int curId;
    BazaDanychManager *dbManager;
    QStandardItemModel *stModel;
    Ui::rozmiaryDialog *ui;
};

#endif // ROZMIARYDIALOG_H
