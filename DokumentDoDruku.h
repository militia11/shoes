#ifndef DOKUMENTDODRUKU_H
#define DOKUMENTDODRUKU_H

#include <QtCore/qglobal.h>
#include <QTextDocument>
#include <QPrinter>

struct ZamowieniaDruk
{
	QStringList captions;
};

class DokumentDoDruku
{
	public:
		DokumentDoDruku();

		void dodajZamowienia(ZamowieniaDruk p);
		void populateDocumentUsingHtml(QTextDocument *document);
		QString itemsAsHtmlTable(const ZamowieniaDruk &thePage);

	private:
		QList<ZamowieniaDruk> pages;
};

#endif // DOKUMENTDODRUKU_H
