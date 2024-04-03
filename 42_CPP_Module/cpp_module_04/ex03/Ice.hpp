/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 15:07:14 by kaye              #+#    #+#             */
/*   Updated: 2021/08/08 15:43:22 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
# define ICE_HPP

#include "AMateria.hpp"

class Ice : public AMateria {
	public:
		Ice(void);
		Ice(Ice const & src);
		virtual ~Ice(void);

		Ice &	operator=(Ice const & rhs);
	
	public:
		AMateria	*clone(void) const;
		void		use(ICharacter & target);
};

#endif