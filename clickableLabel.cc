#include "clickableLabel.h"
#include <QSize>
#include <QMouseEvent>

void clickableLabel::mousePressEvent(QMouseEvent *e)
{
	QLabel::mousePressEvent(e);
	emit clicked();
}

clickableLabel::clickableLabel(QWidget *parent) : QLabel (parent)
{
    setFixedSize(QSize(201, 150));
    setFrameStyle(QFrame::WinPanel);
    setFrameShadow(QFrame::Raised);
}
