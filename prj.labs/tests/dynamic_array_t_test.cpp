#include <iostream>
#include <stdexcept>

#include "dynamic_array_t/dynamic_array_t.h"

int main() {
  using namespace std;

  DynamicArrayT<int32_t> dynamic_array;
  cout << "DynamicArray dynamic_array is " << dynamic_array << endl;
  cout << "Size of dynamic_array: " << dynamic_array.Size() << endl;
  cout << "Capacity of dynamic_array: " << dynamic_array.Capacity()
       << endl << endl;

  DynamicArrayT<int32_t> x(5);
  cout << "DynamicArray x(5) before filling is " << x << endl;
  cout << "Size of x: " << x.Size() << endl;
  cout << "Capacity of x: " << x.Capacity() << endl << endl;

  for (int i = 0; i < x.Size(); i++) {
    x[i] = i * i;
  }
  cout << "DynamicArray x(5) after filling is " << x << endl << endl;

  DynamicArrayT<int32_t> y(x);
  cout << "DynamicArray y(x) is " << y << endl << endl;

  DynamicArrayT<int32_t> z(5);
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
    DynamicArrayT<int>(-3);
  }
  catch (const invalid_argument& except) {
    cout << "Trying to create DynamicArrayT<int>(-3) is failed" << endl;
  }

  cout << "---------------------------------------------------------------"
       << endl;

  DynamicArrayT<double> dynamic_array_new;
  cout << "DynamicArray dynamic_array_new is " << dynamic_array_new << endl;
  cout << "Size of dynamic_array_new: " << dynamic_array_new.Size() << endl;
  cout << "Capacity of dynamic_array_new: " << dynamic_array_new.Capacity() <<
       endl << endl;

  DynamicArrayT<double> x_new(5);
  cout << "DynamicArray x_new(5) before filling is " << x_new << endl;
  cout << "Size of x_new: " << x_new.Size() << endl;
  cout << "Capacity of x_new: " << x_new.Capacity() << endl << endl;

  for (int i = 0; i < x_new.Size(); i += 1) {
    x_new[i] = 0.1 * i * i;
  }
  cout << "DynamicArray x_new(5) after filling is " << x_new << endl << endl;

  DynamicArrayT<double> y_new(x_new);
  cout << "DynamicArray y_new(x_new) is " << y_new << endl << endl;

  DynamicArrayT<double> z_new(5);
  for (int i = 0; i < z.Size(); i += 1) {
    z_new[i] = 0.1 * i;
  }
  cout << "DynamicArray z_new(5) is " << z_new << endl << endl;


  x_new = z_new;
  cout << "DynamicArray x after x_new=z_new is " << x_new << endl
       << endl;

  (x_new = z_new) = y_new;
  cout << "DynamicArray x_new after (x_new=z_new)=y_new is " << x_new << endl <<
       endl;

  x_new = x_new;
  cout << "DynamicArray x_new after x_new=x_new is " << x_new << endl << endl;

  cout << "x_new[1] is " << x_new[1] << endl << endl;

  x_new.Resize(3);
  cout << "DynamicArray x_new after x_new.Resize(3) is " << x_new << endl;
  cout << "Size of x_new: " << x_new.Size() << endl;
  cout << "Capacity of x_new: " << x_new.Capacity() << endl << endl;

  x_new.Resize(7);
  cout << "DynamicArray x_new after x_new.Resize(7) is " << x_new << endl;
  cout << "Size of x_new: " << x_new.Size() << endl;
  cout << "Capacity of x_new: " << x_new.Capacity() << endl << endl;

  x_new.Resize(15);
  cout << "DynamicArray x_new after x_new.Resize(15) is " << x_new << endl;
  cout << "Size of x_new: " << x_new.Size() << endl;
  cout << "Capacity of x_new: " << x_new.Capacity() << endl << endl;

  x_new.Resize(0);
  cout << "DynamicArray x_new after x_new.Resize(0) is " << x_new << endl;
  cout << "Size of x_new: " << x_new.Size() << endl;
  cout << "Capacity of x_new: " << x_new.Capacity() << endl << endl;

  try {
    x_new.Resize(-1);
  }
  catch (const length_error& except) {
    cout << "x_new.Resize(-1) is failed" << endl;
  }

  try {
    double value = y_new[-2];
  }
  catch (const out_of_range& except) {
    cout << "Trying to get y_new[-2] is failed" << endl;
  }

  try {
    y_new[5] = 50.2;
  }
  catch (const out_of_range& except) {
    cout << "Trying to set y_new[5] to 50 is failed" << endl;
  }

  return 0;
}
