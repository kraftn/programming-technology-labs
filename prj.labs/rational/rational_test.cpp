#include <sstream>
#include "rational.h"

bool testParse(const std::string& str) {
	using namespace std;
	istringstream istrm(str);
	Rational z;
	istrm >> z;
	if (istrm.good()) {
		cout << "Read success: " << str << " -> " << z << endl;
	}
	else {
		cout << "Read error : " << str << " -> " << z << endl;
	}
	return istrm.good();
}

int main() {
	using namespace std;

	cout << "Create rational number 4/0: ";
	try {
		Rational x(4, 0);
	}
	catch (const invalid_argument& exept) {
		cout << "Zero denominator in Rational" <<endl;
	}
	cout << "Create rational number 4/2: y=";
	Rational y(4, 2);
	cout << y << endl;
	cout << "Create rational number 3/-9: z=";
	Rational z(3, -9);
	cout << z << endl;
	cout << "Create rational number -5/10: v=";
	Rational v(-5, 10);
	cout << v << endl;
	cout << "Create rational number -6/-30: w=";
	Rational w(-6, -30);
	cout << w << endl;
	cout << "Create rational number -6: e=";
	Rational e(-6);
	cout << e << endl << endl;

	testParse("(1/7)");
	testParse("(1/2");
	try {
		testParse("(12/0)");
	}
	catch (const invalid_argument& exept) {
		cout << "Reading (12/0) is failed" << endl << endl;
	}

	cout << "y after y+=z: " << (y += z) << endl;
	cout << "y after y-=v: " << (y -= v) << endl;
	cout << "y after y*=w: " << (y *= w) << endl;
	cout << "y after y/=z: " << (y /= z) << endl << endl;

	int32_t integ(2);
	cout << "z after z+=2: " << (z += integ) << endl;
	cout << "z after z-=2: " << (z -= integ) << endl;
	cout << "z after z*=2: " << (z *= integ) << endl;
	cout << "z after z/=2: " << (z /= integ) << endl << endl;

	cout << v << "+" << w << "=" << v + w << endl;
	cout << v << "-" << w << "=" << v - w << endl;
	cout << v << "*" << w << "=" << v * w << endl;
	cout << v << "/" << w << "=" << v / w << endl << endl;

	if (Rational(1, 3) == Rational(3, 9))cout << "(1/3)==(3/9)" << endl;
	if (Rational(1, 3) != Rational(2, 4))cout << "(1/3)!=(2/4)" << endl << endl;

	y = Rational(5, 6);
	cout << "y after y=(5/6): " << y << endl;
	
	return 0;
}
