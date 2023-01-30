// $Id: ubigint.h,v 1.4 2022-03-21 16:02:26-07 - - $

#ifndef UBIGINT_H
#define UBIGINT_H

#include <exception>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>
using namespace std;

#include "debug.h"
#include "relops.h"

class ubigint {
   friend ostream& operator<< (ostream&, const ubigint&);
   private:
      using ubigvalue_t = vector<uint8_t>; //<--Changed from ... = unsigned long;
      ubigvalue_t uvalue {};

	  //Helper remove zeros function
	  void removeZeros();
   public:
      void multiply_by_2();
      void divide_by_2();

      ubigint() = default; // Need default ctor as well.
      ubigint (unsigned long);
      ubigint (const string&);

      ubigint operator+ (const ubigint&) const;
      ubigint operator- (const ubigint&) const;
      ubigint operator* (const ubigint&) const;
      ubigint operator/ (const ubigint&) const;
      ubigint operator% (const ubigint&) const;

      bool operator== (const ubigint&) const;
      bool operator<  (const ubigint&) const;
      
      void print(bool) const;
      void print() const;
};

#endif

