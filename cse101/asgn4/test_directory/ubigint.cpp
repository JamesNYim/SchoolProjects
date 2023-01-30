// $Id: ubigint.cpp,v 1.4 2022-03-21 16:02:26-07 - - $

#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "util.h"
#include "debug.h"
#include "ubigint.h"

//Remove Zeros Function
void ubigint::removeZeros()
{
	while (uvalue.size() > 0 && uvalue.back() == 0)
	{
		uvalue.pop_back();
	}
}

ostream& operator<< (ostream& out, const vector<uint8_t>& vec) {
   for (auto itor = vec.rbegin(); itor != vec.rend(); ++itor) {
      out << int (*itor);
   }
   return out;
}

ostream& operator<< (ostream& out, const ubigint& that) { 
   return out << "ubigint(" << that.uvalue << ")";
}

//Constructor w/ a long
ubigint::ubigint (unsigned long that): uvalue (that) {
    DEBUGF ('~', this << " -> " << uvalue)
	uvalue.push_back(that % 10);
	for (unsigned long thatIter = 10; thatIter <= that; thatIter *= 10)
	{
		uvalue.push_back(that / thatIter % 10);
	}
}

//Constructor w/ a string
ubigint::ubigint (const string& that): uvalue(0) {
   DEBUGF ('~', "that = \"" << that << "\"");

   //This for loop starts at the last index of "that" and iterates to the first index
   for (auto digit = that.rbegin(); digit != that.rend(); ++digit)
   {
      //Checking if its a valid digit
      if (not isdigit (*digit)) {
         throw invalid_argument ("ubigint::ubigint(" + that + ")");
      }
      	  //Putting the digit in the vec
	  uvalue.push_back(*digit - '0');
   }
}

//Addition
ubigint ubigint::operator+ (const ubigint& that) const {
    ubigint sum;

	unsigned char carry;
	unsigned int currentDigit = 0;
	//Looping through and adding
	//Loops through the bigger number
	for (; currentDigit < uvalue.size(); currentDigit++)
	{
		int digitSum = 0;
		//Checks if we should still be adding with other number
		if (currentDigit < that.uvalue.size())
		{
			digitSum = carry + uvalue[currentDigit] + that.uvalue[currentDigit];
		}
		//If we arent then just continue with current digit of `this` and carry
		else
		{
			digitSum = carry + uvalue[currentDigit];
		}

		carry = 0;
		
		//Checking if carry
		if (digitSum >= 10)
		{
			carry = 1;
			digitSum -= 10;
		}

		//Adding digit to sum vector
		sum.uvalue.push_back(digitSum);
	}

	//If rhs has more digits than lhs we still need to have those digits
	for (; currentDigit < that.uvalue.size(); currentDigit++)
	{
		sum.uvalue.push_back(carry + that.uvalue[currentDigit]);
		carry = 0;
	}

	//If there is a left over carry
	if (carry != 0)
	{
		sum.uvalue.push_back(carry);
	}
    DEBUGF ('u', *this << "+" << that);
    DEBUGF ('u', sum);
    
	//Removing leading zeros
	sum.removeZeros();
    
	return sum;
}

//Subtraction
ubigint ubigint::operator- (const ubigint& that) const {
    if (*this < that) throw domain_error ("ubigint::operator-(a<b)");
   	ubigint difference;

	unsigned char borrow;
	unsigned int currentDigit = 0;

	//Looping through and subtracting
	//Looping through the bigger number
	for (; currentDigit < uvalue.size(); currentDigit++)
	{
		int digitDifference = 0;
		//Checking if there is a digit in `that` that we can subtract
		if (currentDigit < that.uvalue.size())
		{
			digitDifference = uvalue[currentDigit] - that.uvalue[currentDigit] - borrow;
		}
		//If not just continue with the currentDigit and the borrow
		else
		{
			digitDifference = uvalue[currentDigit] - borrow;
		}

		borrow = 0;

		//Checking if carry
		if (digitDifference < 0)
		{
			borrow = 1;
			digitDifference += 10;
		}

		//Adding digitDiff to difference vector
		difference.uvalue.push_back(digitDifference);
	}
		
	//Removing leading zeros
	difference.removeZeros();
		
	return difference;
}

