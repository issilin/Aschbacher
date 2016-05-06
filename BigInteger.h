/******************************************************
 * Integer.h -- C++ Integer class for the gmp integer library (from the
 *   GNU project.) Allows you to use the arbitrary precision integers 
 *   from gmp as if they were plain old (int)'s or (long int)'s.  Just 
 *   include this file in your source code.  Example main(): 
 *
 *    #include "Integer.h"
 *    int main(int argc, char **argv) { 
 *	Integer a, b, c;
 *
 *	a = argv[1];		// automaticaly converts a string
 *	b = argv[2];		//  into an Integer.
 *	c = a*b;
 *	cout << a << " x " << b << " = " << c << endl;
 *    }
 *
 ********
 * To Do:
 *   Rewrite all additions to check for signed (int)s  (Done! with 000605)
 * ChangeLog:
 *   970304 - Created    -- Paul Herman <a540pau@pslc.ucla.edu>
 *   980804 - Cleaned up -- Paul Herman <a540pau@pslc.ucla.edu>
 *   000605 - bug fixes  -- Paul Herman <pherman@frenchfries.net>
 *******************************************************/


/***************************** BEGIN ********************************/

#include <stdlib.h>

#ifndef		FALSE
#define		FALSE 0
#endif // FALSE
#ifndef		TRUE
#define		TRUE 1
#endif // TRUE

#ifndef __GMP_INTEGER_CLASS__
#define __GMP_INTEGER_CLASS__

#include <gmp.h>		// provides the mpz integer routines
#include <iostream>		// for cin & cout istreams & ostreams
#include <time.h>		// use time as seed for random numbers

#ifndef		ABSmodN
#define		ABSmodN(x, n) (x%n)	// in gmp lib, (-x)%n = (n-x)%n
#endif // ABSmodN

using namespace std;

/**************************** INTEGER ***************************************/

class BigInteger {
  private:
	mpz_t _x;
	int base;
  public:
//
// Constructors
//
    BigInteger(void);
    BigInteger(int a);
    BigInteger(unsigned int a);
    BigInteger(const BigInteger &a);
    BigInteger(char * a);
    BigInteger(mpz_t a);
//
// Destructor
//
    ~BigInteger(void);
//
// Simple access functions
//
    int		getbase(void);
    void	setbase(int b);
//
// Casting	(changing BigInteger to another type)
//
    operator bool(void);	// (bool) i
    operator int(void);		// (int)  i
    operator unsigned int(void);// (unsigned int) i
    operator float(void);	// (float) i
    operator double(void);	// (double)i
//
// Assignments	(Setting BigInteger equal to something else)
//
    void operator =(BigInteger a);		// c = (BigInteger) a;
    void operator =(int a);		// c = (int) a;
    void operator =(unsigned int a);	// c = (unsigned int) a;
    void operator =(char *a);		// c = a (a string);
    void operator =(const char *a);	// c = "1231231";
    void operator =(mpz_t a);		// c = a (a mpz number);
//
// Binary (one sided) operators
//
    BigInteger operator -(void);		// c = -a;
    bool operator !(void);		// c = (bool) (!a)
    void operator +=(BigInteger a);	// c += a;
    void operator +=(int a);		// c += a;
    void operator +=(unsigned int a);	// c += a;
    void operator -=(BigInteger a);	// c -= a;
    void operator -=(int a);		// c -= a;
    void operator -=(unsigned int a);	// c -= a;
    void operator *=(BigInteger a);	// c *= a;
    void operator *=(int a);		// c *= a;
    void operator *=(unsigned int a);	// c *= a;
    void operator /=(BigInteger a);	// c /= a;
    void operator /=(int a);		// c /= a;
    void operator /=(unsigned int a);	// c /= a;
    void operator %=(BigInteger a);	// c %= a;
    void operator %=(int a);		// c %= a;
    void operator ^=(int a);		// c ^= a;
// WARNING: No ^ with type (BigInteger) as exponent

