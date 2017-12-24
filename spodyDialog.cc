#include "spodyDialog.h"
#include "ui_spodyDialog.h"
#include "BazaDanychManager.h"
spodyDialog::spodyDialog(BazaDanychManager *db,QWidget *parent) :
	QDialog(parent),
	ui(new Ui::spodyDialog)
	{
		ui->setupUi(this);
	}

spodyDialog::~spodyDialog()
	{
		delete ui;
	}

void spodyDialog::showEvent(QShowEvent *e)
	{

	}
