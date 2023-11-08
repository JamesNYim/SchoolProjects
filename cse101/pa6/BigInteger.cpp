#include "BigInteger.h"
#include "List.h"

#include <cctype>
#include <cmath>
#include <stdexcept>

using namespace std;

const ListElement BASE  = 1000000000;  // 10^(power)
const int         POWER = 9;           // log_10(base)

// -=Helper Functions=-

// Remove leading zeros
void delZero( List* L) 
{
    L->moveFront();
    while (L->length() > 0 && !L->peekNext()) 
	{
        L->eraseAfter();
    }
}

List tempMult(long s, List *b, int* ctr) 
{
    List L;
    long carry = 0;
    long temp = 0;
    for (b->moveBack(); b->position() > 0; b->movePrev()) 
	{
        temp = (b->peekPrev() * s) + carry;
        carry = temp / BASE;
        temp %= BASE;
        L.insertAfter(temp);
    }
    if (carry > 0) 
	{
        L.insertAfter(carry);
    }
    L.moveBack();
    for (int i = 0; i < *ctr; i++) 
	{
        L.insertAfter(0);
    }
    return L;
}

// -= Constructors =-

// Blank Constructor
BigInteger::BigInteger() 
{
    signum = 0;
    digits = List();
}

// Long Constructor
BigInteger::BigInteger(long x) 
{
    // Handle zero separately
    if (x == 0) 
	{
        signum = 0;
        digits.insertAfter(0);
        return;
    }
    // Handle negative numbers
    if (x < 0) 
	{
        signum = -1;
        x = -x;
    } 
	else 
	{
        signum = 1;
    }
    // Extract digits from the long value
    while (x > 0) 
	{
        digits.insertBefore(x % BASE);
        x /= BASE;
    }
}

