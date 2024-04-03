/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 15:46:09 by adbenoit          #+#    #+#             */
/*   Updated: 2021/11/16 18:25:05 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

_BEGIN_NS_WEBSERV

const char*	Cgi::CgiError::what() const throw()
{ return "cgi failed"; }

Cgi::Cgi(Request *request) :
	_env(NULL),
	_program(""),
	_extension(""),
	_request(request),
	_header(""),
	_status(200),
	_cgiStep(CGI_INIT_STATUS),
	_outputContent("")
{
	const t_location	*loc = request->getLocation();

	if (loc && !loc->cgi.first.empty())
	{
		_extension = loc->cgi.first;
		_program = loc->cgi.second;
		this->setEnv();
	}
}

Cgi::~Cgi()
{
	this->clear();
}

/*
** Getters
*/

const std::string&	Cgi::getExtension(void)		const { return this->_extension; }
const std::string&	Cgi::getProgram(void)		const { return this->_program; }
char**				Cgi::getEnv(void)			const { return this->_env; }
const int&			Cgi::getStatus(void)		const { return this->_status; }
const int&			Cgi::getCgiStep(void)		const { return this->_cgiStep; }
const std::string&	Cgi::getOutputContent(void) const { return this->_outputContent; };
const std::string&	Cgi::getHeader(void)		const { return this->_header; }

/* Returns the value of a cgi environment variables */
const std::string	Cgi::getEnv(const std::string &varName)
{
	std::string	envVar[] = {
		"CONTENT_LENGTH",
		"CONTENT_TYPE",
		"GATEWAY_INTERFACE",
		"PATH_INFO",
		"PATH_TRANSLATED",
		"QUERY_STRING",
		"REDIRECT_STATUS",
		"REQUEST_METHOD",
		"SCRIPT_FILENAME",
		"SERVER_PROTOCOL",
		"SERVER_PORT",
		""
	};
	std::string	str;
	int			i = 0;
	
	for ( ; !envVar[i].empty(); ++i)
	{
		if (varName == envVar[i])
			break ;
	}
	switch (i)
	{
	case 0:
		if (_request->getHeader().request_method == "GET")
			return std::to_string(_request->getHeader().queryString.size());
		else
			return std::to_string(_request->getContent().size());
	case 1: return vectorJoin(_request->getHeader().data["Content-Type"], '\0');
	case 2: return "CGI/1.1";
	case 3: return _request->getConstructPath().substr(sizeof(ROOT_PATH) - 1);
	case 4: return _request->getConstructPath().substr(sizeof(ROOT_PATH) - 1);
	case 5: return _request->getHeader().queryString;
	case 6: return "200";
	case 7: return _request->getHeader().request_method;
	case 8: return _request->getConstructPath();
	case 9: return HTTP_PROTOCOL_VERSION;
	case 10: return std::to_string(_request->getServer()->port());
	default: return std::string("");
	}
}

/*
** Modifiers
*/

void	Cgi::setHeader(const std::string& header)
{
	std::vector<std::string>	lines = split_string(header, NEW_LINE);
	
	for (size_t i = 0 ; i < lines.size(); ++i)
	{
		if (ft_strcut(lines[i], ':') != "Status")
		{
			this->_header += lines[i] + NEW_LINE;
		}
		else
		{
			/* Modify the status according to the header */
			std::string status = lines[i].substr(8);
			std::stringstream(status) >> this->_status;
		}
	}
}

void	Cgi::setCgiStep(const int step)
{
	this->_cgiStep = step;
}

/* Free _env */
void    Cgi::clear()
{
	if (this->_env != NULL)
	{
		for (int i = 0; this->_env[i]; ++i)
			free(this->_env[i]);
		free(this->_env);
		this->_env = NULL;
	}
}

