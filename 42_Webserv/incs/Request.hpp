/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 22:41:14 by adbenoit          #+#    #+#             */
/*   Updated: 2021/11/12 17:07:40 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "defs.hpp"
# include "HttpHeader.hpp"
# include "Server.hpp"
# include "cgi.hpp"

_BEGIN_NS_WEBSERV

enum	e_uploadKey
{
	FN,
	DQ,
	CT,
	RN,
	DRN,
	LAST_BOUNDARY
};

class Cgi;

class Request
{
	public:
		typedef std::map<std::string, std::string>             info_type;
		typedef std::vector<std::string>                       vector_type;
		typedef std::vector<t_location *>                      location_type;
		typedef std::pair<std::string, std::string>            pair_type;
	
	public:
		Request(const Request &);
		Request(void);
		~Request();
		Request&			operator=(const Request &);

	private:

	public:
		HttpHeader&			getHeader(void);
		const std::string&	getContent(void) const;
		const std::string&	getConstructPath(void) const;
		size_t				getContentLength(void) const;
		const Server*		getServer(void) const;
		const t_location*	getLocation(void) const;
		const int&			getStatus(void) const;
		
		
		bool				setRequestFirstLine(const std::string &);
		void				setConstructPath(void);
		void				setConstructPath(const std::string &);
		void				setContent(void);
		void				setHeaderData(const std::string &);
		void				setChunked(void);
		void				setServer(const Server *);
		void				setStatus(const int &);

		const info_type&	getFileInfo(void) const;
		bool				checkIsUploadCase(void);
		const std::string&	getBoundary(void) const;
		bool				parseFile(void);

		void				print(void) const;

	private:
		HttpHeader			_header;
		std::string			_constructPath;
		std::string			_content;
		const Server		*_server;
		bool				_isChunked;
	
		info_type			_fileInfo;
		std::string			_boundary;
		int					_status;
	
}; /* class Request */

_END_NS_WEBSERV

#endif
