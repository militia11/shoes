#ifndef DOROZKROJUDIALOG_H
#define DOROZKROJUDIALOG_H

#include <QtWidgets/QDialog>
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

		QStandardItemModel *getModel() const;
		void setModel(QStandardItemModel *value);

	private slots:
		void on_buttonBox_accepted();
        void on_buttonBox_rejected();
	private:

		void showEvent(QShowEvent *e);
		Ui::DoRozkrojuDialog *ui;
		std::vector<int> zamowienia;
		QStandardItemModel *model;
};

#endif // DOROZKROJUDIALOG_H
