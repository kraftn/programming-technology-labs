#include "stack_on_list/stack_on_list.h"

#include <iostream>

int main() {

  StackOnList stDef;
  std::cout << "Let's create stack. Stack is " << stDef << std::endl;
  std::cout << "Is def create stack emty -> " << stDef.IsEmpty() << std::endl;

  StackOnList st;
  int val(10);
  std::cout << "Let's push " << val << std::endl;
  st.Push(val);
  std::cout << "Stack is " << st << std::endl;
  std::cout << "Is stack empty -> " << st.IsEmpty() << std::endl;
  std::cout << "Top value is   -> " << st.Top() << std::endl;
  std::cout << "Let's pop " << std::endl;
  st.Pop();
  std::cout << "Stack is " << st << std::endl;
  std::cout << "Is stack empty -> " << st.IsEmpty() << std::endl;

  std::cout << "Let's push values from " << (val + 1) << " to " << (val + 3) << std::endl;
  st.Push(val + 1);
  st.Push(val + 2);
  st.Push(val + 3);
  std::cout << "Stack is " << st << std::endl;
  std::cout << "Top value is   -> " << st.Top() << std::endl;

  StackOnList x(st);
  std::cout << "Stack x, which was copied from last stack, is " << x << std::endl;

  StackOnList y;
  y = x;
  std::cout << "Stack y, which was copied from last stack using =, is " << y << std::endl;

  std::cout << "Let's pop in stack y" << std::endl;
  y.Pop();
  std::cout << "Stack y is " << y << std::endl;

  StackOnList z;
  z.Push(15);
  std::cout << "Stack z is " << z << std::endl;

  x = y = z;
  std::cout << "Stack x after x=y=z is " << x << std::endl;

  x = x;
  std::cout << "Stack x after x=x is " << x << std::endl;
}