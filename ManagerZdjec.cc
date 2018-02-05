#include "ManagerZdjec.h"

ManagerZdjec::ManagerZdjec()
{

}

QImage ManagerZdjec::getImage(QWidget *p)
{
	QString filename = QFileDialog::getOpenFileName(
				   p, "Dodaj plik", QString(), "Pliki JPG  (*.jpg)") ;
	if ( !filename.isNull() ) {
		QImage image = QImage( filename );
		if ( image.isNull() ) {
			QMessageBox::warning( p, "",
						  QString("Nie mozna otworzyc pliku.").arg( filename ) );
			return QImage();
		} else {
			return image;
		}
	} else {
		return QImage();
	}
}
