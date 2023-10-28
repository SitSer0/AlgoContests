#include <iostream>
#include <vector>

int GivePivot(int left, int right) {
  int random_index = left + rand() % (right - left + 1);
  return random_index;
}

std::pair<int, int> Partition(std::vector<long long>& arr, int left,
                              int right) {
  int pivot_ind = GivePivot(left, right);
  long long pivot = arr[pivot_ind];
  int equal_left = pivot_ind;
  int equal_right = pivot_ind;
  for (int i = equal_left - 1; i >= left; --i) {
    if (arr[i] == pivot) {
      std::swap(arr[i], arr[equal_left - 1]);
      equal_left--;
    } else if (arr[i] > pivot) {
      std::swap(arr[i], arr[equal_left - 1]);
      std::swap(arr[equal_left - 1], arr[equal_right]);
      equal_left--;
      equal_right--;
    }
  }
  for (int i = equal_right + 1; i <= right; ++i) {
    if (arr[i] == pivot) {
      std::swap(arr[equal_right + 1], arr[i]);
      equal_right++;
    } else if (arr[i] < pivot) {
      std::swap(arr[i], arr[equal_right + 1]);
      std::swap(arr[equal_right + 1], arr[equal_left]);
      equal_right++;
      equal_left++;
    }
  }
  return std::pair<int, int>(equal_left, equal_right);
}

void QuickSort(std::vector<long long>& arr, int left, int right) {
  if (left < right) {
    std::pair<int, int> pivot = Partition(arr, left, right);
    QuickSort(arr, left, pivot.first - 1);
    QuickSort(arr, pivot.second + 1, right);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int number;
  std::cin >> number;
  std::vector<long long> arr(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> arr[i];
  }
  QuickSort(arr, 0, number - 1);
  for (int i = 0; i < number; ++i) {
    std::cout << arr[i] << " ";
  }

  return 0;
}