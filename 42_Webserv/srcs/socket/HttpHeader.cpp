/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpHeader.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 16:09:26 by besellem          #+#    #+#             */
/*   Updated: 2021/11/14 18:16:19 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpHeader.hpp"

_BEGIN_NS_WEBSERV

HttpHeader::HttpHeader(void) :
	data(),
	request_method(),
	uri("/"),
	queryString(""),
	content(),
	chunked(false)
{}

HttpHeader::HttpHeader(const HttpHeader &x)
{ *this = x; }

HttpHeader::~HttpHeader()
{}

HttpHeader&		HttpHeader::operator=(const HttpHeader &x)
{
	if (this == &x)
		return *this;
	data = x.data;
	request_method = x.request_method;
	uri = x.uri;
	queryString = x.queryString;
	content = x.content;
	chunked = x.chunked;
	return *this;
}

const char*		HttpHeader::HttpHeaderParsingError::what() const throw()
{ return "incomplete http header received"; }

const char*		HttpHeader::HttpBadRequestError::what() const throw()
{ return "bad http request"; }

_END_NS_WEBSERV
