/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:04:47 by kaye              #+#    #+#             */
/*   Updated: 2021/11/18 08:43:01 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"


_BEGIN_NS_WEBSERV

Socket::Socket(void) :
	_port(0),
	_serverFd(SYSCALL_ERR),
	_addrLen(sizeof(sockaddr_in))
{
	std::memset(&_addr, 0, sizeof(_addr));
}

Socket::Socket(const std::vector<Server *> serv) :
	_server_blocks(serv),
	_port(serv[0]->port()),
	_addrLen(sizeof(sockaddr_in)),
	_currResponse(NULL)
{
	_serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (SYSCALL_ERR == _serverFd)
		errorExit("socket()");
	_addr.sin_family = AF_INET;
	if ((_addr.sin_addr.s_addr = inet_addr(serv[0]->ip().c_str())) == (in_addr_t)SYSCALL_ERR)
		errorExit("inet_addr()");
	_addr.sin_port = htons(_port);
	std::memset(_addr.sin_zero, 0, sizeof(_addr.sin_zero));

	int	optval = 1;
	if (SYSCALL_ERR == setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int))) // can rebind
	{
		close(_serverFd);
		errorExit("setsockopt()");
	}
	setNonBlock(_serverFd);
}

Socket::Socket(const Socket &x)
{ *this = x; }

Socket::~Socket(void)
{}

Socket&		Socket::operator=(const Socket &x)
{
	if (this == &x)
		return *this;
	_server_blocks = x._server_blocks;
	_port = x._port;
	_serverFd = x._serverFd;
	_addrLen = x._addrLen;
	std::memcpy(&_addr, &x._addr, sizeof(sockaddr_in));
	return *this;
}

/** @brief public function */

short			Socket::getPort(void)     const { return _port; }
int				Socket::getServerFd(void) const { return _serverFd; }
sockaddr_in		Socket::getAddr(void)     const { return _addr; }
size_t			Socket::getAddrLen(void)  const { return _addrLen; }

const Server*	Socket::getServer(void)	const { return _server_blocks[0]; }

const Server*	Socket::selectServer(const std::string &name) const
{
	for (size_t i = 0; i < _server_blocks.size(); ++i)
	{
		for (size_t j = 0; j < _server_blocks[i]->name().size(); ++j)
		{
			if (_server_blocks[i]->name()[j] == name)
				return _server_blocks[i];
		}
	}
	return _server_blocks[0];
}

void	Socket::startSocket(void)
{
	bindStep(_serverFd, _addr);
	listenStep(_serverFd);
}

void	Socket::setNonBlock(int & fd)
{
	if (SYSCALL_ERR == fcntl(fd, F_SETFL, O_NONBLOCK))
		errorExit("fcntl()");
}

/* Returns the the content length of the request */
size_t	Socket::requestLen(std::string const & content)
{
	size_t pos = content.find("Content-Length: ");

	if (pos == std::string::npos)
		return std::string::npos;
	
	pos += std::string("Content-Length: ").length();

	std::string getLen;

	for (size_t i = pos; i < content.length() - pos; i++)
	{
		if (std::isdigit(content[i]))
			getLen += content[i];
		else
			break ;
	}

	std::stringstream sstream(getLen);
	size_t ret = 0;

	sstream >> ret;
	return ret;
}

