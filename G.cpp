#include <iostream>
#include <vector>

const int kMagicNumber10 = 10;
const int kMagicNumber22 = 20;

unsigned long long PwTen(int kk) {
  unsigned long long ans = 1;
  for (int i = 0; i < kk; ++i) {
    ans *= kMagicNumber10;
  }
  return ans;
}

void RadixSort(std::vector<unsigned long long>& arr, int number, int index,
               int left, int right) {
  if ((right - left < 1) || index == kMagicNumber22 + 1) {
    return;
  }
  std::vector<std::vector<unsigned long long> > raz(
      kMagicNumber10, std::vector<unsigned long long>(0));
  for (int i = left; i <= right; ++i) {
    unsigned long long ind =
        (arr[i] / PwTen(kMagicNumber22 - index)) % kMagicNumber10;
    raz[ind].push_back(arr[i]);
  }
  int kk;
  for (int i = 0; i < kMagicNumber10; i++) {
    kk = 0;
    int razsize = raz[i].size();
    for (int j = 0; j < razsize; ++j) {
      arr[left + kk] = raz[i][j];
      kk++;
    }
    RadixSort(arr, number, index + 1, left, left + razsize - 1);
    left += razsize;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int number;
  std::cin >> number;
  std::vector<unsigned long long> input(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> input[i];
  }
  RadixSort(input, number, 0, 0, number - 1);
  for (int i = 0; i < number; ++i) {
    std::cout << input[i] << "\n";
  }
}