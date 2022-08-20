#include <memory>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<int> *v = new std::vector<int>();
  std::vector<int> &vref = *v;
  std::unique_ptr<std::vector<int>> v2 = std::make_unique<std::vector<int>>();
  std::vector<int> v3;
  return 0;
}
