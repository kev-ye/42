# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    init.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/19 10:39:45 by kaye              #+#    #+#              #
#    Updated: 2021/02/22 15:25:21 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Init configuration ##

# Creat ssl certificate #
## req :            creat certificate siging request
## -x509 :          sign
## -newkey rsa :    encrypt with rsa (4096 bytes)
## -sha256 :        hash with sha256
## -nodes :         no ask encryption when creat private key
## -keyout :        output key file(.pem)
## -out :           output certificate file
## -days :          valid period
## -subj :          information "/CN=Country name/ST=State/L=Locality/O=Organization/OU=Organization unit/CN=Common/emailAddress=Email"
mkdir /etc/nginx/ssl
openssl req \
        -x509 \
        -newkey rsa:4096 \
        -sha256 \
        -nodes \
        -keyout /etc/nginx/ssl/key.pem \
        -out /etc/nginx/ssl/cert.pem \
        -days 3650 \
        -subj "/CN=FR/ST=Paris/L=Paris/O=42/OU=42/CN=kaye"

# Start mysql #
service mysql start

# Configure wordpress database #
echo "create database wordpress;" | mysql -u root
echo "create user 'wordpress'@'%';" | mysql -u root
echo "grant all privileges on wordpress.* to 'wordpress'@'%' with grant option;" | mysql -u root
echo "flush privileges" | mysql -u root

# Creat website folder #
mkdir /var/www/website

# Download and configure phpmyadmin #
wget https://files.phpmyadmin.net/phpMyAdmin/5.0.4/phpMyAdmin-5.0.4-all-languages.tar.gz
tar -xzvf phpMyAdmin-5.0.4-all-languages.tar.gz
rm -rf phpMyAdmin-5.0.4-all-languages.tar.gz
mv phpMyAdmin-5.0.4-all-languages /var/www/website/phpmyadmin
mv /APP/srcs/config.inc.php /var/www/website/phpmyadmin/
chmod -R 755 /var/www/website/phpmyadmin/
chown -R www-data:www-data /var/www/website/phpmyadmin

# Download and configure wordpress #
wget https://wordpress.org/latest.tar.gz
tar -xzvf latest.tar.gz
rm -rf latest.tar.gz
mv wordpress /var/www/website/wordpress
mv /APP/srcs/wp-config.php /var/www/website/wordpress
chmod -R 755 /var/www/website/wordpress/
chown -R www-data:www-data /var/www/website/wordpress

# Configure server #
cp /APP/srcs/website_autoindex_on /etc/nginx/sites-available/website
rm /etc/nginx/sites-enabled/default
ln -s /etc/nginx/sites-available/website /etc/nginx/sites-enabled/

# Access for script #
chmod 755 /APP/srcs/autoindex.sh

# Start php-fpm service #
## service php7.3-fpm stop -> to stop
## service php7.3-fpm restart -> to restart
service php7.3-fpm start

# Start nginx service #
service nginx start

# Check database and grants #
echo "show databases" | mysql -u root | grep 'wordpress'
echo "show grants for wordpress;" | mysql -u root

# Run bash #
bash