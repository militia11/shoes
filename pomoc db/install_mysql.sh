#!/bin/bash

INSTALL_MYSQL_SCRIPT_DIR="$( cd "$( dirname "$0" )" && pwd )"

source $INSTALL_MYSQL_SCRIPT_DIR/die.sh

if [ $(id -u) != "0" ] || [ "$1" == "--help" ] || [ $# -ne "3" ] ; then
	echo "This script must be run as root"
	echo "Usage:"
	echo "	./install_database.sh new_mysql_root_password new_mysql_monitoring_write_password new_mysql_monitoring_read_password"
	echo
	exit 2
fi

echo "Stopping MySQL deamon..."
killall -w mysqld

echo "Moving old MySQL files..."
NOW="$(date +'%Y%m%dT%H%M%S')"
if sudo test -d "/var/lib/mysql"; 
then
	mv "/var/lib/mysql" "/var/lib/mysql-old-$NOW"
fi
mkdir -m 700 /var/lib/mysql || die
if sudo test -d "/etc/mysql"; 
then
	mv "/etc/mysql" "/etc/mysql-old-$NOW"
fi

echo "Creating MySQL system account..."
useradd -M mysql
if [ "$?" == 9 ]; then
	echo "User mysql already exists"
elif [ "$?" != 0 ]; then
	die
fi
chsh -s /bin/bash mysql || die
chown -R mysql:mysql /var/lib/mysql || die
usermod -d /var/lib/mysql mysql || die

echo "Installing base MySQL files..."
pushd /wb-5.0/system
su mysql -c "./scripts/mysql_install_db --datadir=/var/lib/mysql --basedir=/wb-5.0/system/" || die
popd

echo "Setting MySQL password of user root..."
touch /var/run/mysql.pid
chmod u+w /var/run/mysql.pid
chown mysql:mysql /var/run/mysql.pid
su mysql -c "$INSTALL_MYSQL_SCRIPT_DIR/start_mysql" || die
/wb-5.0/system/bin/mysqladmin password $1 || die

echo "Installing schema..."
su mysql -c "$INSTALL_MYSQL_SCRIPT_DIR/install_schema.sh $1" || die

echo "Creating users..."
/wb-5.0/system/bin/mysql -u root --password=$1  <<MYSQL_SCRIPT
CREATE USER 'monitoring_read'@'%' IDENTIFIED BY '$Read_Pass';
GRANT SELECT ON monitor_zssw.* TO 'monitoring_read'@'%' IDENTIFIED BY '$2';
CREATE USER 'monitoring_write'@'localhost' IDENTIFIED BY '$Write_Pass';
GRANT INSERT, SELECT, UPDATE ON monitor_zssw.* TO 'monitoring_write'@'localhost' IDENTIFIED BY '$3';
DELETE FROM mysql.user WHERE User = '';
FLUSH PRIVILEGES;
MYSQL_SCRIPT

echo "Modifing rc.local script..."
touch /etc/rc.local || die
chmod u+x /etc/rc.local || die
sed -i '/wb-mysql-start/d' /etc/rc.local || die
sed -ie '$i # server wb-mysql-start' /etc/rc.local || die
COMMANDS="touch /var/run/mysql.pid # wb-mysql-start\n"
COMMANDS="${COMMANDS}chmod u+w /var/run/mysql.pid # wb-mysql-start\n"
COMMANDS="${COMMANDS}chown mysql:mysql /var/run/mysql.pid # wb-mysql-start\n"
COMMANDS="${COMMANDS}su - mysql -c '${INSTALL_MYSQL_SCRIPT_DIR}/start_mysql' # wb-mysql-start"
sed -i "`grep -n server /etc/rc.local | cut -d : -f 1 | head -1` i\\`echo $COMMANDS`" /etc/rc.local || die
echo "Configuration finished"
