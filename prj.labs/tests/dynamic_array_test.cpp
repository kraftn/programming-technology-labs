#include <iostream>
#include <stdexcept>

#include "dynamic_array/dynamic_array.h"

int main() {
  using namespace std;

  DynamicArray dynamic_array;
  cout << "DynamicArray dynamic_array is " << dynamic_array << endl;
  cout << "Size of dynamic_array: " << dynamic_array.Size() << endl;
  cout << "Capacity of dynamic_array: " << dynamic_array.Capacity() << endl
       << endl;

  DynamicArray x(5);
  cout << "DynamicArray x(5) before filling is " << x << endl;
  cout << "Size of x: " << x.Size() << endl;
  cout << "Capacity of x: " << x.Capacity() << endl << endl;

  for (int i = 0; i < x.Size(); i++) {
    x[i] = i * i;
  }
  cout << "DynamicArray x(5) after filling is " << x << endl << endl;

  DynamicArray y(x);
  cout << "DynamicArray y(x) is " << y << endl << endl;

  DynamicArray z(5);
  for (int i = 0; i < z.Size(); i++) {
    z[i] = i;
  }
  cout << "DynamicArray z(5) is " << z << endl << endl;


  x = z;
  cout << "DynamicArray x after x=z is " << x << endl << endl;

  (x = z) = y;
  cout << "DynamicArray x after (x=z)=y is " << x << endl << endl;

  x = x;
  cout << "DynamicArray x after x=x is " << x << endl << endl;

  cout << "x[1] is " << x[1] << endl << endl;

  x.Resize(3);
  cout << "DynamicArray x after x.Resize(3) is " << x << endl;
  cout << "Size of x: " << x.Size() << endl;
  cout << "Capacity of x: " << x.Capacity() << endl << endl;

  x.Resize(7);
  cout << "DynamicArray x after x.Resize(7) is " << x << endl;
  cout << "Size of x: " << x.Size() << endl;
  cout << "Capacity of x: " << x.Capacity() << endl << endl;

  x.Resize(15);
  cout << "DynamicArray x after x.Resize(15) is " << x << endl;
  cout << "Size of x: " << x.Size() << endl;
  cout << "Capacity of x: " << x.Capacity() << endl << endl;

  x.Resize(0);
  cout << "DynamicArray x after x.Resize(0) is " << x << endl;
  cout << "Size of x: " << x.Size() << endl;
  cout << "Capacity of x: " << x.Capacity() << endl << endl;

  try {
    x.Resize(-1);
  }
  catch (const length_error& except) {
    cout << "x.Resize(-1) is failed" << endl;
  }

  try {
    int32_t value = y[-2];
  }
  catch (const out_of_range& except) {
    cout << "Trying to get y[-2] is failed" << endl;
  }

  try {
    y[5] = 50;
  }
  catch (const out_of_range& except) {
    cout << "Trying to set y[5] to 50 is failed" << endl;
  }

  try {
    DynamicArray arr(-1);
  }
  catch (const invalid_argument& except) {
    cout << "Trying to create DynamicArray arr(-1) is failed" << endl;
  }

  return 0;
}
