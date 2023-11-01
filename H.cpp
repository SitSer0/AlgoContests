#include <cmath>
#include <iostream>
#include <string>
#include <vector>

const int kMagicNumber = 6;

long GetDepth(long index) {
  long depth = -1;
  while (index > 0) {
    depth++;
    index >>= 1;
  }
  return depth;
}

long ParentIndex(long index) {
  if (index == 0) {
    return -1;
  }
  return (index - 1) / 2;
}

long Minimum(std::vector<long long>& heap, std::vector<long>& ind, int len,
             long size) {
  long ans = ind[0];
  for (int i = 1; i < len; ++i) {
    if (ind[i] < size && heap[ind[i]] < heap[ans]) {
      ans = ind[i];
    }
  }
  return ans;
}

long Maximum(std::vector<long long>& heap, std::vector<long>& ind, int len,
             long size) {
  long ans = ind[0];
  for (int i = 1; i < len; ++i) {
    if (ind[i] < size && heap[ind[i]] > heap[ans]) {
      ans = ind[i];
    }
  }
  return ans;
}

long GrandIndex(long index) { return ParentIndex(ParentIndex(index)); }

long LeftChild(long index) { return 2 * index + 1; }
long RightChild(long index) { return 2 * index + 2; }
long GrChild1(long index) { return LeftChild(LeftChild(index)); }
long GrChild2(long index) { return RightChild(LeftChild(index)); }
long GrChild3(long index) { return LeftChild(RightChild(index)); }
long GrChild4(long index) { return RightChild(RightChild(index)); }

void PushUpMin(std::vector<long long>& heap, long index) {
  if (index == 0) {
    return;
  }
  if (GrandIndex(index) >= 0 && heap[index] < heap[GrandIndex(index)]) {
    std::swap(heap[index], heap[GrandIndex(index)]);
    index = GrandIndex(index);
    PushUpMin(heap, index);
  }
}

void PushUpMax(std::vector<long long>& heap, long index) {
  if (index < 3) {
    return;
  }
  if (GrandIndex(index) >= 0 && heap[index] > heap[GrandIndex(index)]) {
    std::swap(heap[index], heap[GrandIndex(index)]);
    index = GrandIndex(index);
    PushUpMax(heap, index);
  }
}

void PushUp(std::vector<long long>& heap, long index) {
  if (GetDepth(index + 1) % 2 == 0) {
    if (index == 0) {
      return;
    }
    if (heap[ParentIndex(index)] < heap[index]) {
      std::swap(heap[ParentIndex(index)], heap[index]);
      index = ParentIndex(index);
      PushUpMax(heap, index);
    } else {
      PushUpMin(heap, index);
    }
  } else {
    if (heap[ParentIndex(index)] > heap[index]) {
      std::swap(heap[ParentIndex(index)], heap[index]);
      index = ParentIndex(index);
      PushUpMin(heap, index);
    } else {
      PushUpMax(heap, index);
    }
  }
}

void PushDown(std::vector<long long>& heap, long index, long size);

void PushDownMax(std::vector<long long>& heap, long index, long size) {
  if (LeftChild(index) > size - 1 || size == 0) {
    return;
  }
  std::vector<long> ind = {LeftChild(index), RightChild(index),
                           GrChild1(index),  GrChild2(index),
                           GrChild3(index),  GrChild4(index)};

  long max_index = Maximum(heap, ind, kMagicNumber, size);
  if (max_index >= GrChild1(index)) {
    if (heap[max_index] > heap[index]) {
      std::swap(heap[max_index], heap[index]);
      if (heap[max_index] < heap[ParentIndex(max_index)]) {
        std::swap(heap[max_index], heap[ParentIndex(max_index)]);
      }
      PushDown(heap, max_index, size);
    }
  } else if (heap[max_index] > heap[index]) {
    std::swap(heap[max_index], heap[index]);
  }
}

void PushDownMin(std::vector<long long>& heap, long index, long size) {
  if (LeftChild(index) > size - 1 || size == 0) {
    return;
  }
  std::vector<long> ind = {LeftChild(index), RightChild(index),
                           GrChild1(index),  GrChild2(index),
                           GrChild3(index),  GrChild4(index)};

  long min_index = Minimum(heap, ind, kMagicNumber, size);
  if (min_index >= GrChild1(index)) {
    if (heap[min_index] < heap[index]) {
      std::swap(heap[min_index], heap[index]);
      if (heap[min_index] > heap[ParentIndex(min_index)]) {
        std::swap(heap[min_index], heap[ParentIndex(min_index)]);
      }
      PushDown(heap, min_index, size);
    }
  } else if (heap[min_index] < heap[index]) {
    std::swap(heap[min_index], heap[index]);
  }
}

void PushDown(std::vector<long long>& heap, long index, long size) {
  if (GetDepth(index + 1) % 2 == 0) {
    PushDownMin(heap, index, size);
  } else {
    PushDownMax(heap, index, size);
  }
}

void Insert(std::vector<long long>& heap, long long number, long& size) {
  heap.push_back(number);
  PushUp(heap, size);
  size++;
  std::cout << "ok\n";
}

void ExtractMin(std::vector<long long>& heap, long& size) {
  if (size == 0) {
    std::cout << "error\n";
    return;
  }
  std::cout << heap[0] << "\n";
  std::swap(heap[0], heap[size - 1]);
  heap.pop_back();
  size--;
  PushDown(heap, 0, size);
}

void GetMin(std::vector<long long>& heap, long size) {
  if (size == 0) {
    std::cout << "error\n";
  } else {
    std::cout << heap[0] << "\n";
  }
}

void ExtractMax(std::vector<long long>& heap, long& size) {
  if (size == 0) {
    std::cout << "error\n";
    return;
  }
  if (size == 1) {
    std::cout << heap[0] << "\n";
    heap.pop_back();
    size--;
    return;
  }
  if (size == 2) {
    std::cout << heap[1] << "\n";
    heap.pop_back();
    size--;
    return;
  }
  std::cout << std::max(heap[1], heap[2]) << "\n";
  if (heap[1] > heap[2]) {
    std::swap(heap[1], heap[size - 1]);
    heap.pop_back();
    size--;
    PushDown(heap, 1, size);
  } else {
    std::swap(heap[2], heap[size - 1]);
    heap.pop_back();
    size--;
    PushDown(heap, 2, size);
  }
}

void GetMax(std::vector<long long>& heap, long size) {
  if (size == 0) {
    std::cout << "error\n";
    return;
  }
  if (size == 1) {
    std::cout << heap[0] << "\n";
    return;
  }
  if (size == 2) {
    std::cout << heap[1] << "\n";
    return;
  }
  std::cout << std::max(heap[1], heap[2]) << "\n";
}

void Size(long& size) { std::cout << size << "\n"; }

void Clear(std::vector<long long>& heap, long& size) {
  heap.clear();
  size = 0;
  std::cout << "ok\n";
}

int main() {
  std::vector<long long> heap(0);
  std::string command;
  long long number;
  long count;
  long size = 0;
  std::cin >> count;
  for (long i = 0; i < count; ++i) {
    std::cin >> command;
    if (command == "insert") {
      std::cin >> number;
      Insert(heap, number, size);
    } else if (command == "extract_min") {
      ExtractMin(heap, size);
    } else if (command == "get_min") {
      GetMin(heap, size);
    } else if (command == "extract_max") {
      ExtractMax(heap, size);
    } else if (command == "get_max") {
      GetMax(heap, size);
    } else if (command == "size") {
      Size(size);
    } else if (command == "clear") {
      Clear(heap, size);
    }
  }
  return 0;
}