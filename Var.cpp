#include <algorithm>
#include <assert.h>
#include <map> // use map to make 'DictType'
#include <vector> // use vector to make 'ListType'
#include <string> // use string to make 'StringType'
#include <sstream>

#include "Var.h"
#include "BigInt.h"

static const double FLOAT_EPS = 1e-10;

using std::map;
using std::vector;
using std::string;

Var::Var() {
	this -> varType = NoneType;
	this -> varPointer.intType = nullptr;
}

Var::Var(int intVal) {
	this -> varType = IntType;
	this -> varPointer.intType = new BigInt(intVal);
}

Var::Var(long long longLongVal) {
	this -> varType = IntType;
	this -> varPointer.intType = new BigInt(longLongVal);
}

Var::Var(const BigInt& bigIntVal) {
	this -> varType = IntType;
	this -> varPointer.intType = new BigInt(bigIntVal);
}

Var::Var(double doubleVal) {
	this -> varType = FloatType;
	this -> varPointer.floatType = new double(doubleVal);
}

Var::Var(const char* stringVal) {
	this -> varType = StringType;
	this -> varPointer.stringType = new string(stringVal);
}

Var::Var(const string& stringVal) {
	this -> varType = StringType;
	this -> varPointer.stringType = new string(stringVal);
}

Var::Var(const vector<Var>& listValue) {
	this -> varType = ListType;
	this -> varPointer.listType = new vector<Var>(listValue);
}

Var::Var(const vector<DictKey>& createDict) {
	this -> varType = DictType;
	this -> varPointer.dictType = new map<Var, Var>;
	VarDict& dict = *(this -> varPointer.dictType);
	for(auto pairVarVar: createDict) {
		assert(dict.count(pairVarVar.first) == 0);
		dict[pairVarVar.first] = pairVarVar.second;
	}
}

Var::Var(const map<Var, Var>& dictVal) {
	this -> varType = DictType;
	this -> varPointer.dictType = new map<Var, Var>(dictVal);
}

Var::Var(const Var& varVal) {
	this -> varType = varVal.varType;
	switch(this -> varType) {
		case NoneType:
			this -> varPointer.intType = nullptr;
			break;
		case IntType:
			this -> varPointer.intType = new BigInt(*varVal.varPointer.intType);
			break;
		case FloatType:
			this -> varPointer.floatType = new double(*varVal.varPointer.floatType);
			break;
		case StringType:
			this -> varPointer.stringType = new string(*varVal.varPointer.stringType);
			break;
		case ListType:
			this -> varPointer.listType = new vector<Var>(*varVal.varPointer.listType);
			break;
		case DictType:
			this -> varPointer.dictType = new map<Var, Var>(*varVal.varPointer.dictType);
			break;
		default:
			assert(false); // Type Not Found
			break;
	}
}

Var::~Var() { // destructor
	switch(this -> varType) {
		case NoneType:
			break;
		case IntType:
			delete this -> varPointer.intType;
			break;
		case FloatType:
			delete this -> varPointer.floatType;
			break;
		case StringType:
			delete this -> varPointer.stringType;
			break;
		case ListType:
			delete this -> varPointer.listType;
			break;
		case DictType:
			delete this -> varPointer.dictType;
			break;
		default:
			assert(false);
			break;
	}
}

ostream& operator<< (ostream& out, const Var& varVal) {
	int first = 1;
	VarList& vec = *(varVal.varPointer.listType); // output a list of var
	switch(varVal.varType) {
		case Var::NoneType: // No Output if None
			out << "None";
			break;
		case Var::IntType:
			out << *(varVal.varPointer.intType);
			break;
		case Var::FloatType:
			out << *(varVal.varPointer.floatType);
			break;
		case Var::StringType:
			out << char(34);
			for(auto c: *(varVal.varPointer.stringType)) {
				if(c == 34) {
					out << "\\" << char(34);
				}else if(c == 10) {
					out << "\\" << 'n';
				}else if(c == 13) {
					out << "\\" << 'r';
				}else if(c == '\t') {
					out << "\\" << 't';
				}else {
					out << c;
				}
			}
			out << char(34);
			break;
		case Var::ListType:
			out << '[';
			for(int i = 0; i < vec.size(); i ++) {
				out << vec[i];
				if(i != vec.size() - 1) {
					out << ", ";
				}
			}
			out << ']';
			break;
		case Var::DictType:
			out << '{';
			for(auto pairVarVar: *(varVal.varPointer.dictType)) {
				if(first) {
					first = 0;
				}else {
					out << ", "; // no comma before the first value
				}
				out << pairVarVar.first << ":" << pairVarVar.second;
			}
			out << '}';
			break;
		default:
			assert(false);
			break;
	}
	return out;
}

