# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    init.sh                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/16 19:09:09 by kaye              #+#    #+#              #
#    Updated: 2021/05/12 19:04:29 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# TIPS : to connect ssh : ssh (ID)@(ADDRESS IP) -p (PORT)

# init
openrc
touch /run/openrc/softlevel

# run sshd
service sshd start

# start telegraf
telegraf --config /etc/telegraf.conf &

# run nginx
nginx -g 'daemon off;'