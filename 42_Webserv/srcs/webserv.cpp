/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 05:59:50 by besellem          #+#    #+#             */
/*   Updated: 2021/11/18 08:28:15 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"


_BEGIN_NS_WEBSERV

WebServer::WebServer(void) :
	_servers(),
	_socks(NULL)
{}

WebServer::~WebServer()
{
	if (_socks != NULL)
	{
		delete [] _socks;
		_socks = NULL;
	}
}

/*
** Declared in `parser.cpp' :
**
** void		WebServer::parse(const std::string&);
*/

size_t			WebServer::serverSize(void) const
{ return this->_servers.size(); }

const Server&	WebServer::getServer(int i) const
{ return *(this->_servers[i]); }

/* Count the differents socket of the config file */
size_t			WebServer::countSocket() const
{
	size_t	count = _servers.size();

	for (size_t i = 0; i < _servers.size(); ++i)
	{
		for (size_t j = 0; j < i; ++j)
		{
			if (_servers[i]->ip() == _servers[j]->ip() && _servers[i]->port() == _servers[j]->port())
			{
				--count;
				break ;
			}
		}
	}
	return count;
}

/* Selects all server blocks adapted to the socket */
std::vector<Server *>	WebServer::selectServers(size_t& index)
{
	std::vector<Server *>	blocks;
	bool					firstOccur = false;

	/* is index the first server block of this socket */
	while (false == firstOccur)
	{
		firstOccur = true;
		for (size_t j = 0; j < index; ++j)
		{
			if (_servers[index]->ip() == _servers[j]->ip() &&
				_servers[index]->port() == _servers[j]->port())
			{
				firstOccur = false;
				if (index == _servers.size()) // should never happen
					return blocks;
				++index;
				break ;
			}
		}
	}
	
	blocks.push_back(_servers[index]);
	
	/* get the others server blocks for this socket */
	for (size_t i = index + 1; i < _servers.size(); i++)
	{
		if (_servers[index]->ip() == _servers[i]->ip() &&
			_servers[index]->port() == _servers[i]->port())
		{
			blocks.push_back(_servers[i]);
		}
	}
	return blocks;
}

void			WebServer::createServers(void)
{
	const size_t	n = countSocket();
	Socket			cur;

	/* create a socket for each different server declared in the config file */
	_socks = new Socket[n];
	for (size_t i = 0, j = 0; j < n; ++i, ++j)
	{
		/** @brief init server */
		_socks[j] = Socket(selectServers(i));
		_socks[j].startSocket();
	}

	/** @brief start server */
	Epoll	_epoll(_socks, n);
	_epoll.startEpoll();
}

const char*		WebServer::ParsingError::what() const throw()
{ return "file not served by webserv"; }


_END_NS_WEBSERV
