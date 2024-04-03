# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    livenessProbe.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/29 20:03:42 by kaye              #+#    #+#              #
#    Updated: 2021/04/29 20:13:59 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

if ! pidof nginx ; then
	service nginx restart
fi

if ! pidof sshd ; then
	service sshd start
fi