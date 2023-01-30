//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// James Yim
// Cruz ID: jnyim
// #1798845
// CSE 101-01 Tantalo
// Programming Assignment 6
// ListTest.cpp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"

using namespace std;

int main()
{

	/*
	List l;

	//Inserting After
	
	
	l.insertAfter(4);
	l.insertAfter(5);
	l.insertAfter(7);
	l.insertAfter(12);
	l.insertAfter(69);
	//printf("length(): %d\n", l.length());

	//Inserting After
	l.insertBefore(1);
	//printf("length(): %d\n", l.length());


	//movingNext()
	//printf("moveNext(): %d\n", l.moveNext());

	//Erasing Before
	l.eraseBefore();
	//printf("length(): %d\n", l.length());

	List A;
	List B;
	List C;
    	A.insertAfter(1);
    	A.insertAfter(2);
    	A.insertAfter(3);
    	B.insertAfter(4);
    	B.insertAfter(5);
    	B.insertAfter(6);

    	C = A.concat(B);
	//std::cout << "Length of C: " << C.length() << endl;


	List a;
    	a.insertBefore(1);
     	a.insertBefore(2);
    	a.insertBefore(3);
    	a.insertBefore(3);
    	a.insertBefore(5);
	a.insertBefore(6);
	a.insertBefore(3);
	//std::cout << "Before Cleanup: " << a << endl;
	a.cleanup();
	//std::cout << "After Cleanup: " << a << endl;

	std::cout << "------------------------------\n";
	List L;
    	int n = 5;
    	for (int i = 0; i <= n; i++) {
        L.insertAfter(i);
    	}
    	//std::cout << "L:" << L << std::endl;

	List F;
	F.insertBefore(1);
    	F.insertBefore(2);
    	F.insertBefore(2);
    	F.insertBefore(1);
    	F.insertBefore(2);
    	F.insertBefore(3);
    	F.insertBefore(1);
    	F.findPrev(3);
	//std::cout << "Before Cleanup: " << F << endl;
	//std::cout << "Position() before cleanup: " << F.position() << std::endl;
    	F.cleanup();
	//std::cout << "After Cleanup: " << F << endl;
	//std::cout << "Position() after cleanup: " << F.position() << std::endl;

	List k;
	k.insertBefore(1);
    	k.insertBefore(1);
   	k.insertBefore(2);
    	k.insertBefore(3);
    	k.insertBefore(3);
	k.movePrev();
	k.movePrev();
	k.moveFront();
	k.moveNext();
	k.moveBack();
	std::cout << "k: " << k << endl;
	std::cout << "k pos before: " << k.position() << endl;

	k.cleanup();
	std::cout << "k after cleanup: " << k << endl;
	std::cout << "k pos after: " << k.position() << endl;
	*/
	List A;
	A.insertBefore(1);
    	A.insertBefore(5);
    	A.insertBefore(22);
    	A.insertBefore(176);
    	A.insertBefore(3215);
	std::cout << A << std::endl;
    	A.movePrev();
	std::cout << "1st movePrev(): " << A.movePrev() << " (176) " << std::endl;


    	A.eraseAfter();
    	A.eraseAfter();
    	A.movePrev();
    	A.movePrev();
	std::cout << "2nd movePrev(): " << A.movePrev() << " (1) " << std::endl;


    	A.moveBack();
    	std::cout << "3rd movePrev(): " << A.movePrev() << " (22) " << std::endl;


	return 0;
}

