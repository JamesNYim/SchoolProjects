#pragma once

#include <functional>
#include <initializer_list>
#include <memory>

template<typename key_t, typename val_t, class less_t = std::less<key_t>>
class AVLTree 
{	
	public: /* Type Aliases */
		using key_type = key_t;
		using mapped_type = val_t;
		using value_type = std::pair<const key_type, mapped_type>;

	public: /* Constructors */
		AVLTree(less_t cmp = {});
		AVLTree(std::initializer_list<value_type> init, less_t cmp = {});

	public: /* Iterator Classes */
		class iterator;

	public: /* Methods */
		iterator insert (value_type const &);
		iterator find (key_type const &);
		iterator erase (iterator); /* do this in asgn6, not asgn5 */
		iterator begin();
		iterator end();
		bool empty() const;
//		operator bool() const;


	public: /* Operators */
		mapped_type& operator[] (key_type const &);

	private: /* Internal Classes*/
		struct node;
		using node_ptr = std::unique_ptr<node>;

	private: /* Helpers */

	private: /* Members */
		less_t cmp_;
		unsigned long long size_ = 0;
		node_ptr head_;
};


//Node Class
template<typename key_t, typename val_t, class less_t>
struct AVLTree<key_t, val_t, less_t>::node 
{
    value_type data_;
    unsigned height_ {};
    node* parent_ {};
    node_ptr left_, right_;

    node(value_type data, node* parent);
    void calcHeight();
    unsigned height() const;
};

//Iterator Class
template<typename key_t, typename val_t, class less_t>
class AVLTree<key_t, val_t, less_t>::iterator 
{
	public:
    	iterator(node *n);
    	value_type& operator*();
    	value_type* operator->();
    	bool operator!=(iterator const &) const;
    	bool operator==(iterator const &) const;
    	iterator& operator++();
    	//operator bool() const;
	
	private:
    	node* where = {};
};

#include "avl.tcc"
