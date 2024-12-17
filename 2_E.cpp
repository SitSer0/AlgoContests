#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

const int cTen = 10;
const int cTwentySix = 26;

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


std::string Bwt(const std::string& s1) {
  std::string s = s1;
  int sz = static_cast<int>(s.size());
  s += s;

  std::vector<int> suffix_array = Build(s);

  std::string ans;

  for (int index : suffix_array) {
    if (index < sz) {
      ans += s[index + sz - 1];
    }
  }

  return ans;
}

std::string Mtf(const std::string& s) {
  std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
  std::string result;

  for (char c : s) {
    auto it = find(alphabet.begin(), alphabet.end(), c);
    result += static_cast<char>(distance(alphabet.begin(), it) + 'a');
    alphabet.erase(it);
    alphabet.insert(alphabet.begin(), c);
  }

  return result;
}

std::string Rle(const std::string& s) {
  std::string result;
  int count = 1;

  for (size_t i = 1; i <= s.size(); ++i) {
    if (i < s.size() && s[i] == s[i - 1]) {
      count++;
    } else {
      result += s[i - 1] + std::to_string(count);
      count = 1;
    }
  }

  return result;
}

std::string RleDecode(const std::string& s1) {
  std::string s = s1 + "$";
  std::string result;
  char c;
  int i = 0;
  int sz = static_cast<int>(s.size());
  int count = 0;
  while (i < sz) {
    if (isdigit(s[i]) != 0) {
      count = count * cTen + (s[i] - '0');
      ++i;
    } else {
      for (int j = 0; j < count; ++j) {
        result += c;
      }
      count = 0;
      c = s[i];
      ++i;
    }
  }
  return result;
}

std::string MtfDecode(const std::string& s) {
  std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
  std::string result;

  for (char c : s) {
    int index = c - 'a';
    result += alphabet[index];
    char moved_char = alphabet[index];
    alphabet.erase(alphabet.begin() + index);
    alphabet.insert(alphabet.begin(), moved_char);
  }

  return result;
}

std::string BwtInverse(const std::string& bwt_str, int last_index) {
  int n = static_cast<int>(bwt_str.size());
  std::vector<int> count(cTwentySix, 0);

  for (int i = 0; i < n; ++i) {
    count[static_cast<int>(bwt_str[i] - 'a')]++;
  }
  int sum = 0;

  for (int i = 0; i < cTwentySix; ++i) {
    sum += count[i];
    count[i] = sum - count[i];
  }
  std::vector<int> t(n);
  for (int i = 0; i < n; ++i) {
    t[count[static_cast<int>(bwt_str[i] - 'a')]] = i;
    count[static_cast<int>(bwt_str[i] - 'a')]++;
  }
  int j = t[last_index];
  std::string ans(n, '!');
  for (int i = 0; i < n; ++i) {
    ans[i] = bwt_str[j];
    j = t[j];
  }
  return ans;
}


int main() {
  int mode;
  std::cin >> mode;

  if (mode == 1) {
    std::string str;
    std::cin >> str;

    std::string bwt_result = Bwt(str);
    std::string mtf_result = Mtf(bwt_result);
    std::string rle_result = Rle(mtf_result);

    std::cout << rle_result;

  } else if (mode == 2) {
    std::string rle_input;
    std::string bwt_index_str;
    std::cin >> rle_input >> bwt_index_str;
    int bwt_index = stoi(bwt_index_str);

    std::string mtf_result = RleDecode(rle_input);
    std::string bwt_result = MtfDecode(mtf_result);
    std::string original_text = BwtInverse(bwt_result, bwt_index);

    std::cout << original_text;
  }

  return 0;
}