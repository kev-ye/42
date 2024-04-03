/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 18:07:29 by kaye              #+#    #+#             */
/*   Updated: 2021/08/09 18:36:59 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_H
# define CLAPTRAP_H

#include <iostream>

class ClapTrap {
	public:
		ClapTrap(void);
		ClapTrap(std::string const & name);
		ClapTrap(ClapTrap const & src);
		virtual ~ClapTrap(void);

		ClapTrap & operator=(ClapTrap const & rhs);

	public:
		virtual void	attack(std::string const & target);
		void			takeDamage(unsigned int amount);
		void			beRepaired(unsigned int amount);

		std::string	getName(void) const;
		int			getAttackDamage(void) const;

	protected:
		std::string	_name;
		int			_hit_p;
		int			_energy_p;
		int			_attack_d;
};

#endif
