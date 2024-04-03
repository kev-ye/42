/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:13:21 by kaye              #+#    #+#             */
/*   Updated: 2021/10/15 14:18:10 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

#include <cstddef>
#include "utils.hpp"

_BEGIN_NS_FT

/*
 * category tags
 */

	/** 
	 * @brief input iterator category
	 * @note empty class to identify the category of an iterator as an input iterator.
	 */
	struct input_iterator_tag {};
	
	/** 
	 * @brief output iterator category
	 * @note empty class to identify the category of an iterator as an output iterator.
	 */
	struct output_iterator_tag {};

	/** 
	 * @brief forward iterator category
	 * @note empty class to identify the category of an iterator as a forward iterator.
	 */
	struct forward_iterator_tag : public input_iterator_tag {};

	/** 
	 * @brief bidirectional iterator category
	 * @note empty class to identify the category of an iterator as a bidirectional iterator.
	 */
	struct bidirectional_iterator_tag : public forward_iterator_tag {};

	/** 
	 * @brief random-access iterator category
	 * @note empty class to identify the category of an iterator as a random-access iterator:.
	 */
	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

/** 
 * @class template: iterator traits
 */

	/** 
	 * @class template: iterator_traits
	 * @brief Traits class defining properties of iterators.
	 */
	template < class Iterator >
	struct iterator_traits {
	/* member types */

		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};
	
	template < class T >
	struct iterator_traits<T*> {
	/* member types */

		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template < class T >
	struct iterator_traits<const T*> {
	/* member types */

		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

/*
 * function - iterator operations:  iterator operations
 */

	/**
	 * @brief advance iterator
	 * @note advances the iterator it by n element positions.
	 * 
	 * @param it: iterator to be advanced.
	 * @param n: number of element positions to advance.
	 */
	template <class InputIterator, class Distance> // need to test
	void advance(InputIterator& it, Distance n) { it += n; }

	/**
	 * @brief return distance between iterators
	 * @note calculates the number of elements between first and last.
	 * 
	 * @param first: iterator pointing to the initial element.
	 * @param last: iterator pointing to the final element. This must be reachable from first.
	 */
	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last) {
		typename iterator_traits<InputIterator>::difference_type count = 0;
		for (; first != last; ++first)
			++count;

		return count;
	}

/** 
 * @class template: iterator
 */

	/**
	 * @class template: iterator
	 * @brief iterator base class.
	 * @param Category: category to which the iterator belons to. It must be one of the followng iterator tags:
	 * intput_iterator_tag:	input iterator
	 * output_iterator_tag: output iterator
	 * forward_iterator_tag: forward iterator
	 * bidirectional_iterator_tag: bidirectional iterator
	 * random_access_iterator_tage: random-access iterator
	 * @param T: type of elements pointer by the iterator.
	 * @param Distance: type to represent the difference between two iterators.
	 * @param Pointer: type to represent a pointer to an element pointed by the iterator.
	 * @param Reference: type to represent a reference to an element pointed by the iterator.
	 */
	template < class Category,
		class T,
		class Distance = ptrdiff_t,
		class Pointer = T*,
		class Reference = T& >
	struct iterator {
	/* member types */

		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

/** 
 * @class template: predefined iterators: reverse_iterator
 */

	/**
	 * @class template: reverse_iterator
	 * @brief reverse iterator
	 * @note this class reverses the direction in which a bidirectional or random-access iterator iterates through a range.
	 */
	template <class Iterator>
	class reverse_iterator {
		public:
		/* member types */

			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

		public:
		/* member functions */

		/* constructor / destructor */

			/** 
			 * @brief constructor: default
			 * @note constructs a reverse iterator that points to no object.
			 */
			reverse_iterator(void) : _it() {}
			
			/**
			 * @brief constructor: initialization
			 * @note constructs a reverse iterator from some original iterator it.
			 * 
			 * @param it: an iterator, whose sense of iteration is inverted in the constructed object.
			 */
			explicit reverse_iterator(iterator_type it) : _it(it) {}

			/**
			 * @brief constructor: copy
			 * @note constructs a reverse iterator from some other reverse iterator.
			 * 
			 * @param rev_it: an iterator of a reverse_iterator type, whose sense of iteration is preserved.
			 */
			template< class Iter >
			reverse_iterator(const reverse_iterator<Iter> & rev_it) : _it(rev_it.base()) {}

			virtual ~reverse_iterator(void) {}
		
		/* getters */

			/**
			 * @brief return base iterator
			 * @note returns a copy of the base iterator.
			 * 
			 * @return a copy of the base iterator, which iterates in the oppsite direction.
			*/
			iterator_type base(void) const { return _it; }

		/* operator */

			/**
			 * @brief dereference iterator
			 * @note returns a reference to the element pointed to by the iterator.
			 * 
			 * @return a reference to the element pointed by the iterator.
			 */
			reference operator*(void) const { 
				iterator_type tmp = _it;

				return *(--tmp);
			}

			/**
			 * @brief addition operator
			 * @note returns a reverse iterator pointing to the element located n positions away from the element the iterator currently points to.
			 * 
			 * @param n: number of elements to offset
			 * @return an iterator pointing to the element n positions away.
			 */
			reverse_iterator operator+ (difference_type n) const { return reverse_iterator(_it - n); }

			/**
			 * @brief increment iterator position
			 * @note advances the reverse_iterator by one position.
			 * 
			 * @return the pre-increment version: return *this.
			 * @return the post-increment version: return the value *this had before the call.
			 */
			reverse_iterator& operator++(void) {
				--_it;
				return *this;
			}

			reverse_iterator  operator++(int) {
				reverse_iterator tmp(*this);
				operator++();
				return tmp;
			}

			/**
			 * @brief advance iterator
			 * @note advances the reverse_iterator by n element positions.
			 * 
			 * @param n: number of elements to offset
			 * @return the reverse iterator itself (*this).
			 */
			reverse_iterator& operator+= (difference_type n) {
				_it -= n;
				return *this;
			}

			/**
			 * @brief subtraction operator
			 * @note returns a reverse iterator pointing to the element located n positions before the element the iterator currently points to.
			 * 
			 * @param n: number of elements to offset
			 * @return an iterator pointing to the element n positions before the currently pointed one.
			 */
			reverse_iterator operator- (difference_type n) const { return reverse_iterator(_it + n); }

			/**
			 * @brief decrease iterator position
			 * @note decrease the reverse_iterator by one position.
			 * 
			 * @return the pre-decrment version: return *this.
			 * @return the post-decrment version: return the value *this had before the call.
			 */
			reverse_iterator& operator--(void) {
				++_it;
				return *this;
			}

			reverse_iterator  operator--(int) {
				reverse_iterator tmp(*this);
				operator--();
				return tmp;
			}

			/**
			 * @brief retrocede iterator
			 * @note descreases the reverse_iterator by n element positions.
			 * 
			 * @param n: number of elements to offset
			 * @return the reverse iterator itself (*this).
			 */
			reverse_iterator& operator-= (difference_type n) {
				_it += n;
				return *this;
			}

			/**
			 * @brief dereference iterator
			 * @note returns a pointer to the element pointed to by the iterator.
			 */
			pointer operator->() const { return &(operator*()); }

			/**
			 * @brief dereference iterator with offset
			 * @note accesses the element located n positions away from the element currently pointed to by the iterator.
			 * 
			 * @param n: number of elements to offset
			 * @return a reference to the element n positions away from the element currently pointed by the iterator.
			 */
			reference operator[] (difference_type n) const { return _it[-n - 1]; }

		/* non-member function: reverse_iterator */

			/**
			 * @brief relational operators for reverse_iterator
			 * @note performs the appropriate comparison operatioon between the reverse_iterator objects lhs and rhs.
			 * iternally, the function compares directly the base iterators using the reflexively equivalent relational operator:
			 * == : ==
			 * != : !=
			 * <  : >
			 * <= : >=
			 * >  : <
			 * >= : <=
			 * 
			 * @param lhs, rhs: reverse_iterator objects, having both the same template parameter.
			 * @return true if the condition holds, and false otherwise.
			 */
			friend bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
				return lhs.base() == rhs.base();
			}

			template < class _IteratorR >
			friend bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
				return lhs.base() == rhs.base();
			}

			friend bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
				return lhs.base() != rhs.base();
			}

			template < class _IteratorR >
			friend bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
				return lhs.base() != rhs.base();
			}

			friend bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
				return lhs.base() > rhs.base();
			}

			template < class _IteratorR >
			friend bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
				return lhs.base() > rhs.base();
			}

			friend bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
				return lhs.base() >= rhs.base();
			}

			template < class _IteratorR >
			friend bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
				return lhs.base() >= rhs.base();
			}

			friend bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
				return lhs.base() < rhs.base();
			}

			template < class _IteratorR >
			friend bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
				return lhs.base() < rhs.base();
			}

			friend bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {
				return lhs.base() <= rhs.base();
			}

			template < class _IteratorR >
			friend bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<_IteratorR>& rhs) {
				return lhs.base() <= rhs.base();
			}

			/**
			 * @brief Addition operator
			 * @note returns a reverse iterator pointing to the element located n positions away from the element pointed to by rev_it.
			 * 
			 * @param n: number of elements to offset.
			 * @param rev_it: reverse iterator.
			 * @return reverse iterator.
			 */
			friend reverse_iterator<Iterator> operator+ (difference_type n, const reverse_iterator<Iterator>& rev_it) {
				return rev_it + n;
			}

			/**
			 * @brief subtraction operator
			 * @note returns the distance between lhs and rhs.
			 * 
			 * @param lhs, rhs: reverse_iterator objects, having both the same template parameter.
			 * @return the number of elements between lhs and rhs.
			 */
			friend difference_type operator- (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<Iterator>& rhs) {
				return rhs.base() - lhs.base();
			}

			template < class _IteratorR >
			friend difference_type operator- (const reverse_iterator<Iterator>& lhs,
				const reverse_iterator<_IteratorR>& rhs) {
				return rhs.base() - lhs.base();
			}

		private:
		/* attributes */
		
			iterator_type	_it;
	};

_END_NS_FT

#endif