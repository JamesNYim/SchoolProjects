//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// James Yim
// Cruz ID: jnyim
// #1798845
// CSE 101-01 Tantalo
// Programming Assignment 6
// List.cpp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"




//---= Constructors & Destructors =---

//Constructing the Node
List::Node::Node(ListElement x)
{
	data = x;
	next = nullptr;
	prev = nullptr;
}

//Constructing the List
List::List()
{
	frontDummy = new Node(-88);
	backDummy = new Node(-88);
	frontDummy->next = backDummy;
	backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
        afterCursor = backDummy;
	cursorPos = 0;
	num_elements = 0;
}

//Copying the List
List::List(const List& l)
{
	//Making an empty List
	frontDummy = new Node(-88);
        backDummy = new Node(-88);
        frontDummy->next = backDummy;
        backDummy->prev = frontDummy;
	beforeCursor = frontDummy;
        afterCursor = backDummy;
        cursorPos = 0;
        num_elements = 0;

	for (Node* n = l.frontDummy->next; n != l.backDummy; n = n->next)
	{
		insertBefore(n->data);
	}
}

//Deleting the List
List::~List()
{
	moveBack();
	while (length() > 0)
	{
		eraseBefore();
	}
}

//---= Accessor Functions =---


//getting length of list
int List::length() const
{
	return num_elements;
}

//returning the position of cursor
int List::position() const
{
	//Pre-Conditions
	if (!(0 <= cursorPos && cursorPos <= length()))
	{
		throw std::out_of_range("[ADT: List] [Function: position()] [Reason: Cursor position is out of bounds]");
	}

	return cursorPos;
}

//Returning the front element
ListElement List::front() const
{
	//Pre-Conditions
	if (!(length() > 0))
	{
		throw std::length_error("[ADT: List] [Function: front()] [Reason: List is empty]");
	}

	return frontDummy->next->data;
}

//Returning the back element
ListElement List::back() const
{
        //Pre-Conditions
        if (!(length() > 0))
        {
                throw std::length_error("[ADT: List] [Function: back()] [Reason: List is empty]");
        }

        return backDummy->prev->data;
}

//Returning the element after cursor
ListElement List::peekNext() const
{
	//Pre-Conditions
        if (!(length() > position()))
        {
                throw std::out_of_range("[ADT: List] [Function: peekNext()] [Reason: Cursor is out of bounds]");
        }

	return afterCursor->data;
}

//Returning the element after cursor
ListElement List::peekPrev() const
{
        //Pre-Conditions
        if (!(length() > 0))
        {
                throw std::out_of_range("[ADT: List] [Function: peekPrev()] [Reason: Cursor is out of bounds]");
        }

        return beforeCursor->data;
}

//---= Manipulation Functions =---

//Clearing a list
void List::clear()
{
	moveBack();
        while (length() > 0)
        {
                eraseBefore();
        }
}

//Moving the cursor to the front
void List::moveFront()
{
	cursorPos = 0;
	beforeCursor = frontDummy;
	afterCursor = frontDummy->next;

}

//Moving the cursor to the front
void List::moveBack()
{
        cursorPos = num_elements;
        afterCursor = backDummy;
        beforeCursor = backDummy->prev;
}

//Moving the cursor to the next position
ListElement List::moveNext()
{
	//Pre-Conditions
	if (cursorPos == num_elements)
	{
		throw std::out_of_range("[ADT: List] [Function: moveNext()] [Reason: Cursor is at the front]");
	}

	ListElement returnElement = afterCursor->data;
	beforeCursor = afterCursor;
	afterCursor = afterCursor->next;
	cursorPos++;
	return returnElement;
}

//Moving the cursor to the previous position
ListElement List::movePrev()
{
        //Pre-Conditions
        if (cursorPos == 0)
        {
                throw std::out_of_range("[ADT: List] [Function: movePrev()] [Reason: Cursor is at the back]");
        }

        ListElement returnElement = beforeCursor->data;
        afterCursor = beforeCursor;
        beforeCursor = beforeCursor->prev;
        cursorPos--;
        return returnElement;
}

//Inserting a node after the cursor
void List::insertAfter(ListElement x)
{
	Node* newN = new Node(x);
	
	newN->prev = beforeCursor;
	newN->next = afterCursor;
	afterCursor->prev = newN;
	beforeCursor->next = newN;
	afterCursor = newN;
	num_elements++;
}

//Inserting a node before the cursor
void List::insertBefore(ListElement x)
{
	Node* newN = new Node(x);
	newN->next = afterCursor;
	newN->prev = beforeCursor;
	beforeCursor->next = newN;
	afterCursor->prev = newN;
	beforeCursor = newN;
	num_elements++;
	cursorPos++;
}