//Multiplication
ubigint ubigint::operator* (const ubigint& that) const {
	//Creating the product
	ubigvalue_t productVec(uvalue.size() * that.uvalue.size());
	ubigint product;
	product.uvalue = productVec;

	for (unsigned char thisIter = 0; thisIter < uvalue.size(); ++thisIter)
	{
		int carry = 0;
		for (unsigned char thatIter = 0; thatIter < that.uvalue.size(); ++thatIter)
		{
			int digit = product.uvalue[thisIter + thatIter] + uvalue[thisIter] * that.uvalue[thatIter] + carry;
			product.uvalue[thisIter + thatIter] = digit % 10;
			carry = digit / 10;
		}
		product.uvalue[thisIter + that.uvalue.size()] = carry;
	}
	product.removeZeros();
	return product;
}

//Multiplying by 2
void ubigint::multiply_by_2() {
	unsigned long carry = 0;
	for (auto digit = uvalue.begin(); digit != uvalue.end(); ++digit)
	{
		*digit = *digit * 2 + carry;
		carry = *digit / 10;
		*digit = *digit % 10;
	}
	if (carry != 0)
	{
		uvalue.push_back(carry);
	}
}

//Dividing by 2
void ubigint::divide_by_2() {

	unsigned long carry = 0;
	for (auto digit = uvalue.begin(); digit != uvalue.end(); ++digit)
	{
		auto digitNext = next(digit);
		if (digitNext < uvalue.end() && *digitNext % 2)
		{
			carry = 5;
		}
		*digit = *digit / 2 + carry;
		carry = 0;
	}
}


struct quo_rem { ubigint quotient; ubigint remainder; };
quo_rem udivide (const ubigint& dividend, const ubigint& divisor_) {
   // NOTE: udivide is a non-member function.
   ubigint divisor {divisor_};
   ubigint zero {0};
   if (divisor == zero) throw domain_error ("udivide by zero");
   ubigint power_of_2 {1};
   ubigint quotient {0};
   ubigint remainder {dividend}; // left operand, dividend
   while (divisor < remainder) {
      divisor.multiply_by_2();
      power_of_2.multiply_by_2();
   }
   while (power_of_2 > zero) {
      if (divisor <= remainder) {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divisor.divide_by_2();
      power_of_2.divide_by_2();
   }
   DEBUGF ('/', "quotient = " << quotient);
   DEBUGF ('/', "remainder = " << remainder);
   return {.quotient = quotient, .remainder = remainder};
}

//Division
ubigint ubigint::operator/ (const ubigint& that) const {
	
	if (that == 0)
	{
		throw ydc_error("Divide by 0");
	}
	
   ubigint quotient = udivide (*this, that).quotient;
   quotient.removeZeros();
   return quotient;
}

//Modulo
ubigint ubigint::operator% (const ubigint& that) const {
   return udivide (*this, that).remainder;
}

//Equals
bool ubigint::operator== (const ubigint& that) const {

    return uvalue == that.uvalue;
}

//Comparison
bool ubigint::operator< (const ubigint& that) const {
   return uvalue < that.uvalue;
}

//Printing with character limit
void ubigint::print(bool sign) const
{

        if (sign)
        {
                int charNum = 0;
		for (auto digit = uvalue.rbegin(); digit != uvalue.rend(); ++digit)
                {
                        if (charNum == 68)
                        {
                                cout << "\\" << endl;
                        }
                        cout << static_cast<int>(*digit);
                        charNum++;
                }
        }
        
	else
        {
                int charNum = 0;
		for (auto digit = uvalue.rbegin(); digit != uvalue.rend(); ++digit)
                {
                        if (charNum == 69)
                        {
                                cout << "\\" << endl;
                        }
                        cout << static_cast<int>(*digit);
                        charNum++;
                }
        }
}

//Print
void ubigint::print() const {
   DEBUGF ('p', this << " -> " << *this);
   cout << uvalue;
}

