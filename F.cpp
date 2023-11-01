#include <iostream>
#include <string>
#include <vector>

int Parent(int index) { return (index - 1) / 2; }

int LeftChild(int index) { return 2 * index + 1; }

int RightChild(int index) { return 2 * index + 2; }

std::vector<long long> heap(0);
std::vector<int> ind_to_heap(0);
std::vector<int> heap_to_ind(0);
int size = 0;

void PushUp(int index) {
  if (index == 0 || heap[Parent(index)] <= heap[index]) {
    return;
  }
  std::swap(heap[Parent(index)], heap[index]);
  std::swap(ind_to_heap[heap_to_ind[index]],
            ind_to_heap[heap_to_ind[Parent(index)]]);
  std::swap(heap_to_ind[index], heap_to_ind[Parent(index)]);
  PushUp(Parent(index));
}

void PushDown(int index) {
  if (LeftChild(index) > size - 1) {
    return;
  }
  int min_index = LeftChild(index) == size - 1 ||
      heap[LeftChild(index)] < heap[RightChild(index)]
                  ? LeftChild(index)
                  : RightChild(index);
  if (heap[min_index] < heap[index]) {
    std::swap(heap[min_index], heap[index]);
    std::swap(ind_to_heap[heap_to_ind[index]],
              ind_to_heap[heap_to_ind[min_index]]);
    std::swap(heap_to_ind[index], heap_to_ind[min_index]);
  }
  PushDown(min_index);
}

void Insert(long long number) {
  heap.push_back(number);
  size++;
  PushUp(size - 1);
}

void GetMin() { std::cout << heap[0] << "\n"; }

void ExtractMin() {
  std::swap(heap[0], heap[size - 1]);
  std::swap(ind_to_heap[heap_to_ind[0]], ind_to_heap[heap_to_ind[size - 1]]);
  std::swap(heap_to_ind[0], heap_to_ind[size - 1]);
  size--;
  heap.pop_back();
  heap_to_ind.pop_back();
  PushDown(0);
}

void DecreaseKey(int index, long long delta) {
  heap[ind_to_heap[index]] -= delta;
  PushUp(ind_to_heap[index]);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int count;
  int index;
  long long delta;
  long long number;
  std::string type;
  std::cin >> count;
  for (int i = 0; i < count; ++i) {
    ind_to_heap.push_back(-1);
    std::cin >> type;
    if (type == "insert") {
      std::cin >> number;
      ind_to_heap[i] = size;
      heap_to_ind.push_back(i);
      Insert(number);
    } else if (type == "getMin") {
      GetMin();
    } else if (type == "extractMin") {
      ExtractMin();
    } else if (type == "decreaseKey") {
      std::cin >> index >> delta;
      index--;
      DecreaseKey(index, delta);
    }
  }
  return 0;
}