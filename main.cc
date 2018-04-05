#include "MainWindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

void qtTranslation(const QApplication &a, QTranslator *translator) {
    QString path = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    translator->load("qt_" + QLocale::system().name(), path);
    a.installTranslator(translator);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setStyleSheet("QHeaderView::section { background: rgb(255, 255, 127);} ");
    //	a.setStyleSheet("QToolBar {background-color: #7AB7F4} QInputDialog {background-color: rgb(58, 129, 204);}  QLabel {color: white;} QLineEdit {color:darkblue ;background-color: white;}"
//			" QPushButton {background-color: rgb(58, 129, 204); color:white;} QRadioButton {color: #7AB7F4}  QRadioButton::checked {color: #40ff00}QRadioButton::indicator::unchecked {border: 1px solid blue; border-radius: 6px; background-color: white; width: 10px; height: 10px; margin-left: 5px;}"
//			"QRadioButton::indicator::checked {border: 2px solid #ffff00; border-radius: 6px; background-color: #40ff00; width: 10px; height: 10px; margin-left: 5px;} QCheckBox {color: red;}");
    //	a.setStyleSheet("QToolBar {background-color: #7AB7F4} QInputDialog {background-color: rgb(58, 129, 204);}  QLabel {color: white;} QLineEdit {color:darkblue ;background-color: white;}"
    //			" QPushButton {background-color: rgb(58, 129, 204); color:white;} QRadioButton {color: #7AB7F4}  QRadioButton::checked {color: #40ff00}QRadioButton::indicator::unchecked {border: 1px solid blue; border-radius: 6px; background-color: white; width: 10px; height: 10px; margin-left: 5px;}"
    //			"QRadioButton::indicator::checked {border: 2px solid #ffff00; border-radius: 6px; background-color: #40ff00; width: 10px; height: 10px; margin-left: 5px;} QCheckBox {color: red;}");

    QApplication::setOrganizationName("ABIS");
    QApplication::setOrganizationDomain("ABIS");
    QApplication::setApplicationName("ABIS Manager");

    QTranslator qtTranslator;
    qtTranslation(a, &qtTranslator);

    MainWindow w;
    w.showMaximized();

    return a.exec();
}
