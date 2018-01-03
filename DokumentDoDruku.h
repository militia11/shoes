#ifndef DOKUMENTDODRUKU_H
#define DOKUMENTDODRUKU_H

#include <QtCore/qglobal.h>
#include <QTextDocument>
#include <QPrinter>
#include "zamowienie.h"
#include <vector>

class DokumentDoDruku
{
	public:
		DokumentDoDruku();

		void dodajZamowienia(std::vector<zamowienieZRozmiaramiStruct> zam);
		void populateDocumentUsingHtml(QTextDocument *document);

	private:
		std::vector<zamowienieZRozmiaramiStruct> zam;
};

#endif // DOKUMENTDODRUKU_H
