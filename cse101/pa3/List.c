//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// James Yim
// Cruz ID: jnyim
// #1798845
// CSE 101-01 Tantalo
// Programming Assignment 3
// List.c
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include "List.h"
//----------= Structs =----------

//Private Node Type
typedef struct NodeObj* Node;


//Private NodeObj Type
typedef struct NodeObj
{
	int data;
	Node next;
	Node prev;
} NodeObj;

//Private ListObj Type
typedef struct ListObj
{
	Node front;
	Node back;
	Node cursor;
	int cursorIndex;
	int length;
} ListObj;

//----------= Constructors & Destructors =----------

//Creating a new Node
Node newNode(int data)
{
	Node n = malloc(sizeof(NodeObj));
	if (n == NULL) //Checking if a node was successfully allocated
	{
		//free(n);
		return n;
	}
	n->data = data;
	n->next = NULL;
	n->prev = NULL;
	return n;
}

//Freeing a node
void freeNode(Node *n)
{
	if (n != NULL && *n != NULL)
	{
		free(*n);
		*n = NULL;
	}
}

//Creating a new list
List newList(void)
{
	List l = malloc(sizeof(ListObj));
	if (l == NULL)
	{
		free(l);
		return l;
	}
	l->front = NULL;
	l->back = NULL;
	l->cursor = NULL;
	l->cursorIndex = -1;
	l->length = 0;
	return l;
}

//Freeing the list
void freeList(List *l)
{
	if (l != NULL && *l != NULL)
	{
		while (length(*l) > 0) //as long as the list has items
		{
			deleteBack(*l);
		}
		free(*l);
		*l = NULL;
	}
}

//----------= Accessor Functions =----------

//getting length
int length(List l)
{
	return l->length;
}

//getting cursor 
int index(List l)
{
	if (l->cursor == NULL)
	{
		return -1;
	}
	return l->cursorIndex;
}

//Getting the front element
int front(List l)
{
	//pre-conditions
	if (!(length(l) > 0)) //if the list is empty
	{
		fprintf(stderr, "PreCondition Error- [ADT: List] [Function: front()] [pre-cond: !length > 0]\n");
		exit(EXIT_FAILURE);
	}

	return l->front->data;
}

//Getting the back element
int back(List l)
{
	//pre-conditions
	if (!(length(l) > 0)) //if the list is empty
        {
                fprintf(stderr, "PreCondition Error- [ADT: List] [Function: back()] [pre-cond: !length > 0]\n");
                exit(EXIT_FAILURE);
        }

	return l->back->data;
}

//Getting the cursor element
int get(List l)
{
	if (!(length(l) > 0)) //if the list is empty
        {
                fprintf(stderr, "PreCondition Error- [ADT: List] [Function: get()] [pre-cond: !length > 0]\n");
		exit(EXIT_FAILURE);
        }

	if (!(index(l) >= 0)) //if the cursor is undefined
        {
                fprintf(stderr, "PreCondition Error- [ADT: List] [Function: get()] [pre-cond: !index >= 0]\n");
		exit(EXIT_FAILURE);
        }

	//Getting the cursor element
	int pos = 0;
	l->cursor = l->front;
	while (pos < l->cursorIndex)
	{
		l->cursor = l->cursor->next;
		pos++;
	}
	return l->cursor->data;
}

//Checking if two Lists are equal
bool equals(List a, List b)
{
	//If both lists are null
	if (a == NULL && b == NULL)
	{
		return true;
	}

	//If both lists are different sizes
	if (length(a) != length(b))
	{
		return false;
	}

	//Looping through the list and checking each node
	Node currentANode = a->front;
	Node currentBNode = b->front;
	for (int i = 0; i < length(a); i++)
	{
		if (currentANode->data != currentBNode->data)
		{
			return false;
		}
		currentANode = currentANode->next;
		currentBNode = currentBNode->next;
	}
	return true;
}

//----------= Manipulator Functions =----------

