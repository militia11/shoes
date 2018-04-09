#ifndef DELEGATEARROWS_H
#define DELEGATEARROWS_H

#include <QtCore/qglobal.h>

#include <QStyledItemDelegate>

#include <QKeyEvent>

class DelegateArrows : public QStyledItemDelegate {

public:
    DelegateArrows(QObject *parent = Q_NULLPTR);
    bool eventFilter(QObject *object, QEvent *event);
    bool x;
};

#endif // DELEGATEARROWS_H
