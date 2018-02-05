#include "ZdjecieDialog.h"
#include "ui_ZdjecieDialog.h"

ZdjecieDialog::ZdjecieDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::ZdjecieDialog)
{
	ui->setupUi(this);
	ui->label->setScaledContents(true);
}

ZdjecieDialog::~ZdjecieDialog()
{
	delete ui;
}

void ZdjecieDialog::setLabel(QImage im)
{
	ui->label->setPixmap(QPixmap::fromImage(im));
}
