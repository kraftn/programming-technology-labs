#include <sstream>

#include "complex/complex.h"

bool testParse(const std::string& str) {
  using namespace std;
  istringstream istrm(str);
  Complex z;
  istrm >> z;
  if (istrm.good()) {
    cout << "Read success: " << str << " -> " << z << endl;
  } else {
    cout << "Read error : " << str << " -> " << z << endl;
  }
  return istrm.good();
}

int main() {
  using namespace std;

  cout << "Create complex number 15-4i: x=";
  Complex x(15.0, -4.0);
  cout << x << endl;
  cout << "Create complex number -11: y=";
  Complex y(-11.0);
  cout << y << endl << endl;

  testParse("{8.9,9}");
  testParse("{8.9, 9}");
  testParse("{8.9,9");
  cout << endl;

  cout << "x after x += Complex(5.0, 3.5): "
       << (x += Complex(5.0, 3.5)) << endl;
  cout << "x after x -= Complex(1.0, 4.0): "
       << (x -= Complex(1.0, 4.0)) << endl;
  cout << "x after x *= Complex(3.0, 2.0): "
       << (x *= Complex(3.0, 2.0)) << endl;
  cout << "x after x /= Complex(1.0, -2.0): "
       << (x /= Complex(1.0, -2.0)) << endl << endl;

  x = Complex(1.0, -3.0);
  cout << "x after x = Complex(1, -3): " << x << endl << endl;

  cout << "x after x += 2.0: " << (x += 2.0) << endl;
  cout << "x after x -= 2.0: " << (x -= 2.0) << endl;
  cout << "x after x *= -11.0: " << (x *= -11.0) << endl;
  cout << "x after x /= -11.0: " << (x /= -11.0) << endl << endl;

  cout << "Create complex number 5-4i: z=";
  Complex z(5.0, 4.0);
  cout << z << endl << endl;

  cout << x << "+" << z << "=" << x + z << endl;
  cout << x << "-" << z << "=" << x - z << endl;
  cout << x << "*" << z << "=" << x* z << endl;
  cout << x << "/" << z << "=" << x / z << endl << endl;

  cout << x << "+" << 2.0 << "=" << x + 2.0 << endl;
  cout << x << "-" << 2.0 << "=" << x - 2.0 << endl;
  cout << x << "*" << -11.0 << "=" << x * -11.0 << endl;
  cout << x << "/" << 3.0 << "=" << x / 3.0 << endl << endl;

  cout << 2.0 << "+" << x << "=" << 2.0 + x << endl;
  cout << 2.0 << "-" << x << "=" << 2.0 - x << endl;
  cout << -11.0 << "*" << x << "=" << -11.0 * x << endl;
  cout << 3.0 << "/" << x << "=" << 3.0 / x << endl << endl;

  if (Complex(1.0, -2.0) == Complex(1.0, -2.0)) {
    cout << "1-2i==1-2i" << endl;
  }
  if (Complex(1.0, 3.0) != Complex(4.0, 5.0)) {
    cout << "1+3i!=4+5i" << endl;
  }
  cout << endl;

  cout << "x after (x=y)=z: ";
  (x = y) = z;
  cout << x << endl;
  cout << "x after x=x: ";
  x = x;
  cout << x << endl;

  return 0;
}
