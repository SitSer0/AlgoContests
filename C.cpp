#include <deque>
#include <iostream>

int main() {
  int count;
  std::cin >> count;
  std::deque<int> left;
  std::deque<int> right;
  int left_size = 0;
  int right_size = 0;
  char type;
  int index;
  for (int i = 0; i < count; ++i) {
    std::cin >> type;
    if (type == '-') {
      std::cout << left.front() << "\n";
      left.pop_front();
      left_size--;
    } else if (type == '+') {
      std::cin >> index;
      right.push_back(index);
      right_size++;
    } else {
      std::cin >> index;
      left.push_back(index);
      left_size++;
    }
    while (left_size - right_size > 1) {
      right.push_front(left.back());
      left.pop_back();
      right_size++;
      left_size--;
    }
    while (right_size > left_size) {
      left.push_back(right.front());
      right.pop_front();
      left_size++;
      right_size--;
    }
  }
}