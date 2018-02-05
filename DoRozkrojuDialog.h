#ifndef DOROZKROJUDIALOG_H
#define DOROZKROJUDIALOG_H

#include <QtWidgets/QDialog>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QSqlQueryModel>

namespace Ui {
class DoRozkrojuDialog;
}

class DoRozkrojuDialog : public QDialog {
		Q_OBJECT

	public:
		explicit DoRozkrojuDialog(QWidget *parent = 0);
		~DoRozkrojuDialog();

		void setZamowienia(const std::vector<int> &value);

		QAbstractItemModel *getModel() const;
		void setModel(QAbstractItemModel *value);

	private slots:
		void on_buttonBox_accepted();
		void on_buttonBox_rejected();

		//	public slots:
		//		virtual int exec();
	private:
		void copy(QStandardItemModel *from, QStandardItemModel *to)
		{
			to->clear();
			for (int i = 0 ; i < from->rowCount() ; i++)
			{
				to->appendRow(from->item(i)->clone());
			}
		}

		void showEvent(QShowEvent *e);
		Ui::DoRozkrojuDialog *ui;
		std::vector<int> zamowienia;
		QAbstractItemModel *model;
		//QSortFilterProxyModel *proxy;
};

#endif // DOROZKROJUDIALOG_H
