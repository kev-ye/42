/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 16:53:46 by kaye              #+#    #+#             */
/*   Updated: 2021/08/16 17:19:48 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource(void) {
	for (int i = 0; i < INVENTORY; i++)
		this->_materia[i] = NULL;
}

MateriaSource::MateriaSource(MateriaSource const & src) {
	for (int i = 0; i < INVENTORY; i++)
		if (src._materia[i])
			this->_materia[i] = src._materia[i]->clone();
		else
			this->_materia[i] = src._materia[i];
}

MateriaSource::~MateriaSource(void) {
	for (int i = 0; i < INVENTORY; i++) {
		if (this->_materia[i] != NULL)
			delete this->_materia[i];
		this->_materia[i] = NULL;
	}
}

void		MateriaSource::learnMateria(AMateria * materia) {
	if (!materia) {
		std::cout << "\e[1;31m[Error]\e[0mCan't analyze, Materia no exist!" << std::endl;
		return ;
	}

	for (int i = 0; i < INVENTORY; i++)
		if (!this->_materia[i]) {
			std::cout << "\e[1;33m[Analyzing]\e[0m " << materia->getType() << " ..." << std::endl;
			this->_materia[i] = materia;
			return ;
		}
	delete materia; // if inventory is full, materia can't stock in memory, so we need delete it.
	std::cout << "\e[1;31m[Error]\e[0m Can't analyze [" << materia->getType() <<"], source info is full!" << std::endl;
}

AMateria	*MateriaSource::createMateria(std::string const & type) {
	for (int i = 0; i < INVENTORY; i++) {
		if (this->_materia[i] != NULL && this->_materia[i]->getType() == type) {
			std::cout << "\e[1;35m[Creating]\e[0m " << this->_materia[i]->getType() << " ..." << std::endl;
			return this->_materia[i]->clone();
		}
	}
	std::cout << "\e[1;31m[Error]\e[0m Can't create materia [" << type  << "]." << std::endl;
	return NULL;
}

MateriaSource &	MateriaSource::operator=(MateriaSource const & rhs) {
	if (this == &rhs) return *this;
	
	for (int i = 0; i < INVENTORY; i++) {
		if (this->_materia[i])
			delete this->_materia[i];
		if (rhs._materia[i])
			this->_materia[i] = rhs._materia[i]->clone();
		else
			this->_materia[i] = rhs._materia[i];
	}
	return *this;
}