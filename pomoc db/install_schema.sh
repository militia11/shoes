#!/bin/bash

INSTALL_SCHEMA_SCRIPT_DIR="$( cd "$( dirname "$0" )" && pwd )"

source $INSTALL_SCHEMA_SCRIPT_DIR/die.sh

if [ "$1" == "--help" ] || [ "$#" -ne "1" ]; then
	echo "Usage:"
	echo "	$0 mysql_root_password"
	echo
	exit 2
fi

echo "Removing the old data and schema..."
echo "drop database monitor_zssw;" | /wb-5.0/system/bin/mysql -u root --password="$1"

echo "Creating a new database..."
echo "create database monitor_zssw;" | /wb-5.0/system/bin/mysql -u root --password="$1" || die

echo "Importing the new schema..."
/wb-5.0/system/bin/mysql -u root --password="$1" monitor_zssw < $INSTALL_SCHEMA_SCRIPT_DIR/../schema/schema.mysql.sql || die

echo "Importing the dictionary of event types..."
/wb-5.0/system/bin/mysql -u root --password="$1" monitor_zssw < $INSTALL_SCHEMA_SCRIPT_DIR/../schema/eventsTypes.sql || die

echo "Updating database complete"
