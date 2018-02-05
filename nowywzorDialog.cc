#include "nowywzorDialog.h"
#include "ui_nowywzorDialog.h"
#include <QMessageBox>
nowywzorDialog::nowywzorDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::nowywzorDialog)
	{
		ui->setupUi(this);
		wzor = -1;
	}

nowywzorDialog::~nowywzorDialog()
	{
		delete ui;
	}

QString nowywzorDialog::getOpis() const
	{
		return opis;
	}

int nowywzorDialog::getWzor() const
	{
		return wzor;
	}

void nowywzorDialog::wyczyscPola()
	{
		ui->spinBox->setValue(0);
		ui->textEdit->clear();
	}

void nowywzorDialog::on_buttonBox_accepted()
{
		if (ui->spinBox->value() != 0) {
				wzor = ui->spinBox->value();
				opis = ui->textEdit->toPlainText();
				wyczyscPola();
			accept();
		} else {
			QMessageBox::warning(this, "BRAK WYMAGANEGO POLA",
						 QString(" <FONT COLOR='#000080'>Podaj numer wzoru."),
						 QMessageBox::Ok);
		}
}

void nowywzorDialog::on_buttonBox_rejected()
{wyczyscPola();
	reject();
}
