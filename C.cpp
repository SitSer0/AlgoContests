#include <iostream>
#include <vector>

const int64_t kMaxNumber = 100001;
const int64_t kMaxCnt = 17;

int64_t BinSearch(std::vector<std::vector<int64_t>>& dp, int64_t jnd,
                  int64_t ind) {
  int64_t left = 1;
  int64_t right = jnd;
  while (right - left > 1) {
    int64_t mid = left + (right - left) / 2;
    if (dp[jnd - mid][ind] > dp[mid - 1][ind - 1]) {
      left = mid;
    } else {
      right = mid;
    }
  }
  return right;
}

int64_t Solve(int64_t number, int64_t cnt,
              std::vector<std::vector<int64_t>>& dp) {
  if (number > 1 && cnt == 0) {
    return -1;
  }
  if (number == 1) {
    return 0;
  }
  for (int64_t i = 1; i <= cnt; ++i) {
    dp[1][i] = 1;
  }
  for (int64_t i = 1; i < number; ++i) {
    dp[i][0] = __INT_MAX__;
    dp[i][1] = i;
  }
  for (int64_t i = 2; i <= cnt; ++i) {
    for (int64_t j = 2; j < number; ++j) {
      int64_t right = BinSearch(dp, j, i);
      dp[j][i] = std::max(dp[right - 1][i - 1], dp[j - right][i]) + 1;
    }
  }
  return dp[number - 1][cnt];
}

int main() {
  int64_t number;
  int64_t cnt;
  std::cin >> number >> cnt;
  cnt = std::min(cnt, kMaxCnt);
  std::vector<std::vector<int64_t>> dp(kMaxNumber,
                                       std::vector<int64_t>(kMaxCnt + 1));
  std::cout << Solve(number, cnt, dp);
}