/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   epoll.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 18:35:48 by kaye              #+#    #+#             */
/*   Updated: 2021/11/16 16:36:48 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "epoll.hpp"

_BEGIN_NS_WEBSERV

#define WRITING true

/** @brief public function */

Epoll::Epoll(void) {}
Epoll::~Epoll(void) {}

Epoll::Epoll(Socket *multiSock, int const & serverSize) :
	_serverSocks(multiSock),
	_serverSize(serverSize),
	_epollFd(-1)
{}

void	Epoll::startEpoll(void) {
	_epollFd = kqueue();
	if (_epollFd < 0)
		errorExit("kqueue()");
	
	for (int i = 0; i < _serverSize; ++i) {
		int sockFd = _serverSocks[i].getServerFd();
		_updateEvt(sockFd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL, "init");
	}
	_serverLoop();
}

/** @brief private function */

void	Epoll::_serverLoop(void) {
	struct timespec	tmout = {5, 0};

	while (true) {
		// get ready event
		int readyEvts = kevent(_epollFd, NULL, 0, _evlist, _nEvents, &tmout);
		if (readyEvts <= 0) {
			if (readyEvts == 0)
				warnMsg("timeout: no active event for 5s");
			else if (readyEvts < 0)
				warnMsg("kevent failed");
			continue ;
		}

#if DEBUG >= DEBUG_LVL_3
		if (readyEvts > 0)
			std::cout << "---\nStart: Num of request: [" S_GREEN << readyEvts << S_NONE "]\n---\n\n";
#endif

		// handle ready event
		for (int i = 0; i < readyEvts; ++i) {
			struct kevent	currEvt = _evlist[i];

			if (true == _clientConnect(currEvt.ident, _connMap))
				continue ;
			else {
				if (false == _checkClient(currEvt.ident)) {
					warnMsg("could not find client fd");

					_updateEvt(currEvt.ident, EVFILT_READ, EV_DELETE, 0, 0, NULL, "deleting read");
					_updateEvt(currEvt.ident, EVFILT_WRITE, EV_DELETE, 0, 0, NULL, "deleting write");

					close(currEvt.ident);
					continue ;
				}

				if (currEvt.flags & EV_EOF) {
					updateMsg("Client quit (EOF case)");
					_clientDisconnect(currEvt.ident, _connMap);
					continue ;
				}

				Socket	*tmp = _checkServ(currEvt.ident, _connMap);
				if (NULL == tmp) {
					warnMsg("socket connexion not found");
					close(currEvt.ident);
					continue ;
				}

				_handleRequest(currEvt, *tmp);
			}
		}
	}
}

void	Epoll::_updateEvt(int ident, short filter, u_short flags, u_int fflags, int data, void *udata, std::string msg) {
	struct kevent	chlist;
	int				ret;

	EV_SET(&chlist, ident, filter, flags, fflags, data, udata);
	ret = kevent(_epollFd, &chlist, 1, NULL, 0, NULL);
	if (ret < 0)
		warnMsg("kevent failed: " + msg);
}

Socket	*Epoll::_checkServ(int const & currConn, std::map<const int, Socket> & _connMap) const {
	if (_connMap.empty() == true)
		return NULL;

	for (std::map<const int, Socket>::iterator it = _connMap.begin(); it != _connMap.end(); it++) {
		if (currConn == it->first)
			return &it->second;
	}
	return NULL;
}

bool	Epoll::_checkClient(int const & clientFd) const {
	conn_type::const_iterator	it = _connMap.find(clientFd);

	return (it != _connMap.end());
}

bool	Epoll::_clientConnect(int const & toConnect, std::map<const int, Socket> & _connMap) {
	sockaddr_in	clientAddr;
	socklen_t	clientAddrLen = sizeof(clientAddr);
	int			newSock;
	bool		isClient = false;
	int			i = 0;

	for ( ; i < _serverSize; ++i) {
		if (toConnect == _serverSocks[i].getServerFd()) {
			isClient = true;
			break ;
		}
	}

	if (false == isClient)
		return false;

	newSock = accept(toConnect, (sockaddr *)&clientAddr, &clientAddrLen);
	if (SYSCALL_ERR == newSock)
		return false;
	
	if (SYSCALL_ERR == fcntl(newSock, F_SETFL, O_NONBLOCK))
		warnMsg("non-blocking failed at client connect!");

	_connMap[newSock] = _serverSocks[i];
	_updateEvt(newSock, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL, "adding read");
	_updateEvt(newSock, EVFILT_WRITE, EV_ADD | EV_DISABLE, 0, 0, NULL, "adding write");

#if DEBUG >= DEBUG_LVL_3
	std::cout << "Client Connected form: [" S_GREEN << inet_ntoa(clientAddr.sin_addr)
			  << S_NONE "]:[" S_GREEN << ntohs(clientAddr.sin_port)
			  << S_NONE "] with socket: [" << toConnect << "]\n\n";
#endif

	return true;
}

void	Epoll::_clientDisconnect(int const & toClose, std::map<const int, Socket> & _connMap) {
#if DEBUG >= DEBUG_LVL_3
	std::cout << "closing: [" S_RED << toClose << S_NONE "] ..."<< "\n\n";
#endif

	_updateEvt(toClose, EVFILT_READ, EV_DELETE, 0, 0, NULL, "deleting read");
	_updateEvt(toClose, EVFILT_WRITE, EV_DELETE, 0, 0, NULL, "deleting write");
	_connMap.erase(toClose);
	close(toClose);
}

void	Epoll::_handleRequest(struct kevent const & currEvt, Socket & sock) {
	if (currEvt.filter == EVFILT_READ) {
		updateMsg("receiving request (READ)");

		Request	*request = new Request();
		int		readStatus;

		readStatus = sock.readHttpRequest(request, currEvt);
		if (readStatus != READ_OK)
			_clientDisconnect(currEvt.ident, _connMap);

		_reqMap[currEvt.ident] = request;
		_updateEvt(currEvt.ident, EVFILT_READ, EV_DISABLE, 0, 0, NULL, "disabling read");
		_updateEvt(currEvt.ident, EVFILT_WRITE, EV_ENABLE, 0, 0, NULL, "enabling write");
	}
	else if (currEvt.filter == EVFILT_WRITE) {
		updateMsg("sending reponse (WRITE)");
		int sendStatus = SEND_OK;

		req_type::iterator it = _reqMap.find(currEvt.ident);
		if (it != _reqMap.end())
			sendStatus = sock.sendHttpResponse(it->second, currEvt.ident);

		if (it == _reqMap.end() || sendStatus == SEND_OK) {
			delete it->second;
			_reqMap.erase(currEvt.ident);
			_updateEvt(currEvt.ident, EVFILT_READ, EV_ENABLE, 0, 0, NULL, "enabling read");
			_updateEvt(currEvt.ident, EVFILT_WRITE, EV_DISABLE, 0, 0, NULL, "disabling write");
			// _clientDisconnect(currEvt.ident, _connMap);
		}
	}
}

_END_NS_WEBSERV