int		Socket::readHttpRequest(Request *request, struct kevent currEvt)
{
	char	*buff = new char[currEvt.data + 1];
	int		ret;

	std::memset(buff, 0, currEvt.data + 1);
	ret = recv(currEvt.ident, buff, currEvt.data, 0);
	if (ret == 0)
	{
		updateMsg("closing the connection");
		return READ_DISCONNECT;
	}
	else if (SYSCALL_ERR == ret)
	{
		warnMsg("recv request failed!");
		return READ_FAIL;
	}
	request->getHeader().content.assign(buff, currEvt.data);
	delete [] buff;

	size_t reqLen = requestLen(request->getHeader().content);
	if (reqLen > static_cast<size_t>(currEvt.data) && reqLen != std::string::npos)
	{
		warnMsg("request length too large");
		request->setStatus(413);
	}

	if (RESOLVE_FAIL == resolveHttpRequest(request))
	{
		warnMsg("resolve request failed!");
		request->setStatus(400);
	}
	
	// request->print();

#if DEBUG >= DEBUG_LVL_3
	std::cout << "++++++++++++++ REQUEST +++++++++++++++\n" << std::endl;
	std::cout << request->getHeader().content << std::endl;
	std::cout << "\n+++++++++++ FINAL REQ ++++++++++++++++" << std::endl << std::endl;
#endif
	return READ_OK;
}
/*
** Parse the http request
**
** @return a `enum e_resolve' value
*/
int		Socket::resolveHttpRequest(Request *request)
{
	/* the buffer is empty, therefore the header was also empty */
	// if (request->getHeader().content.empty())
	// 	return RESOLVE_EMPTY;
	
	vector_type				buffer = split_string(request->getHeader().content, NEW_LINE);
	vector_type::iterator	line = buffer.begin();

	/*
	** Parse first line of request. Must be formatted like so:
	**   GET /index.html HTTP/1.1
	*/
	if (request->setRequestFirstLine(*line++) == false)
	{
		request->setServer(selectServer(""));
		return RESOLVE_FAIL;
	}

	/* set query string */
	size_t pos = request->getHeader().uri.find("?");
	if (pos != std::string::npos)
		request->getHeader().queryString = request->getHeader().uri.substr(pos + 1);

	/* map each line of the header */
	for ( ; line != buffer.end() && !(*line).empty(); ++line)
		request->setHeaderData(*line);

	std::string name = request->getHeader().data["Host"][0];
	request->setServer(selectServer(name));
	request->setConstructPath();

#if DEBUG >= DEBUG_LVL_1
	std::cout << "Request: [" S_CYAN << request->getConstructPath() << S_NONE "]\n";
#endif

	request->setChunked();
	request->setContent();

	return RESOLVE_OK;
}

/*
** Construct the htttp response and send it to the server
**
** @return a `enum e_send' value
*/
int		Socket::sendHttpResponse(Request* request, int socket_fd)
{
	std::string		toSend;
	bool			responseStatus = false;

	if (_respMap.empty())
		responseStatus = false;
	else
	{
		_currResponse = getCurrResponse(socket_fd);
		responseStatus = (_currResponse != NULL);
	}

	if (responseStatus == false)
	{
		Response	*response = new Response(request);

		_respMap[socket_fd] = response;
		_currResponse = response;
	}

	_currResponse->setContent(getFileContent(request->getConstructPath()));

	if (_currResponse->getCgiStatus() == false)
		return SEND_FAIL;
	
	/* actual construction of the header we're sending */
	_currResponse->setHeader();
	toSend =  _currResponse->getHeader();
	toSend += NEW_LINE;
	toSend += _currResponse->getContent();
	
	_currResponse->printStatus();

	/* send to client */
	if (SYSCALL_ERR == send(socket_fd, toSend.c_str(), toSend.length(), 0))
	{
		warnMsg("send response failed!");
		delete _currResponse;
		_respMap.erase(socket_fd);
		return SEND_OK;
	}
	delete _currResponse;
	_respMap.erase(socket_fd);

#if DEBUG >= DEBUG_LVL_3
	std::cout << "------------- RESPONSE ---------------" << std::endl;
	std::cout << toSend.c_str() << std::endl;
	std::cout << "--------------------------------------" << std::endl << std::endl;
#endif

	return SEND_OK;
}

Response	*Socket::getCurrResponse(int const currSockFd) const
{
	resp_type::const_iterator it = _respMap.find(currSockFd);
	if (it != _respMap.end())
		return it->second;
	return NULL;
}

/** @brief private function */

void	Socket::bindStep(const int& serverFd, const sockaddr_in& addr)
{
	if (SYSCALL_ERR == bind(serverFd, (struct sockaddr *)&addr, sizeof(addr)))
		errorExit("bind()");
}

void	Socket::listenStep(const int& serverFd)
{
	if (SYSCALL_ERR == listen(serverFd, SOMAXCONN))
		errorExit("listen()");
}

_END_NS_WEBSERV
