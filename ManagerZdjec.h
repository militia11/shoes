#ifndef MANAGERZDJEC_H
#define MANAGERZDJEC_H
#include <QFileDialog>
#include <QMessageBox>
#include <QtCore/qglobal.h>

class ManagerZdjec
{
	public:
		ManagerZdjec();
		static QImage getImage(QWidget *p);
};

#endif // MANAGERZDJEC_H
