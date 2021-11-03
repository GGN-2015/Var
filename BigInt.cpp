#include <assert.h>
#include <algorithm>
#include <cctype>
//#include <iostream>
#include <stack>

#include "BigInt.h"

using std::istream;
using std::ostream;

BigInt::BigInt() {
	this -> isneg = false;
	this -> len = 0;
	this -> arr = nullptr;
}

BigInt::BigInt(int intVal) { // transform int => BigInt
	const int MAX_INT_LENGTH = 15;
	
	if(intVal < 0) {
		this -> isneg = true;
		intVal = - intVal; // negative check
	}else {
		this -> isneg = false;
	}
	
	int stack[MAX_INT_LENGTH], stackSize = 0;
	while(intVal != 0) {
		stack[stackSize ++] = intVal % 10; // Decimal
		intVal /= 10;
	}
	
	this -> len = stackSize;
	if(stackSize == 0) {
		this -> arr = nullptr;
	}else {
		this -> arr = new int[stackSize];
		for(int i = 0; i < stackSize; i ++) { // copy to arr
			this -> arr[i] = stack[i];
		}
	}
	// warning: if intVal = 0, this -> len = 0
}

BigInt::BigInt(long long longLongVal) { // transform long long => BigInt
	const int MAX_LONG_LONG_LENGTH = 25;

	if(longLongVal < 0) {
		this -> isneg = true;
		longLongVal = - longLongVal;
	}else {
		this -> isneg = false;
	}
	
	int stack[MAX_LONG_LONG_LENGTH], stackSize = 0;
	while(longLongVal != 0) {
		stack[stackSize ++] = longLongVal % 10;
		longLongVal /= 10;
	}
	
	this -> len = stackSize;
	if(stackSize == 0) {
		this -> arr = nullptr;
	}else {
		this -> arr = new int[stackSize];
		for(int i = 0; i < stackSize; i ++) {
			this -> arr[i] = stack[i];
		}
	}
}

BigInt::BigInt(const BigInt& bigInt) { // Deep Copy a BigInt
	this -> len = bigInt.len;
	this -> isneg = bigInt.isneg;
	if(this -> len == 0) {
		this -> arr = nullptr; // do not copy if bigInt is zero
	}else {
		this -> arr = new int[this -> len];
		for(int i = 0; i < this -> len; i ++) {
			this -> arr[i] = bigInt.arr[i];
		}
	}
}

BigInt::~BigInt() {
	delete[] this -> arr; // Destructor
}

ostream& operator<< (ostream& out, const BigInt& bigInt) { // output function
	if(bigInt.len == 0) { // zero is special
		out << '0';
	}else {
		if(bigInt.isneg) { // output negative '-'
			out << '-';
		}
		for(int i = bigInt.len - 1; i >= 0; i --) { // output from High to Low digits
			out << bigInt.arr[i];
		}
	}
	return out;
}

istream& operator>> (istream& in, BigInt& bigInt) { // input function
	bigInt.isneg = false;
	char c = in.get();
	while(!isdigit(c)) {
		if(isgraph(c)) { // if c is not a empty char
			assert(c == '-');
			bigInt.isneg = true; // get a negative '-'
		}
		c = in.get();
	}
	
	using std::stack;
	stack<int> stackTmp; // store all the numbers
	
	bigInt.len = 0;
	while(isdigit(c)) {
		if(stackTmp.empty() && c == '0') {
			// you don't need to push any thing
		}else {
			stackTmp.push(c - '0');
			bigInt.len ++;
		}
		c = in.get();
	}
	
	if(bigInt.len == 0) {
		bigInt.isneg = false; // 0 is not negative
		bigInt.arr = nullptr;
	}else {
		bigInt.arr = new int[bigInt.len];
		for(int i = 0; i < bigInt.len; i ++) {
			bigInt.arr[i] = stackTmp.top(); // the last digit in input is Low digits 
			stackTmp.pop();
		}
	}
	return in;
}

BigInt& BigInt::operator= (int intVal) {
	using std::swap;
	BigInt tmp(intVal);
	swap(this -> len, tmp.len);
	swap(this -> isneg, tmp.isneg);
	swap(this -> arr, tmp.arr);
	return *this;
}

BigInt& BigInt::operator= (long long longLongVal) {
	using std::swap;
	BigInt tmp(longLongVal);
	swap(this -> len, tmp.len);
	swap(this -> isneg, tmp.isneg);
	swap(this -> arr, tmp.arr);
	return *this;
}

