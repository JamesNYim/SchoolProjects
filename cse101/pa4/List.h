//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// James Yim
// Cruz ID: jnyim
// #1798845
// CSE 101-01 Tantalo
// Programming Assignment 3
// List.h
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#pragma once

#include <stdbool.h>
#include <stdio.h>

//Generic Type 
typedef void* Type;

typedef struct ListObj* List;

//Constructors-Destructors

List newList(void); //Creates & Returns a new empty List

void freeList (List *listPointer); //Frees mem associated with listPointer

//Accessor Functions

int length(List L); //Returns the number of elements in L

int index(List L); //Returns index of current element if filled, else return -1

Type front(List L); //Returns the front element (PreCond: length() > 0)

Type back(List L); //Returns the back element (PreCond: length() > 0)

Type get(List L); //Returns the current element (PreCond: length() > 0, index() >= 0)

//Manipulation Procedures

void clear(List L); //Resets L to its original empty state

void set(List L, Type x); //Overwrites the cursor element with x (PreCond: length() > 0, index() >= 0)

void moveFront(List L); //if L isn't empty, sets the cursor to be at the front element, otherwise do nothing

void moveBack(List L); //if L isn't empty, sets the cursor to be at the back element, otherwise do nothing

void movePrev(List L); //if cursor is defined and not at front, move cursor one step toward the front of L; if cursor is defined and at front, the cursor becomes undefined, if cursor is undefined do nothing

void moveNext(List L); //if cursor is defined and not at back, move cursor one step toward the back of L; if cursor is defined and at back, cursor becomes undefined, if cursor is undefined do nothing

void prepend(List L, Type x); //inserts new element into L. If L is non-empty insertion takes place before front element

void append(List L, Type x); //inserts new element into L. If L is non-empty insertion takes place after back element

void insertBefore(List L, Type x); //insert new element before cursor (PreCond: length() > 0, index() >= 0)

void insertAfter(List L, Type x); //insert new element after cursor (PreCond: length() > 0, index() >= 0)

void deleteFront(List L); //Deletes the front element (PreCond: length() > 0)

void deleteBack(List L); //Deletes the back element (PreCond: length() > 0)

void delete(List L); //Deletes the cursor element, making cursor undefined (PreCond: length() > 0, index() >= 0)

//Other Operations

void printList(FILE *outFile, List L); //Prints to the file pointed to by out, string representation of L consisting of a space seperated by a sequence of integers with the front on left 

List concatList(List A, List B); //Returns a new List which is a concatenation of A and B. The cursor is in the new List is undefined, regardless of the states of the cursors in A and B. The states of A and B are unchanged.

