#include "zmienparyzamdialog.h"
#include "ui_zmienparyzamdialog.h"

zmienParyZamDialog::zmienParyZamDialog(BazaDanychManager *bm, QWidget *parent) :
    QDialog(parent),
    dbmanager(bm),
    ui(new Ui::zmienParyZamDialog) {
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    //ui->tableView->verticalHeader()->setDefaultSectionSize(ui->tableView->verticalHeader()->minimumSectionSize());
}

zmienParyZamDialog::~zmienParyZamDialog() {
    delete ui;
}