BigInt& BigInt::operator= (const BigInt& bigInt) {
	using std::swap;
	BigInt tmp(bigInt);
	swap(this -> len, tmp.len);
	swap(this -> isneg, tmp.isneg);
	swap(this -> arr, tmp.arr);
	return *this;
}

int BigInt::toInt() const { // BigInt => int
	int ans = 0;
	for(int i = this -> len - 1; i >= 0; i --) { // sum up all bits
		ans  = ans * 10 + this -> arr[i];
		assert(ans >= 0); // ans < 0 means it overflows
	}
	if(this -> isneg) { // considering the flag of number
		return - ans;
	}else {
		return ans;
	}
}

long long BigInt::toLongLong() const { // BigInt => Long Long
	long long ans = 0;
	for(int i = this -> len - 1; i >= 0; i --) {
		ans = ans * 10 + this -> arr[i];
		assert(ans >= 0);
	}
	if(this -> isneg) {
		return - ans;
	}else {
		return ans;
	}
}

double BigInt::toDouble() const { // BigInt => double
	double ans = 0;
	for(int i = this -> len - 1; i >= 0; i --) {
		ans = ans * 10 + this -> arr[i];
	}
	if(this -> isneg) {
		return -ans;
	}else {
		return ans;
	}
}

BigInt& BigInt::toAbs() {
	this -> isneg = false;
	return *this;
}

BigInt& BigInt::add(const BigInt& rhs) {
	using std::swap;
	BigInt ans(*this); 
	if(this -> isneg == rhs.isneg) { // flag are the same
		ans.val_add(rhs);
		ans.isneg = this -> isneg;
	}else {
		ans.val_sub(rhs);
		if(!ans.isZero()) {
			if(this -> val_greater(rhs)) { // decide the flag
				ans.isneg = this -> isneg;
			}else {
				ans.isneg = rhs.isneg;
			}
		}
	}
	swap(ans.len, this -> len);
	swap(ans.isneg, this -> isneg);
	swap(ans.arr, this -> arr);
	return *this;
}

BigInt& BigInt::sub(const BigInt& rhs) {
	BigInt tmp = rhs;
	tmp.isneg = ! tmp.isneg; // A + B = A - (-B)
	this -> add(tmp);
	return *this;
}

BigInt& BigInt::mul(const BigInt& rhs) { // A *= B
	using std::swap;
	BigInt ans;
	ans.len = this -> len + rhs.len;
	ans.isneg = this -> isneg ^ rhs.isneg;
	ans.arr = new int[ans.len];
	for(int i = 0; i < ans.len; i ++) { // remember to clear it to zero
		ans.arr[i] = 0;
	}
	for(int i = 0; i < this -> len; i ++) { // multiply
		for(int j = 0; j < rhs.len; j ++) {
			ans.arr[i + j] += this -> arr[i] * rhs.arr[j];
		}
	}
	for(int i = 0; i < ans.len - 1; i ++) {
		ans.arr[i + 1] += ans.arr[i] / 10;
		ans.arr[i] %= 10;
	}
	ans.unify();
	swap(ans.len, this -> len);
	swap(ans.isneg, this -> isneg);
	swap(ans.arr, this -> arr);
	return *this;
}

BigInt& BigInt::div(const BigInt& rhs) {
	using std::swap;
	BigInt ans(*this);
	ans.val_div(rhs);
	ans.isneg = this -> isneg ^ rhs.isneg;
	swap(ans.len, this -> len);
	swap(ans.isneg, this -> isneg);
	swap(ans.arr, this -> arr);
	
	if(this -> len == 0) {
		this -> isneg = false;
	}
	return *this;
}

BigInt& BigInt::mod(const BigInt& rhs) {
	BigInt quotient(*this);
	quotient.div(rhs);
	quotient.mul(rhs);
	this -> sub(quotient); // A - (A/B) * B
	return *this;
}

BigInt& BigInt::operator+= (const BigInt& rhs) {
	return this -> add(rhs);
}

BigInt& BigInt::operator-= (const BigInt& rhs) {
	return this -> sub(rhs);
}

BigInt& BigInt::operator*= (const BigInt& rhs) {
	return this -> mul(rhs);
}

BigInt& BigInt::operator/= (const BigInt& rhs) {
	return this -> div(rhs);
}

BigInt& BigInt::operator%= (const BigInt& rhs) {
	return this -> mod(rhs);
}

BigInt operator+ (const BigInt& lhs, const BigInt& rhs) {
	BigInt tmp(lhs);
	tmp += rhs;
	return tmp;
}

