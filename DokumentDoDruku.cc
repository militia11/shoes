#include "DokumentDoDruku.h"
#include <QDebug>

DokumentDoDruku::DokumentDoDruku()
{}

void DokumentDoDruku::dodajStrone(OnePage p)
{
	pages.append(p);
}

void DokumentDoDruku::populateDocumentUsingHtml(QTextDocument *document) {
	QString html("<html>\n<body>\n");
	for (int page = 0; page < pages.count(); ++page) {
		html += pageAsHtml(page);
		if (page + 1 < pages.count()) {
			html += "<br style='page-break-after:always;'/>\n";
		}
	}

	html += "</body>\n</html>\n";
	qDebug() << html;
	document->setHtml(html);
}

QString DokumentDoDruku::pageAsHtml(int page) {
	const OnePage &thePage = pages.at(page);
	QString html;
	html += "<p>";
	html += itemsAsHtmlTable(thePage);

	html += "</p>\n";
	return html;
}

QString DokumentDoDruku::itemsAsHtmlTable(const OnePage &thePage) {
	QString html("<table border='1' cellpadding='20' width='100%'>");
	for (int i = 0; i < thePage.filenames.count(); ++i) {
		if (i % 2 == 0) {
			html += "<tr>\n";
		}
		html += QString("<td align='center'><img src='%1'/>"
				"<p style='font-size:18pt'>%2</p></td>\n")
			.arg(thePage.filenames.at(i))
			.arg(QString(thePage.captions.at(i)).toHtmlEscaped());
		if (i % 2 != 0) {
			html += "</tr>\n";
		}
	}
	if (!html.endsWith("</tr>\n")) {
		html += "</tr>\n";
	}
	html += "</table>\n";
	return html;
}
