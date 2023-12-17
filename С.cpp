#include <iostream>
#include <vector>

class SecTree {
 public:
  static int LeftChild(int index) { return 2 * index + 1; }
  static int RightChild(int index) { return 2 * index + 2; }

  void InitTree(int number) {
    int inp;
    for (int i = 0; i < number; ++i) {
      std::cin >> inp;
      arr_.push_back(inp);
      for (int j = 0; j < 4; ++j) {
        tree_.push_back(0);
      }
    }
    BuildTree(0, 0, number - 1);
  }

  void BuildTree(int vertex, int left, int right) {
    if (right == left) {
      tree_[vertex] = arr_[left];
      return;
    }
    int mid = (left + right) / 2;
    BuildTree(LeftChild(vertex), left, mid);
    BuildTree(RightChild(vertex), mid + 1, right);
    tree_[vertex] =
        std::max(tree_[LeftChild(vertex)], tree_[RightChild(vertex)]);
  }

  void Change(int vertex, int left, int right, int index, int new_value) {
    if (left == right) {
      tree_[vertex] = new_value;
      return;
    }
    int mid = (left + right) / 2;
    if (index <= mid) {
      Change(LeftChild(vertex), left, mid, index, new_value);
    } else {
      Change(RightChild(vertex), mid + 1, right, index, new_value);
    }
    tree_[vertex] =
        std::max(tree_[LeftChild(vertex)], tree_[RightChild(vertex)]);
  }

  int Get(int vertex, int left, int right, int q_left, int x_val) {
    if (tree_[vertex] < x_val) {
      return -1;
    }
    if (left == right) {
      return left;
    }
    int mid = (left + right) / 2;
    if (mid >= q_left && tree_[LeftChild(vertex)] >= x_val) {
      int result = Get(LeftChild(vertex), left, mid, q_left, x_val);
      if (result != -1) {
        return result;
      }
    }
    return Get(RightChild(vertex), mid + 1, right, std::max(q_left, mid + 1),
               x_val);
  }

 private:
  std::vector<int> tree_;
  std::vector<int> arr_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int number;
  int req_count;
  std::cin >> number >> req_count;
  SecTree sec_tree;
  sec_tree.InitTree(number);
  int type;
  int ind;
  int value;
  for (int i = 0; i < req_count; ++i) {
    std::cin >> type >> ind >> value;
    if (type == 1) {
      int ans;
      ans = sec_tree.Get(0, 0, number - 1, ind - 1, value);
      std::cout << (ans == -1 ? ans : ans + 1) << '\n';
    } else {
      sec_tree.Change(0, 0, number - 1, ind - 1, value);
    }
  }
  return 0;
}