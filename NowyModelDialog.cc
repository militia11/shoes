#include "NowyModelDialog.h"
#include "ui_NowyModelDialog.h"
#include <QFileDialog>
#include <QMessageBox>

NowyModelDialog::NowyModelDialog(matryceDialog *matryce, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::NowyModelDialog), matryce(matryce)
{
	ui->setupUi(this);
}

NowyModelDialog::~NowyModelDialog()
{
	delete ui;
}

void NowyModelDialog::on_pushButton_9_clicked() {
	if (matryce->selectExec() == QDialog::Accepted) {
		ui->labelMatryca->setText(matryce->getAktualnaMatrycaNazwa());
	}
}

void NowyModelDialog::on_pushButton_14_clicked() {
	QString filename = QFileDialog::getOpenFileName(
				   this, tr("Dodaj plik"), QString(), tr("Pliki JPG  (*.jpg)") );
	if ( !filename.isNull() ) {
		image1 = QImage( filename );
		if ( image1.isNull() ) {
			QMessageBox::warning( this, tr(""),
						  tr("Nie mozna otworzyc pliku '%1'").arg( filename ) );
			return;
		}
		ui->labelPodglad1->setPixmap(QPixmap::fromImage(image1));
	}
}

void NowyModelDialog::on_pushButton_15_clicked()
{

}

void NowyModelDialog::on_pushButton_16_clicked()
{

}

void NowyModelDialog::on_pushButton_17_clicked()
{

}
