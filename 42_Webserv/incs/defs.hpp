/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adbenoit <adbenoit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:18:09 by besellem          #+#    #+#             */
/*   Updated: 2021/11/18 09:33:40 by adbenoit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_HPP
# define DEFS_HPP

/* Debug levels */
# define DEBUG_LVL_0  0 // Only errors - debug disabled
# define DEBUG_LVL_1  1 // Errors and warnings
# define DEBUG_LVL_2  2 // Errors, warnings and infos
# define DEBUG_LVL_3  3 // Errors, warnings, infos and debug

/* Set the debug level */
# define DEBUG        DEBUG_LVL_0



/* ANSI color codes */
# define S_NONE    "\e[0m"
# define S_RED     "\e[1;31m"
# define S_GREEN   "\e[1;32m"
# define S_YELLOW  "\e[1;33m"
# define S_BLUE    "\e[1;34m"
# define S_PURPLE  "\e[1;35m"
# define S_CYAN    "\e[1;36m"


/* Namespace definition */
# define INLINE_NAMESPACE       webserv
# define _BEGIN_NS_WEBSERV      namespace INLINE_NAMESPACE {
# define _END_NS_WEBSERV        }


/* Default paths */
# define ROOT_PATH              "./www"
# define CONFIG_DEFAULT_PATH    "./config_files"
# define CONFIG_FILETYPE        ".conf"
# define DEFAULT_CONFIG_FILE    CONFIG_DEFAULT_PATH "/default" CONFIG_FILETYPE

# define HTTP_PROTOCOL_VERSION  "HTTP/1.1"

/* HTTP header delimiters */
# define NEW_LINE               "\r\n"
# define DELIMITER              "\r\n\r\n"


/* Warnings are not printed if the debug mode is not activated */
# if DEBUG > 0
#  define EXCEPT_WARNING(exception) std::cerr << S_BLUE "Warning: " S_NONE << exception.what() << std::endl
# else
#  define EXCEPT_WARNING(exception)
# endif

/* Errors are always printed */
# define EXCEPT_ERROR(exception)    std::cerr << S_RED  "Error: "   S_NONE << exception.what() << std::endl


/* Most syscalls return -1 */
# define SYSCALL_ERR    (-1)

/* Listen backlog */
#ifndef SOMAXCONN
# define SOMAXCONN      128
#endif

/* Used in the parsing */
# define AUTOINDEX_OFF  false
# define AUTOINDEX_ON   true

/* Used in pipe() */
# define FD_IN          0
# define FD_OUT         1

# define BUFFER_SIZE    4096


/*
** -- Enums --
*/
/* read/recv status */
enum	e_read
{
	READ_OK,
	READ_FAIL,
	READ_DISCONNECT
};

/* resolve status */
enum	e_resolve
{
	RESOLVE_OK,
	RESOLVE_FAIL,
	RESOLVE_EMPTY
};

/* send status */
enum	e_send
{
	SEND_OK,
	SEND_CGI_FAIL,
	SEND_FAIL,
	WAIT_SEND,
	CONTINU_SEND,
	NOFOUND_SEND
};

/* CGI status */
enum	e_cgi
{
	CGI_INIT_STATUS,
	CGI_EXECUTE_STATUS,
	CGI_READ_STATUS,
	CGI_DONE_STATUS
};


/*
** -- Includes --
*/
# include <arpa/inet.h>
# include <sys/select.h>
# include <sys/types.h>
# include <sys/event.h>
# include <sys/time.h>
# include <sys/socket.h>
# include <sys/types.h>
# include <sys/cdefs.h>
# include <netinet/in.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>
# include <signal.h>

# include <string>
# include <cstring>
# include <cstdio>
# include <cstdlib>
# include <cctype>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <sstream>
# include <exception>

# include <map>
# include <vector>
# include <list>
# include <algorithm>

# include "utils.hpp"

#endif /* !defined(DEFS_HPP) */
