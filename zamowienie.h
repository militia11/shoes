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
    QString typ;
    QString mont;
    QString r1;
    QString r2;
    QString r3;
    QString r4;
    QString r5;
    QString r6;
    QString spn;
    QString uwagi;
    QString uwagi2;
    QString rozkrojNr;
};

struct zamowienieZRozmiaramiStruct : public zamowienieStruct {
    QVector<int>rozmiary;
};

#endif // ZAMOWIENIE_H
