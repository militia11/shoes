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
	a.setStyleSheet("QLabel {color: blue;}");
	QApplication::setOrganizationName("ABIS Sp. z o.o.");
	QApplication::setOrganizationDomain("ABIS");
	QApplication::setApplicationName("ABIS Manager");
	QTranslator qtTranslator;
	qtTranslation(a, &qtTranslator);
	MainWindow w;
	w.show();

	return a.exec();
}
