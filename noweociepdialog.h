#ifndef NOWEOCIEPDIALOG_H
#define NOWEOCIEPDIALOG_H

#include <QDialog>

namespace Ui {
class noweociepdialog;
}

class noweociepdialog : public QDialog {
    Q_OBJECT

public:
    explicit noweociepdialog(QWidget *parent = 0);
    ~noweociepdialog();

    QString getRodz() const;

    QString getOpis() const;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    bool eventFilter(QObject *object, QEvent *event);
    void showEvent(QShowEvent *e);
    Ui::noweociepdialog *ui;
    QString rodz;
    QString opis;
};

#endif // NOWEOCIEPDIALOG_H
