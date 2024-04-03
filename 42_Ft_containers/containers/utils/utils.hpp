/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 17:37:13 by kaye              #+#    #+#             */
/*   Updated: 2021/10/12 18:49:45 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

#include <cstddef>

#define _BEGIN_NS_FT namespace ft {
#define _END_NS_FT }

_BEGIN_NS_FT

/** 
 * @class nullptr_t
 */

	struct  nullptr_t {
		void *_ptr;

		struct __nat { int __for_bool_; };

		nullptr_t() : _ptr(0) {}
		nullptr_t(int __nat::*) : _ptr(0) {}

		operator int __nat::*() const { return 0; }

		template <class _T>
		operator _T* () const {return 0;}

		template <class _T, class _U>
		operator _T _U::* () const {return 0;}

		friend  bool operator==(nullptr_t, nullptr_t) { return true; }
		friend  bool operator!=(nullptr_t, nullptr_t) { return false; }
	};

	#define ft_nullptr nullptr_t(0)

/** 
 * @class template: enable_if
 */

	/**
	 * @brief enable type if condition is met
	 * @note the type T is enabled as member type enable_if::type if Cond is true.
	 * 
	 * @param cond: a compile-time constant of type bool.
	 * @param T: a type
	 */
	template < bool Cond, class T = void >
	struct enable_if {};

	template < class T >
	struct enable_if<true, T> { typedef T type; };

/** 
 * @class template: integral_constant
 */
	
	/**
	 * @brief Integral constant
	 * @note this template is designed to provide compile-time constants as types
	 * 
	 * @param T: type of the integral constant.
	 * @param v: value of the integral constant.
	 */
	template < class T, T v >
	struct integral_constant {
		/** @brief the value of the integral_constant */
		// static constexpr T value = v;
		static const T value = v;

	/* member types */

		/** @brief the type of the constant */
		typedef T value_type;

		/** @brief the integral_constant type itself */
		typedef integral_constant<T, v> type;

	/* instantiations */

		/**
		 * @brief returns value
		 * @note returns the value of the integral_constant.
		 * 
		 * @return the value of the integral_constant.
		 */
		// constexpr operator T(void) { return v; }
		operator T() { return v; }
	};

/** 
 * @class template: integral_constant: instantiations
 */

	/**
	 * @brief true type
	 * @note Instantiation of integral_constant to represent the bool value true.
	 */
	typedef integral_constant<bool, true>	true_type;

	/**
	 * @brief false type
	 * @note Instantitation of integral_constant to represent the bool value false.
	 */
	typedef integral_constant<bool, false>	false_type;

/** 
 * @class template: is_integral
 */

	/** 
	 * @brief is integral
	 * @note trait class that identifies whether T is an integral type.
	 */
	template < class T > struct is_integral : public false_type {};
	template <>			 struct is_integral<bool> : public true_type {};
	template <>			 struct is_integral<char> : public true_type {};
	// template <>			 struct is_integral<char16_t> : public true_type {};
	// template <>			 struct is_integral<char32_t> : public true_type {};
	template <>			 struct is_integral<wchar_t> : public true_type {};
	template <>			 struct is_integral<signed char> : public true_type {};
	template <>			 struct is_integral<short int> : public true_type {};
	template <>			 struct is_integral<int> : public true_type {};
	template <>			 struct is_integral<long int> : public true_type {};
	template <>			 struct is_integral<long long int> : public true_type {};
	template <>			 struct is_integral<unsigned char> : public true_type {};
	template <>			 struct is_integral<unsigned short int> : public true_type {};
	template <>			 struct is_integral<unsigned int> : public true_type {};
	template <>			 struct is_integral<unsigned long int> : public true_type {};
	template <>			 struct is_integral<unsigned long long int> : public true_type {};

/*
 * function: equal
 */

	/**
	 * @brief test whether the elements in two ranges are equal
	 * @note compares the elements in the range [first1, last1] with those i nthe range beginning at first2, and returns true if all of the elements in both ranges match.
	 * 
	 * @param first1, last1: Input iterators to the initial and final positions of the first sequence.
	 * @param first2: input iterator to the initial position of the second sequence.
	 * @param pred: Binary function that accepts two elements as argument (one of each of the two sequences, in the same order), and returns a value convertible to bool.
	 * @return true if all the elements in the range [first1, last1] compare equal to those of the range starting at first2.
	 * @return false otherwise.
	 */
	template < class InputIterator1, class InputIterator2 >
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!pred(*first1, *first2)) {
				return false;
			}
		}
		return true;
	}

