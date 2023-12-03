#include <iostream>
#include <vector>

class MergeTree {
 private:
  std::vector<std::vector<int>> tree_;
  std::vector<int> arr_;

  static int LeftChild(int vertex) { return 2 * vertex + 1; }
  static int RightChild(int vertex) { return 2 * vertex + 2; }

  static int Ans(std::vector<int>& vec, int value) {
    int left = 0;
    int right = vec.size() - 1;
    while (right - left > 1) {
      int mid = (left + right) / 2;
      if (vec[mid] > value) {
        right = mid;
      } else {
        left = mid;
      }
    }
    if (vec[right] <= value) {
      return right + 1;
    }
    if (vec[left] > value) {
      return 0;
    }
    return left + 1;
  }

  static void Merge(std::vector<int>& vec1, std::vector<int>& vec2,
                    std::vector<int>& vec) {
    int len1 = vec1.size();
    int len2 = vec2.size();
    int ind = 0;
    int jnd = 0;
    while (ind < len1 && jnd < len2) {
      if (vec1[ind] < vec2[jnd]) {
        vec.push_back(vec1[ind]);
        ind++;
      } else {
        vec.push_back(vec2[jnd]);
        jnd++;
      }
    }
    while (ind < len1) {
      vec.push_back(vec1[ind]);
      ind++;
    }
    while (jnd < len2) {
      vec.push_back(vec2[jnd]);
      jnd++;
    }
  }

  void Build(int vertex, int left, int right) {
    if (left == right) {
      tree_[vertex].push_back(arr_[left]);
      return;
    }
    int mid = (left + right) / 2;
    Build(LeftChild(vertex), left, mid);
    Build(RightChild(vertex), mid + 1, right);
    Merge(tree_[LeftChild(vertex)], tree_[RightChild(vertex)], tree_[vertex]);
  }

 public:
  int q_left;
  int q_right;
  MergeTree(int number) {
    tree_.resize(4 * number, std::vector<int>(0));
    arr_.resize(number);
    for (int i = 0; i < number; ++i) {
      std::cin >> arr_[i];
    }
    Build(0, 0, number - 1);
  }

  int GetCount(int vertex, int left, int right, int value) {
    if (left > q_right || right < q_left) {
      return 0;
    }
    if (q_left <= left && right <= q_right) {
      return Ans(tree_[vertex], value);
    }
    int mid = (left + right) / 2;
    return GetCount(LeftChild(vertex), left, mid, value) +
           GetCount(RightChild(vertex), mid + 1, right, value);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int number;
  int count_req;
  std::cin >> number >> count_req;
  MergeTree tree(number);
  int left;
  int right;
  int min;
  int max;
  for (int i = 0; i < count_req; ++i) {
    std::cin >> left >> right >> min >> max;
    tree.q_left = left - 1;
    tree.q_right = right - 1;
    std::cout << tree.GetCount(0, 0, number - 1, max) -
                     tree.GetCount(0, 0, number - 1, min - 1)
              << "\n";
  }
}