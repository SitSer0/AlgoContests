#include <iostream>
#include <vector>

const int cKonst = 100000;

struct Graph {
  int number;
  std::vector<std::vector<int>> matrix;
  Graph(int number)
      : number(number),
        matrix(
            std::vector<std::vector<int>>(number, std::vector<int>(number))) {}
  void ReadMatrix() {
    for (int i = 0; i < number; ++i) {
      for (int j = 0; j < number; ++j) {
        std::cin >> matrix[i][j];
      }
    }
  }

  std::vector<int> FindNegativeCycle() {
    std::vector<int> dist(number, 0);
    std::vector<int> pred(number, -1);
    int last = -1;

    for (int k = 0; k < number; ++k) {
      last = -1;
      for (int i = 0; i < number; ++i) {
        for (int j = 0; j < number; ++j) {
          if (matrix[i][j] < cKonst && dist[i] + matrix[i][j] < dist[j]) {
            dist[j] = dist[i] + matrix[i][j];
            pred[j] = i;
            last = j;
          }
        }
      }
    }

    if (last == -1) {
      return std::vector<int>(0);
    }
    for (int i = 0; i < number; ++i) {
      last = pred[last];
    }

    std::vector<int> ans;
    for (int v = last;; v = pred[v]) {
      ans.push_back(v);
      if (v == last && ans.size() > 1) {
        break;
      }
    }
    return ans;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int number;
  std::cin >> number;
  Graph bro(number);
  bro.ReadMatrix();
  std::vector<int> ans = bro.FindNegativeCycle();
  if (ans.empty()) {
    std::cout << "NO\n";
  } else {
    std::cout << "YES\n";
    std::cout << ans.size() << "\n";
    for (size_t i = 0; i < ans.size(); ++i) {
      std::cout << ans[ans.size() - 1 - i] + 1 << " ";
    }
  }
  return 0;
}