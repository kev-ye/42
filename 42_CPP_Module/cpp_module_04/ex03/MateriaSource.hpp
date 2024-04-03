/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 15:10:07 by kaye              #+#    #+#             */
/*   Updated: 2021/08/10 17:54:25 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP

#include "IMateriaSource.hpp"

#define INVENTORY 4

class MateriaSource : public IMateriaSource {
	public:
		MateriaSource(void);
		MateriaSource(MateriaSource const & src);
		virtual ~MateriaSource(void);

		MateriaSource &	operator=(MateriaSource const & rhs);
	
	public:
		void		learnMateria(AMateria * materia);
		AMateria	*createMateria(std::string const & type);

	private:
		AMateria	*_materia[INVENTORY];
};

#endif