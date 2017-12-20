#ifndef DOKUMENTDODRUKU_H
#define DOKUMENTDODRUKU_H

#include <QtCore/qglobal.h>
#include <QTextDocument>
#include <QPrinter>

struct OnePage
{
	QString title;
	QStringList filenames;
	QStringList captions;
	QString descriptionHtml;
};

class DokumentDoDruku
{
	public:
		DokumentDoDruku();

		void dodajStrone(OnePage p);
		void populateDocumentUsingHtml(QTextDocument *document);
		QString pageAsHtml(int page);
		QString itemsAsHtmlTable(const OnePage &thePage);

	private:
		QList<OnePage> pages;
};

#endif // DOKUMENTDODRUKU_H
