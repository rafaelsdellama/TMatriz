#include <iostream>
#include "TMatriz.hpp"

using namespace std;

int main(int argc, char** argv) {
	
	matriz<int> a(3,3,0);
	a(0,0) = 1;
	a(0,1) = 1;
	a(1,0) = 1;
	a(1,1) = 1;
	a.print();

	matriz<int> b(3,3,0);
	b(0,0) = 1;
	b(0,1) = 0;
	b(1,0) = 0;
	b(1,1) = 1;
	b.print();
	
	matriz<int> s = a*b + b*4 - a;
	s.print();
	
	s.determinant();
	return 0;
}
