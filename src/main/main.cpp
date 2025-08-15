#include "liba/liba.h"
#include "libmycuda/libmycuda.hpp"

int main() {
  auto a = A{}; 
  auto b = A{};
  a = b;
  int data[] = {1, 2, 3, 4, 5};
  int size = sizeof(data) / sizeof(data[0]);
  addOne(data, size);
  return 0;
}
