#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QSettings>
#include <QtCore/qglobal.h>

class CSettings {
	public:
		CSettings();

		QString getHost();
		QString getDatabaseName();
		QString getUser();
		QString getPassword();
};
#endif // CSETTINGS_H

