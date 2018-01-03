#include "clickableLabel.h"
#include <QSize>
#include <QMouseEvent>
#include <QDebug>
void clickableLabel::mousePressEvent(QMouseEvent *e)
{
	QLabel::mousePressEvent(e);

	emit clicked();
	qDebug() << "SS";
}

clickableLabel::clickableLabel()
{
	//setFixedSieze(QSize(400, 400));
}
