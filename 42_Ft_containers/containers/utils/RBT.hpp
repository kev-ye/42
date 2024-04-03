/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RBT.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:40:35 by kaye              #+#    #+#             */
/*   Updated: 2021/10/13 16:05:31 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RBT_HPP
# define RBT_HPP

#include <memory>
#include "utils.hpp"

_BEGIN_NS_FT

#define RED_NODE 1
#define BLACK_NODE 0

/**
 * @class template: RBT_Node
 */

	/**
	 * @brief Red Black Tree Node
	 */
	template < class T >
	struct RBT_Node {
		/* member types */
		
			typedef T		value_type;
		#if defined(__APPLE__) && defined(__MACH__)
			typedef bool	size_type;

		#else
			typedef size_t	size_type;	

		#endif
			

		/* attributes */

			value_type	val;
			size_type	color;
			RBT_Node	*parent;
			RBT_Node	*left;
			RBT_Node	*right;
			

		/* member function: constructor / destructor / operator=  */

			RBT_Node(void) :
				val(),
				color(BLACK_NODE),
				parent(ft_nullptr),
				left(ft_nullptr),
				right(ft_nullptr) {}
			
			RBT_Node(value_type const & val,
				bool color = BLACK_NODE,
				RBT_Node *parent = ft_nullptr,
				RBT_Node *left = ft_nullptr,
				RBT_Node *right = ft_nullptr) :
					val(val),
					color(color),
					parent(parent),
					left(left),
					right(right) {}

			RBT_Node(RBT_Node const & src) :
				val(src.val),
				color(src.color),
				parent(src.parent),
				left(src.left),
				right(src.right) {}

			~RBT_Node(void) {}

			RBT_Node & operator=(RBT_Node const & rhs) {
				if (this == &rhs) return *this;

				val = rhs.val;
				color = rhs.color;
				parent = rhs.parent;
				left = rhs.left;
				right = rhs.right;
				return *this;
			}

		/* member function: operator==  */

			bool operator==(RBT_Node const & rhs) {
				if (val == rhs.val)
					return true;
				return false;
			}
	};

