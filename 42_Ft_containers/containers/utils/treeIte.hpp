/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treeIte.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:31:14 by kaye              #+#    #+#             */
/*   Updated: 2021/10/12 18:44:26 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREEITE_HPP
# define TREEITE_HPP

#include "RBT.hpp"
#include "iterator.hpp"
#include "utils.hpp"

#include <iostream>

_BEGIN_NS_FT

/**
 * @class template: treeIterator
 */

	/**
	 * @class template: treeIterator
	 * @brief bidirectional iterator
	 */
	template < class T, class Node >
	class treeIterator : public ft::iterator<bidirectional_iterator_tag, T> {
		public:
		/* member types */

			typedef 			T																		value_type;

			typedef typename	ft::iterator<bidirectional_iterator_tag, value_type>::difference_type	difference_type;
			typedef typename 	ft::iterator<bidirectional_iterator_tag, value_type>::pointer			pointer;
			typedef typename 	ft::iterator<bidirectional_iterator_tag, value_type>::reference			reference;
			typedef typename 	ft::iterator<bidirectional_iterator_tag, value_type>::iterator_category	iterator_category;

			typedef Node	node_type;
			typedef Node*	node_pointer;
		
		public:
		/* member functions */

		/* constructor / destructor / operator= */
			
			treeIterator(void) :
				_root(ft_nullptr),
				_node(ft_nullptr),
				_null(ft_nullptr) {}

			treeIterator(node_pointer root, node_pointer node, node_pointer null) :
				_root(root),
				_node(node),
				_null(null) {}

			treeIterator(treeIterator const & src) :
				_root(src._root),
				_node(src._node),
				_null(src._null) {}

			~treeIterator(void) {}

			treeIterator & operator= (treeIterator const & rhs) {
				if (this == &rhs) return *this;

				_root = rhs._root;
				_node = rhs._node;
				_null = rhs._null;
				return *this;
			}
		
		/* getters */

			node_pointer getRoot(void) const { return _root; };
			node_pointer getNode(void) const { return _node; };
			node_pointer getNull(void) const { return _null; };

		/* operator */
			
			reference	operator* (void) const { return _node->val; }

			pointer		operator->(void) const { return &(operator*()); }

			/** @brief increment node position*/
			treeIterator &	operator++ (void) {
				if (_node == max(_root)) {
					_node = _null;
					return *this;
				}
				else if (_node == _null) {
					_node = ft_nullptr;
					return *this;
				}
				_node = successor(_node);
				return *this;
			}
			
			treeIterator	operator++ (int) {
				treeIterator tmp(_root, _node, _null);
				operator++();
				return tmp;
			}

			/** @brief decrease node position*/
			treeIterator &	operator-- (void) {
				if (_node == _null) {
					_node = max(_root);
					return *this;
				}
				_node = predecessor(_node);
				return *this;
			}
			
			treeIterator	operator-- (int) {
				treeIterator tmp(_root, _node, _null);
				operator--();
				return tmp;
			}

			operator treeIterator<const T, Node> (void) {
				return treeIterator<const T, Node>(_root, _node, _null);
			}

		private:
		/** attributes */
			
			node_pointer _root;
			node_pointer _node;
			node_pointer _null;

		/** private function */
			
			node_pointer	min(node_pointer s) {
				while (s->left != _null)
					s = s->left;
				return s;
			}

			node_pointer	max(node_pointer s) {
				while (s->right != _null)
					s = s->right;
				return s;
			}

			node_pointer	successor(node_pointer x) {
				if (x->right != _null)
					return min(x->right);

				node_pointer y = x->parent;
				while (y != _null && x == y->right) {
					x = y;
					y = y->parent;
				}
				return y;
			}

			node_pointer	predecessor(node_pointer s) {
				if (s->left != _null)
					return max(s->left);

				node_pointer	tmp = s->parent;
				while (tmp != _null && s == tmp->left) {
					s = tmp;
					tmp = tmp->parent;
				}
				return tmp;
			}
	};

	template < class _T, class _Node >
	bool operator== (const treeIterator<_T, _Node> & lhs, const treeIterator<_T, _Node> & rhs) {
		return lhs.getNode() == rhs.getNode();
	}

	template < class _TL, class _TR, class _Node >
	bool operator== (const treeIterator<_TL, _Node> & lhs, const treeIterator<_TR, _Node> & rhs) {
		return lhs.getNode() == rhs.getNode();
	}

	template < class _T, class _Node >
	bool operator!= (const treeIterator<_T, _Node> & lhs, const treeIterator<_T, _Node> & rhs) {
		return lhs.getNode() != rhs.getNode();
	}

	template < class _TL, class _TR, class _Node >
	bool operator!= (const treeIterator<_TL, _Node> & lhs, const treeIterator<_TR, _Node> & rhs) {
		return lhs.getNode() != rhs.getNode();
	}

_END_NS_FT

#endif