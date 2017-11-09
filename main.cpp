#include <iostream>
#include "TMatriz.hpp"

using namespace std;

int main(int argc, char** argv) {
	
	matriz<int> a(5,5,0);
	a(0,0) = 0; 	a(0,1) = 2; 	a(0,2) = 2; 	a(0,3) = 4; 	a(0,4) = 5;
	a(1,0) = 8; 	a(1,1) = 9; 	a(1,2) = 10; 	a(1,3) = 13; 	a(1,4) = 19;
	a(2,0) = 23; 	a(2,1) = 28; 	a(2,2) = 19; 	a(2,3) = 20; 	a(2,4) = 21;
	a(3,0) = 22; 	a(3,1) = 2; 	a(3,2) = 38; 	a(3,3) = 9; 	a(3,4) = 8;
	a(4,0) = 42; 	a(4,1) = 21; 	a(4,2) = 8; 	a(4,3) = 11; 	a(4,4) = 24;
	a.print();
	cout << a.determinant();
	
	return 0;
}
