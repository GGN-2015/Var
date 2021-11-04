// Var.h
// Author: GGN_2015
// Date: 2021-11-03
// Use C++ to make a dynamic data type like python

#ifndef __VAR_H__
#define __VAR_H__

#include <map> // use map to make 'DictType'
#include <vector> // use vector to make 'ListType'
#include <string> // use string to make 'StringType'
#include <iostream>

using std::map;
using std::vector;
using std::string;
using std::pair;

class BigInt; // use BigInt to make 'IntType'

class Var;

typedef vector<Var> VarList, CreateList;
typedef map<Var, Var> VarDict;
typedef pair<Var, Var> DictKey;
typedef vector<DictKey> CreateDict; // only use it to create a DictType

class Var {
public:
	Var(); 						// Default Type: NoneType
	Var(int);
	Var(long long);
	Var(const BigInt&); 		// IntType (int & long long may be upgrade to 'double')
	Var(double); 				// FloatType
	
	Var(const char*);
	Var(const string&); 		// StringType
	
	Var(const vector<Var>&); 	// ListType
	
	Var(const vector<DictKey>&);
	Var(const map<Var, Var>&); 	// DictType
	Var(const Var&); 			// Copy Constructor: Deep-Copy
	~Var();						// Destructor
	
	friend std::ostream& operator<< (std::ostream&, const Var&); // output Var to ostream
	//friend istream& operator>> (istream&, Var&); // input var from istream(hard to code)
	
	Var& operator= (int);
	Var& operator= (long long);
	Var& operator= (const BigInt&);
	Var& operator= (double);
	Var& operator= (const string&);
	Var& operator= (const vector<Var>&);
	Var& operator= (const map<Var, Var>&);
	Var& operator= (const Var&);		// Deep-Copy
	
	Var& toInt();
	Var& toFloat();				// transform between IntType and FloatType (or StringType)
	
	bool numeric() const;		// Check type() in "IntType, FloatType"
	
	Var& add(const Var&);
	Var& sub(const Var&);
	Var& mul(const Var&);
	Var& div(const Var&);
	Var& mod(const Var&); 		// Algebra Calculations
	
	Var& operator+= (const Var&);
	Var& operator-= (const Var&);
	Var& operator*= (const Var&);
	Var& operator/= (const Var&);
	Var& operator%= (const Var&);// all the self construct operator
	
	bool equ(const Var&) const;
	bool less(const Var&) const;
	bool greater(const Var&) const;
	bool leq(const Var&) const;
	bool geq(const Var&) const;		// Comparison between Vars
	bool neq(const Var&) const;
	
	friend bool operator == (const Var&, const Var&);
	friend bool operator < (const Var&, const Var&);  // these two operator are only used in map<Var, Var>
	
	string type() const;			// "NoneType", "IntType", "FloatType", "ListType", "DictType"
	
	Var& toList();
	Var& toDict();					// transform between ListType and DictType
	
	Var& toString();				// transform any Type of Value to a StringType
	
	int len() const;				// get the size of StringType, ListType or DictType
	
	bool exist(const Var&) const;	// check if Var exist in a ListType
	Var index(const Var&) const; 	// search in a ListType, and return first index, Not Found => NoneType
	
	Var get(const Var&) const;		// Get a value of a key from a DictType
	Var del(const Var&);			// delete a value from ListType/DictType
	
	Var& operator[](const Var&);	// index must exist in List/Dict, or throw an exception
	
	Var substr(int, int);			// get a substring of a StringType/ListType
	
	enum VarType {
		NoneType = 0, IntType, FloatType, StringType, ListType, DictType
	};
private:
	VarType varType;
	
	union {
		BigInt* intType;
		double* floatType;
		string* stringType;
		vector<Var>* listType;
		map<Var, Var>* dictType;
	} varPointer;
};

const Var None;

#endif /* __VAR_H__ */
