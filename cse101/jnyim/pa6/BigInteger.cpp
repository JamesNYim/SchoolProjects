//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// James Yim
// Cruz ID: jnyim
// #1798845
// CSE 101-01 Tantalo
// Programming Assignment 6
// BigInteger.cpp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <stdexcept>
#include "List.h"
#include "BigInteger.h"

using namespace std;


//Defininitions


#define BASE 1000000000
#define POWER 9

//---= Constructors & Destructors =---

//Constructing an empty Big Number
BigInteger::BigInteger()
{
	signum = 0;
}
//Constructing the Big Number
BigInteger::BigInteger(std::string s)
{
	//Checking if the input string is empty
	if (s == "")
	{
		throw std::invalid_argument("BigInteger: Constructor: empty string");
	}
	
	//Checking if the input string is not a number
	std::size_t notNumber = s.find_first_not_of("+-0123456789");
	if (notNumber != std::string::npos)
	{
		throw std::invalid_argument("BigInteger: Constructor: non-numeric string");

	}

	//Getting the sign of the number
	if (s[0] == '-')
	{
		signum = -1;
	}
	else if (s[0] == 0)
	{
		signum = 0;
		return;
	}
	else
	{
		signum = 1;
	}
	
	//Getting the number from the string
	size_t startingIndex = 0;
	int sizeOfFirst = 0;
	//Checking if there is a sign
	if (s[0] == '+' || s[0] == '-')
	{
		startingIndex = 1;
		sizeOfFirst = (s.size() - 1) % POWER;

	}
	else
	{
		sizeOfFirst = s.size() % POWER;
	}

	//Looping through getting number
	for (size_t i = startingIndex; i < s.size() - 1; i = i)

	{
		std::string nodeValue;
		if (digits.length() == 0 && sizeOfFirst != 0)
		{
			nodeValue = s.substr(i, sizeOfFirst);
			i += sizeOfFirst;
		}
		else
		{
			nodeValue = s.substr(i, POWER);
			i += POWER;
		}
		digits.insertBefore(stol(nodeValue));
	}
	
	//Getting rid of leading zeros
	digits.moveFront();
	while (digits.position() < digits.length())
	{
		if (digits.moveNext() == 0)
		{
			digits.eraseBefore();
		}
		else
		{
			break;
		}
	}
}		

//Copying a Big Number

BigInteger::BigInteger(const BigInteger& n)

{
	signum = n.signum;
	digits = n.digits;
}

//Deleting a Big Number

//---= Accessor Functions =---

//Getting the sign of the number
int BigInteger::sign() const
{
	return signum;
}

//Comparing two numbers
int BigInteger::compare(const BigInteger& n) const
{
	//Checking signs
	if (this->signum < n.signum)
	{
		return -1;
	}
	else if (this->signum > n.signum)
	{
		return 1;
	}
	
	//Checking the lengths
	if (this->signum == -1 && n.signum == -1) 
	{
		if (this->digits.length() > n.digits.length())
		{
			return -1;
		}
		else if (this->digits.length() < n.digits.length())
		{
			return 1;
		}
	}
	else if (this->signum == 1 && n.signum == 1)
	{
		if (this->digits.length() > n.digits.length())
                {
                        return 1;
                }
                else if (this->digits.length() < n.digits.length())
                {
                        return -1;
                }
	}

	//Looping through if both signs and length are same
	int compareInt = 0;
	List thisDigits = this->digits;
	List nDigits = n.digits;

	thisDigits.moveFront();
	nDigits.moveFront();

	while (thisDigits.position() < thisDigits.length())
	{
		ListElement thisDigitsVal = thisDigits.moveNext();
		ListElement nDigitsVal = nDigits.moveNext();

		if (thisDigitsVal > nDigitsVal)
		{
			compareInt = 1;
			thisDigits.moveBack();
			nDigits.moveBack();
		}
		else if (thisDigitsVal < nDigitsVal)
		{
			compareInt = -1;
			thisDigits.moveBack();
                        nDigits.moveBack();
		}
	}
	//Checking if its negative
	if (this->signum == -1)
	{
		compareInt *= -1;
	}

	return compareInt;
}

//---= Manipulation Functions =---

