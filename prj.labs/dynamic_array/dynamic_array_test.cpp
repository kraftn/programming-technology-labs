#include <iostream>
#include <stdexcept>
#include "dynamic_array.h"

int main() {
	using namespace std;

	DynamicArray x(5);
	cout << "DynamicArray x(5) before filling:" << endl;
	for (int i = 0; i < x.Size(); i++) {
		cout << i << ": " << x[i] << endl;
	}
	cout << "Size of x: " << x.Size() << endl << endl;

	for (int i = 0; i < x.Size(); i++) {
		x[i] = i*i;
	}
	cout << "DynamicArray x(5) after filling:" << endl;
	for (int i = 0; i < x.Size(); i++) {
		cout << i <<": " << x[i] << endl;
	}
	cout << endl;

	DynamicArray y(x);
	cout << "DynamicArray y(x):" << endl;
	for (int i = 0; i < y.Size(); i++) {
		cout << i << ": " << y[i] << endl;
	}
	cout << endl;

	DynamicArray z(5);
	for (int i = 0; i < z.Size(); i++) {
		z[i] = i;
	}
	cout << "DynamicArray z(5):" << endl;
	for (int i = 0; i < z.Size(); i++) {
		cout << i << ": " << z[i] << endl;
	}
	cout << endl;

	x = z;
	cout << "DynamicArray x after x=z:" << endl;
	for (int i = 0; i < x.Size(); i++) {
		cout << i << ": " << x[i] << endl;
	}
	cout << endl;

	try {
		DynamicArray t(-1);
	}
	catch (const invalid_argument& except) {
		cout << "Trying to create DynamicArray t(-1) is failed" << endl;
	}
	try {
		int32_t t=x[-2];
	}
	catch (const out_of_range& except) {
		cout << "Trying to get x[-2] is failed" << endl;
	}
	DynamicArray v(6);
	try {
		v = x;
	}
	catch (const invalid_argument& except) {
		cout << "DynamicArray v consists of 6 elements. v=x is failed" << endl;
	}

	return 0;
}