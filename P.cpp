#include <cmath>
#include <iostream>
#include <vector>

// Мы имеем то, что для каждой маски следующая за ней может быть либо такой же
// (но только в том случае если эта маска вида 10101010... или 01010101...) либо
// инвертированной, других быть не может. Если маска вида 1010101/010101, то
// должно выполнятся условие mask xor ((1 << number) - 1) == InvMask

const int64_t kMod = 1000000007;

void PrintMask(int64_t mask, int number) {
  if (number == 0) {
    return;
  }
  PrintMask(mask / 2, number - 1);
  std::cout << mask % 2;
}

int Bit(int mask, int index) { return ((mask >> index) & 1); }

int InvMask(int mask, int number) { return (1 << number) - mask - 1; }

bool IsCher(int mask, int number) {
  return (mask + (mask << 1) + (Bit(mask, 0) xor 1)) % (1 << number) ==
         ((1 << number) - 1);
}

bool IsGood(std::string temp, int mask, int number) {
  for (int i = 0; i < number; ++i) {
    if ((temp[number - i - 1] == '+' && Bit(mask, i) != 1) ||
        (temp[number - i - 1] == '-' && Bit(mask, i) != 0)) {
      return false;
    }
  }
  return true;
}

bool CanBe(int number, int mask1, int mask2) {
  for (int i = 0; i < number - 1; ++i) {
    if (Bit(mask1, i) + Bit(mask1, i + 1) + Bit(mask2, i) + Bit(mask2, i + 1) !=
        2) {
      return false;
    }
  }
  return true;
}

void CalcGoodMaks(int& good_mask1, int& good_mask2, int number) {
  for (int i = 0; i < number; ++i) {
    if (i % 2 == 0) {
      good_mask1 += std::pow(2, i);
    } else {
      good_mask2 += std::pow(2, i);
    }
  }
}

int SolveDP(int number, std::vector<std::vector<int64_t>>& dp, std::vector<std::string>& arr, int count) {
  int good_mask1 = 0;
  int good_mask2 = 0;
  int ans = 0;
  CalcGoodMaks(good_mask1, good_mask2, number);
  for (int mask = 0; mask < std::pow(2, number); ++mask) {
    if (mask == good_mask1 || mask == good_mask2 ||
        !IsGood(arr[0], mask, number)) {
      continue;
    }
    for (int i = 0; i < count; ++i) {
      if (IsGood(arr[i], (i % 2 == 0 ? mask : InvMask(mask, number)), number)) {
        dp[mask][i] = 1;
      } else {
        break;
      }
    }
  }
  dp[good_mask2][0] = IsGood(arr[0], good_mask1, number) ? 1 : 0;
  dp[good_mask1][0] = IsGood(arr[0], good_mask2, number) ? 1 : 0;
  for (int i = 1; i < count; ++i) {
    int point = (IsGood(arr[i], good_mask1, number) ? 1 : 0) +
        (IsGood(arr[i], good_mask2, number) ? 1 : 0);
    dp[good_mask2][i] = (dp[good_mask2][i - 1] * point) % kMod;
    dp[good_mask1][i] = (dp[good_mask1][i - 1] * point) % kMod;
  }
  for (int i = 0; i < std::pow(2, number); ++i) {
    ans = (ans + dp[i][count - 1]) % kMod;
  }
  return ans;
}

int main() {
  for (int i = 1; i < 100; ++i) {
    PrintMask((pow(4, (i + 1) / 2) - 1) / 3, i);
    std::cout << " " << i << "\n";
  }
  int number;
  int count;
  char chr;
  std::string temp;
  std::cin >> number >> count;
  std::vector<std::string> arr(count);
  for (int i = 0; i < number; ++i) {
    for (int j = 0; j < count; ++j) {
      std::cin >> chr;
      arr[j] += chr;
    }
  }
  std::vector<std::vector<int64_t>> dp(std::pow(2, number),
                                       std::vector<int64_t>(count, 0));
  int64_t ans = 0;
  std::cout << SolveDP(number, dp, arr, count);
  return 0;
}
