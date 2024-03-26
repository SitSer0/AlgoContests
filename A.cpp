#include <algorithm>
#include <iostream>
#include <vector>

int BinSearch(std::vector<int>& arr, int val) {
  size_t left = 0;
  size_t right = arr.size();
  while (right - left > 1) {
    size_t mid = (right + left) / 2;
    if (arr[mid] < val) {
      left = mid;
    } else {
      right = mid;
    }
  }
  return right;
}

void CalcDP(std::vector<int>& dp, std::vector<int>& arr, std::vector<int>& pos,
            std::vector<int>& prev, int& max_len) {
  int num = (int)arr.size();
  for (int i = 0; i < num; ++i) {
    int len = BinSearch(dp, arr[i]);
    if (dp[len - 1] <= arr[i] && arr[i] < dp[len]) {
      max_len = std::max(max_len, len);
      pos[len] = i;
      dp[len] = arr[i];
      prev[i] = pos[len - 1];
    }
  }
}

void ReverseProMax(std::vector<int>& arr) {
  for (size_t i = 0; i < arr.size() / 2; ++i) {
    std::swap(arr[i], arr[arr.size() - i - 1]);
  }
}

signed main() {
  int num;
  std::cin >> num;
  std::vector<int> arr(num);
  std::vector<int> dp(num + 1, __INT_MAX__);
  std::vector<int> pos(num + 1, -1);
  std::vector<int> prev(num + 1);
  for (int i = 0; i < num; ++i) {
    std::cin >> arr[i];
  }
  ReverseProMax(arr);
  int max_len = 0;
  dp[0] = -__INT_MAX__;
  CalcDP(dp, arr, pos, prev, max_len);
  std::vector<int> ans;
  int cur = pos[max_len];
  while (cur != -1) {
    ans.push_back(num - cur);
    cur = prev[cur];
  }
  std::cout << ans.size() << '\n';
  for (int val : ans) {
    std::cout << val << ' ';
  }
}
