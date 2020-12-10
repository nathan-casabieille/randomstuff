sudo dnf install httpd-manual php phpmyadmin mariadb
systemctl start httpd.service
systemctl start mariadb.service
mariadb
# -> CREATE DATABASE `mydb`;
# -> CREATE USER 'myuser' IDENTIFIED BY 'mypassword';
# -> GRANT USAGE ON *.* TO 'myuser'@localhost IDENTIFIED BY 'mypassword';
# -> FLUSH PRIVILEGES;
composer install
npm install
php -S localhost:8000 -t .
