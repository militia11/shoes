//#include"Zamowienia.h"
//#include"Zamowienia.h"
//#include<QMessageBox>

//static const int COLUMNS(5);

//Zamowienia::Zamowienia(QObject *parent) :  QAbstractTableModel(
//		parent)//mZamowienia(people) //QList<Zamowienie*>people  {/
//{}

//int Zamowienia::rowCount(const QModelIndex &parent) const {
//	Q_UNUSED(parent);
//	return mZamowienia.size();
//}

//int Zamowienia::columnCount(const QModelIndex &parent) const {
//	Q_UNUSED(parent);
//	return COLUMNS;
//}

//QList<Zamowienie *> Zamowienia::getData() const {
//	return mZamowienia;
//}

//QVariant Zamowienia::data(const QModelIndex &index, int role) const {
//	if (role != Qt::DisplayRole) {
//		return QVariant();
//	}
//	int row = index.row();
//	switch ( index.column() ) {
//		case 0:
//			return mZamowienia[row]->getName();
//		case 1:
//			return mZamowienia[row]->getPhoneNumber();
//		case 2:
//			return mZamowienia[row]->getAdress();
//		case 3:
//			return mZamowienia[row]->getAge();
//		case 4:
//			return mZamowienia[row]->getPESEL();
//		default:
//			return QVariant();
//	}
//}

//QModelIndex Zamowienia::createIndex(int row, int column, quintptr id) const {
//	Q_UNUSED(id);
//	return QAbstractItemModel::createIndex(row, column);
//}

//Qt::ItemFlags Zamowienia::flags(const QModelIndex &index) const {
//	if (index.isValid()) {
//		return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
//	}
//	else {
//		return 0;
//	}
//}

//bool Zamowienia::setData(const QModelIndex &index, const QVariant &value,
//			 int role) {
//	if (role != Qt::EditRole) {
//		return false;
//	}
//	int row = index.row(), col = index.column();
//	if ( col == 0 ) {
//		if ( !value.toString().isEmpty() ) {
//			mZamowienia[row]->setName(value.toString());
//		}
//		else {
//			QMessageBox::warning( 0, "Warning Incorrect Zamowienie Name",
//						  "<center>You can't set <b>empty</b> word as Zamowienie's name.<br> Please enter correct Zamowienie's' name. ",
//						  QMessageBox::Ok);
//		}
//	}
//	if ( col == 1 ) {
//		mZamowienia[row]->setPhoneNumber(value.toString());
//	}
//	if ( col == 2 ) {
//		mZamowienia[row]->setCity(value.toString());
//	}
//	if ( col == 3 ) {
//		mZamowienia[row]->setAge(value.toInt());
//	}
//	if ( col == 4 ) {
//		mZamowienia[row]->setPESEL(value.toLongLong());
//	}
//	QModelIndex indexAfterChanged = createIndex(row, col);
//	emit dataChanged(indexAfterChanged, indexAfterChanged);
//	return true;
//}
//void Zamowienia::insertRows(int row, int count, Zamowienie *Zamowienie,
//				const QModelIndex &parent ) {
//	beginInsertRows(parent, row, row + count - 1);
//	for ( int i = 0; i < count; ++i) {
//		mZamowienia.insert(row + i, Zamowienie);
//	}
//	endInsertRows();
//}
//void Zamowienia::insertRows(int row, int count, QList<Zamowienie *> people,
//				const QModelIndex &parent ) {
//	beginInsertRows(parent, row, row + count - 1);
//	for ( int i = 0; i < count; ++i) {
//		mZamowienia.insert(row + i, people[i]);
//	}
//	endInsertRows();
//}

//bool Zamowienia::removeRows(int row, int count, const QModelIndex &parent ) {
//	beginRemoveRows(parent, row, row + count - 1);
//	mZamowienia.removeAt(row);
//	endRemoveRows();
//	return true;
//}
//QVariant Zamowienia::headerData(const int section,
//				const Qt::Orientation orientation, const int role) const {
//	if ( orientation != Qt::Horizontal || role != Qt::DisplayRole ) {
//		return QAbstractItemModel::headerData( section, orientation, role );
//	}
//	switch ( section ) {
//		case 0:
//			return "Zamowienie:";
//		case 1:
//			return "Phone number:";
//		case 2:
//			return "City:";
//		case 3:
//			return "Age:";
//		case 4:
//			return "PESEL:";
//	}
//	return QVariant();
//}

//Zamowienie *Zamowienia::getItem(int row) const {
//	return mZamowienia[row];
//}

//Zamowienia::~Zamowienia() {
//	qDeleteAll(mZamowienia);
//	mZamowienia.clear();
//}
