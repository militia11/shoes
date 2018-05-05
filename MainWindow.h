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
#include "edycjazamowieniadialog.h"
#include "RozkrojeDialog.h"
#include "nowawkladkadialog.h"
#include "noweociepdialog.h"
#include "logowaniedialog.h"
#include "Delegate.h"
#include "mwdialog.h"
#include "rozmiarydialog.h"
#include "rwdialog.h"
#include "pzdialog.h"
#include "historiadrukdialog.h"
#include "edycjazamdelegat.h"

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
    void showTable();
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

    void on_actionWyloguj_triggered();

    void on_actionEdycja_triggered();

    void updateZdj(int id);

    void on_actionMagazyn_wolne_triggered();

    void on_radioButton_6_clicked();

    void on_actionRozch_d_wewn_trzny_triggered();

    void on_actionPrzyj_cie_zewn_trzne_triggered();
    void on_actionEksport_do_Excela_triggered();

    void on_pushButtondruk1_toggled(bool checked);

    void on_pushButtondruk2_toggled(bool checked);

    void on_actionHistoria_wydruk_w_triggered();

private:
    bool eventFilter(QObject *object, QEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void filtruj();
    bool logowanie();
    void rozciagnijWiersze();
    void podlaczSygnaly();

    void upButtonUpdateZdj();
    void downButtonUpdateZdj();
    int getIdUp();
    int getIdDown();
    Ui::MainWindow *ui;
    BazaDanychManager *dbManager;
    mwDialog *mw;
    rwDialog *rwDial;
    UstawieniaForm *dialog;
    ZdjecieDialog *dialogzdj;
    noweZamowienieDialog *dialogNoweZamowienie;
    nowyKlientDialog *dialognowyKlient;
    NowyHandlowiecDialog *dialognowyHandl;
    Delegate *del;
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
    EdycjaZamowieniaDialog *dialogEdycjaZam;
    logowanieDialog *log;
    rozmiaryDialog *rozmDialo;
    pzDialog *pz;
    NotEditableDelegate *delNoEdit;
    QItemDelegate *stadnardDel;
    EdycjaZamDelegat *edycjaZamDel;
    void block();
    void wszystkieBlock();
    void noblock();
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
    bool wysylkaMode;
    QString getNrZam(QModelIndex idx);
    QString getNrZamWl(QModelIndex idx);
    int getiDZam(QModelIndex idx);
    QString prepareRozkroj();
    QString prepareZam();

};

#endif // MAINWINDOW_H_
