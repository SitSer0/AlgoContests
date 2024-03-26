#include <iostream>
#include <vector>

const int kInf = 1000000000;

void Read(std::vector<int>& arr, int size) {
  for (int i = 0; i < size; ++i) {
    std::cin >> arr[i];
  }
}

int main() {
  int number;
  int max;
  std::cin >> number >> max;
  std::vector<int> weight(number);
  std::vector<int> cost(number);
  Read(weight, number);
  Read(cost, number);
  std::vector<std::vector<int>> dp(number + 1, std::vector<int>(max + 1, 0));
  std::vector<std::vector<bool>> used(number + 1,
                                      std::vector<bool>(max + 1, false));
  dp[0][0] = 0;
  for (int i = 1; i <= number; ++i) {
    for (int j = 0; j <= max; ++j) {
      if (j - weight[i - 1] >= 0) {
        if (dp[i - 1][j - weight[i - 1]] + cost[i - 1] > dp[i - 1][j]) {
          dp[i][j] = dp[i - 1][j - weight[i - 1]] + cost[i - 1];
          used[i][j] = true;
        } else {
          dp[i][j] = dp[i - 1][j];
        }
      } else {
        dp[i][j] = dp[i - 1][j];
      }
    }
  }

  std::vector<int> ans;
  int size = 0;
  int index = number;
  int jndex = max;
  while (index > 0 && jndex > 0) {
    if (used[index][jndex]) {
      ans.push_back(index - 1);
      jndex -= weight[index - 1];
      size++;
    }
    --index;
  }

  for (int i = 0; i < size; ++i) {
    std::cout << ans[size - 1 - i] + 1 << "\n";
  }

  return 0;
}