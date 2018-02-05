#ifndef DELEGATEARROWS_H
#define DELEGATEARROWS_H

#include <QtCore/qglobal.h>

#include <QStyledItemDelegate>

#include <QKeyEvent>
#include <QDebug>

class DelegateArrows : public QStyledItemDelegate
{
	public:
		DelegateArrows(QObject *parent = Q_NULLPTR);
		bool eventFilter(QObject *object, QEvent *event);
};

#endif // DELEGATEARROWS_H