//Making the Big Number 0
void BigInteger::makeZero()
{
	signum = 0;
	digits.clear();
}

//Negating the Big Number
void BigInteger::negate()
{
	signum *= -1;
}

//---= BigInteger Arithmetic Helper Functions =---

//negateList()
//Changing the sign of each integer in a list 
//Used in sub()
void negateList (List& l)
{
	l.moveFront();
	while (l.position() < l.length())
	{
		ListElement val = l.moveNext();
		l.setBefore(-val); 
	}
}

//sumList()
//Overwrites the state of C = A + sgn*B
//Used in sub() and sum()
void sumList (List& C, List A, List B, int sign)
{
	//Making sure that C is empty
	if (C.length() > 0)
	{
		C.clear();
	}

	A.moveBack();
        B.moveBack();
	long currentSum = 0;
	while (A.position() > 0 || B.position() > 0)
	{
		if (sign == 1)
		{
			if (B.position() == 0)
			{
				currentSum = A.movePrev();
			}
			else if (A.position() == 0)
			{
				currentSum = B.movePrev();
			}
			else
			{
				currentSum = A.movePrev() + B.movePrev();
			}
		}
		else if (sign == -1)
		{
			if (B.position() == 0)
			{
				currentSum = A.movePrev();
			}
			else if (A.position() == 0)
			{
				currentSum = -B.movePrev();
			}
			else
			{
				currentSum = A.movePrev() - B.movePrev();
			}
		}
		C.insertAfter(currentSum);
	}
}

// normalizeList()
// Performs carries from right to left (least to most significant
// digits), then returns the sign of the resulting integer. Used
// by add(), sub() and mult().
void normalizeList(List& L)
{
	//Normalizing
        List normList;
	long carryOver = 0;
        long newVal = 0;
        long currentVal = 0;
        L.moveBack();
        while (L.position() > 0)
        {
                currentVal = L.movePrev();
                newVal = currentVal % BASE;
                newVal += carryOver;
                normList.insertAfter(newVal);
                carryOver = currentVal / BASE;
        }
        if (carryOver > 0)
        {
                normList.insertAfter(carryOver);
        }
        L = normList;
}

// shiftList()
// Prepends p zero digits to L, multiplying L by base^p. Used by mult().
void shiftList(List& L, int p)
{
	L.moveBack();
	for (int i = 0; i < p; i++)
	{
		L.insertAfter(0);
	}
}

// scalarMultList()
// Multiplies L (considered as a vector) by m. Used by mult().
void scalarMultList(List& L, ListElement m)
{
	List productList;
	L.moveFront();
	while (L.position() < L.length())
	{
		ListElement val = L.moveNext();
		ListElement valProduct = val * m;
		productList.insertBefore(valProduct);
	}
	L = productList;
}

//---= BigInteger Arithmetic Functions =---

//Adding two BigIntegers
//Still need to figure out having two different signs and lenghts
BigInteger BigInteger::add(const BigInteger& n) const
{
	//Copying Lists
	List thisDigits = this->digits;
	List nDigits = n.digits;
	
	//Checking the signs
	int nSign = n.signum;
	int thisSign = this->signum;
	
	//Making BigInt copies
	BigInteger thisInt = *this;
	BigInteger nInt = n;

	//Intializing BigInteger
	BigInteger sum;
	
	//Adding Lists
	List listSum;
	//If Signs are the same
	if (nSign == thisSign)
	{
		sum.signum = thisSign;
		sumList(listSum, thisDigits, nDigits, 1);
	}

	//The signs are different
	else
	{
		if (thisInt.signum == -1)
		{
			thisInt.negate();
		}
		else
		{
			nInt.negate();
		}
		int biggerAbs = thisInt.compare(nInt);
		if (biggerAbs == 0)
                {
                        BigInteger zero;
			zero.signum = 0;
                        return zero;
                }

		//Figuring out which one has the bigger absolute value
		if (biggerAbs == 1)
		{
			sum.signum = thisSign;
			sumList(listSum, thisDigits, nDigits, -1);
		}
		else
		{
			sum.signum = nSign;
			sumList(listSum, nDigits, thisDigits, -1);
		}
	}

	//Normalzing List
	normalizeList(listSum);
	
	//Setting list 
	sum.digits = listSum;

	return sum;
}

