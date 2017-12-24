#include "DokumentDoDruku.h"
#include <QDebug>

DokumentDoDruku::DokumentDoDruku()
{}

void DokumentDoDruku::dodajZamowienia(ZamowieniaDruk p)
{
	pages.append(p);
}

void DokumentDoDruku::populateDocumentUsingHtml(QTextDocument *document) {
	QString html;
	//<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN" "http://www.w3.org/Math/DTD/mathml2/xhtml-math11-f.dtd"><html xmlns="http://www.w3.org/1999/xhtml"><!--This file was converted to xhtml by LibreOffice - see http://cgit.freedesktop.org/libreoffice/core/tree/filter/source/xslt for the code.--><head profile="http://dublincore.org/documents/dcmi-terms/"><meta http-equiv="Content-Type" content="application/xhtml+xml; charset=utf-8"/><title xml:lang="en-US">- no title specified</title><meta name="DCTERMS.title" content="" xml:lang="en-US"/><meta name="DCTERMS.language" content="en-US" scheme="DCTERMS.RFC4646"/><meta name="DCTERMS.source" content="http://xml.openoffice.org/odf2xhtml"/><meta name="DCTERMS.issued" content="2017-12-24T02:07:40.852730599" scheme="DCTERMS.W3CDTF"/><meta name="DCTERMS.modified" content="2017-12-24T02:42:04.835241136" scheme="DCTERMS.W3CDTF"/><meta name="DCTERMS.provenance" content="" xml:lang="en-US"/><meta name="DCTERMS.subject" content="," xml:lang="en-US"/><link rel="schema.DC" href="http://purl.org/dc/elements/1.1/" hreflang="en"/><link rel="schema.DCTERMS" href="http://purl.org/dc/terms/" hreflang="en"/><link rel="schema.DCTYPE" href="http://purl.org/dc/dcmitype/" hreflang="en"/><link rel="schema.DCAM" href="http://purl.org/dc/dcam/" hreflang="en"/><style type="text/css">
	html += QString("<HTML><HEAD><STYLE type=\"text/css\">"
			"	table { border-style: solid;  border-color:#000000;	border: 1px solid black; border-spacing:0; empty-cells:show }"
			"	td, th { vertical-align:top; font-size:12pt;}"
			"	h1, h2, h3, h4, h5, h6 { clear:both }"
			"	ol, ul { margin:0; padding:0;}"
			"	li { list-style: none; margin:0; padding:0;}"
			"	<!-- 'li span.odfLiEnd' - IE 7 issue-->"
			"	li span. { clear: both; line-height:0; width:0; height:0; margin:0; padding:0; }"
			"	span.footnodeNumber { padding-right:1em; }"
			"	span.annotation_style_by_filter { font-size:95%; font-family:Arial; background-color:#fff000;  margin:0; border:0; padding:0;  }"
			"	* { margin:0;}"
			"	.Header { font-size:12pt; font-family:Liberation Serif; writing-mode:page; }"
			"	.P1 { font-size:7pt; font-family:Liberation Serif; writing-mode:page; }"
			"	.P2 { font-size:7pt; font-family:Liberation Serif; writing-mode:page; }"
			"	.P3 { font-size:7pt; font-family:Liberation Serif; writing-mode:page; }"
			"	.P4 { font-size:7pt; font-family:Liberation Serif; writing-mode:page; }"
			"	.P5 { font-size:7pt; font-family:Liberation Serif; writing-mode:page; }"
			"	.Standard { font-size:12pt; font-family:Liberation Serif; writing-mode:page; }"
			"	.Tabela1 { width:8.7cm; margin-left:0px; margin-right:auto;}"
			"	.Tabela1_A1 { padding:0.097cm; border-left-width:thin; border-left-style:solid; border-left-color:#000000; border-right-style:none; border-top-width:thin; border-top-style:solid; border-top-color:#000000; border-bottom-width:thin; border-bottom-style:solid; border-bottom-color:#000000; }"
			"	.Tabela1_A2 { padding:0.097cm; border-left-width:thin; border-left-style:solid; border-left-color:#000000; border-right-style:none; border-top-style:none; border-bottom-width:thin; border-bottom-style:solid; border-bottom-color:#000000; }"
			"	.Tabela1_D1 { padding:0.097cm; border-width:thin; border-style:solid; border-color:#000000; }"
			"	.Tabela1_D2 { padding:0.097cm; border-left-width:thin; border-left-style:solid; border-left-color:#000000; border-right-width:thin; border-right-style:solid; border-right-color:#000000; border-top-style:none; border-bottom-width:thin; border-bottom-style:solid; border-bottom-color:#000000; }"
			"	.Tabela1_A { width:2.605cm; }"
			"	.Tabela1_B { width:1.69cm; }"
			"	.Tabela1_C { width:2.014cm; }"
			"	.Tabela1_D { width:2.39cm; }"
			"	<!-- ODF styles with no properties representable as CSS -->"
			"	.Tabela1.1 .Tabela1.2 .Tabela1.3 .Tabela1.4 .Tabela1.5 .T1 .T2  { }"
			"	</style></head><body dir='ltr' style='max-width:21.001cm;margin-top:2cm; margin-bottom:2cm; margin-left:2cm; margin-right:2cm; '><table border='1' cellspacing='0' cellpadding='0' class='Tabela1'><colgroup><col width='114'/><col width='74'/><col width='88'/><col width='104'/></colgroup><tr class='Tabela11'>"
			"<td style='text-align:left;width:2.605cm; ' class='Tabela1_A1'><p class='P1'><span class='T2'>WPRO</span>W<span class='T1'>ADZONO:</span>                   </p><p class='P1'> </p><p class='P1'>DATA <span class='T1'>REALIZACJI</span>:</p><p class='P2'> </p></td><td colspan='2' style='text-align:left;width:1.69cm; ' class='Tabela1_A1'>"
			"<p class='P2'>ZAMÓWIENIE:</p></td><td style='text-align:left;width:2.39cm; ' class='Tabela1_D1'><p class='P2'>ZLECAJĄCY:</p></td></tr><tr class='Tabela12'><td style='text-align:left;width:2.605cm; ' class='Tabela1_A2'><p class='P2'>WZÓR:</p><p class='P2'> </p><p class='P2'> </p></td><td style='text-align:left;width:1.69cm; ' class='Tabela1_A2'>"
			"<p class='P3'>SPODY:</p></td><td style='text-align:left;width:2.014cm; ' class='Tabela1_A2'><p class='P4'>KOLOR SKÓRA</p></td><td style='text-align:left;width:2.39cm; ' class='Tabela1_D2'><p class='P4'>SZARFIARZ:</p></td></tr><tr class='Tabela13'><td colspan='3' rowspan='2' style='text-align:left;width:2.605cm; ' class='Tabela1_A2'><p class='P5'>sss</p></td><td style='text-align:left;width:2.39cm; '"
			" class='Tabela1_D2'><p class='P4'>PRZYJMUJĄCY:</p></td></tr><tr class='Tabela14'><td style='text-align:left;width:2.39cm; ' class='Tabela1_D2'><p class='P4'>MONTAŻ:</p></td></tr><tr class='Tabela15'><td colspan='4' style='text-align:left;width:2.605cm; ' class='Tabela1_D2'><p class='P4'>UWAGI:</p></td></tr></table><p class='Standard'> </p></body></html>");

	document->setHtml(html);
}

QString DokumentDoDruku::itemsAsHtmlTable(const ZamowieniaDruk &thePage) {
	QString html("<table border='1' cellpadding='3' cellspacing='0' style='page-break-before: always; page-break-after: auto'>");
	for (int i = 0; i < thePage.captions.count(); ++i) {
		if (i % 2 == 0) {
			html += "<tr>\n";
		}
		html += QString("<td align='center'><p style='font-size:18pt'>%1</p></td>\n")
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
