/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Weapon.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 18:24:43 by kaye              #+#    #+#             */
/*   Updated: 2021/07/30 13:46:53 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>

class Weapon {
	public:
		Weapon(std::string weapon_type);
		~Weapon(void);

	public:
		std::string const	&getType(void) const;
		void				setType(std::string to_set);

	private:
		std::string _weapon_type;
};

#endif
