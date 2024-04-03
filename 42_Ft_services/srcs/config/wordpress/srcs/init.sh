# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    init.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/16 19:08:35 by kaye              #+#    #+#              #
#    Updated: 2021/05/12 18:53:50 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# init
openrc
touch /run/openrc/softlevel

# configure msql password
sed -i "s/WP_PASSWORD/$WP_PASS/g" /var/www/wordpress/wordpress/wp-config.php

# start telegraf
telegraf --config /etc/telegraf.conf &

# start php
php-fpm7

# start nginx
nginx -g 'daemon off;'