//Setting the element after the cursor
void List::setAfter(ListElement x)
{
	//Pre-Conditions
	if (!(position() < length()))
	{
		throw std::out_of_range("[ADT: List] [Function: setAfter()] [Reason: Cursor is at the back, cannot set backDummy]");
	}
	afterCursor->data = x;
}

//Setting the element before the cursor
void List::setBefore(ListElement x)
{
        //Pre-Conditions
        if (!(position() > 0))
        {
                throw std::out_of_range("[ADT: List] [Function: setBefore()] [Reason: Cursor is at the front, cannot set frontDummy]");
        }
        beforeCursor->data = x;
}

//Erasing the element after the cursor
void List::eraseAfter()
{
        //Pre-Conditions
        if (!(position() < length()))
        {
                throw std::out_of_range("[ADT: List] [Function: eraseAfter()] [Reason: Cursor is at the back, cannot delete backDummy]");
        }
	Node* n = afterCursor;
        afterCursor->next->prev = beforeCursor;
        beforeCursor->next = afterCursor->next;
        afterCursor = beforeCursor->next;
        num_elements--;
        delete n;
}

//Erasing the element before the cursor
void List::eraseBefore()
{

	//Pre-Conditions
	if (!(position() > 0))
        {
                throw std::out_of_range("[ADT: List] [Function: eraseBefore()] [Reason: Cursor is at the front, cannot delete frontDummy]");
        }

	Node* n = beforeCursor;
	beforeCursor->prev->next = afterCursor;
	afterCursor->prev = beforeCursor->prev;
	beforeCursor = beforeCursor->prev;
	num_elements--;
	cursorPos--;
	delete n;
}

//---= Other Functions =---

//Finding an element in front of cursor
int List::findNext(ListElement x)
{
	while (cursorPos < length())
	{
		if (moveNext() == x)
		{
			return cursorPos;
		}
	}
	cursorPos = length();
	return -1;
}

//Finding an element in previous of cursor
int List::findPrev(ListElement x)
{
	while (cursorPos > 0)
	{
		if (movePrev() == x)
		{
			return cursorPos;
		}
	}
	cursorPos = 0;
	return -1;
}

//Cleaning up duplicate elements
void List::cleanup()
{
	int ogCursorPos = position();

	moveFront();
	for (Node* n = frontDummy->next; n != backDummy; n = n->next)
	{
		moveNext();
		while (findNext(n->data) != -1)
		{
			eraseBefore();
			if (position() < ogCursorPos)
			{
				ogCursorPos--;
			}
		}

		findPrev(n->data); 
		moveNext();
	}

	//Setting afterCursor and beforeCursor
	Node *n = frontDummy->next;
	for (int i = 0; i <= ogCursorPos; i++)
	{

		if (i == ogCursorPos)
		{
			afterCursor = n;
			beforeCursor = n->prev;
			break;
		}
		n = n->next;
	}
			
	cursorPos = ogCursorPos;	
}

//Concatenating two Lists
List List::concat(const List& l) const
{
	List concatL;
	Node* n = this->frontDummy->next;
	Node* m = l.frontDummy->next;

	while (n != this->backDummy)
	{
		concatL.insertBefore(n->data);
		n = n->next;
	}
	while (m != l.backDummy)
	{
		concatL.insertBefore(m->data);
		m = m->next;
	}
	concatL.moveFront();
	return concatL;
}


//---= Miscellaneous Functions =---

//Returning a string representation of a List
std::string List::to_string() const
{
	std::string s = "(";
	for (Node* n = frontDummy->next; n != backDummy; n = n->next)
	{
		if (n == backDummy->prev)
		{
			s += std::to_string(n->data) + ")";
		}
		else
		{
			s += std::to_string(n->data) + ", ";
		}
	}
	return s;
}

//Checking if two Lists are equal
bool List::equals(const List& l) const
{
	bool isEqual = false;
	Node* n = nullptr;
	Node* m = nullptr;

	isEqual = (length() == l.length());
	n = this->frontDummy->next;
	m = l.frontDummy->next;

	while (isEqual && n != nullptr)
	{
		isEqual = (n->data == m->data);
		n = n->next;
		m = m->next;
	}
	return isEqual;
}

//---= Overidden Operators =---

//Operator<<()
std::ostream& operator<< (std::ostream& stream, const List& l)
{
	return stream << l.List::to_string();
}

//Operator==()
bool operator== (const List& a, const List& b)
{
	return a.List::equals(b);
}

//Operator=()
List& List::operator= (const List& l)
{
	if (this != &l) //not self assignment
	{
		List temp = l;
		
		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(num_elements, temp.num_elements);
	}
	return *this;
}











