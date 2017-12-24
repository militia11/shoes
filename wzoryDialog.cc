#include "wzoryDialog.h"
#include "ui_wzoryDialog.h"

wzoryDialog::wzoryDialog(BazaDanychManager *db,QWidget *parent) :
	QDialog(parent),
	ui(new Ui::wzoryDialog),dbManager(db)
	{
		ui->setupUi(this);
	}

wzoryDialog::~wzoryDialog()
	{
		delete ui;
	}

void wzoryDialog::showEvent(QShowEvent *e)
	{

	}
