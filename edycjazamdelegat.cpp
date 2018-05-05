#include "edycjazamdelegat.h"
#include <QEvent>
#include <QTableView>
EdycjaZamDelegat::EdycjaZamDelegat(QObject *parent): QStyledItemDelegate(parent)
{

}

bool EdycjaZamDelegat::eventFilter(QObject *object, QEvent *event) {
    QWidget *editor = qobject_cast<QWidget *>(object);
    if (!editor) {
        return false;
    }
     if (event->type() == QEvent::FocusIn) {
         QTableView *view = qobject_cast<QTableView*>(parent());
         QString y;
         if(view->model()->columnCount() > 37 ) {
             y = view->model()->data(view->model()->index(view->currentIndex().row(),38)).toString();
         }
         if(y == "MAGAZYN TOWARÓW" || y == "ZREALIZOWANO" || y == "ZLEC W PRODUKCJI") {
             emit closeEditor(editor);
         }
          return false;
     } else {
         return QStyledItemDelegate::eventFilter(object, event);
     }
}
