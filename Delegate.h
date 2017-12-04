#ifndef DELEGATE_H
#define DELEGATE_H

#include <QtCore/qglobal.h>
#include <QItemDelegate>
#include <QSpinBox>

class Delegate : public QItemDelegate
{
    Q_OBJECT

public:
    explicit Delegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void paint(QPainter* painter,
               const QStyleOptionViewItem& option,
               const QModelIndex& index) const;
};
#endif // DELEGATE_H
