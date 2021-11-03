#ifndef __BIGINT_H__
#define __BIGINT_H__

#include <iostream>

using std::istream;
using std::ostream;

class BigInt {
public:
	BigInt();
	BigInt(int);
	BigInt(long long);
	//BigInt(double); // transform int/long long/double to BigInt
	BigInt(const BigInt&);
	~BigInt();
	
	friend ostream& operator<< (ostream&, const BigInt&); 	// output the value of BigInt
	friend istream& operator>> (istream&, BigInt&);			// input the value of BigInt
	
	BigInt& operator= (int);
	BigInt& operator= (long long);
	//BigInt& operator= (double); // Don't allow this for accuracy concern
	BigInt& operator= (const BigInt&); // Deep Copy
	
	int toInt() const;
	long long toLongLong() const;
	double toDouble() const;
	
	BigInt& toAbs(); // to non-negative number
	
	BigInt& add(const BigInt&);
	BigInt& sub(const BigInt&);
	BigInt& mul(const BigInt&);
	BigInt& div(const BigInt&);
	BigInt& mod(const BigInt&); // algebra calculations
	
	BigInt& operator+= (const BigInt&);
	BigInt& operator-= (const BigInt&);
	BigInt& operator*= (const BigInt&);
	BigInt& operator/= (const BigInt&);
	BigInt& operator%= (const BigInt&);
	
	friend BigInt operator+ (const BigInt& lhs, const BigInt& rhs);
	friend BigInt operator- (const BigInt& lhs, const BigInt& rhs);
	friend BigInt operator* (const BigInt& lhs, const BigInt& rhs);
	friend BigInt operator/ (const BigInt& lhs, const BigInt& rhs);
	friend BigInt operator% (const BigInt& lhs, const BigInt& rhs);
	
	bool equ(const BigInt&) const;
	bool less(const BigInt&) const;
	bool greater(const BigInt&) const;
	bool leq(const BigInt&) const;
	bool geq(const BigInt&) const;
	bool neq(const BigInt&) const; // comparison between two 'BigInt'
	
	friend bool operator== (const BigInt&, const BigInt&);
	friend bool operator<  (const BigInt&, const BigInt&);
	friend bool operator>  (const BigInt&, const BigInt&);
	friend bool operator<= (const BigInt&, const BigInt&);
	friend bool operator>= (const BigInt&, const BigInt&);
	friend bool operator!= (const BigInt&, const BigInt&); // operators
	
	bool isZero() const;
	
	//void debug(ostream&);
	
private:
	bool val_equ(const BigInt&) const;
	bool val_less(const BigInt&) const;
	bool val_greater(const BigInt&) const;
	bool val_leq(const BigInt&) const;
	bool val_geq(const BigInt&) const;
	bool val_neq(const BigInt&) const; // val_cmp means don't care about 'isneg' flag
	
	bool val_pre_geq(const BigInt&) const; // |pre(*this)| >= |rhs|
	BigInt& val_pre_sub(const BigInt&);
	
	BigInt& unify(); // delete pre zeros
	
	BigInt& val_add(const BigInt&); // return the positive number
	BigInt& val_sub(const BigInt&); // val_sub return the absolute value of the subtraction
	BigInt& val_div(const BigInt&); 
	
	int len;
	bool isneg; // isneg = True: BigInt < 0
	int* arr;
};

#endif /* __BIGINT_H__ */
