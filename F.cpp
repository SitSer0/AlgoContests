#include <iostream>
#include <string>
#include <vector>

class MinHeap {
 public:
  MinHeap() { size_ = 0; }

  void Insert(long long number) {
    heap_.push_back(number);
    size_++;
    PushUp(size_ - 1);
  }

  long long GetMin() { return heap_[0]; }

  void ExtractMin() {
    Swap(0, size_ - 1);
    size_--;
    heap_.pop_back();
    PushDown(0);
  }

  void DecreaseKey(int index, long long delta) {
    heap_[index] -= delta;
    PushUp(index);
  }

 private:
  std::vector<long long> heap_;
  int size_;

  void Swap(int index1, int index2) { std::swap(heap_[index1], heap_[index2]); }

  static int Parent(int index) { return (index - 1) / 2; }
  static int LeftChild(int index) { return 2 * index + 1; }
  static int RightChild(int index) { return 2 * index + 2; }


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