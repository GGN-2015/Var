#include <cstdlib>
#include <ctime>
#include <iostream>

#include "BigInt.h"
#include "Var.h"

int rand(int L, int R) {
	int RND = (rand() << 15) | rand();
	return RND % (R - L + 1) + L;
}

int main(int argc, char** argv) {
	using std::cin;
	using std::cout;
	using std::endl;
	
	//cout << "$Test Main for Project Var " << endl;
	Var tmp = CreateDict();
	tmp[5] = 6;
	tmp[2] = CreateList({0, 1, BigInt("123456789"), "hello\nworld"});
	tmp[4] = CreateDict({DictKey(3, 5), DictKey("hello", 123.456), DictKey(tmp[2], None)});
	cout << tmp;
	return 0;
}
