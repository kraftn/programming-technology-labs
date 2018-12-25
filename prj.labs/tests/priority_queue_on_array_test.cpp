#include "priority_queue_on_array/priority_queue_on_array.h"

#include <iostream>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

int main() {
  PriorityQueueOnArray x;
  std::cout << "Queue x before filling: " << x << std::endl;

  std::cout << "Queue x after filling: ";
  for (ptrdiff_t i(0); i < 5; i++) {
    x.Push(i, i);
  }
  std::cout << x << std::endl;

  std::cout << "Get top element of queue x: " << x.Top() << std::endl;

  std::cout << "Queue y(x): ";
  PriorityQueueOnArray y(x);
  std::cout << y << std::endl;

  std::cout << "Queue z=x: ";
  PriorityQueueOnArray z;
  z = x;
  std::cout << z << std::endl;

  std::cout << "Queue y after y.Pop() two times: ";
  y.Pop();
  y.Pop();
  std::cout << y << std::endl;

  std::cout << "Queue z after z.Push(50, 50): ";
  z.Push(50, 50);
  std::cout << z << std::endl;

  std::cout << "Queue z after z.Push(-5, 10): ";
  z.Push(-5, 10);
  std::cout << z << std::endl;

  std::cout << "Queue x after x=y=z: ";
  x = y = z;
  std::cout << x << std::endl;

  std::cout << "Queue x after x=x: ";
  x = x;
  std::cout << x << std::endl;

  std::cout << "x.IsEmpty(): " << x.IsEmpty() << std::endl;

  std::cout << "Queue x after x.Pop() 6 times: ";
  for (ptrdiff_t i(0); i < 7; i += 1) {
    x.Pop();
  }
  std::cout << x << std::endl;

  std::cout << "x.IsEmpty(): " << x.IsEmpty() << std::endl;

  std::cout << "Try x.Top(): ";
  try {
    int32_t t = x.Top();
  }
  catch (std::logic_error excepton) {
    std::cout << "queue is empty" << std::endl;
  }

  return 0;
}
