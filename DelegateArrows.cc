#include "DelegateArrows.h"
#include <QLineEdit>
#include <QApplication>
#include <QTableView>

DelegateArrows::DelegateArrows(QObject *parent) : QStyledItemDelegate(parent) {

}

bool DelegateArrows::eventFilter(QObject *object, QEvent *event) {
    QWidget *editor = qobject_cast<QWidget *>(object);
    if (!editor) {
        return false;
    }
    if (event->type() == QEvent::KeyPress) {
        switch (static_cast<QKeyEvent *>(event)->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Tab:
        case Qt::Key_Right:
            emit commitData(editor);
            emit closeEditor(editor, QAbstractItemDelegate::EditNextItem);
            return true;
        case Qt::Key_Left:
            emit commitData(editor);
            emit closeEditor(editor, QAbstractItemDelegate::EditPreviousItem);
            return true;
        case Qt::Key_Escape:
            emit closeEditor(editor, QAbstractItemDelegate::RevertModelCache);
            break;
        default:
            return false;
        }
        if (editor->parentWidget()) {
            editor->parentWidget()->setFocus();
        }
        return true;
    } else if (event->type() == QEvent::FocusOut || (event->type() == QEvent::Hide && editor->isWindow())) {
        //the Hide event will take care of he editors that are in fact complete dialogs
        if (!editor->isActiveWindow() || (QApplication::focusWidget() != editor)) {
            QWidget *w = QApplication::focusWidget();
            while (w) { // don't worry about focus changes internally in the editor
                if (w == editor) {
                    return false;
                }
                w = w->parentWidget();
            }

            emit commitData(editor);
            emit closeEditor(editor, NoHint);
        }
    } else if (event->type() == QEvent::ShortcutOverride) {
        if (static_cast<QKeyEvent *>(event)->key() == Qt::Key_Escape) {
            event->accept();
            return true;
        }
    } else if (event->type() == QEvent::FocusIn) {
        QTableView *view = qobject_cast<QTableView*>(parent());
        QString x = view->model()->data(view->model()->index(view->currentIndex().row(),22)).toString();
        if(x == "MAGAZYN TOWARÓW") {
            emit closeEditor(editor);
        } else {
        }
        return false;
    }
    return false;
}
