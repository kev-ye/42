# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    init.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/28 21:35:30 by kaye              #+#    #+#              #
#    Updated: 2021/05/12 19:18:24 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# init
openrc
touch /run/openrc/softlevel

# run influxdb
service influxdb start

sleep 2

# create database
echo "create database telegraf" | influx

# start telegraf
telegraf --config /etc/telegraf.conf