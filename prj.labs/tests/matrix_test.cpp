#include <iostream>
#include <stdexcept>

#include "matrix/matrix.h"

int main() {
  using namespace std;

  Matrix default_matrix;
  cout << "Create a default matrix: " << endl;
  cout << default_matrix << endl;

  Matrix x(3, 4);
  cout << "Matrix x(3,4) before filling:" << endl;
  cout << x;
  cout << "Number of rows of x: " << x.GetNumberRows() << endl;
  cout << "Number of columns of x: " << x.GetNumberColumns() << endl << endl;

  for (int i = 0; i < x.GetNumberRows(); i++) {
    for (int j = 0; j < x.GetNumberColumns(); j++) {
      x.Value(i, j) = i * j;
    }
  }
  cout << "Matrix x(3,4) after filling:" << endl;
  cout << x;
  cout << endl;

  Matrix y(x);
  cout << "Matrix y(x):" << endl;
  cout << y;
  cout << endl;

  Matrix z(3, 4);
  for (int i = 0; i < z.GetNumberRows(); i++) {
    for (int j = 0; j < z.GetNumberColumns(); j++) {
      z.Value(i, j) = i;
    }
  }
  cout << "Matrix z(3,4):" << endl;
  cout << z;
  cout << endl;

  x = z;
  cout << "Matrix x after x=z:" << endl;
  cout << x;
  cout << endl;

  (x = z) = y;
  cout << "Matrix x after (x=z)=y:" << endl;
  cout << x;
  cout << endl;

  x = x;
  cout << "Matrix x after x=x:" << endl;
  cout << x;
  cout << endl;

  cout << "Result of x+z: " << endl;
  cout << x + z << endl;

  cout << "Result of x-z: " << endl;
  cout << x - z << endl;

  cout << "Result of x*3: " << endl;
  cout << x * 3 << endl;

  cout << "Result of 2*x: " << endl;
  cout << 2 * x << endl;

  Matrix a(4, 3);
  for (int i = 0; i < a.GetNumberRows(); i++) {
    for (int j = 0; j < a.GetNumberColumns(); j++) {
      a.Value(i, j) = i * 2;
    }
  }
  cout << "Matrix a(4,3):" << endl;
  cout << a;
  cout << endl;

  cout << "Result of x*a: " << endl;
  cout << x* a << endl;

  try {
    Matrix t(-1, 1);
  }
  catch (const exception& except) {
    cout << "Trying to create Matrix t(-1,1) is failed" << endl;
  }
  try {
    x = Matrix(3, 5);
  }
  catch (const invalid_argument& except) {
    cout << "Matrix(3, 5) has 3x5 sizes. x=Matrix(3, 5) is failed" << endl;
  }
  try {
    int32_t t = x.Value(-1, -4);
  }
  catch (const out_of_range& except) {
    cout << "Trying to get x.Value(-1,-4) is failed" << endl;
  }
  try {
    Matrix(2, 1) + Matrix(1, 2);
  }
  catch (const invalid_argument& except) {
    cout << "Matrix(2, 1) + Matrix(1, 2) is failed" << endl;
  }
  try {
    Matrix(2, 1) - Matrix(1, 2);
  }
  catch (const invalid_argument& except) {
    cout << "Matrix(2, 1) - Matrix(1, 2) is failed" << endl;
  }
  try {
    Matrix(2, 3) * Matrix(1, 2);
  }
  catch (const invalid_argument& except) {
    cout << "Matrix(2, 3) * Matrix(1, 2) is failed" << endl;
  }
  try {
    Matrix(2, -3);
  }
  catch (const invalid_argument& except) {
    cout << "Create Matrix(2, -3) is failed" << endl;
  }
  return 0;
}
