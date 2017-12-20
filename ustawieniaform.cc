#include "ustawieniaform.h"
#include "ui_ustawieniaform.h"
#include "BazaDanychManager.h"
#include <QDebug>
#include <QSettings>
#include <QMessageBox>

UstawieniaForm::UstawieniaForm(BazaDanychManager *dbManager, QWidget *parent) :
	QDialog(parent),
	dbManager(dbManager),
	ui(new Ui::UstawieniaForm) {
	ui->setupUi(this);

	updateSettings();
}

UstawieniaForm::~UstawieniaForm() {
	delete ui;
}

QString UstawieniaForm::getHost()
{
	return host;
}

QString UstawieniaForm::getDatabaseName()
{
	return databaseName;
}

QString UstawieniaForm::getUser()
{
	return user;
}

QString UstawieniaForm::getPassword() {
	return password;
}

void UstawieniaForm::on_buttonBox_accepted() {
	if(!ui->lineEditPassword->text().isEmpty() && !ui->lineEditHost->text().isEmpty() && !ui->lineEditUser->text().isEmpty() && !ui->lineEditDatabase->text().isEmpty()) {
	QSettings qSetting;
	qSetting.beginGroup("database");
	host = ui->lineEditHost->text();
	user = ui->lineEditUser->text();
	databaseName = ui->lineEditDatabase->text();
	password = ui->lineEditPassword->text();
	qSetting.setValue("host", host);
	qSetting.setValue("user", user);
	qSetting.setValue("databaseName", databaseName);
	qSetting.setValue("password", password);
	qSetting.endGroup();
	if (dbManager->ponowniePolacz()) {
		accept();
	} else {
		ui->labelError->setText("Brak połączenia z bazą danych");
		ui->labelError->setStyleSheet("background-color: red; color: white");
	}
	} else {
		QMessageBox::warning( this, "BRAK PARAMETRÓW POŁĄCZENIA",
					  " <FONT COLOR='#000080'><br>Proszę uzupełnić parametry połączenia. ",
					  QMessageBox::Ok);
	}

}

void UstawieniaForm::on_buttonBox_rejected() {
	reject();
}

void UstawieniaForm::updateSettings() {
	QSettings settings;
	settings.beginGroup("database");
	QString driver = settings.value("driver").toString();

	ui->lineEditDatabase->setText(settings.value("databaseName").toString());
	ui->lineEditHost->setText(settings.value("host").toString());
	ui->lineEditUser->setText(settings.value("user").toString());
	ui->lineEditPassword->setText(settings.value("password").toString());
	settings.endGroup();
}

void UstawieniaForm::showEvent(QShowEvent *e) {
	Q_UNUSED(e);
	if (dbManager->lastConnectionError == true) {
		ui->labelError->setVisible(true);
	} else {
		ui->labelError->setText("Połączono");
		ui->labelError->setStyleSheet("background-color: green; color: white");
	}
	ui->lineEditDatabase->setStyleSheet("color:darkblue ;background-color: lightblue;");
	ui->lineEditHost->setStyleSheet("color:darkblue ;background-color: lightblue;");
	ui->lineEditPassword->setStyleSheet("color:darkblue ;background-color: lightblue;");
	ui->lineEditUser->setStyleSheet("color:darkblue ;background-color: lightblue;");

}
