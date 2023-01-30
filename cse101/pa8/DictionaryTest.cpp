#include <iostream>
#include "Dictionary.h"

int main()
{
	Dictionary A;
	A.setValue("d", 1);
    A.setValue("b", 5);
    A.setValue("a", 10);
    A.setValue("c", 15);
    A.setValue("f", 20);
    A.setValue("e", 25);
    A.setValue("g", 30);
    A.begin();
    A.remove("a");
    A.end();
    A.remove("d");
    std::string ideal2 = "e\nb\nc\nf\ng\n";
	std::cout << ideal2 << std::endl;
	std::cout << A.pre_string() << std::endl;

	Dictionary B;
	B.setValue("c", 3);
	B.setValue("a", 1);
	B.setValue("b", 2);
	A.remove("a");
	return 0;
}
