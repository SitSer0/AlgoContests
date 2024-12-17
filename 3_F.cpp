#include <cmath>
#include <complex>
#include <iostream>
#include <vector>
int64_t NearPow(int64_t val) {
  val--;
  int64_t ans = 1;
  while (val > 0) {
    val = val / 2;
    ans = ans * 2;
  }
  return ans;
}

void Fft(std::vector<std::complex<double>>& arr, std::complex<double> root) {
  if (static_cast<int>(arr.size()) == 1) {
    return;
  }
  std::vector<std::complex<double>> p_1(arr.size() / 2);
  std::vector<std::complex<double>> p_0(arr.size() / 2);
  for (size_t i = 0; i < arr.size(); ++i) {
    if (i % 2 == 0) {
      p_0[i / 2] = arr[i];
    } else {
      p_1[i / 2] = arr[i];
    }
  }
  Fft(p_1, root * root);
  Fft(p_0, root * root);
  std::complex<double> temp = 1;
  for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
    arr[i] = temp * p_1[i % (arr.size() / 2)] + p_0[i % (arr.size() / 2)];
    temp *= root;
  }
}

void Mult(std::vector<std::complex<double>>& first,
          std::vector<std::complex<double>>& second) {
  int64_t new_size =
      NearPow(static_cast<int64_t>(first.size() + second.size() - 1));
  first.resize(new_size);
  second.resize(new_size);
  double angle = 2 * M_PI / (double)new_size;
  std::complex<double> root = std::complex<double>(cos(angle), sin(angle));
  Fft(first, root);
  Fft(second, root);
  for (size_t i = 0; i < first.size(); ++i) {
    first[i] *= second[i];
  }
  root = std::complex<double>(cos(angle), -sin(angle));
  Fft(first, root);
}

void Read(std::vector<std::complex<double>>& arr, int64_t& size_arr) {
  std::cin >> size_arr;
  int64_t input;
  for (int64_t i = 0; i < size_arr + 1; ++i) {
    std::cin >> input;
    arr.emplace_back(input, 0);
  }
}

int main() {
  int64_t first_sz;
  int64_t second_sz;
  std::vector<std::complex<double>> first;
  std::vector<std::complex<double>> second;
  Read(first, first_sz);
  Read(second, second_sz);
  Mult(first, second);
  std::cout << first_sz + second_sz << ' ';
  for (int64_t i = 0; i < first_sz + second_sz + 1; ++i) {
    std::cout << static_cast<int64_t>(round((first[i].real() / first.size())))
              << " ";
  }
}