BigInt operator- (const BigInt& lhs, const BigInt& rhs) {
	BigInt tmp(lhs);
	tmp -= rhs;
	return tmp;
}

BigInt operator* (const BigInt& lhs, const BigInt& rhs) {
	BigInt tmp(lhs);
	tmp *= rhs;
	return tmp;
}

BigInt operator/ (const BigInt& lhs, const BigInt& rhs) {
	BigInt tmp(lhs);
	tmp /= rhs;
	return tmp;	
}

BigInt operator% (const BigInt& lhs, const BigInt& rhs) {
	BigInt tmp(lhs);
	tmp %= rhs;
	return tmp;
}

bool BigInt::equ(const BigInt& rhs) const {
	if(this -> isneg != rhs.isneg) return false;
	if(this -> len != rhs.len) return false;
	for(int i = this -> len - 1; i >= 0; i --) {
		if(this -> arr[i] != rhs.arr[i]) {
			return false;
		}
	}
	return true;
}

bool BigInt::less(const BigInt& rhs) const {
	if(this -> isneg != rhs.isneg) {
		return this -> isneg; // neg < pos
	}else {
		if(this -> isneg) {
			return this -> val_greater(rhs);
		}else {
			return rhs.val_greater(*this);
		}
	}
}

bool BigInt::greater(const BigInt& rhs) const {
	return rhs.less(*this);
}

bool BigInt::leq(const BigInt& rhs) const {
	return this -> less(rhs) || this -> equ(rhs);
}

bool BigInt::geq(const BigInt& rhs) const {
	return !(this -> less(rhs));
}

bool BigInt::neq(const BigInt& rhs) const {
	return !(this -> equ(rhs));
}

bool operator== (const BigInt& lhs, const BigInt& rhs) {
	return lhs.equ(rhs);
}

bool operator<  (const BigInt& lhs, const BigInt& rhs) {
	return lhs.less(rhs);
}

bool operator>  (const BigInt& lhs, const BigInt& rhs) {
	return lhs.greater(rhs);
}

bool operator<= (const BigInt& lhs, const BigInt& rhs) {
	return lhs.leq(rhs);
}

bool operator>= (const BigInt& lhs, const BigInt& rhs) {
	return lhs.geq(rhs);
}

bool operator!= (const BigInt& lhs, const BigInt& rhs) {
	return lhs.neq(rhs);
}

bool BigInt::isZero() const {
	return this -> len == 0; // check if the big int is zero
}

//void BigInt::debug(ostream& out) {
//	out << "len = " << len << std::endl;
//	out << "neg = " << isneg << std::endl;
//	out << "arr = ";
//	for(int i = 0; i < len; i ++) {
//		out << arr[i] << ",";
//	}
//	out << std::endl;
//}

bool BigInt::val_greater(const BigInt& rhs) const { // |*this| > |rhs|
	if(this -> len != rhs.len) {
		return this -> len > rhs.len;
	}else {
		for(int i = this -> len - 1; i >= 0; i --) {
			if(this -> arr[i] != rhs.arr[i]) {
				return this -> arr[i] > rhs.arr[i];
			}
		}
		return false; // EQU
	}
}

bool BigInt::val_geq(const BigInt& rhs) const {
	if(this -> len != rhs.len) {
		return this -> len > rhs.len;
	}else {
		for(int i = this -> len - 1; i >= 0; i --) {
			if(this -> arr[i] != rhs.arr[i]) {
				return this -> arr[i] > rhs.arr[i];
			}
		}
		return true;
	}
}

bool BigInt::val_neq(const BigInt& rhs) const { // |*this| != |rhs|
	if(this -> len != rhs.len) {
		return true;
	}else {
		for(int i = this -> len - 1; i >= 0; i --) {
			if(this -> arr[i] != rhs.arr[i]) {
				return true; // NEQ
			}
		}
		return false; // EQU
	}
}

bool BigInt::val_pre_geq(const BigInt& rhs) const { // |pre(*this)| > |rhs|
	assert(this -> len >= rhs.len);
	// !! there may be some zero at the beginning of (*this)
	// that is: (*this) may not be unified before calling val_geq_pre
	for(int k = 0; k < rhs.len; k ++) {
		int i = this -> len - 1 - k;
		int j = rhs.len - 1 - k;
		if(this -> arr[i] != rhs.arr[j]) {
			return this -> arr[i] > rhs.arr[j];
		}
	}
	return true;
}

