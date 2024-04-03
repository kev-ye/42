/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 13:02:47 by kaye              #+#    #+#             */
/*   Updated: 2021/08/10 16:29:24 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_HPP
# define BRAIN_HPP

#include <iostream>
#include <cstdlib>

#define NBR_IDEAS 100

class Brain {
	public:
		Brain(void);
		Brain(Brain const & src);
		virtual ~Brain(void);

		Brain & operator=(Brain const & rhs);
	
	public:
		std::string const &	getIdea(int idx) const;
		void				setIdea(int idx, std::string to_set);

	private:
		std::string _ideas[NBR_IDEAS];
};

#endif