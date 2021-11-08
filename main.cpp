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
	
	cout << "$Test Main for Project Var" << endl;
	//Var A = CreateList({1, 2, 3});
	//cout << A << endl;
	Var lis = CreateList({0, 1, 2, 3, 4, 5, 6, 7});
	cout << lis << endl;
	return 0;
}

