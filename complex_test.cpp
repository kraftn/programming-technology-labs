#include <sstream>
#include "complex.hpp"

bool testParse(const std::string& str) {
	using namespace std;
	istringstream istrm(str);
	Complex z;
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

	Complex z;
	z += Complex(8.0);
	cout << "z=" << z <<endl;
	z -= Complex(1.0, 4.0);
	cout << "z=" << z << endl;;
	z *= Complex(2.0, 3.0);
	cout << "z=" << z << endl;
	testParse("{8.9,9}");
	testParse("{8.9, 9}");
	testParse("{8.9,9");
	return 0;
}
