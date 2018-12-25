#include "priority_queue_on_list/priority_queue_on_list.h"

#include <iostream>
#include <cstdint>

int main() {

  PriorityQueueOnList queue;
  std::cout << "PriorityQueueOnList queue is " << queue << std::endl;
  std::cout << "queue.IsEmpty(): " << queue.IsEmpty() << std::endl;

  PriorityQueueOnList queue_new;
  int32_t val(3), key(10);
  std::cout << "Let's push " << val << " with key " << key << std::endl;
  queue_new.Push(val, key);
  std::cout << "Queue is " << queue_new << std::endl;
  std::cout << "Is queue empty -> " << queue_new.IsEmpty() << std::endl;
  std::cout << "Top value is   -> " << queue_new.Top() << std::endl;
  std::cout << "Let's pop " << std::endl;
  queue_new.Pop();
  std::cout << "Queue is " << queue_new << std::endl;
  std::cout << "Is queue empty -> " << queue_new.IsEmpty() << std::endl;

  std::cout << "Let's push values from " << (val + 1) << " to " << (val + 3) << " with keys from " << val + 2 << " to " << val + 4 << std::endl;
  queue_new.Push(val + 1, val + 2);
  queue_new.Push(val + 2, val + 3);
  queue_new.Push(val + 3, val + 4);
  std::cout << "Queue is " << queue_new << std::endl;
  std::cout << "Top value is   -> " << queue_new.Top() << std::endl;

  PriorityQueueOnList x(queue_new);
  std::cout << "Queue x, which was copied from last queue, is " << x << std::endl;

  PriorityQueueOnList y;
  y = x;
  std::cout << "Queue y, which was copied from last queue using =, is " << y << std::endl;

  std::cout << "Let's pop in queue y" << std::endl;
  y.Pop();
  std::cout << "Queue y is " << y << std::endl;

  PriorityQueueOnList z;
  z.Push(15, -3);
  std::cout << "Queue z is " << z << std::endl;

  x = y = z;
  std::cout << "Queue x after x=y=z is " << x << std::endl;

  x = x;
  std::cout << "Queue x after x=x is " << x << std::endl;
}