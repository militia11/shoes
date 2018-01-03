#include "nowySpodDialog.h"
#include "ui_nowySpodDialog.h"

nowySpodDialog::nowySpodDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::nowySpodDialog)
	{
		ui->setupUi(this);
	}

nowySpodDialog::~nowySpodDialog()
	{
		delete ui;
	}
