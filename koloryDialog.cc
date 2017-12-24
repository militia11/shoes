#include "koloryDialog.h"
#include "ui_koloryDialog.h"

koloryDialog::koloryDialog(BazaDanychManager *db,QWidget *parent) :
	QDialog(parent),
	ui(new Ui::koloryDialog),dbManager(db)
	{
		ui->setupUi(this);
	}

koloryDialog::~koloryDialog()
	{
		delete ui;
	}

void koloryDialog::showEvent(QShowEvent *e)
	{

	}
