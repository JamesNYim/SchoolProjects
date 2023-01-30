#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "List.h"


void deleteLength(void)
{
	List A = newList();

    prepend(A, 5);
    prepend(A, 65);
    prepend(A, 43);
    prepend(A, 2);
    prepend(A, 8);
    prepend(A, 1);
    moveFront(A);
    printList(stdout, A);
    deleteFront(A);
    printf("index(A): %d\n", index(A));
    printList(stdout, A);
    assert(index(A) == -1);
    moveBack(A);
    deleteFront(A);
    printf("Index After: %d\n", index(A));
    printList(stdout, A);
    //assert(index(A) != 3);



}


int main()
{
/*
	List list1 = newList();
	printList(stdout, list1);

	//appending element
	append(list1, 69);
	append(list1, 420);
	printList(stdout, list1);

	//prepending an element
	prepend(list1, 88);
	printList(stdout, list1);

	//moving cursor to back
	moveBack(list1);
	printList(stdout, list1);

	//moving cursor to front
	moveFront(list1);
	printList(stdout, list1);

	//moving the cursor to middle
	moveNext(list1);
	printList(stdout, list1);
	
	//Setting cursor data
	set(list1, 28);
	printList(stdout, list1);

	//Inserting before
	insertBefore(list1, 99);
	printList(stdout, list1);

	//Inserting after
	insertAfter(list1, 111);
	printList(stdout, list1);

	//Deleting cursor
	delete(list1);
	printList(stdout, list1);
*/
	deleteLength();
	return 0;
}





