// $Id: bigint.cpp,v 1.2 2021-12-28 14:11:26-08 - - $

#include <cstdlib>
#include <exception>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"

//Constructor w/ Long
bigint::bigint (long that)
    : uvalue (that), is_negative (that < 0)
{
   DEBUGF ('~', this << " -> " << uvalue)
}

//Constructor w/ ubigint
bigint::bigint (const ubigint& uvalue_, bool is_negative_)
    : uvalue(uvalue_), is_negative(is_negative_)
{ }

//Constructor w/ uvalue
bigint::bigint (ubigint&& uvalue_, bool is_negative_)
    : uvalue(std::move(uvalue_)), is_negative(is_negative_)
{ }

//Constructor w/ String
bigint::bigint (const string& that) {
   is_negative = that.size() > 0 and that[0] == '_';
   uvalue = ubigint (that.substr (is_negative ? 1 : 0));
}

//Positive
bigint bigint::operator+ () const {
   return *this;
}

//Negative
bigint bigint::operator- () const {
   return {uvalue, not is_negative};
}

//Addition
bigint bigint::operator+ (const bigint& that) const {
   ubigint result;
   bool sign = false;

   //If both same sign
   if (is_negative == that.is_negative)
   {
	   result = uvalue + that.uvalue;
	   sign = is_negative;
   }
   //if not same sign
   else
   {
	   bool thisGreater = uvalue > that.uvalue;

       //Making sure the left is bigger than right
	   auto resultOne = uvalue - that.uvalue;
	   auto resultTwo = that.uvalue - uvalue;
	   if (thisGreater)
	   {
		   result = resultOne;
	   }
	   else
	   {
		   result = resultTwo;
	   }
	   
	   //Setting the sign
	   if (thisGreater)
	   {
		   sign = is_negative;
	   }
	   else
	   {
		   sign = that.is_negative;
	   }
   }
   return bigint(result, sign);
}

//Subtracting
bigint bigint::operator- (const bigint& that) const {
	ubigint result;
	bool sign = false;

	//If both same sign
	if (is_negative == that.is_negative)
	{
		bool thisGreater = uvalue > that.uvalue;
		
		//If left > right
		if (thisGreater)
		{
			result = uvalue - that.uvalue;
			sign = is_negative;
		}
		//if right > left
		else
		{
			result = that.uvalue - uvalue;
			if (result == 0)
			{
				sign = false;
			}
			else
			{
				sign = !that.is_negative;
			}
		}
	}
	//If not same sign
	else
	{
		result = uvalue + that.uvalue;
		sign = is_negative;
	}
	return bigint(result, sign);
}

//Multiplying
bigint bigint::operator* (const bigint& that) const {
   bool sign = !(is_negative == that.is_negative);
   ubigint result = uvalue * that.uvalue; 
   return bigint(result, sign);
}

//Dividing 
bigint bigint::operator/ (const bigint& that) const {
   bool sign = !(is_negative == that.is_negative);
   ubigint result = uvalue / that.uvalue;
   return bigint(result, sign);
}

//Modulus
bigint bigint::operator% (const bigint& that) const {
   bool sign = false;
   ubigint result = uvalue % that.uvalue;
   return bigint(result, sign);
}

//equals equals
bool bigint::operator== (const bigint& that) const {
   return is_negative == that.is_negative and uvalue == that.uvalue;
}

//Comparison
bool bigint::operator< (const bigint& that) const {
   if (is_negative != that.is_negative) return is_negative;
   return is_negative ? uvalue > that.uvalue
                      : uvalue < that.uvalue;
}

//Printing
void bigint::print() const {
   DEBUGF ('p', this << " -> " << *this);
   if (is_negative) cout << "-";
   uvalue.print(is_negative);
}

//Insertion
ostream& operator<< (ostream& out, const bigint& that) {
   return out << "bigint(" << (that.is_negative ? "-" : "+")
              << "," << that.uvalue << ")";
}

