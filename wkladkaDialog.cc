#include "wkladkaDialog.h"
#include "ui_wkladkaDialog.h"

wkladkaDialog::wkladkaDialog(BazaDanychManager *db,QWidget *parent) :
	QDialog(parent),dbManager(db),
	ui(new Ui::wkladkaDialog)
	{
		ui->setupUi(this);
	}

wkladkaDialog::~wkladkaDialog()
	{
		delete ui;
	}

void wkladkaDialog::showEvent(QShowEvent *e)
	{
		Q_UNUSED(e);
		dbManager->setWkladki();
	}