/* Set the CGI environment variables.
CGI Environment variables contain data about the transaction
between the client and the server. */
void	Cgi::setEnv()
{
	std::string	envVar[] = {
		"CONTENT_LENGTH",
		"CONTENT_TYPE",
		"GATEWAY_INTERFACE",
		"PATH_INFO",
		"PATH_TRANSLATED",
		"QUERY_STRING",
		"REDIRECT_STATUS",
		"REQUEST_METHOD",
		"SCRIPT_FILENAME",
		"SERVER_PROTOCOL",
		"SERVER_PORT",
		""
	};
	size_t		size = 0;
	size_t		i = 0;
	
	while (!envVar[size].empty())
		++size;
	this->_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!this->_env)
		throw std::bad_alloc();
	for ( ; i < size; ++i)
	{
		std::string str = envVar[i] + "=" + this->getEnv(envVar[i]);
		this->_env[i] = strdup(str.c_str());
		if (!this->_env[i])
			throw std::bad_alloc();
	}  
	this->_env[i] = NULL;
}

/* Read the standard output of the program */
bool	Cgi::getOuput(int fd)
{
	char		buffer[BUFFER_SIZE] = {0};
	int			ret;

	while (true)
	{
		ret = read(fd, buffer, sizeof(buffer) - 1);
		if (ret < 0)
			break ;
		buffer[ret] = 0;
		_outputContent += buffer;
		if (ret == 0)
			break ;
	}
	if (ret < 0)
		return false;
	return true;
}

/* Executes the CGI program on a file.
Returns the output in a string */
void	Cgi::execute(void)
{
	pid_t		pid;
	int			fdIn[2];
	int			fdOut[2];
	std::string	content;
	std::string	method = this->getEnv("REQUEST_METHOD");

#if DEBUG >= DEBUG_LVL_2
	std::cout << "Executing cgi ..." << std::endl;
#endif

	if (pipe(fdIn) == SYSCALL_ERR || pipe(fdOut) == SYSCALL_ERR)
		throw CgiError();

	// Send variables to the standard input of the program
	if (write(fdIn[FD_OUT], this->_request->getContent().c_str(), this->_request->getContent().size()) < 0)
		throw CgiError();

	this->setCgiStep(CGI_EXECUTE_STATUS);

	// time_t beginTime = time(NULL);
	if ((pid = fork()) == SYSCALL_ERR)
		throw CgiError();
	else if (pid == 0)
	{
		// Modify standard input and output
		close(fdIn[FD_OUT]);
		if (dup2(fdIn[FD_IN], STDIN_FILENO) == SYSCALL_ERR)
			exit(EXIT_FAILURE);
		close(fdIn[FD_IN]); 

		close(fdOut[FD_IN]);
		if (dup2(fdOut[FD_OUT], STDOUT_FILENO) == SYSCALL_ERR)
			exit(EXIT_FAILURE);
		close(fdOut[FD_OUT]);
		
		// Execute the cgi program on the file
		execve(this->_program.c_str(), NULL, this->_env);
		exit(EXIT_FAILURE);
	}
	
	close(fdOut[FD_OUT]);
	close(fdIn[FD_IN]);
	close(fdIn[FD_OUT]);
	
	_cgiFd = fdOut[FD_IN];

	if (fcntl(_cgiFd, F_SETFL, O_NONBLOCK))
		warnMsg("set get output non blocking failed");
}

bool	Cgi::parseCgiContent(void) {
	this->setCgiStep(CGI_READ_STATUS);

	if (true == this->getOuput(_cgiFd)) {
		this->setCgiStep(CGI_DONE_STATUS);
		
		int status;
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
		{
			this->_status = 502;
			throw CgiError();
		}
		
		close(_cgiFd);

		this->setHeader(_outputContent.substr(0, _outputContent.find(DELIMITER)));

		/* remove cgi header from content */
		size_t pos = _outputContent.find(DELIMITER);
		if (std::string::npos != pos)
			_outputContent = _outputContent.substr(pos + 4);

#if DEBUG >= DEBUG_LVL_3
		std::cout << "............ CGI HEADER ............." << std::endl;
		std::cout << this->_header << std::endl;
		std::cout << "............ CGI ENVIRON ............." << std::endl;
		for (size_t i = 0; this->_env && this->_env[i]; ++i)
			std::cout << this->_env[i] << std::endl;
		std::cout << "......................................" << std::endl;
#endif

		return true;
	}
	return false;
}

_END_NS_WEBSERV
