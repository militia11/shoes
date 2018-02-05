#ifndef ROZKROJEDIALOG_H
#define ROZKROJEDIALOG_H

#include <QtWidgets/QDialog>
namespace Ui {
class RozkrojeDialog;
}

class RozkrojeDialog : public QDialog
{
		Q_OBJECT

	public:
		explicit RozkrojeDialog(QWidget *parent = 0);
		~RozkrojeDialog();

	private:
		Ui::RozkrojeDialog *ui;
};

#endif // ROZKROJEDIALOG_H
