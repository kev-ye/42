/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 23:01:12 by adbenoit          #+#    #+#             */
/*   Updated: 2021/11/18 09:29:24 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

_BEGIN_NS_WEBSERV

Response::Response(Request *req)
{
	_request = req;
	_location = req->getLocation();

	if (_location && !_location->cgi.first.empty()) {
		_cgi = new Cgi(req);
	}
	else
		_cgi = NULL;
	setStatus(_request->getStatus());
	if (!is_valid_path(_request->getConstructPath()))
		setStatus(404);
}

Response::~Response()
{
	if (_cgi != NULL)
	{
		delete _cgi;
		_cgi = NULL;
	}
}

/*
** Getters
*/

const std::string&				Response::getHeader(void)        const { return this->_header; }
const std::string&				Response::getContent(void)       const { return this->_content; }
size_t							Response::getContentLength(void) const { return this->_content.size(); }
const Response::status_type&	Response::getStatus(void)        const { return this->_status; }
bool							Response::getCgiStatus(void)     const { return this->_cgiStatus; }
int								Response::getCgiStep(void)       const { return this->_cgi->getCgiStep(); }

/*
** Setters
*/

void    Response::setStatus(const status_type &status)
{
	this->_status = status;
}

void    Response::setStatus(int code)
{
	static int			codeTab[] = {
		200,
		202,
		204,
		300,
		301,
		302,
		303,
		304,
		308,
		400,
		403,
		404,
		405,
		408,
		413,
		500,
		502
	};

	static std::string	actionTab[] = {
		"OK",
		"Accepted",
		"No Content",
		"Multiple Choice",
		"Moved Permanently",
		"Found",
		"See Other",
		"Not Modified",
		"Temporary Redirect",
		"Bad Request",
		"Forbidden",
		"Not Found",
		"Method Not Allowed",
		"Request Timeout",
		"Request Entity Too Large",
		"Internal Server Error",
		"Bad Gateway",
		""
	};
	size_t				i = 0;

	if (this->_location && !this->_location->redirection.second.empty())
	{
		if (is_valid_path(ROOT_PATH + this->_location->redirection.second))
			code = this->_location->redirection.first;
		else
			code = 404;
	}
	while (!actionTab[i].empty() && codeTab[i] != code)
		++i;
	this->_status = std::make_pair(codeTab[i], actionTab[i]);
}

void    Response::setHeader(void)
{
    this->_header =  HTTP_PROTOCOL_VERSION " ";
	this->_header += std::to_string(this->_status.first) + " ";
	this->_header += this->_status.second + NEW_LINE;
	this->_header += "Content-Length: " + std::to_string(this->_content.size()) + NEW_LINE;
	if (this->_cgi && !this->_cgi->getHeader().empty())
		this->_header += this->_cgi->getHeader();
	else if (this->_status.first >= 300 && this->_status.first <= 400)
	{
		this->_header += "Location: ";
		this->_header += this->_location->redirection.second + NEW_LINE;
	}
}

void    Response::setContent(const std::string &file_content)
{
	if (this->_status.first < 400)
		this->isMethodAllowed(this->_request->getHeader().request_method);

	_cgiStatus = true;
	
	if (this->_cgi != NULL && getExtension(this->_request->getConstructPath()) == this->_cgi->getExtension())
		this->cgi();												 // run CGI
	else if (this->_request->getHeader().request_method == "GET")	 // run GET method
		this->methodGet(file_content);
	else if (this->_request->getHeader().request_method == "POST")	 // run POST method
		this->methodPost();
	else if (this->_request->getHeader().request_method == "DELETE") // run DELETE method
		this->methodDelete();

	/* Error case */
	if (this->_status.first >= 400)
		this->setErrorContent();
}

