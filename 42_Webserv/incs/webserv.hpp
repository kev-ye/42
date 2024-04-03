/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 14:22:05 by besellem          #+#    #+#             */
/*   Updated: 2021/11/16 15:51:59 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include "defs.hpp"
# include "ServerGenerator.hpp"
# include "cgi.hpp"
# include "socket.hpp"
# include "epoll.hpp"

_BEGIN_NS_WEBSERV

class ServerGenerator;
class cgi;
class Socket;
class Epoll;

class WebServer
{
	public:
		WebServer(void);
		~WebServer();
	
	private:
		WebServer(const WebServer &);
		WebServer&				operator=(const WebServer &);
	
	public:
		void					parse(const std::string &);
		size_t					serverSize(void) const;
		const Server&			getServer(int) const;
		void					createServers(void);

	private:
		size_t					countSocket() const;
		std::vector<Server *>	selectServers(size_t& index);

	public:
		class ParsingError : public std::exception
		{
			public:
				virtual const char*	what() const throw();
		};
		
	private:
		ServerGenerator		_servers;
		Socket				*_socks;
	
}; /* class WebServer */

_END_NS_WEBSERV

#endif /* !defined(WEBSERV_HPP) */
