#ifndef ZAMOWIENIE_H
#define ZAMOWIENIE_H

#include <QString>
#include <QVector>
struct zamowienieStruct {
	QString nrZ;
	QString klNaz;
	QString klNr;
	QString wzor;
	QString kolor;
	QString status;
	QString ociep;
	QString mat;
	QString uzyt;
	QString wkladka;
	QString sk1;
	QString sk2;
	QString sk3;
	QString ha ;
	QString snaz;
	QString sprod;
	QString wpr;
	QString rea;
};

struct zamowienieZRozmiaramiStruct : public zamowienieStruct {
	QVector<int>rozmiary;
};

#endif // ZAMOWIENIE_H
