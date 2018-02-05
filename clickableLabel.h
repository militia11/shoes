#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QLabel>
#include <QObject>

class clickableLabel : public QLabel
{
		Q_OBJECT
	public:
		clickableLabel(QWidget *parent);

	signals:

		void clicked();
	protected:

		void mousePressEvent(QMouseEvent *e);

};

#endif // CLICKABLELABEL_H