//Clearing A List
void clear(List l)
{
	//Looping through list and deleting
	for (int i = 0; i < length(l); i++)
	{
		deleteBack(l);
	}

	//Setting List to default values
	l->front = NULL;
	l->back = NULL;
	l->cursor = NULL;
	l->cursorIndex = -1;
	l->length = 0;
}

//Setting Cursor Element
void set(List l, int x)
{
	//Pre-Conditions
	if (!(length(l) > 0)) //If the list is empty
	{
		fprintf(stderr, "PreCondition Error- [ADT: List] [Function: set()] [pre-cond: !length > 0]\n");
		exit(EXIT_FAILURE);
	}

	 if (!(index(l) >= 0)) //If the cursor is uninitalized
        {
                fprintf(stderr, "PreCondition Error- [ADT: List] [Function: set()] [pre-cond: !index >= 0]\n");
		exit(EXIT_FAILURE);
        }

	//setting cursor element
	l->cursor->data = x;
}

//Moving the cursor to front
void moveFront(List l)
{
	//Pre-Conditions
        if (!(length(l) > 0)) //If the list is empty
        {
		return;
        }

	//setting cursor
	l->cursorIndex = 0;
	l->cursor = l->front;
}

//Moving the cursor to back
void moveBack(List l)
{
	//Pre-Conditions
        if (!(length(l) > 0)) //If the list is empty
        {
		return;
        }
	if (l->back == NULL)
	{
		return;
	}
	//setting cursor
        l->cursorIndex = length(l) - 1;
        l->cursor = l->back;

}

//Moving cursor to previous
void movePrev(List l)
{
	//Pre-Conditions
        if (l->cursor == NULL)
        {
                return;
        }

        if (l->cursor != NULL && l->cursorIndex == 0)
        {
                l->cursor = NULL;
                l->cursorIndex = -1;
                return;
        }
	//Moving cursor
	l->cursor = l->cursor->prev;
	l->cursorIndex--;
}

//Moving cursor to next
void moveNext(List l)
{
        //Pre-Conditions
        if (l->cursor == NULL) //if cursor is undefined
        {
                return;
        }

	if (l->cursor != NULL && l->cursorIndex == length(l) - 1) //if cursor is defined but at the back
        {
		l->cursor = NULL;
		l->cursorIndex = -1;
		return;
        }

        //Moving cursor
        l->cursor = l->cursor->next;
        l->cursorIndex++;
}

//Prepending an element
void prepend(List l, int x)
{
	Node new = newNode(x);
	if (length(l) == 0)
        {
                l->front = new;
                l->back = new;
                l->length++;
                return;
        }

	if (l->cursor != NULL)
	{
		l->cursorIndex++;
	}
	l->front->prev = new;
	new->next = l->front;
	l->front = new;
	l->length++;
}

//Appending an element
void append(List l, int x)
{
	if (l == NULL)
	{
		fprintf(stderr, "PreCondition Error- [ADT; List] [Function: append()] [pre-cond: l == nNULL]\n");
	}
	Node new = newNode(x);
        if (length(l) == 0)
	{
		l->front = new;
		l->back = new;
		l->length++;
		return;
	}
       	l->back->next = new;
        new->prev = l->back;
        l->back = new;
        l->length++;

}

//Inserting before cursor
void insertBefore(List l, int x)
{
	//Pre-Conditions
	if (!(length(l) > 0))
	{
		fprintf(stderr, "PreCondition Error- [ADT: List] [Function: insertBefore()] [pre-cond: !length() > 0]\n");
		exit(EXIT_FAILURE);
	}
	
	if (!(index(l) >= 0))
	{
		fprintf(stderr, "PreCondition Error- [ADT; List] [Function: insertBefore()] [pre-cond: !index() >= 0]\n");
		exit(EXIT_FAILURE);
	}


	Node new = newNode(x);
	//Inserting when cursor is at front
	if (l->front == l->cursor)
	{
		new->next = l->cursor;
		new->prev = NULL;
		l->front->prev = new;
		l->front = new;
	}

	//inserting cursor
	else
	{
		new->next = l->cursor;
		new->prev = l->cursor->prev;
		l->cursor->prev->next = new;
		l->cursor->prev = new;
	}

	//incrimenting
	l->length++;
	l->cursorIndex++;
}

