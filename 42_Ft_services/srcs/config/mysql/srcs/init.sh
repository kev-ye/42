# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    init.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/16 19:09:41 by kaye              #+#    #+#              #
#    Updated: 2021/05/12 19:14:22 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# TIPS : check database accessible : mysql -h["IP address"] -P["PORT"] -u["USER"] -p["PASSWORD"] ["DATABSE"]

# init
openrc
touch /run/openrc/softlevel

# create mariadb
/etc/init.d/mariadb setup

# remote access
sed -i 's/skip-networking/# skip-networking/g' /etc/my.cnf.d/mariadb-server.cnf
sed -i 's/#bind-address/bind-address/g' /etc/my.cnf.d/mariadb-server.cnf

# start mariadb
service mariadb start

sleep 10

# Configure wordpress database & admin database
echo "create database wordpress;" | mysql -u root
echo "create user 'wordpress'@'%' IDENTIFIED BY '$WP_PASS';" | mysql -u root
echo "grant all privileges on wordpress.* to 'wordpress'@'%' with grant option;" | mysql -u root
echo "create database admin;" | mysql -u root
echo "create user 'admin'@'%' IDENTIFIED BY '$ADMIN_PASS';" | mysql -u root
echo "grant all privileges on *.* to 'admin'@'%' with grant option;" | mysql -u root
echo "flush privileges" | mysql -u root

mysql -u root "wordpress" < /APP/srcs/wordpress.sql

# restart mariadb
service mariadb restart

# start telegraf
telegraf --config /etc/telegraf.conf