#include <iostream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

using namespace std;

int main()
{
	//Creating a dictionary
	Dictionary d;
	
	//Adding entries
	d.setValue("a", 1);
	d.setValue("c", 3);
	d.setValue("b", 2);
	cout << d << endl;

	//Getting Val
	cout << "Val of c: " << d.getValue("c") << endl;

	//Copying the dictionary
	Dictionary h = d;
	cout << h << endl;
	
	//Seeing if two dictionaries are equal
	cout << d.equals(h) << endl;
	d.setValue("a", 4);
	cout << d.equals(h) << endl;
	//Clearing the Dictionary
	d.clear();
	cout << d << endl;

	//Testing Contains
	Dictionary l;
	if (l.contains("d"))
	{
		cout << "failed 1 contains" << endl;
	}
	else
	{
		cout << "passed 1 contains" << endl;
	}
	
	l.setValue("d", 1);
	if (!l.contains("d"))
        {
                cout << "failed 2 contains" << endl;
        }
        else
        {
                cout << "passed 2 contains" << endl;
        }

	cout << "end of test" << endl;

	return 0;
}