Var& Var::operator= (int intVal) {
	using std::swap;
	Var tmp(intVal);
	swap(tmp.varType, this -> varType);
	swap(tmp.varPointer, this -> varPointer);
	return *this;
}

Var& Var::operator= (long long longLongVal) {
	using std::swap;
	Var tmp(longLongVal);
	swap(tmp.varType, this -> varType);
	swap(tmp.varPointer, this -> varPointer);
	return *this;
}

Var& Var::operator= (const BigInt& bigIntVal) {
	using std::swap;
	Var tmp(bigIntVal);
	swap(tmp.varType, this -> varType);
	swap(tmp.varPointer, this -> varPointer);
	return *this;
}

Var& Var::operator= (double doubleVal) {
	using std::swap;
	Var tmp(doubleVal);
	swap(tmp.varType, this -> varType);
	swap(tmp.varPointer, this -> varPointer);
	return *this;
}

Var& Var::operator= (const string& stringVal) {
	using std::swap;
	Var tmp(stringVal);
	swap(tmp.varType, this -> varType);
	swap(tmp.varPointer, this -> varPointer);
	return *this;
}

Var& Var::operator= (const vector<Var>& listVal) {
	using std::swap;
	Var tmp(listVal);
	swap(tmp.varType, this -> varType);
	swap(tmp.varPointer, this -> varPointer);
	return *this;
}

Var& Var::operator= (const map<Var, Var>& dictVal) {
	using std::swap;
	Var tmp(dictVal);
	swap(tmp.varType, this -> varType);
	swap(tmp.varPointer, this -> varPointer);
	return *this;
}

Var& Var::operator= (const Var& varVal) {
	using std::swap;
	Var tmp(varVal);
	swap(tmp.varType, this -> varType);
	swap(tmp.varPointer, this -> varPointer);
	return *this;
}

bool operator== (const Var& lhs, const Var& rhs) {
	if(lhs.varType != rhs.varType) {
		return false;
	}
	switch(lhs.varType) {
		case Var::NoneType:
			return true; // all the None are equal to each other
		case Var::IntType:
			return (*lhs.varPointer.intType) == (*rhs.varPointer.intType);
		case Var::FloatType:
			return abs((*lhs.varPointer.floatType) - (*rhs.varPointer.floatType)) < FLOAT_EPS;
		case Var::StringType:
			return (*lhs.varPointer.stringType) == (*rhs.varPointer.stringType);
		case Var::ListType:
			return (*lhs.varPointer.listType) == (*rhs.varPointer.listType);
		case Var::DictType:
			return (*lhs.varPointer.dictType) == (*rhs.varPointer.dictType);
		default:
			assert(false);
	}
}

bool operator< (const Var& lhs, const Var& rhs) {
	if(lhs.varType != rhs.varType) {
		return lhs.varType < rhs.varType;
	}
	switch(lhs.varType) {
		case Var::NoneType:
			return true; // all the None are equal to each other
		case Var::IntType:
			return (*lhs.varPointer.intType) < (*rhs.varPointer.intType);
		case Var::FloatType:
			return (*lhs.varPointer.floatType) < (*rhs.varPointer.floatType) - FLOAT_EPS;
		case Var::StringType:
			return (*lhs.varPointer.stringType) < (*rhs.varPointer.stringType);
		case Var::ListType:
			return (*lhs.varPointer.listType) < (*rhs.varPointer.listType);
		case Var::DictType:
			return (*lhs.varPointer.dictType) < (*rhs.varPointer.dictType);
		default:
			assert(false);
	}
}

