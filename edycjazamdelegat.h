#ifndef EDYCJAZAMDELEGAT_H
#define EDYCJAZAMDELEGAT_H

#include <QStyledItemDelegate>
class EdycjaZamDelegat : public QStyledItemDelegate
{
public:
    EdycjaZamDelegat(QObject *parent = Q_NULLPTR);
    bool eventFilter(QObject *object, QEvent *event);
};

#endif // EDYCJAZAMDELEGAT_H