/*
 * function: lexicographical_compare
 */

	/**
	 * @brief lexicographical less-than comparison
	 * @note returns true if the range [first1, last1] compres lexicographically less than the range [first2, last2].
	 * 
	 * @param first1, last1: input iterators to the initial and final positions of the first sequence.
	 * @param first2, last2: input iterators to the initial and final positions of the second sequence.
	 * @param comp: binary function that accepts two arguments of the types pointed by the iterators, and returns a value convertible to bool.
	 * @return true if the first range compares lexicographically less than the second.
	 * @return false otherwise.
	 */
	template < class InputIt1, class InputIt2 >
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template < class InputIt1, class InputIt2, class Compare >
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

/** 
 * @class template: binary_function
 */

	/**
	 * @brief binary function object base class
	 * @note this is a base class for standard binary function objects.
	 */
	template < class Arg1, class Arg2, class Result >
	struct binary_function {
	/* member types */
		
		/** @brief type of the first argument in member operator(). */
		typedef Arg1	first_argument_type;
		/** @brief type of the second argument in member operator(). */
		typedef Arg2	second_argument_type;
		/** @brief type returned by member operator(). */
		typedef Result	result_type;
	};

/** 
 * @class template: less
 */

	/**
	 * @brief function object class for less-than inequality comparison
	 * @note binary function object class whose call returns
	 * whether the its first argument compares less than the second (as returned by operator <).
	 * 
	 * @param T type of the arguments to compare by the functional call.
	 */
	template < class T >
	struct less : binary_function <T, T, bool> {
	/* member functions */

		/** @brief member function returning whether the first argument compares less than the second (x < y). */
		bool operator() (const T& x, const T& y) const { return x < y; }
	};

/** 
 * @class template: pair
 */

	/**
	 * @brief pair of values
	 * @note this class couples together a pair of values, which may be of different types (T1 and T2).
	 * the individual values can be accessed through its public members first and second.
	 * 
	 * @param T1: type of member first.
	 * @param T2: tyoe of member second.
	 */
	template < class T1, class T2 >
	struct pair {
	/* member functions */
	
		typedef T1	first_type;
		typedef T2	second_type;

	/* member variables */
	
		first_type	first;
		second_type second;

	/* member functions */
	
	/* constructor / destructor / operator= */
		
		/**
		 * @brief constructor: default
		 * @note constructs a pair object with its elements value-initialized
		 */
		pair(void) :
			first(),
			second() {}
		
		/**
		 * @brief constructor: copy
		 * @note the object is iniialized with the contents of the pr pair object.
		 * the corresponding member of pr is passed to the constructor of each of its members.
		 * 
		 * @param pr: another pair object.
		 */
		template< class U, class V >
		pair(const pair<U, V> & pr) :
			first(pr.first),
			second(pr.second) {}
		
		/**
		 * @brief constructor: initialization
		 * @note member first is constructed with a and member second with b.
		 * 
		 * @param a: an object of the type of first, of some other type implicitly convertible to it.
		 * @param b: an object of the type of second, of some other type implicitly convertible to it.
		 */
		pair(const first_type & a, const second_type & b) :
			first(a),
			second(b) {}

		/**
		 * @brief assign contents
		 * @note assigns pr as the new content for the pair object.
		 * 
		 * @param pr: another par object.
		 * @return *this
		 */
		// implicitly declared:
		pair& operator= (const pair & pr) {
			if (this == &pr) return *this;

			first = pr.first;
			second = pr.second;
			return *this;
		}
	};
	
	/* non-member function: pair */

	/**
	 * @brief relational operators for pair
	 * @note performs the appropriate comparison operation between the pair objects lhs and rhs.
	 * 
	 * @param lhs, rhs: pair object, having both the same template parameters (T1 and T2).
	 */
	template < class T1, class T2 >
	bool operator== (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template < class T1, class T2 >
	bool operator!= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs == rhs);
	}

	template < class T1, class T2 >
	bool operator<  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template < class T1, class T2 >
	bool operator<= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(rhs < lhs);
	}

	template < class T1, class T2 >
	bool operator>  (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return rhs < lhs;
	}

	template < class T1, class T2 >
	bool operator>= (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
		return !(lhs < rhs);
	}

/** 
 * @class template: make_pair
 */

	/**
	 * @brief construct pair object
	 * @note constricts a pair object with its first element set to x and its second element set to y.
	 * 
	 * @param x, y: values for the members first and second, respectively, of the pair object being constructed.
	 * @return a pair object whose elements first and second are set to x and y respectivelly.
	 * The template parameters can be implicitly deduced.
	 */
	template < class T1, class T2 >
	pair<T1, T2> make_pair (T1 x, T2 y) {
		return pair<T1, T2>(x, y);
	}

_END_NS_FT

#endif