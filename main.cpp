#include <iostream>
#include <hare/hare.h>
#include <fmt/format.h>

int main() {
  hare::trace("");
  std::cout << fmt::format("Hello, World! {}!", 42) << std::endl;
  return 0;
}
