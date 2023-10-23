#include <iostream>
#include <vector>

const long long kMagicNumber = 10000000 + 4321;
const long long kMagicNumber123 = 123;
const long long kMagicNumber45 = 45;

void FillArr(std::vector<long long>& arr, int number) {
  for (int i = 2; i < number; ++i) {
    arr[i] = (arr[i - 1] * kMagicNumber123 + arr[i - 2] * kMagicNumber45) %
        (kMagicNumber);
  }
}

int GivePivot(int left, int right) {
  int random_index = (left + right) / 2;
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

int main() {
  int number;
  int k_stat;
  long frst;
  long scond;
  std::cin >> number >> k_stat >> frst >> scond;
  k_stat--;
  std::vector<long long> arr(number);
  arr[0] = frst;
  arr[1] = scond;
  FillArr(arr, number);
  int left = 0;
  int right = number - 1;
  int can_use = 1;
  while (can_use == 1) {
    std::pair<int, int> mid = Partition(arr, left, right);
    if (mid.first <= k_stat && k_stat <= mid.second) {
      can_use = 0;
      std::cout << arr[k_stat];
    } else if (mid.first > k_stat) {
      right = mid.first - 1;
    } else {
      left = mid.second + 1;
    }
  }
  return 0;
}