#include "delegateKli.h"
#include<QPainter>
#include<QLineEdit>
#include<QMessageBox>
#include<QComboBox>

Delegate::Delegate(BazaDanychManager *dbManager,QObject *parent) : QItemDelegate(parent), dbManager(dbManager) {}

QWidget* Delegate::createEditor(QWidget *parent,const QStyleOptionViewItem &option,const QModelIndex &index) const {
    QString field = index.model()->headerData(index.column(), Qt::Horizontal).toString();
    if (field == "HANDLOWIEC") {
        QComboBox* editor = new QComboBox(parent);
        editor->setFrame(true);

        QString q = QString("select skrot, id from handlowce");
        QSqlQuery query(q);
        QAbstractItemModel *vModel = dbManager->getModelForQuery(&query);
        if (vModel) {
            for (int i = 0; i < vModel->rowCount(); ++i) {
                QString vEventName = vModel->data(vModel->index(i, 0)).toString();
                QVariant vEventMnemonic = vModel->data(vModel->index(i, 1));
                editor->addItem(
                    vEventName,
                    vEventMnemonic);
            }
            delete vModel;
        }

        return editor;
    }

    return QItemDelegate::createEditor(parent, option, index);
}

void Delegate::setEditorData(QWidget *editor,const QModelIndex &index) const {
    QString field = index.model()->headerData(index.column(), Qt::Horizontal).toString();
    if (field == "HANDLOWIEC") {
        int value = index.model()->data(index).toInt();
        QComboBox *comboBox = static_cast<QComboBox *>(editor);

        comboBox->setCurrentIndex(value);
        return;
    }
    QString value = index.model()->data(index).toString();

    QLineEdit* lineEditNumber = static_cast<QLineEdit*>(editor);
    lineEditNumber->setText(value);
}

void Delegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex &index) const {
    QString field = index.model()->headerData(index.column(), Qt::Horizontal).toString();
    if (field == "HANDLOWIEC") {
        int idk =  model->data(model->index(index.row(),0)).toInt();
        QComboBox *comboBox = static_cast<QComboBox *>(editor);
        int data = comboBox->currentData().toInt();
        dbManager->updateHandl(data,idk);

        return;
    }
    QItemDelegate::setModelData(editor,model,index);
}

void Delegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const {
    editor->setGeometry(option.rect);
}

void Delegate::paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const {
    return QItemDelegate::paint(painter,option, index );
}
