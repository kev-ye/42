/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vecIte.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:37:08 by kaye              #+#    #+#             */
/*   Updated: 2021/10/15 14:06:00 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECITE_HPP
# define VECITE_HPP

#include "iterator.hpp"
#include "utils.hpp"

_BEGIN_NS_FT

/** 
 * @class template: vecIterator
 */
	
	/**
	 * @class template: vecIterator
	 * @brief random-access iterator
	 */
	template < class T >
	class vecIterator : public ft::iterator<random_access_iterator_tag, T> {
		public:
		/* member types */

			typedef typename ft::iterator<random_access_iterator_tag, T>::value_type		value_type;
			typedef typename ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename ft::iterator<random_access_iterator_tag, T>::pointer			pointer;
			typedef typename ft::iterator<random_access_iterator_tag, T>::reference			reference;
			typedef typename ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

		public:
		/* member functions */

		/* constructor / destructor / operator= */

			vecIterator(void) : _val(ft_nullptr) {}
			explicit vecIterator(pointer val) : _val(val) {}
			vecIterator(vecIterator const & src) : _val(src._val) {}
			~vecIterator(void) {}

			vecIterator & operator= (vecIterator const & rhs) {
				if (this == &rhs) return *this;

				this->_val = rhs._val;
				return *this;
			}

		/* getter */

			/** @brief return a base pointer */
			pointer base(void) const { return _val; }

		/* operator */
		
			/** @brief dereference value */
			reference	operator* (void) const { return *_val; }

			/** @brief addition value */
			vecIterator	operator+ (difference_type n) const {
				vecIterator tmp(*this);

				tmp._val += n;
				return tmp;
			}

			/** @brief increment value position*/
			vecIterator &	operator++ (void) {
				++_val;
				return *this;
			}
			
			vecIterator	operator++ (int) {
				vecIterator tmp(*this);
				operator++();
				return tmp;
			}

			/** @brief advance value */
			vecIterator &	operator+= (difference_type n) {
				_val += n;
				return *this;
			}

			/** @brief subtraction value*/
			vecIterator	operator- (difference_type n) const {
				vecIterator tmp(*this);

				tmp._val -= n;
				return tmp;
			}

			/** @brief decrease value position*/
			vecIterator &	operator-- (void) {
				--_val;
				return *this;
			}
			
			vecIterator	operator-- (int) {
				vecIterator tmp(*this);
				operator--();
				return tmp;
			}

			/** @brief retrocede value */
			vecIterator &	operator-= (difference_type n) {
				_val -= n;
				return *this;
			}

			/** @brief derefence value */
			pointer	operator->(void) const { return &(operator*()); }

			/** @brief dereference value with offset  */
			reference	operator[] (difference_type n) const { return *(_val + n); }

			/** @brief cast vecIterator<T> to vecIterator<const T> */
			operator vecIterator<const T> (void) {
				return vecIterator<const T>(_val);
			}

		/* non-member function: vecIterator */

			friend bool operator== (const vecIterator<T> & lhs, const vecIterator<T> & rhs) {
				return lhs.base() == rhs.base();
			}

			/* no const -> const case */
			template < class _TR >
			friend bool operator== (const vecIterator<T> & lhs, const vecIterator<_TR> & rhs) {
				return lhs.base() == rhs.base();
			}

			friend bool operator!= (const vecIterator<T> & lhs, const vecIterator<T> & rhs) {
				return lhs.base() != rhs.base();
			}

			/* no const -> const case */
			template < class _TR >
			friend bool operator!= (const vecIterator<T> & lhs, const vecIterator<_TR> & rhs) {
				return lhs.base() != rhs.base();
			}

			friend bool operator<  (const vecIterator<T> & lhs, const vecIterator<T> & rhs) {
				return lhs.base() < rhs.base();
			}

			/* no const -> const case */
			template < class _TR >
			friend bool operator<  (const vecIterator<T> & lhs, const vecIterator<_TR> & rhs) {
				return lhs.base() < rhs.base();
			}

			friend bool operator<= (const vecIterator<T> & lhs, const vecIterator<T> & rhs) {
				return lhs.base() <= rhs.base();
			}

			/* no const -> const case */
			template < class _TR >
			friend bool operator<= (const vecIterator<T> & lhs, const vecIterator<_TR> & rhs) {
				return lhs.base() <= rhs.base();
			}

			friend bool operator>  (const vecIterator<T> & lhs, const vecIterator<T> & rhs) {
				return lhs.base() > rhs.base();
			}

			/* no const -> const case */
			template < class _TR >
			friend bool operator>  (const vecIterator<T> & lhs, const vecIterator<_TR> & rhs) {
				return lhs.base() > rhs.base();
			}

			friend bool operator>= (const vecIterator<T> & lhs, const vecIterator<T> & rhs) {
				return lhs.base() >= rhs.base();
			}

			/* no const -> const case */
			template < class _TR >
			friend bool operator>= (const vecIterator<T> & lhs, const vecIterator<_TR> & rhs) {
				return lhs.base() >= rhs.base();
			}

			friend vecIterator<T> operator+ (difference_type n, const vecIterator<T> & it) {
				return it + n;
			}

			friend difference_type operator- (const vecIterator<T> lhs, const vecIterator<T> rhs) {
				return lhs.base() - rhs.base();
			}

			/* no const -> const case */
			template < class _TR >
			friend difference_type operator- (const vecIterator<T> lhs, const vecIterator<_TR> rhs) {
				return lhs.base() - rhs.base();
			}

		private:
		/** attributes */

			pointer _val;
	};

_END_NS_FT

#endif