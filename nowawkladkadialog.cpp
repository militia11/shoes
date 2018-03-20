#include "nowawkladkadialog.h"
#include "ui_nowawkladkadialog.h"

NowaWkladkaDialog::NowaWkladkaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NowaWkladkaDialog) {
    ui->setupUi(this);
    ui->plainTextEdit->installEventFilter(this);
    this->setWindowFlags(Qt::Window);
}

NowaWkladkaDialog::~NowaWkladkaDialog() {
    delete ui;
}

QString NowaWkladkaDialog::getRodzaj() const {
    return rodzaj;
}

QString NowaWkladkaDialog::getOpis() const {
    return opis;
}

void NowaWkladkaDialog::showEvent(QShowEvent *e) {
    ui->lineEdit->clear();
    ui->plainTextEdit->clear();
    ui->lineEdit->setFocus();
}

void NowaWkladkaDialog::on_buttonBox_accepted() {
    rodzaj = ui->lineEdit->text();
    opis = ui->plainTextEdit->toPlainText();
    accept();
}

void NowaWkladkaDialog::on_buttonBox_rejected() {
    reject();
}

bool NowaWkladkaDialog::eventFilter(QObject *object, QEvent *event) {
    if (object == ui->plainTextEdit) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Return) {
                qDebug("Enter Key Pressed...");
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
