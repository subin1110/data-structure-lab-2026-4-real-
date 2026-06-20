#include "Polynomial.h"
using namespace std;

void main() {
	Polynomial a, b, c;
	a.read();
	b.read();
	c.add(a, b);
	a.display("A= ");
	b.display("B= ");
	c.display("C= ");
	a.negate();
	a.display("-A= ");
	cout << "Is the highest order of B Zero?" << boolalpha << b.isZero() << endl;
}