/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerGenerator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 15:53:17 by adbenoit          #+#    #+#             */
/*   Updated: 2021/10/26 23:11:26 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVERGENERATOR_HPP
# define SERVERGENERATOR_HPP

# include "defs.hpp"
# include "Server.hpp"

_BEGIN_NS_WEBSERV

/* Config file states */
enum	e_config_state
{
	START,
	NEW_SERVER,
	IN_SERVER,
	NEW_LOCATION,
	IN_LOCATION
};

class ServerGenerator
{

	public:
		typedef Server::tokens_type                            tokens_type;
	
	public:
		ServerGenerator();
		ServerGenerator(const ServerGenerator &);
		~ServerGenerator();
		ServerGenerator&	operator=(const ServerGenerator &);
		
	public:
		int					state() const;
		size_t				size() const;

		/* Element access */
		Server*				operator[](int) const;
		Server*				last() const;
		
		/* Modifiers / Checkers */
		void				newDirective(Server *, const tokens_type &);
		void				newLocation(Server *, const tokens_type &);
		void				newServer(const tokens_type &);
		void				openBlock(const tokens_type &);
		void				closeBlock(const tokens_type &);
		
	private:
		std::vector<Server *>	_servers;
		int						_state;

}; /* class ServerGenerator */

std::ostream&	operator<<(std::ostream &, const ServerGenerator &);

_END_NS_WEBSERV

#endif /* !defined(SERVERGENERATOR_HPP) */
