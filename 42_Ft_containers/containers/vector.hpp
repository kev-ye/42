/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:04:16 by kaye              #+#    #+#             */
/*   Updated: 2021/10/14 19:28:01 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <memory>
#include <cstddef>
#include <exception>
#include <stdexcept>
#include <limits>
#include "./utils/vecIte.hpp"

_BEGIN_NS_FT

/**
 * @class template: vector
 */

	/**
	 * @brief vector
	 * @note vectors are sequence containers representing arrays that can change in size.
	 * 
	 * container properties:
	 *  - sequence:
	 *   elements in sequence containers are ordered in a strict linear sequence.
	 *   Individual elements are accessed by their position in this sequence.
	 *  - dynamic array
	 *   allows direct access to any element in the sequence, even through pointer arithmetics,
	 *   and provides relatively fast addition/removal of elements at the end of the sequence.
	 *  - allocator-aware
	 *   the container uses an allocator object to dynamically handle its storage needs.
	 * 
	 * @param T: type of the elements.
	 * @param Alloc: type of the allocator object used to define the storage allocation model.
	 */
	template < class T, class Alloc = std::allocator<T> >
	class vector {
		public:
		/* member types */

			typedef 			T										value_type;
			typedef 			Alloc									allocator_type;

			typedef typename	allocator_type::reference				reference;
			typedef typename	allocator_type::const_reference			const_reference;
			typedef typename	allocator_type::pointer					pointer;
			typedef typename	allocator_type::const_pointer			const_pointer;

			/** @note usually the same as ptrdiff_t */
			typedef typename	allocator_type::difference_type			difference_type;
			/** @note usually the same as size_t */
			typedef typename	allocator_type::size_type				size_type;

			/** @note convertible to const_iterator */
			typedef typename	ft::vecIterator<value_type> 			iterator;
			typedef typename	ft::vecIterator<const value_type>		const_iterator;

			typedef typename	ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename	ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		public:
		/* member functions: constructor / destructor / operator= */

			/**
			 * @brief constructor: default
			 * @note constructs an empty container, with no elements.
			 * 
			 * @param alloc: allocator object.
			 */
			explicit vector(const allocator_type & alloc = allocator_type()) :
				_alloc(alloc),
				_begin(ft_nullptr),
				_end(ft_nullptr),
				_capacity(ft_nullptr) {}

			/**
			 * @brief constructor: fill
			 * @note constructs a container with n elements. Each element is a copy of val.
			 * 
			 * @param n: initial container size.
			 * @param val: value to fill the container with.
			 * @param alloc: allocator object.
			 */
			explicit vector(size_type n,
				const value_type & val = value_type(),
				const allocator_type & alloc = allocator_type()) :
				_alloc(alloc),
				_begin(ft_nullptr),
				_end(ft_nullptr),
				_capacity(ft_nullptr) {
					try {
						_begin = _alloc.allocate(n);
					}
					catch (std::length_error &e) {
						throw std::length_error("vector");
					}

					_end = _begin;
					_capacity = _begin + n;

					for (; n != 0; n--)
						_alloc.construct(_end++, val);
			}

			/**
			 * @brief constructor: range
			 * @note constructs a container with as many elements as the range [first, last],
			 * with each element constructed from its corresponding element in that range, in the same order.
			 * 
			 * @param first: input iterators to the initial positions in a range.
			 * @param last: input iterator to the final positions in a range.
			 * @param alloc: allocator object.
			 */
			template < class InputIterator >
			vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = ft_nullptr) : _alloc(alloc) {
				size_type n = static_cast<size_type>(ft::distance(first, last));

				_begin = _alloc.allocate(n);
				_end = _begin;
				_capacity = _begin + n;

				for (; n != 0; n--)
					_alloc.construct(_end++, *first++);
			}

			/**
			 * @brief constructor: copy
			 * @note constructs a container with a copy of each of the elements in x, in the same order.
			 * 
			 * @param x: another vector object of the same type, whose contents are either copied or acquired.
			 */
			vector(const vector & x) {
				size_type n = x.size();

				this->_begin = this->_alloc.allocate(n);
				this->_end = this->_begin;
				this->_capacity = this->_end + n;
				
				pointer tmp = x._begin;
				for (; n != 0; n--)
					this->_alloc.construct(this->_end++, *tmp++);
			}
			
			/**
			 * @brief destructor
			 * @note this destroys all container elements,
			 * and deallocates all the storage capacity allocated by the vector using its allocator.
			 */
			~vector(void) {
				clear();
				_alloc.deallocate(_begin, capacity());
			}

			/**
			 * @brief operator: copy
			 * @note copies all the elements from x into the container.
			 * 
			 * @param x: a vector object of the same type.
			 * @return *this.
			 */
			vector &	operator= (vector const & x) {
				if (this == &x) return *this;

				clear();

				size_type n = x.size();
				if (n > this->capacity())
					reserve(n);
				
				pointer tmp = x._begin;
				for (; n != 0; n--)
					this->_alloc.construct(this->_end++, *tmp++);
				return *this;
			}

		/* member functions: iterators */

			/**
			 * @brief return iterator to beginning
			 * @note returns an iterator pointing to the first element in the vector.
			 * 
			 * @return an iterator to the beginning of the sequence container.
			 */
			iterator		begin(void) { return iterator(_begin); }
			const_iterator	begin(void) const { return const_iterator(_begin); }

			/**
			 * @brief return iterator to end
			 * @note returns an iterator referring to the past-the-end element int the vector container.
			 * 
			 * @return an iterator to the past the end of the sequence.
			 */
			iterator		end(void) { return iterator(_end); }
			const_iterator	end(void) const { return const_iterator(_end); }

			
			/**
			 * @brief return reverse iterator to reverse beginning
			 * @note returns a reverse iterator pointing to the last element in the vector.
			 * 
			 * @return a reverse iterator to the reverse beginning of the sequence container.
			 */
			reverse_iterator		rbegin(void) { return reverse_iterator(end()); }
			const_reverse_iterator	rbegin(void) const { return const_reverse_iterator(end()); }

			/**
			 * @brief return reverse iterator to reverse end.
			 * @note returns a reverse iterator pointing to the theoretical element preceding the first element in the vector.
			 * 
			 * @return a reverse iterator to the reverse end of the sequence container.
			 */
			reverse_iterator		rend(void) { return reverse_iterator(begin()); }
			const_reverse_iterator	rend(void) const { return const_reverse_iterator(begin()); }

		/* member functions: capacity */

			/**
			 * @brief return size.
			 * @note returns the number of elements in the vector.
			 * 
			 * @return the number of elements in the container. 
			 */
			size_type	size(void) const { return _end - _begin; }

			/**
			 * @brief return maximum size.
			 * @note return the maximum number of elements that the vector can hold.
			 * 
			 * @return the maximum number of elements a vector container can hold as content.
			 */
			size_type	max_size(void) const {
			#if defined(__APPLE__) && defined(__MACH__)
				size_type ret1 = allocator_type().max_size();
				size_type ret2 = std::numeric_limits<difference_type>::max();
				return (ret1 < ret2) ? ret1 : ret2;

			#else
				return allocator_type().max_size();

			#endif
			}

			/**
			 * @brief change size.
			 * @note resizes the container so that it contains n elements
			 * 
			 * @param n: new container size, expressed in number of elements.
			 * @param val: object whose content is copied to the added elements in case that n is greater than the current container size.
			 * If not specified, the default constructor is used instead.
			 * @exception throw length_error exception
			 */
			void		resize(size_type n, value_type val = value_type()) {
				if (n > max_size())
					throw std::length_error("vector");

				size_type oldN = size();
				size_type oldCap = capacity();

				if (n < oldN) {
					while (size() > n)
						_alloc.destroy(--_end);
				}
				else {
					if (n <= oldCap) {
						// do nothing;
					}
					else {
						if (oldCap * 2 >= n)
							reserve(oldCap * 2);
						else
							reserve(n);
					}
				}
				for (; oldN < n; oldN++)
					_alloc.construct(_end++, val);
			}

			/**
			 * @brief return size of allocated storage capacity.
			 * @note returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
			 * 
			 * @return the size of the currently allocated storage capacity in the vector,
			 * measured in terms of the number elements it can hold.
			 */
			size_type	capacity(void) const { return _capacity - _begin; }

			/**
			 * @brief test whether vector is empty.
			 * @note return whether the vector is empty.
			 * @return true if the container size is 0, false otherwise.
			 */
			bool		empty(void) const { return size() == 0; }

			/**
			 * @brief request a change in capacity.
			 * @note requests that the vector capacity be at least enough to contain n elements.
			 * 
			 * @exception length_error exception
			 * @param n: minimum capacity fot the vector.
			 */
			void		reserve(size_type n) {
				if (n > max_size())
					throw std::length_error("vector");

				if (n > capacity()) {
					pointer oldStart = _begin;
					pointer oldEnd = _end;
					size_type oldN = size();
					size_type oldCap = capacity();

					_begin = _alloc.allocate(n);
					_end = _begin;
					_capacity = _begin + n;
					while (oldStart != oldEnd)
						_alloc.construct(_end++, *oldStart++);
					_alloc.deallocate(oldStart - oldN, oldCap);
				}
			}
			
		/* member functions: element access */

			/** 
			 * @brief access element.
			 * @note returns a reference to the element at position n in the vector container.
			 * 
			 * @param n: position of an element in the container.
			 * @return the element at the specified position in the vector.
			 */
			reference			operator[](size_type n) { return *(_begin + n); }
			const_reference		operator[](size_type n) const { return *(_begin + n); }

			/**
			 * @brief access element.
			 * @note returns a refenrece to the elelment at position n in the vector.
			 * 
			 * @exception throw out_of_range exception
			 * @param n: position of an element in the container.
			 * @return the element at the specified position in the container.
			 */
			reference			at(size_type n) {
				if (n >= size())
					throw std::out_of_range("vector");
				return (*this)[n];
			}
			const_reference		at(size_type n) const {
				if (n >= size())
					throw std::out_of_range("vector");
				return (*this)[n];
			}
			
			/**
			 * @brief access first element.
			 * @note returns a reference to the first element in the vector.
			 * 
			 * @return a reference to hte first element in the vector container. 
			 */
			reference			front(void) { return *_begin; }
			const_reference		front(void) const { return *_begin; }

			/**
			 * @brief access last element.
			 * @note returns a reference to the last element in the vector.
			 * 
			 * @return a reference to the last element in the vector. 
			 */
			reference			back(void) { return *(_end - 1); }
			const_reference		back(void) const { return *(_end - 1); }

		/* member functions: modifiers */
			
			/**
			 * @brief assign vector content.
			 * @note assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
			 *
			 * @remarks range version: the new contents are elements constructed from each of the elements in the range between first,
			 * in the same order.
			 * @param first: input iterators to the initial positions in a sequence.
			 * @param last: input iterators to the final positions in a sequence.
			 * 
			 * @remarks fill version: the new contents are n elements, each initialized to a copy of val.
			 * @param n: new size for the container.
			 * @param val: value to fill the container with. 
			 */
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = ft_nullptr) {
				clear();

				size_type n = static_cast<size_type>(ft::distance(first, last));
				reserve(n);

				for (; first != last; first++) {
					_alloc.construct(_end++, *first);
				}
			}

			void assign(size_type n, const value_type & val) {
				clear();
				reserve(n);
				
				for (; n != 0; n--) {
					_alloc.construct(_end++, val);
				}
			}

			/**
			 * @brief add element at the end.
			 * @note add a new element at the end of the vector, after its current last element.
			 * 
			 * @param val: value to be copied to the new element.
			 */
			void push_back(const value_type & val) {
				if (_end == _capacity)
					reserve(size() > 0 ? size() * 2 : 1);
				_alloc.construct(_end, val);
				++_end;
			}

			/**
			 * @brief delete last element.
			 * @note removes the last element in the vector, effectively reducing the container size by one.
			 */
			void pop_back(void) {
				_alloc.destroy(_end - 1);
				--_end;
			}

			/** 
			 * @brief insert elements.
			 * @note the vector is extended by inserting new elements before the element at the specified position,
			 * effectively increasing the container size by the number of elements inserted.
			 * 
			 * @param position: position in the vector where the new elements are inserted.
			 * @param val: value to be copied(or moved) to the inserted elements.
			 * @param first, last: iterators specifying a range of elements.
			 * Copies of the elements in the range [first, last] are inserted at position(in the same order).
			 * @return an iterator that points to the first of the newly inserted elements.
			 */
			iterator insert(iterator position, const value_type & val) {
				insert(position, 1, val);
				return iterator(position);
			}

			void insert(iterator position, size_type n, const value_type & val)  {
				size_type pos = ft::distance(begin(), position);

				resize(size() + n);
				position = begin() + pos;
				
				size_type toMoveRight = ft::distance(position, end() - n);
				pointer oldEnd = _end - n - 1;
				for (size_type i = 0; i < toMoveRight; i++) {
					*(_end - i - 1) = *oldEnd--;
				}
				for (size_type i = 0; i < n; i++) {
					*(position + i) = val;
				}
			}

			template < class InputIterator >
			void insert(iterator position, InputIterator first, InputIterator last,
				typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = ft_nullptr) {
				size_type pos = ft::distance(begin(), position);
				size_type n = ft::distance(first, last);

				resize(size() + n);
				position = begin() + pos;
				
				size_type toMoveRight = ft::distance(position, end() - n);
				pointer oldEnd = _end - n - 1;
				for (size_type i = 0; i < toMoveRight; i++) {
					*(_end - i - 1) = *oldEnd--;
				}
				for (size_type i = 0; i < n && first != last; i++, first++) {
					*(position + i) = *first;
				}
			}

			/** 
			 * @brief erase elements.
			 * @note removes from the vector either a single element or a range of elements.
			 * 
			 * @param position: iterator pointing to a single element to be removed from the vector.
			 * @param first, last: Iterators specifying a range within the vector to be removed: [first, last].
			 * @return an iterator pointing to the new location of the element that followed the last element erased by the function call.
			 */
			iterator erase(iterator position) {
				iterator pos = position;
				size_type toDestroyPos = ft::distance(begin(), position);

				_alloc.destroy(_begin + toDestroyPos);

				for (; pos + 1 != end(); ++pos)
					*pos = *(pos + 1);
				--_end;
				return iterator(position);
			}

			iterator erase(iterator first, iterator last) {
				for (; first != last; --last)
					erase(first);
				return iterator(first);
			}

			/** 
			 * @brief swap content.
			 * @note exchanges the content of the container by the content of x,
			 * which is another vector object of the same type.
			 * 
			 * @param x: another vector container of the same type.
			 */
			void swap(vector & x) {
				pointer beginTmp = _begin;
				pointer endTmp = _end;
				pointer capacityTmp = _capacity;
				allocator_type allocTmp = _alloc;

				_begin = x._begin;
				_end = x._end;
				_capacity = x._capacity;
				_alloc = x._alloc;

				x._begin = beginTmp;
				x._end = endTmp;
				x._capacity = capacityTmp;
				x._alloc = allocTmp;
			}

			/** @brief removes all elements from the vector, leaving the container with a size of 0. */
			void	clear(void) {
				size_type len = size();

				for (size_type i = 0; i < len; i++)
					_alloc.destroy(--_end);
			}

		/* member functions: allocator */

			/** 
			 * @brief returns a copy of the allocator object associated with the vector;
			 * 
			 * @return the allocator.
			 */
			allocator_type get_allocator() const { return _alloc; }
		
		private:
		/* attributes */

			allocator_type	_alloc;
			pointer			_begin;
			pointer			_end;
			pointer			_capacity;
	};

	/* non-member function: vector */
	
		/**
		 * @brief relational operators for vector
		 * @note performs the appropriate comparison operation between the vector containers lhs and rhs.
		 * The other operations also use the operators == and < internally to compare the elements,
		 * behaving as if the following equivalent operations were performed:
		 * a != b : !(a == b)
		 * a > b  : b < a
		 * a <= b : !(b < a)
		 * a >= b : !(a < b)
		 * 
		 * @param lhs, rhs: vector container, having both the same template parameters.
		 * @return true if the condition holds, and false otherwise.
		 */
		template < class T, class Alloc >
		bool operator== (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
			if (lhs.size() != rhs.size())
				return false;
			return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
		}

		template < class T, class Alloc >
		bool operator!= (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
			return !(lhs == rhs);
		}

		/** @brief lexicographically compares the values in the vector */
		template < class T, class Alloc> 
		bool operator< (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

		/** @brief lexicographically compares the values in the vector */
		template < class T, class Alloc >
		bool operator<= (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
			return !(rhs < lhs);
		}

		/** @brief lexicographically compares the values in the vector */
		template < class T, class Alloc >
		bool operator> (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
			return rhs < lhs;
		}

		/** @brief lexicographically compares the values in the vector */
		template < class T, class Alloc >
		bool operator>= (const vector<T, Alloc> & lhs, const vector<T, Alloc> & rhs) {
			return !(lhs < rhs);
		}

		/**
		 * @brief exchange contents of vectors
		 * @note the contents of container x are exchanged with those of y.
		 */
		template < class T, class Alloc >
		void swap (vector<T, Alloc> & x, vector<T, Alloc> & y) {
			x.swap(y);
		}

_END_NS_FT

#endif