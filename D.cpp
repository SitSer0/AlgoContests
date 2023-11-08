#include <deque>
#include <iostream>
#include <queue>
#include <string>

class MinQueue {
 public:
  MinQueue() { size_ = 0; }

  void Add(long long number) {
    que_.push(number);
    while (!dec_.empty() && dec_.back() > number) {
      dec_.pop_back();
    }
    dec_.push_back(number);
    size_++;
    std::cout << "ok\n";
  }

  void Pop() {
    if (size_ == 0) {
      std::cout << "error\n";
      return;
    }
    size_--;
    std::cout << que_.front() << "\n";
    if (que_.front() == dec_.front()) {
      que_.pop();
      dec_.pop_front();
    } else {
      que_.pop();
    }
  }

  void Front() {
    if (size_ == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << que_.front() << "\n";
  }

  void Size() const { std::cout << size_ << "\n"; }

  void Clear() {
    size_ = 0;
    while (!que_.empty()) {
      que_.pop();
    }
    while (!dec_.empty()) {
      dec_.pop_back();
    }
    std::cout << "ok\n";
  }

  void GetMin() {
    if (size_ == 0) {
      std::cout << "error\n";
      return;
    }
    std::cout << dec_.front() << "\n";
  }

 private:
  std::queue<long long> que_;
  std::deque<long long> dec_;
  int size_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int count;
  long long number;
  std::cin >> count;
  std::string type;
  MinQueue min_queue;

  for (int i = 0; i < count; ++i) {
    std::cin >> type;
    if (type == "enqueue") {
      std::cin >> number;
      min_queue.Add(number);
    } else if (type == "dequeue") {
      min_queue.Pop();
    } else if (type == "front") {
      min_queue.Front();
    } else if (type == "size") {
      min_queue.Size();
    } else if (type == "clear") {
      min_queue.Clear();
    } else if (type == "min") {
      min_queue.GetMin();
    }
  }
  return 0;
}