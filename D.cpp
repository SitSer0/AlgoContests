#include <deque>
#include <iostream>
#include <queue>
#include <string>

std::queue<long long> que;
std::deque<long long> dec;
int size = 0;

void Add(long long number) {
  que.push(number);
  while (not dec.empty() && dec.back() > number) {
    dec.pop_back();
  }
  dec.push_back(number);
  size++;
  std::cout << "ok\n";
}

void Pop() {
  if (size == 0) {
    std::cout << "error\n";
    return;
  }
  size--;
  std::cout << que.front() << "\n";
  if (que.front() == dec.front()) {
    que.pop();
    dec.pop_front();
  } else {
    que.pop();
  }
}

void Front() {
  if (size == 0) {
    std::cout << "error\n";
    return;
  }
  std::cout << que.front() << "\n";
}

void Size() { std::cout << size << "\n"; }

void Clear() {
  size = 0;
  while (not que.empty()) {
    que.pop();
  }
  while (not dec.empty()) {
    dec.pop_back();
  }
  std::cout << "ok\n";
}

void GetMin() {
  if (size == 0) {
    std::cout << "error\n";
    return;
  }
  std::cout << dec.front() << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int count;
  long long number;
  std::cin >> count;
  std::string type;
  for (int i = 0; i < count; ++i) {
    std::cin >> type;
    if (type == "enqueue") {
      std::cin >> number;
      Add(number);
    } else if (type == "dequeue") {
      Pop();
    } else if (type == "front") {
      Front();
    } else if (type == "size") {
      Size();
    } else if (type == "clear") {
      Clear();
    } else if (type == "min") {
      GetMin();
    }
  }
  return 0;
}