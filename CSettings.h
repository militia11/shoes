#ifndef CSETTINGS_H
#define CSETTINGS_H

#include <QSettings>
#include <QtCore/qglobal.h>

/**
 * @brief The CSettings class represents application settings
 */
class CSettings {
 public:
  /**
   * @brief CSettings constructor
   */
  CSettings();

  QString getHost();
  QString getDatabaseName();
  QString getUser();
  QString getPassword();
};
#endif // CSETTINGS_H

