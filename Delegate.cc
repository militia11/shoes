#include "Delegate.h"
#include<QPainter>
#include<QLineEdit>
#include<QMessageBox>
#include<QRegExpValidator>
#include<QRegExp>

Delegate::Delegate(QObject *parent) :QItemDelegate(parent){}

QWidget* Delegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const {
    QString field = index.model()->headerData(index.column(), Qt::Horizontal).toString();
    if (field == "Age:") {
        QSpinBox* editor = new QSpinBox(parent);
        editor->setFrame(true);
        editor->setMinimum(1);
        editor->setMaximum(100);
        return editor;
    }
    if(field == "Capital:") {
        QSpinBox* editor = new QSpinBox(parent);
        editor->setFrame(true);
        editor->setMinimum(0);
        editor->setMaximum(1000000);
        editor->setSingleStep(100);
        return editor;
    }
    if (field == "Phone number:") {
        QLineEdit *editor = new QLineEdit(parent);
        QRegExp phoneFormat("([1-9]\\d\\d)-(\\d{3})-(\\d{3})");
        QRegExpValidator* phoneValid(new QRegExpValidator(phoneFormat));
        editor->setValidator(phoneValid);
        return editor;
    }
    return QItemDelegate::createEditor(parent, option, index);
}

void Delegate::setEditorData(QWidget *editor,const QModelIndex &index) const {
    QString field = index.model()->headerData(index.column(), Qt::Horizontal).toString();
    if (field == "Age:" || field == "Capital:" ) {
        int value = index.model()->data(index).toInt();
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->setValue(value);
        return;
    }
    if (field == "Employee:" ) {
        if(index.model()->data(index).toString() == "[OPEN JOB]") {
            QMessageBox::warning(0,"Warning","<center>This is Open Job.<br><b>Can't edit.</b> Empty Position", QMessageBox::Ok);
            editor->setDisabled(true);
            return;
        }
    }
    QString value = index.model()->data(index).toString();
    QLineEdit *lineEditNumber = static_cast<QLineEdit*>(editor);
    lineEditNumber->setText(value);
}

void Delegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex &index) const {
    QString field = index.model()->headerData(index.column(), Qt::Horizontal).toString();
    if ( field == "Age:" || field == "Capital:" ) {
        QSpinBox* spinBox = static_cast<QSpinBox*>(editor);
        spinBox->interpretText();
        int value = spinBox->value();
        model->setData(index, value);
        return;
    }
    if ( field == "Employee:" && index.model()->data(index).toString() == "[OPEN JOB]" ) {
       return;
    }
    QItemDelegate::setModelData(editor,model,index);
}

void Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const {
    editor->setGeometry(option.rect);
}

void Delegate::paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const {
    QString field = index.model()->headerData(index.column(), Qt::Horizontal).toString();

    if (field == "Position:") {
        QString str ="->" + index.data(Qt::DisplayRole).toString()  ;
        painter->drawText(option.rect, str, QTextOption());
        if (option.state & QStyle::State_Selected){
            QItemDelegate::paint(painter,option, index );
        }
        return;
    }
    if (field == "Employee:") {
        QString str = index.data(Qt::DisplayRole).toString();
        painter->save();
        if(str != "[OPEN JOB]"){
            QImage image(":/resources/icon_08.png");
            painter->drawImage(option.rect, image);
            painter->setPen(Qt::blue);
        }
        painter->drawText(option.rect, Qt::AlignCenter, "     -*-" + str + "-*-");
        painter->restore();
        if (option.state & QStyle::State_Selected){
            QItemDelegate::paint(painter,option, index );
        }
        return;
    }
       return QItemDelegate::paint(painter,option, index );
}
