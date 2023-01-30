#include <algorithm>
#include <stack>

// Node ========================================================================
template<typename key_t, typename val_t, class less_t>
AVLTree<key_t,val_t,less_t>::node::node(value_type data, node* parent)
    : data_(std::move(data)), parent_(parent)
{ calcHeight(); }

//calcHeight()
template<typename key_t, typename val_t, class less_t>
void AVLTree<key_t, val_t, less_t>::node::calcHeight()
{
	//Todo

	//If there are no children
	if ((left_ == nullptr) && (right_ == nullptr))
	{
		height_ = 1;
	}

	//If left is the highest height
	else if ((right_ == nullptr) || left_->height_ > right_->height_)
	{
		height_ = left_->height_ + 1;
	}
	//If right is higher or they are equal
	else if ((left == nullptr) || left_->height_ < right_->height_)
	{
		height_ = right_->height_ + 1;
	}
}

//height()
template<typename key_t, typename val_t, class less_t>
unsigned AVLTree<key_t, val_t, less_t>::node::height() const
{
	//Todo
	return height_;
}

// Iterator ====================================================================

//Iterator Constructor
template<typename key_t, typename val_t, class less_t>
AVLTree<key_t, val_t, less_t>::iterator::iterator(node *n)
{
	where = n;
}

//Pointer overload operator
template<typename key_t, typename val_t, class less_t>
typename AVLTree<key_t, val_t, less_t>::value_type& //This is the return type 
AVLTree<key_t, val_t, less_t>::iterator::operator*()
{
	//todo
	//lol is this right?
	return (where->data_);

}

//Reference overload operator
template<typename key_t, typename val_t, class less_t>
typename AVLTree<key_t, val_t, less_t>::value_type* 
AVLTree<key_t, val_t, less_t>::iterator::operator->()
{
	//todo
	//IS THIS RIGHT?
	return &(where->data_);
}

//Does not equal overload operator
template<typename key_t, typename val_t, class less_t>
bool AVLTree<key_t, val_t, less_t>::iterator::operator!=(const iterator& that) const
{
	//todo
	return (where != that.where);
}

//Equals overloaded operator
template<typename key_t, typename val_t, class less_t>
bool AVLTree<key_t, val_t, less_t>::iterator::operator==(const iterator& that) const
{
	//todo
	return (where == that.where);
}

//++ for Iterator for the AVL Tree and this is done already
template<typename key_t, typename val_t, class less_t>
typename AVLTree<key_t, val_t, less_t>::iterator& 
AVLTree<key_t, val_t, less_t>::iterator::operator++() 
{
    if (!where) 
	{
		return *this;
	}

    // Helpers
    enum class Dir {LEFT, RIGHT};
    auto which_child = [] (node *n) 
	{
        if (not n->parent_) 
		{
			return Dir::LEFT;
		}
		//If n == n->parent_left_.get() is true we return Dir::LEFT
		//If it is false we return Dir::RIGHTr
        return n == n->parent_->left_.get() ? Dir::LEFT : Dir::RIGHT;
    };
    auto go_left = [] (node* &n) 
	{
        while (n->left_) //While there is a left we get the left node
		{
			n = n->left_.get();
		}
    };

    // Increment Iterator
    if (where->right_) 
	{
        where = where->right_.get();
        go_left(where);
    } 
	else 
	{
        Dir child;
        do 
		{
         child = which_child(where);
         where = where->parent_;
        } 
		while (child == Dir::RIGHT);
    }
    return *this;
}

//Bool operator? Apperently we dont need this
/*
operator AVLTree<key_t, val_t, less_t>::iterator::bool() const
{
	//todo
}
*/

// AVLTree =====================================================================

//Constructor
template<typename key_t, typename val_t, class less_t>
AVLTree<key_t, val_t, less_t>::AVLTree (less_t cmp)
    : cmp_(cmp)
{ }

//Intializer list constructor
template<typename key_t, typename val_t, class less_t>

AVLTree<key_t, val_t, less_t>::AVLTree(std::initializer_list<value_type> inList, less_t cmp) 
	: cmp_(cmp)
{
	for (auto iter = inList.begin(); iter != inList.end(); ++iter)
	{
		insert(iter);
	}
}



