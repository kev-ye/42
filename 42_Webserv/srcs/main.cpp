/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:20:57 by besellem          #+#    #+#             */
/*   Updated: 2021/11/16 15:51:40 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

/* global */
INLINE_NAMESPACE::WebServer		webserv_g;

int		main(int ac, char **av)
{
	INLINE_NAMESPACE::printWebservHeader();

	try
	{
		webserv_g.parse((ac > 1) ? av[1] : DEFAULT_CONFIG_FILE);
	}
	catch (std::exception &e)
	{
		EXCEPT_ERROR(e);
		return EXIT_FAILURE;
	}

	signal(SIGINT, INLINE_NAMESPACE::handleSignals);

	webserv_g.createServers();
	
	return EXIT_SUCCESS;
}
