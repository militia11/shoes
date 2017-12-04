#include "noweZamowienieDialog.h"
#include "ui_noweZamowienieDialog.h"

noweZamowienieDialog::noweZamowienieDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::noweZamowienieDialog)
	{
	ui->setupUi(this);
	}

noweZamowienieDialog::~noweZamowienieDialog()
	{
	delete ui;
	}
