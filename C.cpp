#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct Node {
  std::string pattern;
  Node* next = nullptr;
  Node(std::string pat) : pattern(pat), next(nullptr) {}
};

std::string UniqToString(const std::string& str) {
  std::unordered_map<char, char> char_map;
  char current_char = 'a';
  std::string pattern;

  for (char chr : str) {
    if (char_map.find(chr) == char_map.end()) {
      char_map[chr] = current_char++;
    }
    pattern += char_map[chr];
  }

  return pattern;
}

class HashTable {
 public:
  HashTable(int64_t number) : table_(number, nullptr), size_(number) {}

  void Insert(const std::string& str) {
    std::string pattern = UniqToString(str);
    int64_t index = HashFunc(pattern);
    Node* new_node = new Node(pattern);
    new_node->next = table_[index];
    table_[index] = new_node;
  }

  bool Find(const std::string& str) {
    std::string pattern = UniqToString(str);
    int64_t index = HashFunc(pattern);
    Node* cur = table_[index];
    while (cur != nullptr) {
      if (cur->pattern == pattern) {
        return true;
      }
      cur = cur->next;
    }
    return false;
  }

  ~HashTable() {
    for (Node* head : table_) {
      while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
      }
    }
  }

 private:
  int64_t HashFunc(const std::string& pattern) const {
    int64_t hash = 0;
    int64_t st = 1;
    for (char chr : pattern) {
      hash = ((hash + st * (int)(chr - 'a' + 1)) % kP) % size_;
      st = (st * kA) % kP;
    }
    return hash;
  }

  std::vector<Node*> table_;
  int64_t size_;
  const int64_t kA = 17;
  const int64_t kP = 1000000007;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int number;
  std::cin >> number;
  std::string type;
  std::string inp;
  HashTable tab(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> type >> inp;
    if (type == "?") {
      std::cout << (tab.Find(inp) ? "YES" : "NO") << "\n";
    } else {
      tab.Insert(inp);
    }
  }
  return 0;
}