/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FragTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 12:30:15 by kaye              #+#    #+#             */
/*   Updated: 2021/08/09 18:37:17 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRAGTRAP_HPP
# define FRAGTRAP_HPP

#include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap {
	public:
		FragTrap(void);
		FragTrap(std::string const & name);
		FragTrap(FragTrap const & src);
		virtual ~FragTrap(void);
	
		FragTrap & operator=(FragTrap const & rhs);

	public:
		void	highFivesGuys(void);

		void	setHP(void);
		void	setEP(void);
		void	setAD(void);
		
};


#endif