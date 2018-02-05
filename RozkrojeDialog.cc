#include "RozkrojeDialog.h"
#include "ui_RozkrojeDialog.h"

RozkrojeDialog::RozkrojeDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::RozkrojeDialog)
	{
		ui->setupUi(this);
	}

RozkrojeDialog::~RozkrojeDialog()
	{
		delete ui;
	}
