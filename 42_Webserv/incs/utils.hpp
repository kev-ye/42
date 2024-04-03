/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 17:49:10 by besellem          #+#    #+#             */
/*   Updated: 2021/11/12 14:03:33 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "defs.hpp"

_BEGIN_NS_WEBSERV

void						printWebservHeader(void);
std::vector<std::string>	split_string(const std::string &, const std::string &);
std::string	                getExtension(const std::string &);
std::string                 ft_strcut(const std::string &, char);
std::vector<std::string>	ft_vectorcut(const std::vector<std::string> &, char);
std::string                 vectorJoin(const std::vector<std::string> &, char);
bool						is_valid_path(const std::string &);
bool	                    ft_isDirectory(const std::string &);
std::string	                getFileContent(const std::string &);
off_t		                getFileLength(const std::string &);
bool						ft_isNumeric(const std::string &);
bool	                    ft_isIpAddress(const std::string &);
void						handleSignals(int);
void	                    errorExit(const std::string &);
void	                    warnMsg(const std::string &);
void	                    updateMsg(const std::string &);

_END_NS_WEBSERV

#endif /* !defined(UTILS_HPP) */