/**
 * @class template: RBT
 */

	/**
	 * @brief Red Black Tree
	 */
	template < class T,
		class Compare,
		class Node = ft::RBT_Node<T>,
		class AllocNode = std::allocator<Node> >
	class RBT {
		public:
		/* member types */

			typedef				T										value_type;
			typedef				Node									node_type;

			typedef				Compare									value_compare;

			typedef				AllocNode								allocator_type;
			typedef	typename	allocator_type::reference				reference;
			typedef	typename	allocator_type::const_reference			const_reference;
			typedef	typename	allocator_type::pointer					pointer;
			typedef	typename	allocator_type::const_pointer			const_pointer;

			/** @note usually the same as ptrdiff_t */
			typedef	typename	allocator_type::difference_type			difference_type;
			/** @note usually the same as size_t */
			typedef	typename	allocator_type::size_type				size_type;

		public:
		/* member function: constructor / destructor  */

			RBT(value_compare const & comp = value_compare()) : _comp(comp) {
				_null = allocator_type().allocate(1);
				allocator_type().construct(_null, node_type());
				_root = _null;
			}

			~RBT() {}

		/* member function: getters  */

			pointer	getRoot() const { return _root; }

			pointer	getNull() const { return _null; }

		/* member function: capacity  */

			size_type	size() const { return size(_root); }

			size_type	max_size() const { return allocator_type().max_size(); }

		/* member function: operation  */

			pointer	searchTree(value_type val) const { return searchTreeHelper(_root, val); }

			pointer	min() const { return min(_root); }

			pointer	max() const { return max(_root); }

			pointer lower_bound(value_type const & val) const {
				pointer begin = min();

				while (begin != _null) {
					if (_comp(begin->val, val) == false)
						break ;
					begin = successor(begin);
				}
				return begin;
			}

			pointer upper_bound(value_type const & val) const {
				pointer begin = min();

				while (begin != _null) {
					if (_comp(val, begin->val) == true)
						break ;
					begin = successor(begin);
				}
				return begin;
			}

		/* member function: modifiers  */

			void	swap(RBT & toSwap) {
				pointer root_ = _root;
				pointer null_ = _null;

				_root = toSwap.getRoot();
				_null = toSwap.getNull();

				toSwap._root = root_;
				toSwap._null = null_;
			}

			bool	insert(value_type const & val) {
				pointer toInsert = allocator_type().allocate(1);
				allocator_type().construct(toInsert, node_type(val, RED_NODE, ft_nullptr, _null, _null)); // new node must be red

				pointer current = ft_nullptr;
				pointer root = _root;

				while (root != _null) {
					current = root;
					if (_comp(toInsert->val, root->val))
						root = root->left;
					else if (_comp(root->val, toInsert->val))
						root = root->right;
					else {
						allocator_type().destroy(toInsert);
						allocator_type().deallocate(toInsert, 1);
						return false;
					}
				}

				toInsert->parent = current;
				if (current == ft_nullptr)
					_root = toInsert;
				else if (_comp(toInsert->val, current->val))
					current->left = toInsert;
				else
					current->right = toInsert;

				if (toInsert->parent == ft_nullptr) {
					toInsert->color = BLACK_NODE;
					return true;
				}

				if (toInsert->parent->parent == ft_nullptr)
					return true;

				fixInsert(toInsert);
				return true;
			}

			bool	deleteNode(value_type const & val) { return deleteNodeHelper(_root, val); }

			void	destroyTree() {
				destroyTree(_root);
				_root = _null;
			}

			void	destroyNull() {
				allocator_type().destroy(_null);
				allocator_type().deallocate(_null, 1);
			}

		/* member function: iteration  */

			pointer	successor(pointer node) const {
				if (node->right != _null)
					return min(node->right);

				if (node->parent == ft_nullptr || node == max())
					return _null;
				pointer tmp = node->parent;
				while (tmp != _null && node == tmp->right) {
					node = tmp;
					tmp = tmp->parent;
				}
				return tmp;
			}

			pointer	predecessor(pointer node) const {
				if (node->left != _null)
					return max(node->left);

				if (node->parent == ft_nullptr || node == min())
					return _null;
				pointer	tmp = node->parent;
				while (tmp != _null && node == tmp->left) {
					node = tmp;
					tmp = tmp->parent;
				}
				return tmp;
			}

		private:
		/* member function (private): capacity  */
	
			size_type size(pointer root) const {
				if (root == _null)
					return 0;
				return size(root->left) + 1 + size(root->right);
			}

		/* member function (private): operation  */

			pointer	searchTreeHelper(pointer node, value_type const & val) const {
				if (node == _null)
					return node;
				else if (_comp(val, node->val))
					return searchTreeHelper(node->left, val);
				else if (_comp(node->val, val))
					return searchTreeHelper(node->right, val);
				else
					return node;
			}

			pointer	min(pointer node) const {
				if (node == ft_nullptr || node == _null)
					return _null;
				while (node->left != _null)
					node = node->left;
				return node;
			}

			pointer	max(pointer node) const {
				if (node == ft_nullptr || node == _null)
					return _null;
				while (node->right != _null)
					node = node->right;
				return node;
			}

		/* member function (private): modifiers  */

			void	leftRotate(pointer node) {
				pointer	tmp = node->right;
				
				node->right = tmp->left;
				if (tmp->left != _null)
					tmp->left->parent = node;
	
				tmp->parent = node->parent;
				if (node->parent == ft_nullptr)
					_root = tmp;
				else if (node == node->parent->left)
					node->parent->left = tmp;
				else
					node->parent->right = tmp;

				tmp->left = node;
				node->parent = tmp;
			}

			void	rightRotate(pointer node) {
				pointer	tmp = node->left;
				
				node->left = tmp->right;
				if (tmp->right != _null)
					tmp->right->parent = node;

				tmp->parent = node->parent;
				if (node->parent == ft_nullptr)
					_root = tmp;
				else if (node == node->parent->right)
					node->parent->right = tmp;
				else
					node->parent->left = tmp;

				tmp->right = node;
				node->parent = tmp;
			}

			void	fixInsert(pointer toFix) {
				pointer	tmp;
				
				while (toFix->parent->color == RED_NODE) {
					if (toFix->parent == toFix->parent->parent->right) {
						tmp = toFix->parent->parent->left;
						if (tmp->color == RED_NODE) {
							tmp->color = BLACK_NODE;
							toFix->parent->color = BLACK_NODE;
							toFix->parent->parent->color = RED_NODE;
							toFix = toFix->parent->parent;
						}
						else {
							if (toFix == toFix->parent->left) {
								toFix = toFix->parent;
								rightRotate(toFix);
							}
							toFix->parent->color = BLACK_NODE;
							toFix->parent->parent->color = RED_NODE;
							leftRotate(toFix->parent->parent);
						}
					}
					else {
						tmp = toFix->parent->parent->right;

						if (tmp->color == RED_NODE) {
							tmp->color = BLACK_NODE;
							toFix->parent->color = BLACK_NODE;
							toFix->parent->parent->color = RED_NODE;
							toFix = toFix->parent->parent;	
						}
						else {
							if (toFix == toFix->parent->right) {
								toFix = toFix->parent;
								leftRotate(toFix);
							}
							toFix->parent->color = BLACK_NODE;
							toFix->parent->parent->color = RED_NODE;
							rightRotate(toFix->parent->parent);
						}
					}
					if (toFix == _root)
						break ;
				}
				_root->color = BLACK_NODE;
			}

			void	fixDelete(pointer toFix) {
				pointer	tmp;

				while (toFix != _root && toFix->color == BLACK_NODE) {
					if (toFix == toFix->parent->left) {
						tmp = toFix->parent->right;
						if (tmp->color == RED_NODE) {
							tmp->color = BLACK_NODE;
							toFix->parent->color = RED_NODE;
							leftRotate(toFix->parent);
							tmp = toFix->parent->right;
						}

						if (tmp->left->color == BLACK_NODE && tmp->right->color == BLACK_NODE) {
							tmp->color = RED_NODE;
							toFix = toFix->parent;
						}
						else {
							if (tmp->right->color == BLACK_NODE) {
								tmp->left->color = BLACK_NODE;
								tmp->color = RED_NODE;
								rightRotate(tmp);
								tmp = toFix->parent->right;
							}
							tmp->color = toFix->parent->color;
							toFix->parent->color = BLACK_NODE;
							tmp->right->color = BLACK_NODE;
							leftRotate(toFix->parent);
							toFix = _root;
						}
					}
					else {
						tmp = toFix->parent->left;
						if (tmp->color == RED_NODE) {
							tmp->color = BLACK_NODE;
							toFix->parent->color = RED_NODE;
							rightRotate(toFix->parent);
							tmp = toFix->parent->left;
						}

						if (tmp->left->color == BLACK_NODE && tmp->right->color == BLACK_NODE) {
							tmp->color = RED_NODE;
							toFix = toFix->parent;
						}
						else {
							if (tmp->left->color == BLACK_NODE) {
								tmp->right->color = BLACK_NODE;
								tmp->color = RED_NODE;
								leftRotate(tmp);
								tmp = toFix->parent->left;
							} 

							tmp->color = toFix->parent->color;
							toFix->parent->color = BLACK_NODE;
							tmp->left->color = BLACK_NODE;
							rightRotate(toFix->parent);
							toFix = _root;
						}
					} 
				}
				toFix->color = BLACK_NODE;
			}

			void	rbTransplant(pointer node, pointer toTransplant) {
				if (node->parent == ft_nullptr)
					_root = toTransplant;
				else if (node == node->parent->left)
					node->parent->left = toTransplant;
				else
					node->parent->right = toTransplant;

				toTransplant->parent = node->parent;
			}

			bool	deleteNodeHelper(pointer node, value_type const & key) {
				pointer toDelete = _null;
				pointer tmp;
				pointer current;

				while (node != _null) {
					if (_comp(node->val, key))
						node = node->right;
					else if (_comp(key, node->val))
						node = node->left;
					else {
						toDelete = node;
						node = node->right;
					}
				}

				if (toDelete == _null) {
					return false;
				} 

				current = toDelete;
				int y_original_color = current->color;
				if (toDelete->left == _null) {
					tmp = toDelete->right;
					rbTransplant(toDelete, toDelete->right);
				}
				else if (toDelete->right == _null) {
					tmp = toDelete->left;
					rbTransplant(toDelete, toDelete->left);
				}
				else {
					current = min(toDelete->right);
					y_original_color = current->color;
					tmp = current->right;
					if (current->parent == toDelete) {
						tmp->parent = current;
					}
					else {
						rbTransplant(current, current->right);
						current->right = toDelete->right;
						current->right->parent = current;
					}

					rbTransplant(toDelete, current);
					current->left = toDelete->left;
					current->left->parent = current;
					current->color = toDelete->color;
				}

				allocator_type().destroy(toDelete);
				allocator_type().deallocate(toDelete, 1);

				if (y_original_color == BLACK_NODE)
					fixDelete(tmp);
				return true;
			}

			void destroyTree(pointer root) {
				if (root == _null) {
					return ;
				}

				destroyTree(root->left);
				destroyTree(root->right);

				allocator_type().destroy(root);
				allocator_type().deallocate(root, 1);
			}

		private:
		/* attributes */

			pointer			_root;
			pointer			_null;
			value_compare	_comp;
	};

_END_NS_FT

#endif