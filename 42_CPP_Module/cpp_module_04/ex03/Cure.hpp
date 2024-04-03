/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cure.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 15:26:24 by kaye              #+#    #+#             */
/*   Updated: 2021/08/08 18:57:29 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CURE_HPP
# define CURE_HPP

#include "AMateria.hpp"

class Cure : public AMateria {
	public:
		Cure(void);
		Cure(Cure const & src);
		virtual ~Cure(void);

		Cure &	operator=(Cure const & rhs);
	
	public:
		AMateria	*clone(void) const;
		void		use(ICharacter & target);
};

#endif