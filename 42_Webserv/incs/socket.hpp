/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 16:49:04 by kaye              #+#    #+#             */
/*   Updated: 2021/11/18 08:40:40 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include "defs.hpp"
# include "utils.hpp"
# include "Server.hpp"
# include "HttpHeader.hpp"
# include "Response.hpp"
# include "Request.hpp"

_BEGIN_NS_WEBSERV

class Socket
{
	public:
		typedef std::vector< std::string >		vector_type;
		typedef std::pair< int, std::string >	pair_type;
		typedef std::map<const int, Response*>	resp_type;

	public:
	/** @brief constructor / destructor */

		explicit Socket(void);
		explicit Socket(const std::vector<Server *>);
		Socket(const Socket &);
		~Socket();
		Socket&			operator=(const Socket &);

	public:
		short			getPort(void) const;
		int				getServerFd(void) const;
		const Server*	getServer(void) const;
		sockaddr_in		getAddr(void) const;
		size_t			getAddrLen(void) const;
		Response		*getCurrResponse(int const) const;

		const Server*	selectServer(const std::string &) const;

		/** @brief init socket */
		void			startSocket(void);
		
		// int			readHttpRequest(Request *, int);
		int				readHttpRequest(Request *, struct kevent currEvt);
		int				resolveHttpRequest(Request *);
		int				sendHttpResponse(Request *, int);

		void			setNonBlock(int & fd);
		int				socketAccept(void);


	private:
		void			bindStep(const int &, const sockaddr_in &);
		void			listenStep(const int &);
		
		void			setHeaderData(const std::string &);
		std::string		constructPath(void);

		size_t			requestLen(std::string const &);
		
	private:
		std::vector<Server *>	_server_blocks; // which was parsed for this socket
		short					_port;
		int						_serverFd;
		sockaddr_in				_addr;
		size_t					_addrLen;
	
		int						_sendStatus;
		resp_type				_respMap;
		Response				*_currResponse;

}; /* class Socket */

_END_NS_WEBSERV

#endif /* !defined(SOCKET_HPP) */
