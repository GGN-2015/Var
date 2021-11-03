#include <cstdlib>
#include <ctime>
#include <iostream>

#include "BigInt.h"

int rand(int L, int R) {
	int RND = (rand() << 15) | rand();
	return RND % (R - L + 1) + L;
}

int main(int argc, char** argv) {
	using std::cin;
	using std::cout;
	using std::endl;
	
	//cout << "$Test Main for Project Var " << endl;
	for(int i = 1; i <= 10000; i ++) {
		int a = rand(-10000, 10000);
		int b = rand(-10000, 10000);
		BigInt A(a), B(b);
		if((a%b) != (A%B)) {
			cout << a << " " << b << " " << a % b << " " << A % B << endl;
			//(A%B).debug(cout);
			system("pause");
		}
	}
	return 0;
}
