/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 22:41:14 by adbenoit          #+#    #+#             */
/*   Updated: 2021/11/14 14:35:44 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "defs.hpp"
# include "cgi.hpp"
# include "Request.hpp"

_BEGIN_NS_WEBSERV

class Response
{

	public:
		typedef std::map<std::string, std::string>             info_type;
		typedef std::pair<int, std::string>                    status_type;

	public:
		Response(Request *);
		~Response();

	private:
		Response(void);
		Response(const Response &);
		Response&			operator=(const Response &);

	public:
		const std::string&  getHeader(void) const;
		const std::string&  getContent(void) const;
		size_t				getContentLength(void) const;
		const status_type&  getStatus(void) const;
		bool				getCgiStatus(void) const;
		int					getCgiStep(void) const;
		
	
		const std::string   generateAutoindexPage(std::string const &) const;
		void		        setContent(const std::string &);
		void		        setHeader(void);
		void		        setStatus(const status_type &);
		void		        setStatus(int);
		void                setErrorContent(void);
		
		/* various http methods (eg: GET, POST or DELETE) */
		void				methodGet(const std::string &);
		void				methodPost(void);
		void				methodDelete(void);
		bool                isMethodAllowed(const std::string &);
		void				cgi(void);
		
		bool				uploadFile(void);

		void				printStatus(void) const;

	private:
		std::string			_header;
		std::string			_content;
		status_type			_status;
		Request*			_request;
		Cgi*				_cgi;
		const t_location*	_location;
		bool				_cgiStatus;
	
}; /* class Response */

_END_NS_WEBSERV

#endif
