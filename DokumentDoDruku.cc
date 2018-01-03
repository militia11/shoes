#include "DokumentDoDruku.h"
#include <QDebug>

DokumentDoDruku::DokumentDoDruku()
{}

void DokumentDoDruku::dodajZamowienia(std::vector<zamowienieZRozmiaramiStruct>
					  zam) {
	zam = zam;
}

void DokumentDoDruku::populateDocumentUsingHtml(QTextDocument *document) {
	QString html;
	//<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd"><html xmlns="http://www.w3.org/1999/xhtml"><!--This file was converted to xhtml by LibreOffice - see http://cgit.freedesktop.org/libreoffice/core/tree/filter/source/xslt for the code.--><head profile="http://dublincore.org/documents/dcmi-terms/"><meta http-equiv="Content-Type" content="application/xhtml+xml; charset=utf-8"/><title xml:lang="en-US">- no title specified</title><meta name="DCTERMS.title" content="" xml:lang="en-US"/><meta name="DCTERMS.language" content="en-US" scheme="DCTERMS.RFC4646"/><meta name="DCTERMS.source" content="http://xml.openoffice.org/odf2xhtml"/><meta name="DCTERMS.issued" content="2017-12-24T02:07:40.852730599" scheme="DCTERMS.W3CDTF"/><meta name="DCTERMS.modified" content="2017-12-24T02:42:04.835241136" scheme="DCTERMS.W3CDTF"/><meta name="DCTERMS.provenance" content="" xml:lang="en-US"/><meta name="DCTERMS.subject" content="," xml:lang="en-US"/><link rel="schema.DC" href="http://purl.org/dc/elements/1.1/" hreflang="en"/><link rel="schema.DCTERMS" href="http://purl.org/dc/terms/" hreflang="en"/><link rel="schema.DCTYPE" href="http://purl.org/dc/dcmitype/" hreflang="en"/><link rel="schema.DCAM" href="http://purl.org/dc/dcam/" hreflang="en"/><style type="text/css">
	html += QString("<HTML><HEAD><STYLE type=\"text/css\">"

			"	</style></head></html>");
	qDebug() << zam[0].rozmiary[0];
	document->setHtml(html);
}

//QString DokumentDoDruku::itemsAsHtmlTable(const ZamowieniaDruk &thePage) {
//	QString html("<table border='1' cellpadding='3' cellspacing='0' style='page-break-before: always; page-break-after: auto'>");
//	for (int i = 0; i < thePage.captions.count(); ++i) {
//		if (i % 2 == 0) {
//			html += "<tr>\n";
//		}
//		html += QString("<td align='center'><p style='font-size:18pt'>%1</p></td>\n")
//			.arg(QString(thePage.captions.at(i)).toHtmlEscaped());
//		if (i % 2 != 0) {
//			html += "</tr>\n";
//		}
//	}
//	if (!html.endsWith("</tr>\n")) {
//		html += "</tr>\n";
//	}
//	html += "</table>\n";
//	return html;
//}
