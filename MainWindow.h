#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtWidgets/QMainWindow>
#include <QString>
#include <QTableView>
#include <QHeaderView>
#include "nowaSkoraDialog.h"
#include "BazaDanychManager.h"
#include "ustawieniaform.h"
#include "noweZamowienieDialog.h"
#include "NowyHandlowiecDialog.h"
#include "klienciDialog.h"
#include "handlowceDialog.h"
#include "wkladkaDialog.h"
#include "modeleDialog.h"
#include "skoryDialog.h"
#include "koloryDialog.h"
#include "spodyDialog.h"
#include "ocieplenieDialog.h"
#include "matryceDialog.h"
#include "owyModelDialog.h"
#include "wzoryDialog.h"
#include "NowaMatrycaDialog.h"
#include "nowySpodDialog.h"
#include <QSortFilterProxyModel>
#include "ZdjecieDialog.h"
#include "nowyKolorDialog.h"
#include "nowywzorDialog.h"
#include "DoRozkrojuDialog.h"
#include "RozniceDialog.h"
#include "edycjazamowieniadialog.h"
#include "RozkrojeDialog.h"
#include "nowawkladkadialog.h"
#include "noweociepdialog.h"
#include "logowaniedialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void aktualizujTabele();

public slots:
    void ustawIFiltruj();

private slots:
    void refreshTable();
    void updateZamSum(const QModelIndex &topLeft, const QModelIndex &bot,
                      const QVector<int> &);
    void stionResized(int logicalIndex, int oldSize, int newSize);
    void ShowContextMenu(const QPoint &pos);
    void dodajHandlowca();
    void dodajZam();
    void dodajKlienta();
    void edytuj();
    void ustawieniaBazy();
    void on_akcjaZamknij_triggered();
    void on_tableViewZam_clicked(const QModelIndex &index);
    void on_actionKlienci_triggered();
    void on_actionModele_triggered();

    void on_pushButtonSzukaj_clicked();
    void on_radioButton_clicked();
    void on_radioButton_3_clicked();
    void on_radioButton_4_clicked();
    void on_actionWzory_triggered();
    void on_actionMatryce_triggered();
    void on_actionHandlowce_triggered();
    void on_actionSk_ry_triggered();
    void on_actionSpody_triggered();
    void on_actionKolory_triggered();
    void on_actionWk_adki_triggered();
    void on_comboBoxmont_activated(const QString &arg1);
    void on_comboBoxb1_activated(const QString &arg1);
    void on_comboBoxb2_activated(const QString &arg1);
    void on_comboBoxb3_activated(const QString &arg1);
    void on_comboBoxb4_activated(const QString &arg1);
    void on_comboBoxb5_activated(const QString &arg1);
    void on_comboBoxb6_activated(const QString &arg1);
    void on_comboBoxtyp_activated(const QString &arg1);
    void on_pushButton_clicked();
    void on_actionOcieplenia_triggered();
    void on_radioButton_5_clicked();

    void on_actionRozkroje_triggered();
    void on_actionR_nice_rozkroje_triggered();

    void on_radioButton_2_clicked();

    void on_actionWyloguj_triggered();

    void on_actionEdycja_triggered();

private:
    void keyPressEvent(QKeyEvent *event);
    void filtruj();
    bool logowanie();
    void rozciagnijWiersze();
    void podlaczSygnaly();

    Ui::MainWindow *ui;
    BazaDanychManager *dbManager;
    UstawieniaForm *dialog;
    ZdjecieDialog *dialogzdj;
    noweZamowienieDialog *dialogNoweZamowienie;
    nowyKlientDialog *dialognowyKlient;
    NowyHandlowiecDialog *dialognowyHandl;
    klienciDialog *dialogKlienci;
    handlowceDialog *dialogHandl;
    NowaWkladkaDialog *dialogNowaWkl;
    wkladkaDialog *dialogwkladka;
    nowaSkoraDialog *dialognskora;
    skoryDialog *dialogskory;
    nowyKolorDialog *dilogNowyKolor;
    koloryDialog *dialogkolory;
    nowySpodDialog *dialognspod;
    spodyDialog *dialogspody;
    noweociepdialog * dno;
    ocieplenieDialog *dialogocieplenie;
    NowaMatrycaDialog *nowaMatryca;
    matryceDialog *dialogmatryce;
    nowywzorDialog *dialonwzor;
    wzoryDialog *dialogwzory;
    owyModelDialog *dialognowyModel;
    modeleDialog *dialogmodele;
    RozkrojeDialog *rozkroje;
    DoRozkrojuDialog *dorozkroju;
    RozniceDialog *roznicerozkroje;
    EdycjaZamowieniaDialog *dialogEdycjaZam;
    logowanieDialog *log;
    QSortFilterProxyModel *proxy;


    int nrkar;
    int kl;
    int klnr;
    int wz ;
    int oc ;
    int ma ;
    int kol;
    int sp;
    int wkl;
    int s123;
    int uz ;
    int ha ;
    int daty;
    int spnazproc;

    void ustawCombo(QString tabela, QComboBox *com);
    void createCombos();
    void setSumaZamowien();
    bool archiwumMode;
    bool wysylkaMode;
    QString getNrZam(QModelIndex idx);
    int getiDZam(QModelIndex idx);
    QString prepareRozkroj();
    QString prepareZam();
};

#endif // MAINWINDOW_H_
