#ifndef USTAWIENIAFORM_H
#define USTAWIENIAFORM_H

#include <QtCore/qglobal.h>
#include <QDialog>
#include "BazaDanychManager.h"

namespace Ui {
class UstawieniaForm;
}

class UstawieniaForm : public QDialog {
		Q_OBJECT

	public:
		explicit UstawieniaForm(BazaDanychManager *db, QWidget *parent = 0 );
		~UstawieniaForm();

		QString getHost();
		QString getDatabaseName();
		QString getUser();
		QString getPassword();

	private slots:
		void on_buttonBox_accepted();
		void on_buttonBox_rejected();

	signals:
		void databaseChange();

	private:
		void showEvent(QShowEvent *e);
		void updateSettings();

		BazaDanychManager *db;
		QString host;
		QString user;
		QString databaseName;
		QString password;
		Ui::UstawieniaForm *ui;
};

#endif // USTAWIENIAFORM_H
