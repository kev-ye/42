/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 00:36:05 by adbenoit          #+#    #+#             */
/*   Updated: 2021/11/14 15:29:21 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HPP
# define CGI_HPP

# include "Request.hpp"

_BEGIN_NS_WEBSERV

class Request;

class Cgi
{
	public:
		Cgi(Request *);
		~Cgi();
	
	private:
		Cgi(void);
		Cgi(const Cgi &);
		Cgi& 				operator=(const Cgi &);
	
	public:
		const std::string&	getExtension(void) const;
		const std::string&	getProgram(void) const;
		char**				getEnv(void) const;
		const std::string	getEnv(const std::string &);
		const std::string&	getHeader(void) const;
		const int&			getStatus(void) const;
		const int&			getCgiStep(void) const;
		const std::string&	getOutputContent(void) const;
	
		void				execute(void);
		void				clear(void);
		
		bool				parseCgiContent(void);

	private:
		bool				getOuput(int);
		void				handleProcess(int, time_t);
		void				setEnv(void);
		void				setCgiStep(const int step);
		void				setHeader(const std::string &);

	public:
		class CgiError : public std::exception
		{
			public:
				virtual const char*	what() const throw();
		};
	
	private:
		char 				**_env;
		std::string			_program;
		std::string			_extension;
		Request*			_request;
		std::string			_header;
		int					_status;
		int					_cgiStep;
		int					_cgiFd;
		std::string			_outputContent;
	
}; /* class Cgi */

_END_NS_WEBSERV

#endif /* !defined(CGI_HPP) */