BigInt& BigInt::val_pre_sub(const BigInt& rhs) { // |pre(*this)| -= |rhs|
	assert(this -> val_pre_geq(rhs));
	// !! this function will not unify for the answer
	// so there may be pre zeros in the answer
	for(int k = 0; k < rhs.len; k ++) {
		int i = this -> len - 1 - k;
		int j = rhs.len - 1 - k;
		this -> arr[i] -= rhs.arr[j];
	}
	for(int k = rhs.len - 1; k >= 0; k --) {
		int i = this -> len - 1 - k;
		while(this -> arr[i] < 0) {
			this -> arr[i] += 10;
			this -> arr[i + 1] --; // borrow a digit
		}
	}
	// !! don't unify to keep the quptient right
	return *this;
}

BigInt& BigInt::unify() {
	while(this -> len > 0 && this -> arr[this -> len - 1] == 0) {
		this -> len --;
	}
	return *this;
}

BigInt& BigInt::val_add(const BigInt& rhs) { // add two abosolute value
	using std::swap;
	BigInt ans;
	ans.isneg = false; // return the sum of two ABS()
	ans.len = std::max(this -> len, rhs.len) + 1;
	ans.arr = new int[ans.len];
	for(int i = 0; i < ans.len; i ++) { // ans.arr[i]: set to zero
		ans.arr[i] = 0;
	}
	for(int i = 0; i < this -> len; i ++) {
		ans.arr[i] += this -> arr[i]; 
	}
	for(int i = 0; i < rhs.len; i ++) {
		ans.arr[i] += rhs.arr[i];
	}
	for(int i = 0; i < ans.len - 1; i ++) { // upgrade
		ans.arr[i + 1] += ans.arr[i] / 10;
		ans.arr[i] %= 10;
	}
	ans.unify();
	swap(ans.len, this -> len);
	swap(ans.isneg, this -> isneg);
	swap(ans.arr, this -> arr);
	return *this;
}

BigInt& BigInt::val_sub(const BigInt& rhs) { // subtract two ABS() and than return ABS of answer
	using std::swap;
	BigInt ans = 0; 
	if(this -> val_neq(rhs)) { // if equal, don't subtract
		if(this -> val_greater(rhs)) {
			// L > R
			ans = *this;
			for(int i = 0; i < rhs.len; i ++) {
				ans.arr[i] -= rhs.arr[i];
			}
			for(int i = 0; i < this -> len; i ++) {
				while(ans.arr[i] < 0) {
					ans.arr[i] += 10;
					ans.arr[i + 1] --;
				}
			}
		}else {
			// L < R
			ans = rhs;
			for(int i = 0; i < this -> len; i ++) {
				ans.arr[i] -= this -> arr[i];
			}
			for(int i = 0; i < rhs.len; i ++) {
				while(ans.arr[i] < 0) {
					ans.arr[i] += 10;
					ans.arr[i + 1] --;
				}
			}
		}
		ans.unify();
	}
	swap(ans.len, this -> len);
	swap(ans.isneg, this -> isneg); // save answer and return
	swap(ans.arr, this -> arr);
	return *this;
}

BigInt& BigInt::val_div(const BigInt& rhs) { // |*this| / |rhs|
	using std::swap;
	using std::stack;
	assert(!rhs.isZero()); // you can not div 0
	BigInt tmp = *this, ans;
	stack<int> quotient; // record every bit of the quotient
	while(tmp.len > rhs.len) {
		int val = 0;
		while(tmp.val_pre_geq(rhs)) {
			tmp.val_pre_sub(rhs);
			val ++;
		}
		quotient.push(val);
		if(tmp.arr[tmp.len - 1] != 0) { // the first digit of the rest of tmp may has two digits
			tmp.arr[tmp.len - 2] += 10 * tmp.arr[tmp.len - 1];
			tmp.arr[tmp.len - 1] = 0;
		}
		tmp.len --;
	}
	
	tmp.unify();
	int val = 0;
	while(tmp.val_geq(rhs)) {
		tmp.val_sub(rhs); // this must be val_sub not sub
		val ++;
	}
	quotient.push(val); // last value of the quotient
	
	ans.len = quotient.size();
	ans.arr = new int[ans.len];
	for(int i = 0; i < ans.len; i ++) {
		ans.arr[i] = quotient.top();
		quotient.pop();
	}
	ans.unify();
	
	swap(ans.len, this -> len);
	swap(ans.isneg, this -> isneg); // save answer and return
	swap(ans.arr, this -> arr);
	return *this;
}
