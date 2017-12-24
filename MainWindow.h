#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QString>
#include <QTableView>
#include <QHeaderView>
#include <QPageSetupDialog>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QPdfWriter>
#include "WybKlientaDialog.h"
#include "BazaDanychManager.h"
#include "ustawieniaform.h"
#include "noweZamowienieDialog.h"
#include "WybModelDialog.h"
#include "WybHandlDialog.h"
#include "NowyHandlowiecDialog.h"
#include "DokumentDoDruku.h"
#include "klienciDialog.h"
#include "handlowceDialog.h"
#include "wkladkaDialog.h"
#include "modeleDialog.h"
#include "skoryDialog.h"
#include "koloryDialog.h"
#include "spodyDialog.h"
#include "ocieplenieDialog.h"
#include "matryceDialog.h"
#include "nowyModelDialog.h"
#include "wzoryDialog.h"
#include <QSortFilterProxyModel>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

		void aktualizujTabele();
		void a();

	private slots:
		void stionResized (int logicalIndex, int oldSize, int newSize);
		void ShowContextMenu(const QPoint &pos);
		void dodajHandlowca();
		void dodajZam();
		void dodajKlienta();
		void drukuj();
		void edytuj();
		void ustawieniaBazy();
		void on_akcjaZamknij_triggered();
		void on_tableViewZam_clicked(const QModelIndex &index);
		void on_actionKlienci_triggered();
		void on_actionModele_triggered();
		void on_pushButtonSzukaj_clicked();

		void on_radioButton_clicked();

		void on_radioButton_2_clicked();

		void on_radioButton_3_clicked();

		void on_actionDrukuj_zam_wienia_triggered();

		void on_radioButton_4_clicked();

		void on_actionWzory_triggered();

	private:
		void keyPressEvent(QKeyEvent *event);
		void filtruj();
		void logowanie();
		bool pageSetup(QPrinter *printer);
		void populateDocument(QTextDocument *document);
		void printDocument(QPrinter *printer);
		void rozciagnijWiersze();
		void podlaczSygnaly();

		Ui::MainWindow *ui;
		QPrintPreviewDialog *printPreviewDialog;
		QPageSetupDialog *dialogPrint;
		BazaDanychManager *dbManager;
		UstawieniaForm *dialog;
		WybKlientaDialog *dialogWybKlienta;
		WybHandlDialog *dialogWybHandl;
		WybModelDialog *dialogWybModel;
		noweZamowienieDialog *dialogNoweZamowienie;
		nowyKlientDialog *dialognowyKlient;
		NowyHandlowiecDialog *dialognowyHandl;
		nowyModelDialog *dialognowyModel;
		klienciDialog *dialogKlienci;
		handlowceDialog *dialogHandl;
		wkladkaDialog *dialogwkladka;
		modeleDialog *dialogmodele;
		skoryDialog *dialogskory;
		koloryDialog *dialogkolory;
		spodyDialog *dialogspody;
		ocieplenieDialog *dialogocieplenie;
		matryceDialog *dialogmatryce;
		wzoryDialog *dialogwzory;
		QSortFilterProxyModel *proxy;
		void ustawIFiltruj();

		int nrkar;
		int kl;
		int klnr;
		int wz ;
		int oc ;
		int sp ;
		int ma ;
		int kol;
		int wkl;
		int s123;
		int uz ;
		int ha ;
		int daty;
		int spnazproc;
};

#endif // MAINWINDOW_H