Var& Var::operator[](const Var& index) {
	assert(this -> varType == ListType || this -> varType == DictType);
	if(this -> varType == ListType) {
		VarList& vec = *(this -> varPointer.listType);
		BigInt& bigIntIndex = *(index.varPointer.intType);
		
		assert(index.varType == IntType);
		assert(vec.size() > 0);
		assert(BigInt(-(int)vec.size()) <= bigIntIndex && bigIntIndex < BigInt((int)vec.size()));
		
		int intIndex = bigIntIndex.toInt();
		return vec[(intIndex + (int)vec.size()) % (int)vec.size()]; // support negative index
	}else {
		VarDict& dict = *(this -> varPointer.dictType);
		if(dict.count(index) == 0) {
			dict.insert(std::make_pair(index, Var()));
		}
		return dict[index];
	}
}

Var& Var::toInt() {
	Var ans;
	if(this -> varType == IntType) {
		return *this;
	}
	assert(this -> varType == StringType || this -> varType == FloatType);
	if(this -> varType == StringType) {
		ans = BigInt(*(this -> varPointer.stringType));
	}
	if(this -> varType == FloatType) {
		int cnt = 0;
		double tmp = *(this -> varPointer.floatType);
		while(abs(tmp) > 1e19) {
			cnt ++;
			tmp /= 10;
		}
		BigInt bigInt = BigInt((long long)tmp);
		while(cnt --) {
			bigInt *= 10;
		}
		ans = bigInt;
	}
	std::swap(ans.varType, this -> varType);
	std::swap(ans.varPointer, this -> varPointer);
	return *this;
}

Var& Var::toFloat() {
	Var ans;
	if(this -> varType == FloatType) {
		return *this;
	}
	assert(this -> varType == IntType || this -> varType == StringType);
	if(this -> varType == IntType) {
		ans.varType = FloatType;
		ans.varPointer.floatType = new double(this -> varPointer.intType -> toDouble()); // BigInt => double
	}
	if(this -> varType == StringType) {
		std::stringstream ss;
		ss << *(this -> varPointer.stringType);
		double dtmp;
		ss >> dtmp;
		ans = dtmp;
	}
	std::swap(ans.varType, this -> varType);
	std::swap(ans.varPointer, this -> varPointer);
	return *this;
}

Var& Var::toString() {
	if(this -> varType == StringType) {
		return *this;
	}
	std::stringstream ss;
	ss << (*this);
	Var ans = ss.str();
	std::swap(ans.varType, this -> varType);
	std::swap(ans.varPointer, this -> varPointer);
	return (*this);
}

bool Var::numeric() const {
	return this -> varType == IntType || this -> varType == FloatType;
}

Var& Var::add(const Var&rhs) {
	Var ans;
	assert(this -> varType != NoneType);
	assert(rhs.varType != NoneType);
	if(this -> numeric() && rhs.numeric()) { // if two items are both number 
		bool has_float = rhs.varType == FloatType || this -> varType == FloatType;
		if(has_float) {
			this -> toFloat();
			Var rhs_tmp(rhs);
			rhs_tmp.toFloat(); // now *this + rhs_tmp = float + float
			ans = *(this -> varPointer.floatType) + *(rhs_tmp.varPointer.floatType);
		}else {
			// add between BigInt & BigInt
			ans = *(this -> varPointer.intType) + *(rhs.varPointer.intType);
		}
	}else {
		assert(this -> varType == rhs.varType);
		if(this -> varType == StringType) {
			*(this -> varPointer.stringType) += *(rhs.varPointer.stringType);
		}else
		if(this -> varType == ListType) {
			for(auto vars: *rhs.varPointer.listType) { // for every node in rhs
				this -> varPointer.listType -> push_back(vars);
			}
		}else
		if(this -> varType == DictType) {
			for(auto vars: *rhs.varPointer.dictType) { // for every node in rhs
				this -> varPointer.dictType -> insert(vars); // the same index will be ignored without warning
			}
		}
		return *this; // do not use ans
	}
	std::swap(ans.varType, this -> varType);
	std::swap(ans.varPointer, this -> varPointer);
	return *this;
}
