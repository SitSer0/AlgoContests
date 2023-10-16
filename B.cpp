#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

const int kMagicNumber = 8;

int main() {
  std::cout << std::setprecision(kMagicNumber) << std::fixed;
  int number;
  int request_count;
  int left;
  int right;
  std::cin >> number;
  std::vector<double> plants_volume(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> plants_volume[i];
  }
  std::vector<double> prefix_product_log(number + 1, 0.0);
  prefix_product_log[0] = 0.0;

  for (int i = 1; i <= number; ++i) {
    prefix_product_log[i] =
        prefix_product_log[i - 1] + log2(plants_volume[i - 1]);
  }

  std::cin >> request_count;
  for (int i = 0; i < request_count; ++i) {
    std::cin >> left >> right;
    std::cout << pow(2, (1.0 / (right - left + 1)) *
        (prefix_product_log[right + 1] -
            prefix_product_log[left]))
              << "\n";
  }
  return 0;
}