void	Response::setErrorContent(void)
{
	std::map<int, std::string>::const_iterator	it;
	it = this->_request->getServer()->errorPages().find(this->_status.first);
	/* Default error page setup case */
	if (it != this->_request->getServer()->errorPages().end() &&
		is_valid_path(it->second))
	{
		this->_content = getFileContent(it->second);
		return ;
	}
	
	/* Default case */
	std::string content = "<!DOCTYPE html>" NEW_LINE;
	content += "<html lang=\"en\">" NEW_LINE;
	content += "<head>" NEW_LINE;
	content += "<meta charset=\"utf-8\" /><meta http-equiv=\"X-UA-Compatible\" ";
	content += "content=\"IE=edge\" /><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" />" NEW_LINE;
	content += "<title>";
	content += this->_status.second;
	content += " | ";
	content += std::to_string(this->_status.first);
	content += "</title>" NEW_LINE;
	content += "<style type=\"text/css\">";
    content += "body{margin:0}sub{bottom:-.25em}sup{top:-.5em}body,";
	content += "html{width:100%;height:100%;background-color:#21232a}";
	content += "body{color:#fff;text-align:center;text-shadow:0 2px 4px rgba(0,0,0,.5);padding:0;min-height:100%;";
	content += "-webkit-box-shadowinset 0 0 100px rgba(0,0,0,.8);box-shadow:inset 0 0 100px rgba(0,0,0,.8);display:";
	content += "table;font-family:\"Open Sans\",Arial,sans-serif}";
	content += "h1{font-family:inherit;font-weight:500;line-height:1.1;color:inherit;font-size:36px}";
	content += "h1 small{font-size:68%;font-weight:400;line-height:1;color:#777}";
	content += "a{text-decoration:none;color:#fff;font-size:inherit;border-bottom:dotted 1px #707070}";
	content += ".lead{color:silver;font-size:21px;line-height:1.4}";
	content += ".cover{display:table-cell;vertical-align:middle;padding:0 20px}";
	content += "</style>" NEW_LINE;
	content += "</head>" NEW_LINE;
	content += "<body>" NEW_LINE;
	content += "<body>" NEW_LINE;
	content += "<div class=\"cover\"><h1>";
	content += this->_status.second;
	content += " <small>";
	content += std::to_string(this->_status.first);
	content += "</small></h1></div>" NEW_LINE;
	content += "</body>" NEW_LINE;
	
	this->_content = content;
}

/*
** Process the request
*/

bool	Response::isMethodAllowed(const std::string &method)
{
	/* GET is always allowed */
	if (method == "GET")
		return true;

	if (this->_location)
	{
		for (size_t i = 0; i < this->_location->methods.size(); ++i)
		{
			if (method == this->_location->methods[i])
				return true;
		}
	}
	this->setStatus(405);
	return false;
}

void	Response::methodGet(const std::string &file_content)
{
	 if (this->_status.first != 200)
	 	return ;
		 
	/* autoindex case */
	if (ft_isDirectory(this->_request->getConstructPath()))
	{
		if (this->_location && this->_location->autoindex == AUTOINDEX_ON)
			this->_content = generateAutoindexPage(this->_request->getConstructPath());
		else
			this->setStatus(403);
	}
	else
		this->_content = file_content;
}

void	Response::methodPost(void)
{
	if (this->_status.first != 200)
		return ;
	
	bool isUpload = false;
	/* upload case */
	if (this->_location && !this->_location->uploadStore.empty())
	{
		isUpload = uploadFile();
		if (this->_status.first != 200)
			return ;
	}
	
	if (isUpload == true)
	{
		this->_content = "<html>" NEW_LINE;
		this->_content += "<body>" NEW_LINE;
		this->_content += "<h1>File uploaded.</h1>" NEW_LINE;
		this->_content += "</body>" NEW_LINE;
		this->_content += "</html>" NEW_LINE;
	}
	else if ((size_t)this->_request->getServer()->clientMaxBodySize() != 0 &&
		this->_request->getContent().size() > (size_t)this->_request->getServer()->clientMaxBodySize())
		this->setStatus(413);
	else
		this->_content = this->_request->getContent();
}

void	Response::methodDelete(void)
{
	if (this->_status.first != 200)
		return ;
	
	if (std::remove(this->_request->getConstructPath().c_str()) != 0)
		this->setStatus(403);
	
	this->_content = "<html>" NEW_LINE;
	this->_content += "<body>" NEW_LINE;
	this->_content += "<h1>File deleted.</h1>" NEW_LINE;
	this->_content += "</body>" NEW_LINE;
	this->_content += "</html>" NEW_LINE;
}

