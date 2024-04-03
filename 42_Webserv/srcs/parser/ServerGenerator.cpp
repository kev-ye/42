/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerGenerator.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:53:19 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/26 23:06:43 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

_BEGIN_NS_WEBSERV


ServerGenerator::ServerGenerator() { this->_state = START; }

ServerGenerator::~ServerGenerator() {
	for (size_t i = 0; i < this->_servers.size(); i++)
		delete this->_servers[i];
	this->_servers.clear();
}

ServerGenerator::ServerGenerator(const ServerGenerator &x) {
	*this = x;
}

ServerGenerator&	ServerGenerator::operator=(const ServerGenerator &x) {
	if (&x == this)
		return *this;
	this->_servers = x._servers;
	this->_state = x._state;
	return *this;
}

int		ServerGenerator::state() const { return this->_state; }
size_t	ServerGenerator::size()  const { return this->_servers.size(); }

/*
**  Element access
*/

Server*	ServerGenerator::operator[](int i) const { return this->_servers[i]; }
Server*	ServerGenerator::last()            const { return this->_servers.back(); }

/*
**  Modifiers / Checkers
*/

/* if the key 'server' is well placed, add a new location to the generator */
void	ServerGenerator::newServer(const tokens_type &tok) {
	if (tok.size() != 1 || this->_state != START)
		throw WebServer::ParsingError();
	this->_servers.push_back(new Server());
	this->_state = NEW_SERVER;
}

/* if the key 'location' is well placed, add a new location to the server */
void	ServerGenerator::newLocation(Server *server, const tokens_type &tok) {
	if (this->_state != IN_SERVER)
		throw WebServer::ParsingError();
	server->newLocation(tok);
	this->_state = NEW_LOCATION;
}

/* if the directive is well placed, add it to the server */
void	ServerGenerator::newDirective(Server *server, const tokens_type &tok) {
	if (this->_state == IN_SERVER)
		server->newDirective(tok);
	else if (this->_state == IN_LOCATION)
		server->newLocationDirective(tok);
	else
		throw WebServer::ParsingError();
}

/* check if the '{' is well placed */
void	ServerGenerator::openBlock(const tokens_type &tokens)
{
	if (tokens.size() != 1)
		throw WebServer::ParsingError();

	if (this->_state == NEW_SERVER || this->_state == NEW_LOCATION)
		++this->_state;
	else
		throw WebServer::ParsingError();
}

/* check if the '}' is well placed */
void	ServerGenerator::closeBlock(const tokens_type &tokens)
{
	if (tokens.size() != 1)
		throw WebServer::ParsingError();

	if (this->_state == IN_LOCATION)
		this->_state = IN_SERVER;
	else if (this->_state == IN_SERVER)
		this->_state = START;
	else
		throw WebServer::ParsingError();
}

/* Display server blocks like the config file */
std::ostream&	operator<<(std::ostream& os, const ServerGenerator& servers)
{
	for (size_t i = 0; i < servers.size(); i++)
		os << *(servers[i]);
	return os;
}


_END_NS_WEBSERV
