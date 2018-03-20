#include "noweociepdialog.h"
#include "ui_noweociepdialog.h"

noweociepdialog::noweociepdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::noweociepdialog) {
    ui->setupUi(this);
    ui->plainTextEdit->installEventFilter(this);
    this->setWindowFlags(Qt::Window);
}

noweociepdialog::~noweociepdialog() {
    delete ui;
}

void noweociepdialog::on_buttonBox_accepted() {
    rodz = ui->lineEdit->text();
    opis = ui->plainTextEdit->toPlainText();
    accept();
}

void noweociepdialog::on_buttonBox_rejected() {
    reject();
}

bool noweociepdialog::eventFilter(QObject *object, QEvent *event) {
    if (object == ui->plainTextEdit) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Return) {
                return true;
            } else {
                return QDialog::eventFilter(object, event);
            }
        } else {
            return QDialog::eventFilter(object, event);
        }
    } else {
        return QDialog::eventFilter(object, event);
    }
}

void noweociepdialog::showEvent(QShowEvent *e) {
    ui->lineEdit->clear();
    ui->plainTextEdit->clear();
    ui->lineEdit->setFocus();
}

QString noweociepdialog::getOpis() const {
    return opis;
}

QString noweociepdialog::getRodz() const {
    return rodz;
}
