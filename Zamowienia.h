//#ifndef Zamowienia_H
//#define Zamowienia_H

//#include "Zamowienie.h"
//#include <QStandardItemModel>
//#include <QObject>

//class Zamowienia : public QAbstractTableModel
//{
//		Q_OBJECT

//	public:
//		explicit Zamowienia( QObject *parent = 0 );//QList<Zamowienie*>people,
//		~Zamowienia();

//		int rowCount(const QModelIndex &parent = QModelIndex()) const ;
//		int columnCount(const QModelIndex &parent = QModelIndex()) const ;

//		void insertRows(int row, int count, Zamowienie *Zamowienie,
//				const QModelIndex &parent = QModelIndex() );
//		void insertRows(int row, int count, QList<Zamowienie *> people,
//				const QModelIndex &parent = QModelIndex() );
//		bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());

//		QVariant data(const QModelIndex &index, int role) const;
//		Qt::ItemFlags flags(const QModelIndex &index) const;
//		QModelIndex createIndex(int row, int column, quintptr id = 0) const;

//		QVariant headerData(int section, Qt::Orientation orientation, int role) const;
//		bool setData(const QModelIndex &index, const QVariant &value, int role);

//		Zamowienie *getItem(int row) const;
//		QList<Zamowienie *> getData() const;

//	private:
//		QList<Zamowienie *> mZamowienia;
//};
//#endif // Zamowienia_H
