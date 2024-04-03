/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Warlock.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 14:27:52 by kaye              #+#    #+#             */
/*   Updated: 2021/09/10 18:03:37 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WARLOCK_HPP
# define WARLOCK_HPP

#include <iostream>

class Warlock {
	public:
		Warlock(std::string const &, std::string const &);
		virtual ~Warlock(void);

	private:
		Warlock(void);
		Warlock(Warlock const &);
		Warlock & operator=(Warlock const &);

	public:
		void				setTitle(std::string const &);
		std::string const &	getName(void) const;
		std::string const &	getTitle(void) const;
		void				introduce(void) const;

	private:
		std::string _name;
		std::string _title;
};

#endif