//Subtracting two BigIntegers
//using for helper function testing
BigInteger BigInteger::sub(const BigInteger& n) const
{
	//Copying Lists
	List thisDigits = this->digits;
	List nDigits = n.digits;

	//Copying Big Integers
	BigInteger thisNum = *this;
	BigInteger nNum = n;

	//Checking the signs
	int thisSign = this->signum;
	int nSign = n.signum;
	bool diffSign = false;
	if (thisSign != nSign)
	{
		diffSign = true;
	}
	//Subtracting Lists
	List listDifference;
	int signDifference = 0;
	BigInteger difference;
	
	//Comparing numbers
	thisNum.signum = 1;
	nNum.signum = 1;
	int numCompare = thisNum.compare(nNum);

	//If sign is the same
	if (diffSign == false)
	{
		if (numCompare == 1)
		{
			signDifference = 1;
			sumList(listDifference, thisDigits, nDigits, -1);
		}
		else if (numCompare == -1)
		{
			signDifference = -1;
			sumList(listDifference, nDigits, thisDigits, -1);
		}
		else
		{
			return difference;
		}
	}

	//If sign is difference
	if (diffSign == true)
	{
		signDifference = thisSign;
		if (numCompare == 1)
                {
                        sumList(listDifference, thisDigits, nDigits, 1);
                }
                else if (numCompare == -1)
                {
                        sumList(listDifference, nDigits, thisDigits, 1);
                }
                else
                {
			sumList(listDifference, nDigits, thisDigits, 1);
                }
	}
	
	//Setting BigInteger
	difference.signum = signDifference;
	difference.digits = listDifference;
	return difference;
}

//Multiplying two Big Integers
BigInteger BigInteger::mult(const BigInteger& n) const
{
	//Intializing Product Big Int
	BigInteger product;

	//Copying Big Integers
	BigInteger thisInt = *this;
	BigInteger nInt = n;

	//Signs
	if (thisInt.signum == -1 || n.signum == -1)
	{
		product.signum = -1;
	}
	else if (thisInt.signum == 0 || n.signum == 0)
	{
		return product;
	}
	else
	{
		product.signum = 1;
	}

	return *this;

}
//---= Other Functions =---

//to_string()
std::string BigInteger::to_string()
{
	List thisDigits = this->digits;
	std::string s = "";
	if (this->signum == 0)
	{
		return "0";
	}
	if (this->signum == -1)
	{
		s += "-";
	}
	thisDigits.moveFront();
	while (thisDigits.position() < thisDigits.length())
	{
		s += std::to_string(thisDigits.moveNext());
	}
	return s;
}


//---= Overriden Operators =----

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N )
{
	return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B.
bool operator==( const BigInteger& A, const BigInteger& B )
{
	if (A.compare(B) == 0)
	{
		return true;
	}
	return false;
}

// operator<()
// Returns true if and only if A is less than B.
bool operator<( const BigInteger& A, const BigInteger& B )
{
	if (A.compare(B) < 0)
        {
                return true;
        }
        return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B.
bool operator<=( const BigInteger& A, const BigInteger& B )
{
	if (A.compare(B) <= 0)
        {
                return true;
        }
        return false;
}

// operator>()
// Returns true if and only if A is greater than B.
bool operator>( const BigInteger& A, const BigInteger& B )
{
	if (A.compare(B) > 0)
        {
                return true;
        }
        return false;
}
// operator>=()
// Returns true if and only if A is greater than or equal to B.
bool operator>=( const BigInteger& A, const BigInteger& B )
{
	if (A.compare(B) >= 0)
        {
                return true;
        }
        return false;
}

// operator+()
// Returns the sum A+B.
BigInteger operator+( const BigInteger& A, const BigInteger& B )
{
	return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B.
BigInteger operator+=( BigInteger& A, const BigInteger& B )
{
	A = A.add(B);
	return A;
}

// operator-()
// Returns the difference A-B.
BigInteger operator-( const BigInteger& A, const BigInteger& B )
{
	return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B.
BigInteger operator-=( BigInteger& A, const BigInteger& B )
{
	A = A.sub(B);
	return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B )
{
	return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B )
{
	A = A.mult(B);
	return A;
}






