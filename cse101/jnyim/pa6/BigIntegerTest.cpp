#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"
#include "BigInteger.h"

using namespace std;

int main()
{
	/*
	//Testing constructor
	BigInteger n = BigInteger("-17632");
	std::cout << n << std::endl;
	//Testing Compare
	BigInteger m = BigInteger("-17932");
	int comparedInt = n.compare(m);
	std::cout << comparedInt << std::endl;

	//Testing Comparisons
	BigInteger one = BigInteger("1");
	BigInteger two = BigInteger("2");
	BigInteger oneV2 = BigInteger("1");
	
	//==
	if (oneV2 == one)
	{
		std::cout << "They equal" << std::endl;
	}
	else
	{
		std::cout << "they no equal" << std::endl;
	}
	//<
	if (one < two)
        {
                std::cout << "one < two" << std::endl;
        }
        else
        {
                std::cout << "one !< two" << std::endl;
        }
	//<
        if (one <= two)
        {
                std::cout << "one <= two" << std::endl;
        }
        else
        {
                std::cout << "one !<= two" << std::endl;
        }
	//Testing makeZero
	n.makeZero();
*/
	/*
	//Testing add
	BigInteger A = BigInteger("+111122223333");
    	BigInteger B = BigInteger("-111122223333");
    	A += B;
	std::cout << "A: " << A << std::endl;
    	std::cout<< "A.sign(): " << A.sign() << std::endl;
	*/

    	BigInteger A = BigInteger("-111122223333");
    	BigInteger B = BigInteger("-112122223333");
    	BigInteger D = BigInteger("1000000000");
    	A -= B;
	std::cout << "A.Sign(): " << A.sign() << std::endl;
	std::cout << "A: " << A << std::endl;
	std::cout << "D: " << D << std::endl;

	A.mult(B);




/*
	//Testing sub
	BigInteger a = BigInteger("-50");
	BigInteger b = BigInteger("-50");
	BigInteger diff = a.sub(b);
	std::cout << diff << std::endl;

	BigInteger test1 = BigInteger("12345");
	BigInteger test2 = BigInteger("54321");
	std::cout << test1 + test2 << std::endl;
*/



	return 0;
	
}



