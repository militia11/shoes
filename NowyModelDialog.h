#ifndef NOWYMODELDIALOG_H
#define NOWYMODELDIALOG_H

#include <QtWidgets/QDialog>
#include "matryceDialog.h"
#include "NowaMatrycaDialog.h"
#include "nowyKolorDialog.h"
#include "nowySpodDialog.h"
#include "spodyDialog.h"
#include "koloryDialog.h"
#include "skoryDialog.h"
#include "nowaSkoraDialog.h"
#include "wzoryDialog.h"
#include "ocieplenieDialog.h"
#include "wkladkaDialog.h"
#include  <QComboBox>
#include "nowywzorDialog.h"

namespace Ui {
class NowyModelDialog;
}

class NowyModelDialog : public QDialog {
        Q_OBJECT

    public:
        explicit NowyModelDialog(wkladkaDialog *w, ocieplenieDialog *oc, wzoryDialog *wz,
                                 skoryDialog *s, koloryDialog *k, spodyDialog *sp,
                                 matryceDialog *matryce,
                                 BazaDanychManager *dbManager,
                                 QWidget *parent = 0);
        ~NowyModelDialog();
        int editExec(int id);

        int zwrocWybZdjecie();

    public slots:
        virtual int exec();

    private slots:
        void on_pushButton_9_clicked();
        void on_pushButton_14_clicked();
        void on_pushButton_15_clicked();
        void on_pushButton_16_clicked();
        void on_pushButton_17_clicked();
        void on_pushButton_12_clicked();
        void on_pushButton_21_clicked();
        void on_pushButton_25_clicked();
        void on_pushButton_10_clicked();
        void on_pushButton_11_clicked();
        void on_buttonBox_accepted();
        void on_buttonBox_rejected();
        void on_pushButton_19_clicked();

    private:
        void keyPressEvent(QKeyEvent *event);
        void hideEvent(QHideEvent *e);
        void wyczyscPola();
        bool editExecc;

        Ui::NowyModelDialog *ui;
        skoryDialog *s;
        matryceDialog *matryce;
        BazaDanychManager *dbManager;
        wkladkaDialog *w;
        koloryDialog *k;
        spodyDialog *sp;
        ocieplenieDialog *oc;
        wzoryDialog *wz;
        QVector<QImage>images;
        void ustawCombo(QString tabela, QComboBox *com);
        void createCombos();
};

#endif // NOWYMODELDIALOG_H
