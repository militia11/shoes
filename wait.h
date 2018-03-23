#ifndef wait_H
#define wait_H

#include <QtWidgets/QDialog>

namespace Ui {
class wait;
}

class wait : public QDialog {
    Q_OBJECT

public slots:
    void koniecBusy();

public:
    explicit wait(QWidget *parent = 0);
    ~wait();
private:
    Ui::wait *ui;
};

#endif // wait_H
