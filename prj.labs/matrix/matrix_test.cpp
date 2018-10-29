#include <iostream>
#include <stdexcept>
#include "matrix.h"

int main() {
	using namespace std;

	Matrix x(3,4);
	cout << "Matrix x(3,4) before filling:" << endl;
	for (int i = 0; i < x.GetSize1(); i++) {
		for (int j = 0; j < x.GetSize2(); j++) {
			cout << x.data_[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Size1 of x: " << x.GetSize1() << endl;
	cout << "Size2 of x: " << x.GetSize2() << endl << endl;

	for (int i = 0; i < x.GetSize1(); i++) {
		for (int j = 0; j < x.GetSize2(); j++) {
			x.data_[i][j]=i*j;
		}
	}
	cout << "Matrix x(3,4) after filling:" << endl;
	for (int i = 0; i < x.GetSize1(); i++) {
		for (int j = 0; j < x.GetSize2(); j++) {
			cout << x.data_[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	Matrix y(x);
	cout << "Matrix y(x):" << endl;
	for (int i = 0; i < y.GetSize1(); i++) {
		for (int j = 0; j < y.GetSize2(); j++) {
			cout << y.data_[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	Matrix z(3,4);
	for (int i = 0; i < z.GetSize1(); i++) {
		for (int j = 0; j < z.GetSize2(); j++) {
			z.data_[i][j] = i;
		}
	}
	cout << "Matrix z(3,4):" << endl;
	for (int i = 0; i < z.GetSize1(); i++) {
		for (int j = 0; j < z.GetSize2(); j++) {
			cout << z.data_[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	x = z;
	cout << "Matrix x after x=z:" << endl;
	for (int i = 0; i < x.GetSize1(); i++) {
		for (int j = 0; j < x.GetSize2(); j++) {
			cout << x.data_[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	try {
		Matrix t(-1,1);
	}
	catch (const invalid_argument& except) {
		cout << "Trying to create Matrix t(-1,1) is failed" << endl;
	}
	Matrix v(3,5);
	try {
		v = x;
	}
	catch (const invalid_argument& except) {
		cout << "Matrix v has 3x5 sizes. v=x is failed" << endl;
	}

	return 0;
}