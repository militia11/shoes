#ifndef NOWAWKLADKADIALOG_H
#define NOWAWKLADKADIALOG_H

#include <QDialog>

namespace Ui {
class NowaWkladkaDialog;
}

class NowaWkladkaDialog : public QDialog {
    Q_OBJECT

public:
    explicit NowaWkladkaDialog(QWidget *parent = 0);
    ~NowaWkladkaDialog();

    QString getRodzaj() const;

    QString getOpis() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    bool eventFilter(QObject *object, QEvent *event);
    void showEvent(QShowEvent *e);
    Ui::NowaWkladkaDialog *ui;
    QString rodzaj;
    QString opis;
};

#endif // NOWAWKLADKADIALOG_H
