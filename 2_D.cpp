#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> Build(std::string& s) {
  int n = static_cast<int>(s.size());
  std::vector<int> suffix_array(n);
  std::vector<int> rank(n);
  std::vector<int> temp_rank(n);

  for (int i = 0; i < n; ++i) {
    suffix_array[i] = i;
    rank[i] = s[i];
  }
  for (int k = 1; k < n; k *= 2) {
    auto cmp = [&](int a, int b) {
      if (rank[a] != rank[b]) {
        return rank[a] < rank[b];
      }
      int ra = (a + k < n) ? rank[a + k] : -1;
      int rb = (b + k < n) ? rank[b + k] : -1;
      return ra < rb;
    };
    std::sort(suffix_array.begin(), suffix_array.end(), cmp);
    temp_rank[suffix_array[0]] = 0;
    for (int i = 1; i < n; ++i) {
      temp_rank[suffix_array[i]] = temp_rank[suffix_array[i - 1]];
      if (cmp(suffix_array[i - 1], suffix_array[i])) {
        temp_rank[suffix_array[i]]++;
      }
    }
    rank.swap(temp_rank);
  }

  return suffix_array;
}

int main() {
  std::string s;
  std::cin >> s;
  int sz = static_cast<int>(s.size());
  s += s;
  std::cout << s << "\n";

  std::vector<int> suffix_array = Build(s);

  for (int index : suffix_array) {
    if (index < sz) {
      std::cout << s[index + sz - 1];
      std::cout << index << " " << s[index + sz - 1] << "\n";
    }
  }
  return 0;
}