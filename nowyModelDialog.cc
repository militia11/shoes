#include "nowyModelDialog.h"
#include "ui_nowyModelDialog.h"

nowyModelDialog::nowyModelDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::nowyModelDialog)
	{
		ui->setupUi(this);
	}

nowyModelDialog::~nowyModelDialog()
	{
		delete ui;
	}