//Erase() do it pa6
template<typename key_t, typename val_t, class less_t>
typename AVLTree<key_t, val_t, less_t>::iterator
AVLTree<key_t, val_t, less_t>::erase(iterator) {
    // return the iterator after the deleted node
    return end();
}

//Insert() 
//Go left or right until the bottom then insert
//Depending if its less or greater than the key using the cmp instead of < or > cmp_(k1, k2) 
//rather than k1 < k2
template<typename key_t, typename val_t, class less_t>
typename AVLTree<key_t, val_t, less_t>::iterator
AVLTree<key_t, val_t, less_t>::insert(const value_type& val)
{
	//todo

	//New node initalization
	node* currentNode = head_.get();
	node* holderNode = nullptr;
	node_ptr newNode (new node(val, nullptr));//dunno if i can have head_ as parent here

	//Traversing the tree to the spot
	while (currentNode != nullptr)
	{
		holderNode = currentNode;
		//If there is already a key value in the tree
		if (val.first == currentNode->data_.first)
		{
			currentNode->data_.second = val.second;
			return currentNode;
		}
		else if (cmp_(val.first, currentNode->data_.first))
		{
			currentNode = currentNode->left_.get();
		}
		else
		{
			currentNode = currentNode->right_.get();
		}
	}


	
	//Setting position of newNode
		
	//If empty
	if (holderNode == nullptr)
	{
		head_ = node_ptr(new node(val, nullptr));
	}

	//if it should be on left
	else if (cmp_(val.first, holderNode->data_.first))
	{
		holderNode->left_ = node_ptr(new node(val, holderNode));
	}
	//It should be on right
	else
	{
		holderNode->right_ = node_ptr(new node(val, holderNode));
	}

	//Increasing size_
	size_++;

	//returning
	return currentNode;
}

//find()
//Go left or right until we find it
//std::pair *we can go use name->first and name ->second
template<typename key_t, typename val_t, class less_t>
typename AVLTree<key_t, val_t, less_t>::iterator
AVLTree<key_t, val_t, less_t>::find(const key_type& key)
{
	//todo
	node* currentNode = head_.get();

	//If the tree is empty
	if (empty())
	{
		return end();
	}
	
	//If there is stuff in the tree
	while (currentNode != nullptr)
	{
		if (key == currentNode->data_.first)
		{
			return currentNode;
		}
		else if (cmp_(key, currentNode->data_.first))
		{
			currentNode = currentNode->left_.get();
		}
		else
		{
			currentNode = currentNode->right_.get();
		}
	}
	return end();
}

//erase()
//see above

//Begin()
//Returns the left most node
template<typename key_t, typename val_t, class less_t>
typename AVLTree<key_t, val_t, less_t>::iterator
AVLTree<key_t, val_t, less_t>::begin()
{
	//todo
	if (empty())
	{
		return end();
	}
	else
	{
		//Traversing to the beginning
		node* currentNode = head_.get();
		while (currentNode != nullptr)
		{
			if (currentNode->left_.get() == end())
			{
				return currentNode;
			}
			else
			{
				currentNode = currentNode->left_.get();
			}
		}
	}
	return end();
}

//End()
template<typename key_t, typename val_t, class less_t>
typename AVLTree<key_t, val_t, less_t>::iterator
AVLTree<key_t, val_t, less_t>::end()
{
	//todo
	return nullptr;
}
template<typename key_t, typename val_t, class less_t>
bool AVLTree<key_t, val_t, less_t>::empty() const
{
	//todo
	return (size_ == 0);
}

/*
operator AVLTree<key_t, val_t, less_t>::bool() const
{
	//todo
}
*/
//Index Operator
template<typename key_t, typename val_t, class less_t>
typename AVLTree<key_t,val_t,less_t>::mapped_type&
AVLTree<key_t,val_t,less_t>::operator[] (key_type const &k) 
{
    if (auto iter = find(k); iter != end())
        return iter->second;
    else
        return insert({k, mapped_type{}})->second;
}

