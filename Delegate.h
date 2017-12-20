#ifndef DELEGATE_H
#define DELEGATE_H

#include <QItemDelegate>
class NotEditableDelegate : public QItemDelegate
{
	Q_OBJECT
public:
	explicit NotEditableDelegate(QObject *parent = 0)
		: QItemDelegate(parent)
	{}

protected:
	bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
	{ return false; }
	QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const
	{ return Q_NULLPTR; }

};
#endif // DELEGATE_H
