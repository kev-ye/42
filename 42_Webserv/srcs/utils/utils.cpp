/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:41:15 by besellem          #+#    #+#             */
/*   Updated: 2021/11/16 15:38:09 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

_BEGIN_NS_WEBSERV


void		printWebservHeader(void)
{
	std::cout << S_YELLOW;
	std::cout << " _       __     __                        "    << std::endl;
	std::cout << "| |     / /__  / /_  ________  ______   __"    << std::endl;
	std::cout << "| | /| / / _ \\/ __ \\/ ___/ _ \\/ ___/ | / /" << std::endl;
	std::cout << "| |/ |/ /  __/ /_/ (__  )  __/ /   | |/ /"     << std::endl;
	std::cout << "|__/|__/\\___/_.___/____/\\___/_/    |___/"    << std::endl;
	std::cout << S_NONE << std::endl;
	std::cout << S_CYAN "      adbenoit - kaye - besellem" S_NONE << std::endl;
	std::cout << "------------------------------------------\n" << std::endl;
}

/* Returns the extension of a file */
std::string	getExtension(const std::string& fileName)
{
	size_t pos = fileName.rfind(".");
	if (pos == std::string::npos)
		return std::string("");
	std::string	ext = fileName.substr(pos, fileName.size());
	return ext;
	
}

/* Split a string by a delimiter converting it into a vector */
std::vector<std::string>	split_string(const std::string& s, const std::string& delim)
{
	std::string					tmp(s);
	std::vector<std::string>	v;
	std::string					line;
	size_t						pos = tmp.find(delim);

	if (delim[0] != '\0' && !s.empty())
	{
		while ((pos = tmp.find(delim)) != std::string::npos)
		{
			line = tmp.substr(0, pos);
			if (!tmp.empty())
				v.push_back(line);
			tmp.erase(0, pos + delim.length());
		}
	}
	if (!tmp.empty())
		v.push_back(tmp);
	return v;
}

/* Returns 1 if the string is numeric.
Otherwise, returns 0. */
bool	ft_isNumeric(const std::string &str)
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (std::isdigit(str[i]) == 0)
			return false;
	}
	return true;
}

/* Returns 1 if the string is an ip address.
Otherwise, returns 0. */
bool	ft_isIpAddress(const std::string &str)
{
	size_t 		x;
	size_t 		n = 0;
	std::string	tmp = "";
	
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (!std::isdigit(str[i]) && str[i] != '.')
			return false;
		if (std::isdigit(str[i]))
			tmp += str[i];
		if (str[i] == '.' || i == (str.size() - 1))
		{
			++n;
			std::stringstream(tmp) >> x;
			if (x > 255 || n > 4)
				return false;
			tmp = "";
		}
	}
	if (n != 4)
		return false;
	return true;
}

/* Cuts str from delimiter.
Returns the new string. */
std::string    ft_strcut(const std::string& str, char delimiter)
{
	size_t	pos = str.find(delimiter);

	if (pos == std::string::npos)
		return str;
	return str.substr(0, pos);
}

/* Cuts vector from delimiter.
Returns the new vector. */
std::vector<std::string>	ft_vectorcut(const std::vector<std::string>& vect, char delimiter)
{
	std::vector<std::string>					newVect(vect);
	std::vector<std::string>::const_iterator	it;
	size_t										pos = 0;

	for(it = newVect.begin(); it != newVect.end(); ++it, ++pos)
	{
		if (*it != ft_strcut(*it, delimiter))
		{
			newVect[pos] = ft_strcut(*it, delimiter);
			if (!newVect[pos].empty())
				++it;
			break ;
		}
	}
	newVect.erase(it, newVect.end());
	return newVect;
}

/* Joins all the strings of vect separate by sep.
Returns the new string */

std::string	vectorJoin(const std::vector<std::string> &vect, char sep)
{
    if (vect.empty())
        return std::string("");

    std::string	str = vect[0];

    for (size_t i = 1; i < vect.size(); ++i)
    {
        str += sep;
        str += vect[i];
    }
    return str;
}


/* Most optimized way of checking if a file exist */
bool	is_valid_path(const std::string& path)
{
	struct stat	stat_buf;

	return (0 == stat(path.c_str(), &stat_buf));
}

/* Check if a path is a directory */
bool	ft_isDirectory(const std::string& path)
{
	struct stat	stat_buf;

	stat(path.c_str(), &stat_buf);
	return (S_ISDIR(stat_buf.st_mode) != 0);
}

/* Returns the content of a file */
std::string	getFileContent(const std::string& file)
{
	std::ifstream	ifs(file, std::ios::in);
	std::string		content;
	std::string		gline;

	if (ifs.is_open())
	{
		do
		{
			std::getline(ifs, gline);
			content += gline;
			if (ifs.eof())
				break ;
			content += "\n";
		} while (true);
	}
	ifs.close();
	return content;
}

/* Returns the size of a file */
off_t	getFileLength(const std::string &file)
{
	struct stat	buf;

	if (ft_isDirectory(file))
		return 0;
	if (SYSCALL_ERR != stat(file.c_str(), &buf))
		return buf.st_size;
	return SYSCALL_ERR;
}

void	handleSignals(int sig)
{
	std::cout << std::endl << S_RED "[Quit]" S_NONE << std::endl;
	if (SIGINT == sig)
		exit(EXIT_SUCCESS);
}

void	errorExit(const std::string &str)
{
	std::cerr << S_RED "Exit: " S_NONE << str << std::endl;
	exit(EXIT_FAILURE);
}

void	warnMsg(const std::string &str)
{
#if DEBUG >= DEBUG_LVL_1
	std::cerr << S_YELLOW "Warning: " S_NONE << str << std::endl;
#else
	(void)str;
#endif
}

void	updateMsg(const std::string &str)
{
#if DEBUG >= DEBUG_LVL_3
	std::cout << S_PURPLE "Updating: " S_NONE << str << std::endl;
#else
	(void)str;
#endif
}

_END_NS_WEBSERV