//Inserting after cursor
void insertAfter(List l, int x)
{
        //Pre-Conditions
        if (!(length(l) > 0))
        {
                fprintf(stderr, "PreCondition Error- [ADT: List] [Function: insertAfter()] [pre-cond: !length() > 0]\n");
		exit(EXIT_FAILURE);
        }

        if (!(index(l) >= 0))
        {
                fprintf(stderr, "PreCondition Error- [ADT; List] [Function: insertAfter()] [pre-cond: !index() >= 0]\n");
		exit(EXIT_FAILURE);
        }


        Node new = newNode(x);
        //Inserting when cursor is at back
        if (l->back == l->cursor)
        {
                new->prev = l->cursor;
                new->next = NULL;
                l->cursor->next = new;
                l->back = new;
        }

        //inserting cursor
        else
        {
                new->prev = l->cursor;
                new->next = l->cursor->next;
                l->cursor->next->prev = new;
                l->cursor->next = new;
        }

        //incrimenting
        l->length++;
}

//Deleting the front
void deleteFront(List l)
{
	//Pre-Conditions
	if (!(length(l) > 0))
	{
		fprintf(stderr, "PreCondition Error- [ADT: List] [Function: deleteFront()] [pre-cond: !length() > 0)\n");
		exit(EXIT_FAILURE);
	}

	if (l->cursor == l->front)
	{
		l->cursorIndex = -1;
	}
	else
	{

		if (l->cursor != NULL)
		{
			l->cursorIndex--;
		}
	}
	//Deleting the node
	Node deletedNode = l->front;
	l->front = l->front->next;
	l->length--;
	freeNode(&deletedNode);
}

//Deleting the back
void deleteBack(List l)
{
        //Pre-Conditions
        if (!(length(l) > 0))
        {
                fprintf(stderr, "PreCondition Error- [ADT: List] [Function: deleteBack()] [pre-cond: !length() > 0)\n");
		exit(EXIT_FAILURE);
        }

	if (l->cursor == l->back)
	{
		l->cursorIndex = -1;
	}

        //Deleting the node
        Node deletedNode = l->back;
        l->back = l->back->prev;
        l->length--;
        freeNode(&deletedNode);

	
}

//Deleting the cursor
void delete(List l)
{
	//Pre-Conditions
	if (!(length(l) > 0))
        {
                fprintf(stderr, "PreCondition Error- [ADT: List] [Function: delete()] [pre-cond: !length() > 0)\n");
		exit(EXIT_FAILURE);
        }
	if (!(index(l) >= 0))
        {
                fprintf(stderr, "PreCondition Error- [ADT: List] [Function: delete()] [pre-cond: !index() >= 0)\n");
		exit(EXIT_FAILURE);
        }
	
	if (l->cursor == l->back)
	{
		deleteBack(l);
		return;
	}
	if (l->cursor == l->front)
	{
		deleteFront(l);
		return;
	}
	//Deleting the node
	//Node deletedNode = l->cursor;
	l->cursor->next->prev = l->cursor->prev;
	l->cursor->prev->next = l->cursor->next;
	l->cursorIndex = -1;
	freeNode(&(l->cursor));
	//freeNode(&deletedNode);
	l->length--;

}

//Printing the List

void printList(FILE *outFile, List l)
{
	if (l == NULL)
	{
		return;
	}
	Node currentNode = l->front;
        for (int i = 0; i < length(l); i++)
        {
                fprintf(outFile, "%d ", currentNode->data);
                currentNode = currentNode->next;
        }
}

//Copying a list
List copyList(List l)
{
	List newL = newList();
	Node currentNode = l->front;
	for (int i = 0; i < length(l); i++)
	{
		append(newL, currentNode->data);
		currentNode = currentNode->next;
	}
	return newL;
}

		



















	









