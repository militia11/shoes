#include "CSettings.h"

CSettings::CSettings() {
}

QString CSettings::getHost()
{	QString vString;
	QSettings vSettings;
	vSettings.beginGroup("database");
	static_cast<void>(vString = vSettings.value("host").toString()),
	vSettings.endGroup();
	return vString;

}

QString CSettings::getDatabaseName()
{
	QString vString;
	QSettings vSettings;
	vSettings.beginGroup("database");
	vString = vSettings.value("databaseName").toString();
	vSettings.endGroup();
	return vString;
}

QString CSettings::getUser()
{
	QString vString;
	QSettings vSettings;
	vSettings.beginGroup("database");
	static_cast<void>(vString = vSettings.value("user").toString()),
	vSettings.endGroup();
	return vString;
}

QString CSettings::getPassword()
{	QString vString;
	QSettings vSettings;
	vSettings.beginGroup("database");
	static_cast<void>(vString =  vSettings.value("password").toString()),
	vSettings.endGroup();
	return vString;
}
