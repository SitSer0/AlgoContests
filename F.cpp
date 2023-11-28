#include <iostream>
#include <string>
#include <vector>

class MinHeap {
 public:
  MinHeap() { size_ = 0; }
  void PushUp(int index) {
    if (index == 0 || heap_[Parent(index)] <= heap_[index]) {
      return;
    }
    Swap(index, Parent(index));
    PushUp(Parent(index));
  }

  void PushDown(int index) {
    if (LeftChild(index) > size_ - 1) {
      return;
    }
    int min_index = LeftChild(index) == size_ - 1 ||
        heap_[LeftChild(index)] < heap_[RightChild(index)]
                    ? LeftChild(index)
                    : RightChild(index);
    if (heap_[min_index] < heap_[index]) {
      Swap(index, min_index);
      PushDown(min_index);
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int count;
  int index;
  long long delta;
  long long number;
  std::string type;
  std::cin >> count;
  MinHeap min_heap;

  for (int i = 0; i < count; ++i) {
    std::cin >> type;
    if (type == "insert") {
      std::cin >> number;
      min_heap.Insert(number);
    } else if (type == "getMin") {
      std::cout << min_heap.GetMin() << "\n";
    } else if (type == "extractMin") {
      min_heap.ExtractMin();
    } else if (type == "decreaseKey") {
      std::cin >> index >> delta;
      index--;
      min_heap.DecreaseKey(index, delta);
    }
  }

  return 0;
}