void	Response::cgi(void) {
	
	if (this->_status.first != 200)
		return ;

	/* CGI case */
	try
	{
		if (this->getCgiStep() == CGI_INIT_STATUS)
			this->_cgi->execute();
	}
	catch (const std::exception& e)
	{
		if (this->_cgi->getStatus() == 200)
			this->setStatus(500);
		else
			this->setStatus(this->_cgi->getStatus());
		EXCEPT_WARNING(e);
		return ;
	}

	if (this->_cgi->parseCgiContent() == false) {
		this->_cgiStatus = false;
		return ;
	}
	this->_cgiStatus = true;
	this->_content = this->_cgi->getOutputContent();
	this->setStatus(this->_cgi->getStatus());
}

const std::string	Response::generateAutoindexPage(std::string const &path) const
{
	DIR				*dir = opendir(path.c_str());
	struct dirent	*dirInfo;
	struct stat		statBuf;
	std::string		addPrefix, fileName, lastModTime, fileSize, content;
	
	/* begin html */
	content = "<html>\n";
	content += "<head><title>autoindex</title></head>\n";
	content += "<body>\n";
	content += "<h1>Index of ";
	content += path.substr(5);
	content += "</h1><hr/>\n";

	/* create table */
	content += "<table width=\"100%\" border=\"0\">\n";
	content += "<tr>\n";
	content += "<th align=\"left\">Name</th>\n";
	content += "<th align=\"left\">Last modified</th>\n";
	content += "<th align=\"left\">size</th>\n";
	content += "</tr>\n";

	if (dir == NULL) {
		warnMsg("opendir failed");
		return std::string("");
	}

	/* create table content */
	while ((dirInfo = readdir(dir)) != NULL) {
		fileName = dirInfo->d_name;
		if (fileName == ".") {
			fileName.clear();
			continue;
		}

		/* get absolut path */
		addPrefix = path;
		addPrefix += "/";
		if (fileName != "..")
			addPrefix += fileName;
		else
			addPrefix = fileName;

		/* get file status */
		stat(addPrefix.c_str(), &statBuf);

		/* get file modify time */
		lastModTime = ctime(&statBuf.st_mtime);
		lastModTime.erase(lastModTime.end() - 1);

		/* get file size */
		fileSize = std::to_string(statBuf.st_size);

		/* begin of content */
		content += "<tr>\n";

		/* element 1: path access */
		content += "<td><a href=\"";
		content += fileName;
		if (S_ISDIR(statBuf.st_mode))
			content += "/";
		content += "\">";
		content += fileName;
		if (S_ISDIR(statBuf.st_mode))
			content += "/";		
		content += "</a></td>\n";

		/* element 2: modify time */
		content += "<td>";
		content += lastModTime;
		content += "</td>";

		/* element 3: file size */
		content += "<td>";
		if (S_ISDIR(statBuf.st_mode))
			content += "_";
		else
			content += fileSize;
		content += "</td>";

		/* end of content */
		content += "</tr>\n";

		addPrefix.clear();
		fileName.clear();
		lastModTime.clear();
		fileSize.clear();
	}

	closedir(dir);

	/* end of html */
	content += "</table>\n";
	content += "</body>\n";
	content += "</html>\n";

	return content;
}

bool	Response::uploadFile(void)
{
	if (false == _request->parseFile())
		return false;
	
	const std::string	absolutePath = ROOT_PATH + _location->uploadStore;
	info_type			fileInfo = _request->getFileInfo();
	info_type::iterator	it = fileInfo.begin();

	for ( ; it != fileInfo.end(); ++it)
	{
		std::string	toUploadPath = absolutePath + it->first;
		if (_request->getServer()->clientMaxBodySize() &&
			getFileLength(toUploadPath) > _request->getServer()->clientMaxBodySize())
		{
			setStatus(413);
			return false;
		}
		std::ofstream	ofs(toUploadPath, std::ofstream::out);
		if (!ofs.is_open())
		{
			setStatus(403);
			return false;
		}
		ofs << it->second;
		ofs.close();
	}
	return true;
}

void	Response::printStatus(void) const
{
	std::string color;

	_request->print();
	if (this->_status.first < 300)
		color = "\e[30;42m"; // background green
	else if (this->_status.first < 400)
		color = "\e[30;44m"; // background blue
	else
		color = "\e[30;41m"; // background red
	std::cout	<< "[HTTP/1.1 "
				<< color << this->_status.first
				<< S_NONE << " " << this->_status.second << "]" << std::endl;
}

_END_NS_WEBSERV
