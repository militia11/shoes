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
		void dodajHandlowca();
		void dodajZam();

	private slots:
		void ustawieniaBazy();
		void on_pushButton_2_clicked();
		void on_pushButton_clicked();
		void on_akcjaZamknij_triggered();
		void on_tableViewZam_clicked(const QModelIndex &index);
		void on_pushButton_3_clicked();
		void on_tableViewZamMod_clicked(const QModelIndex &index);
		void on_actionDodaj_klienta_triggered();
		void on_actionDodaj_handlowca_2_triggered();
		void on_actionDodaj_zam_wienie_2_triggered();
		void on_pushButton_5_clicked();

		void on_pushButton_4_clicked();

		void on_pushButton_7_clicked();

		void on_pushButton_6_clicked();

	private:
		bool pageSetup(QPrinter *printer);
		void populateDocument(QTextDocument *document);
		void printDocument(QPrinter *printer);
		void rozciagnijWiersze(QTableView *m);
		void podlaczSygnaly();
		void dodajKlienta();

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
		bool selectMode;
};

#endif // MAINWINDOW_H