    BigInteger operator ++(void);		// c = a++;
    BigInteger operator --(void);		// c = a--;
    BigInteger operator ++(int from);	// c = ++a;
    BigInteger operator --(int from);	// c = --a;

//
// The following operators must be friendly because the are binary
//
    friend BigInteger operator +(BigInteger a, BigInteger b);	// a + b;
    friend BigInteger operator +(BigInteger a, int b);	// a + b;
    friend BigInteger operator +(int a, BigInteger b);	// a + b;
    friend BigInteger operator -(BigInteger a, BigInteger b);	// a - b;
    friend BigInteger operator -(BigInteger a, int b);	// a - b;
    friend BigInteger operator -(int a, BigInteger b);	// a - b;
    friend BigInteger operator *(BigInteger a, BigInteger b);	// a * b;
    friend BigInteger operator *(BigInteger a, int b);	// a * b;
    friend BigInteger operator *(int a, BigInteger b);	// a * b;
    friend BigInteger operator /(BigInteger a, BigInteger b);	// a / b;
    friend BigInteger operator /(BigInteger a, int b);	// a / b;
    friend BigInteger operator /(int a, BigInteger b);	// a / b;
    friend BigInteger operator %(BigInteger a, BigInteger b);	// a % b;
    friend BigInteger operator %(BigInteger a, int b);	// a % b;
    friend BigInteger operator %(int a, BigInteger b);	// a % b;
    friend BigInteger operator ^(BigInteger a, int b);	// a ^ b;
    friend BigInteger operator &(BigInteger a, BigInteger b);	// a & b;
    friend BigInteger operator |(BigInteger a, BigInteger b);	// a | b;

    friend bool operator ==(BigInteger a, BigInteger b);	// (c == a)?
    friend bool operator ==(BigInteger a, int b);		// (c == a)?
    friend bool operator ==(int a, BigInteger b);		// (c == a)?
    friend bool operator !=(BigInteger a, BigInteger b);	// (c != a)?
    friend bool operator !=(BigInteger a, int b);		// (c != a)?
    friend bool operator !=(int a, BigInteger b);		// (c != a)?
    friend bool operator <(BigInteger a, BigInteger b);	// (c < a)?
    friend bool operator <(BigInteger a, int b);		// (c < a)?
    friend bool operator <(int a, BigInteger b);		// (c < a)?
    friend bool operator <=(BigInteger a, BigInteger b);	// (c <= a)?
    friend bool operator <=(BigInteger a, int b);		// (c <= a)?
    friend bool operator <=(int a, BigInteger b);		// (c <= a)?
    friend bool operator >(BigInteger a, BigInteger b);	// (c > a)?
    friend bool operator >(BigInteger a, int b);		// (c > a)?
    friend bool operator >(int a, BigInteger b);		// (c > a)?
    friend bool operator >=(BigInteger a, BigInteger b);	// (c >= a)?
    friend bool operator >=(BigInteger a, int b);		// (c >= a)?
    friend bool operator >=(int a, BigInteger b);		// (c >= a)?
    friend ostream& operator <<(ostream &s, BigInteger a);		// cout << a;
    friend istream& operator >>(istream &s, BigInteger &a);	// cin >> a;
    friend BigInteger & operator <<(BigInteger a, int b);		// a << b;
    friend BigInteger & operator >>(BigInteger a, int b);		// a >> b;
//
// These functions are friendly to speed up access to the class'
//  private parts.
//
    friend void		Int2a(BigInteger i, char *string);
    friend BigInteger gcd(BigInteger a, BigInteger b);
    friend BigInteger exgcd(BigInteger a, BigInteger b, BigInteger &c, BigInteger &d);
    friend BigInteger InvModN(BigInteger a, BigInteger n);
    friend BigInteger PowModN(BigInteger base, BigInteger exp, BigInteger n);
    friend BigInteger PowModN(BigInteger base, int exp, BigInteger n);
    friend bool		isprime(BigInteger a);
    friend bool		issquare(BigInteger a);
    friend bool		testbit(BigInteger a, unsigned long int bit_number);
    friend BigInteger sqrt(BigInteger a);
    friend int		digits(BigInteger a, int base);
    friend int		Jacobi(BigInteger m, BigInteger n);
    friend int		Legendre(BigInteger m, BigInteger n);
    friend BigInteger random(BigInteger range);
	friend BigInteger Xor(BigInteger a, BigInteger b);

}; // end 'class BigInteger'
//
//  Misc Number theory functions (non-friendly)
//
BigInteger lcm(BigInteger a, BigInteger b);
BigInteger LCM(BigInteger a);		// LCM(a) = lcm[1, 2, 3, ..., a]
int	logn(BigInteger a, int base);
int	log2(BigInteger a);
BigInteger fact(BigInteger a);
BigInteger P_n_k(BigInteger n, BigInteger k);
BigInteger C_n_k(BigInteger n, BigInteger k);
BigInteger nextprime(BigInteger a);
BigInteger prevprime(BigInteger a);
BigInteger SqrtModN(BigInteger x, BigInteger p);
string getStringValue(BigInteger i);


#endif	//	__GMP_INTEGER_CLASS__
