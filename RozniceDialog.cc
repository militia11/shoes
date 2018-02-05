#include "RozniceDialog.h"
#include "ui_RozniceDialog.h"

RozniceDialog::RozniceDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::RozniceDialog)
	{
		ui->setupUi(this);
	}

RozniceDialog::~RozniceDialog()
	{
		delete ui;
	}
