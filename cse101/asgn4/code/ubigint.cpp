// $Id: ubigint.cpp,v 1.4 2022-03-21 16:02:26-07 - - $

#include <cctype>
#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "debug.h"
#include "ubigint.h"

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

   //Making casts
   for (auto digit = that.rbegin(); digit != that.rend(); ++digit)
   {
	  //Might need to change this if statement. (idk if reverseIter returns an int)
      if (not isdigit (*digit)) {
         throw invalid_argument ("ubigint::ubigint(" + that + ")");
      }
	  //Putting the digit into the vector (does reverseIter return an int tho?)
	  uvalue.push_back(*digit - '0');
   }
}

//Addition
ubigint ubigint::operator+ (const ubigint& that) const {
    ubigint sum;
	ubigint biggerNum;
	ubigint smallerNum;
	//Checking which number is bigger in length
	if (uvalue.size() < that.uvalue.size())
	{
		biggerNum = that;
		smallerNum = this;
	}
	else
	{
		biggerNum = this;
		smallerNum = that;
	}

	//Looping through and adding each digit
	for (int thisDigit : biggerNum.uvalue)
	{
		for (int thatDigit : smallerNum.uvalue)
		{
			//Adding the digit
			int digitSum = thisDigit + thatDigit;
			
			//If there is a carry over
			if (digitSum >= 10)
			{
				int remainder = digitSum - 10;
				sum.uvalue.push_back(remainder);
				sum.uvalue.push_back(1);
			}

			//If there is no carry over
			else
			{
				sum.uvalue.push_back(digitSum);
			}
			//Is it sum.uvalue.push_back() ???
		}
	}
    DEBUGF ('u', *this << "+" << that);
    DEBUGF ('u', result);
	return sum;
}

//Subtraction
ubigint ubigint::operator- (const ubigint& that) const {
    if (*this < that) throw domain_error ("ubigint::operator-(a<b)");
   	ubigint difference;
	ubigint biggerNum = this;
	ubigint smallerNum = that;
	bool borrow = false;
	//Looping through and subtracting each digit
	for (int bigDigit: biggerNum.uvalue)
	{
		for (int smallDigit: smallerNum.uvalue)
		{
			//Checking if bigDigit was borrowed
			if (borrow == true)
			{
				bigDigit += -1;
				borrow = false;
			}
			//If there is a borrow
			if (bigDigit < smallDigit)
			{
				borrow = true;
				bigDigit += 10;
			}

			//Subtracting the digit
			int digitDiff = bigDigit - smallDigit;

			//Adding digit to difference
			difference.uvalue.push_back(digitDiff);
		}
	}

	//Making sure there are no leading 0s
	for (int digitDiff: difference.uvalue)
	{
		if (digitDiff != 0)
		{
			break;
		}
		else
		{
			difference.uvalue.pop_back();
		}
	}

	//returning
	return difference;
}

//Multiplication
ubigint ubigint::operator* (const ubigint& that) const {
	//Creating the product
	std::vector<int> productVec(uvalue.size() * that.uvalue.size());
	ubigint product;
	product.uvalue = productVec;

	for (int thisIter = 0; thisIter < uvalue.size(); ++thisIter)
	{
		int carry = 0;
		for (int thatIter = 0; thatIter < that.uvalue.size(); ++thatIter)
		{
			int digit = product.uvalue[thisIter + thatIter] + uvalue[thisIter] * that->uvalue[thatIter] + carry;
			product.uvalue[thisIter + thatIter] = digit % 10;
			carry = digit / 10;
		}
		product.uvalue[thisIter + that.uvalue.size()] = carry;
	}
	return product;
}

//Multiplying by 2
void ubigint::multiply_by_2() {
	unsigned long carry = 0;
	for (auto digit = uvalue.begin() digit != uvalue.end(); ++digit)
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
			ccarry = 5;
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
	
   return udivide (*this, that).quotient;
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

//Print
void ubigint::print() const {
   DEBUGF ('p', this << " -> " << *this);
   cout << uvalue;
}

