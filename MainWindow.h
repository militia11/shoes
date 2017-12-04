#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets/QMainWindow>
#include <QDebug>
#include <QString>
#include <QTableView>
#include <QHeaderView>

#include "BazaDanychManager.h"
#include "ustawieniaform.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

        void setTables();
        
    private slots:
		void ustawieniaBazy();
		void on_pushButton_2_clicked();
		void on_pushButton_clicked();
		void on_akcjaZamknij_triggered();

	private:

		void rozciagnijWiersze(QTableView *m);
		void podlaczSygnaly();

		Ui::MainWindow *ui;
		BazaDanychManager *dbManager;
		UstawieniaForm *dialog;
};

#endif // MAINWINDOW_H
