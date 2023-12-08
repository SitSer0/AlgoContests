#include <cmath>
#include <iostream>
#include <vector>

class SparseTable {
 public:

  SparseTable(int number) {
    arr.resize(number);
    int height = std::log2(number) + 1;
    table.resize(height, std::vector<int>(number, -1));
    for (int i = 0; i < number; ++i) {
      std::cin >> arr[i];
      table[0][i] = i;
    }
    for (int i = 0; i < height - 1; ++i) {
      for (int j = 0; j + (2 << i) <= number; ++j) {
        int left_index = table[i][j];
        int right_index = table[i][j + (1 << i)];
        table[i + 1][j] =
            arr[left_index] <= arr[right_index] ? left_index : right_index;
      }
    }
  }

  int GetMin(int left, int right) {
    int ln = std::log2(right - left + 1);
    int left_index = table[ln][left];
    int right_index = table[ln][right - (1 << ln) + 1];
    return arr[left_index] <= arr[right_index] ? left_index : right_index;
  }

  std::vector<int> arr;
  std::vector<std::vector<int>> table;
};

int main() {
  int number;
  int count_req;
  std::cin >> number >> count_req;
  SparseTable tab(number);
  int left;
  int right;
  int index;
  for (int i = 0; i < count_req; ++i) {
    std::cin >> left >> right;
    index = tab.GetMin(left - 1, right - 1);
    if (index == left - 1) {
      index = tab.GetMin(left, right - 1);
    } else if (index == right - 1) {
      index = tab.GetMin(left - 1, right - 2);
    } else {
      int index_left = tab.GetMin(left - 1, index - 1);
      int index_right = tab.GetMin(index + 1, right - 1);
      index = tab.arr[index_left] <= tab.arr[index_right] ? index_left
                                                          : index_right;
    }
    std::cout << tab.arr[index] << "\n";
  }
  return 0;
}