#include "wait.h"
#include "ui_wait.h"
void wait::koniecBusy() {
    this->close();
}

wait::wait(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::wait) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

wait::~wait() {
    delete ui;
}

