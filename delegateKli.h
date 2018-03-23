#ifndef DELEGATEKLI_H
#define DELEGATEKLI_H
#include <QItemDelegate>
#include "BazaDanychManager.h"
class Delegate : public QItemDelegate {
    Q_OBJECT

public:
    explicit Delegate(BazaDanychManager *dbManager, QObject *parent = 0);
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
signals:
    //void updateHand();
private:
    BazaDanychManager *dbManager;
};
#endif // DELEGATEKLI_H