// String Constructor
BigInteger::BigInteger(string s) 
{
	// If there is an empty string
    if (!s.length()) 
	{
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    
	// Checking and setting sign
	int offset = 0;
    if ((s[0] == '+') | (s[0] == '-')) 
	{
        signum = 1;
        if (s[0] == '-') 
		{
            signum = -1;
        }
        offset = 1;
        s = s.substr(offset, s.length() - 1);
    } 
	else 
	{
        signum = 1;
    }

	// Checking if string is a valid number
	for (long unsigned int i = 0; i < s.length(); ++i)
	{
		if (!isdigit(s[i]))
		{
			throw invalid_argument("BigInteger string constructor is non-numeric");
		}
	}

    std::string num = "";
    List L;
    size_t max = 0;
    size_t currentDigits = s.length();

    // Divide the input string into chunks of POWER digits and convert each chunk to a number
    while (max < s.length() / POWER) 
	{
        num = s.substr(currentDigits - POWER, POWER);
        digits.insertAfter(std::stol(num, nullptr, 10));
        currentDigits = currentDigits - POWER;
        max++;
    }

    // If there are remaining digits, convert them to a number and insert them
    if (currentDigits > 0) {
        num = s.substr(0, currentDigits);
        digits.insertAfter(std::stol(num, nullptr, 10));
    }

    delZero(&digits);  // Remove leading zeros from the digits list
}

// Big int constructor
BigInteger::BigInteger(const BigInteger& N) 
{
    this->signum = N.signum;
    this->digits = N.digits;
}

// -= Access Functions =-
int BigInteger::sign() const
{
    return this->signum;
}

int BigInteger::compare(const BigInteger& N) const 
{
    // Compare signs
    if (signum > N.signum) 
	{
        return 1;
    }
    else if (signum < N.signum) 
	{
        return -1;
    }
    else if (signum == 0 && N.signum == 0) 
	{
        return 0;
    }

    // Numbers have same sign
    const List& A = digits;
    const List& B = N.digits;
    int aLength = A.length();
    int bLength = B.length();

	// If lengths of numbers are different
	if (aLength != bLength) 
	{
        // If lengths differ, the longer list is larger
        return (aLength > bLength) ? signum : -N.signum;
    }
    
	// Create copies of A and B to avoid modifying the originals
    List aCopy = A;
    List bCopy = B;
    
	// Move cursors to the front of the lists
    aCopy.moveFront();
    bCopy.moveFront();
    
	// Compare digits element by element
    for (int i = 0; i < aLength; ++i) 
	{
        if (aCopy.peekNext() > bCopy.peekNext()) 
		{
            // Current digit in A is larger, so A is larger overall
            return signum;
        }
        else if (aCopy.peekNext() < bCopy.peekNext()) {
            // Current digit in B is larger, so B is larger overall
            return -N.signum;
        }
        // Move cursors to the next element
        aCopy.moveNext();
        bCopy.moveNext();
    }
    // All digits are equal
    return 0;
}

// -= Manipulation Procedures =-
void BigInteger::makeZero() 
{
    digits.clear();
    signum = 0;
}

void BigInteger::negate() 
{
    signum *= -1;
}

// -= Big Integer Arithmetic Functions =-

// Adds two big integers together returning a big int.
BigInteger BigInteger::add(const BigInteger& N) const 
{
    BigInteger addend1 = *this;
    BigInteger addend2 = N;
    BigInteger sum;

    // Differing Signs
    if (addend1.sign() > 0 && addend2.sign() < 0) 
	{
        addend2.negate();
        return addend1.sub(addend2);
    } 
	else if (addend1.sign() < 0 && addend2.sign() > 0) 
	{
        addend1.negate();
        return addend2.sub(addend1);
    } 
	else if (addend1.sign() < 0 && addend2.sign() < 0) 
	{
        addend1.negate();
        addend2.negate();
        sum = addend1.add(addend2);
        sum.negate();
        return sum;
    }

    // Ensure addend1 is the smaller BigInteger
    if (addend1 > addend2) 
	{
        return addend2.add(addend1);
    }

    List addend1Digits = addend1.digits;
    List addend2Digits = addend2.digits;
    List sumDigits = sum.digits;

    long carry = 0;
    long temp = 0;

    // Perform addition digit by digit
    addend1Digits.moveBack();
    addend2Digits.moveBack();
    while (addend1Digits.position() > 0 && addend2Digits.position() > 0) {
        temp = carry + addend1Digits.peekPrev() + addend2Digits.peekPrev();
        carry = temp / BASE;
        temp %= BASE;
        sumDigits.insertAfter(temp);
        addend1Digits.movePrev();
        addend2Digits.movePrev();
    }

    // Handle remaining digits of Y
    while (addend2Digits.position() > 0) 
	{
        temp = carry + addend2Digits.peekPrev();
        carry = temp / BASE;
        temp %= BASE;
        sumDigits.insertAfter(temp);
        addend2Digits.movePrev();
    }

    // If there is a final carry, insert it
    if (carry > 0) 
	{
        sumDigits.insertAfter(carry);
    }

    sum.signum = 1;
    sum.digits = sumDigits;;
    return sum;
}


// Subtracts two Big Integers returning a Big Integer
BigInteger BigInteger::sub(const BigInteger& N) const 
{
    BigInteger minuend = *this;
    BigInteger subtrahend = N;
    BigInteger difference;
    List minuendDigits = minuend.digits;
    List subtrahendDigits = subtrahend.digits;
    List differenceDigits = difference.digits;

    // Check for special cases

	// Return 0 if subtrahend and minuend are requal
    if (subtrahend == minuend) 
	{
        return difference;  
    }
	
	// Return negation of subtrahend if subtrahend is positive and minuend is negative
    if (subtrahend.sign() && !minuend.sign()) 
	{
        subtrahend.negate();
        return subtrahend;  
    }

	// Return minuend if subtrahend is negative and minuend is positive
    if (!subtrahend.sign() && minuend.sign()) 
	{
        return minuend;  
    }

	// Return (subtrahend + (-minuend)) negated if subtrahend is negative and minuend is positive
    if (subtrahend.sign() < 0 && minuend.sign() > 0) 
	{
        minuend.negate();
        difference = subtrahend.add(minuend);
        difference.negate();
        return difference;  
    }

	// Return (subtrahend + (-minuend)) if subtrahend is positive and minuend is negative
    if (subtrahend.sign() > 0 && minuend.sign() < 0) 
	{
        subtrahend.negate();
        difference = subtrahend.add(minuend);
        return difference;  
    }

	// Return (minuend - subtrahend) negated if both are negative
    if (subtrahend.sign() < 0 && minuend.sign() < 0) 
	{
        subtrahend.negate();
        minuend.negate();
        difference = minuend.sub(subtrahend);
        difference.negate();
        return difference;  
    }

	// Return negation of (subtrahend - minuend) if subtrahend is less than minuend
    if (subtrahend < minuend) 
	{
        difference = subtrahend.sub(minuend);
        difference.negate();
        return difference;  
    }

    // Perform digit-by-digit subtraction
    subtrahendDigits.moveBack();
    minuendDigits.moveBack();
    long dist = 0;
    long temp = 0;
    int i = minuendDigits.position();
    while (!(i <= 0)) 
	{
        if (subtrahendDigits.peekPrev() - dist < minuendDigits.peekPrev()) 
		{
            temp = subtrahendDigits.peekPrev() + BASE - minuendDigits.peekPrev() - dist;
            dist = 1;
        } 
		else 
		{
            temp = subtrahendDigits.peekPrev() - dist - minuendDigits.peekPrev();
            if (!(subtrahendDigits.peekPrev() <= 0))
			{
                dist = 0;
            }
        }
        differenceDigits.insertAfter(temp);
        subtrahendDigits.movePrev();
        minuendDigits.movePrev();
        i--;
    }

    while (subtrahendDigits.position() > 0) 
	{
        if (subtrahendDigits.peekPrev() - dist < 0) 
		{
            temp = subtrahendDigits.peekPrev() + BASE - 0 - dist;
            dist = 1;
        } 
		else 
		{
            temp = subtrahendDigits.peekPrev() - dist - 0;
            if (!(subtrahendDigits.peekPrev() <= 0)) 
			{
                dist = 0;
            }
        }
        differenceDigits.insertAfter(temp);
        subtrahendDigits.movePrev();
    }
    difference.digits = differenceDigits;
    delZero(&(difference.digits));  // Remove leading zeros from the result
    difference.signum = -1;  // Set the sign of the result to negative
    return difference;
}

// mult()
// Returns a BigInteger representing the product of this and N. 
BigInteger BigInteger::mult(const BigInteger& N) const 
{
    BigInteger multiplier = *this;
    BigInteger multiplicand = N;
    BigInteger product;
    List multiplicandDigits = multiplicand.digits;
    List multiplierDigits = multiplier.digits;
    int ctr = 0;
    multiplicandDigits.moveBack();
    multiplierDigits.moveBack();
    
	int p = multiplicandDigits.position();
    // Multiply each digit of multiplicand with multiplier and accumulate the result in product
    for (int i = p; i > 0; i--) 
	{
        List temp = tempMult(multiplicandDigits.peekPrev(), &multiplierDigits, &ctr);  // Multiply current digit of multiplicand with multiplier
        BigInteger T;
        T.signum = 1;
        T.digits = temp;
        product = product.add(T);  // Accumulate the result in C
        multiplicandDigits.movePrev();  // Move to the next digit of A
        ctr++;
    }

    product.signum = multiplicand.signum * multiplier.signum;  // Determine the sign of the result
    return product;
}

// Other Functions ----------------------------------------------------------------------------------------------------
std::string BigInteger::to_string() {
    std::string out = "";
    if (this->signum == 0) {
        return "0";  // Return "0" if the BigInteger is zero
    } else if (signum == -1) {
        out += "-";  // Add a negative sign if the BigInteger is negative
    }
    digits.moveFront();
    // Remove leading zeros from the digits list
    while (digits.front() == 0 && digits.length() > 1) {
        digits.eraseAfter();
    }
    for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
        std::string A = std::to_string(digits.peekNext());
        std::string B = "";
        // Pad the number with zeros to ensure each chunk has POWER digits
        while ((int)(B.length() + A.length()) < POWER && digits.position() != 0) {
            B += '0';
        }
        out += (B + A);  // Concatenate the padded chunk with the output string
    }
    return out;
}

// Overriden Operators --------------------------------------------------------------------------------------------------------------
// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream<<N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return (i == 0) ? true : false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return (i == -1) ? true : false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 

bool operator<=( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return ((i == 0) || (i == -1)) ? true : false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return (i == 1) ? true : false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return ((i == 0) || (i == 1)) ? true : false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.add(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}

// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.sub(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.mult(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}
