# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    autoindex.sh                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/22 13:12:57 by kaye              #+#    #+#              #
#    Updated: 2021/02/22 13:35:50 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

auto_on=$(cat /etc/nginx/sites-available/website | grep "autoindex")

if [ "$auto_on" = "" ]; then
    echo "autoindex is off, turning it on..."
    rm /etc/nginx/sites-available/website
    rm /etc/nginx/sites-enabled/website
    cp /APP/srcs/website_autoindex_on /etc/nginx/sites-available/website
else
    echo "autoindex is on, turning it off..."
    rm /etc/nginx/sites-available/website
    rm /etc/nginx/sites-enabled/website
    cp /APP/srcs/website_autoindex_off /etc/nginx/sites-available/website
fi

ln -s /etc/nginx/sites-available/website /etc/nginx/sites-enabled/
service nginx restart