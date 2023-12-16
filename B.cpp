#include <iostream>
#include <vector>

struct Node {
  int64_t val;
  Node* next = nullptr;
  Node(int64_t val) : val(val), next(nullptr) {}
};

class HashTable {
 public:
  HashTable(int64_t number) {
    table_.resize(number, nullptr);
    size_ = number;
  }

  HashTable(int64_t number, std::vector<int64_t>& vec) {
    table_.resize(number, nullptr);
    size_ = number;
    for (int i = 0; i < number; ++i) {
      Insert(vec[i]);
    }
  }

  void Insert(int64_t val) {
    int64_t index = HashFunc(val);
    Node* new_node = new Node(val);
    new_node->next = table_[index];
    table_[index] = new_node;
  };

  bool Find(int64_t val) {
    int64_t index = HashFunc(val);
    Node* find_node = table_[index];
    while (find_node != nullptr) {
      if (find_node->val == val) {
        return true;
      }
      find_node = find_node->next;
    }
    return false;
  };

  void Erase(int64_t val) {
    int64_t index = HashFunc(val);
    Node* cur = table_[index];
    Node* prev = nullptr;

    while (cur != nullptr) {
      if (cur->val == val) {
        if (prev == nullptr) {
          table_[index] = cur->next;
        } else {
          prev->next = cur->next;
        }
        delete cur;
        return;
      }
      prev = cur;
      cur = cur->next;
    }
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
  int64_t size_;
  std::vector<Node*> table_;
  const int64_t kA = 17;
  const int64_t kB = 101;
  const int64_t kP = 1000000007;

  int64_t HashFunc(const int64_t kVal) const {
    return ((kA * kVal + kB) % kP) % size_;
  }
};

void Read(int64_t& number1, int64_t& number2, std::vector<int64_t>& first,
          std::vector<int64_t>& second) {
  std::cin >> number1;
  first.resize(number1);
  for (int i = 0; i < number1; ++i) {
    std::cin >> first[i];
  }
  std::cin >> number2;
  second.resize(number2);
  for (int i = 0; i < number2; ++i) {
    std::cin >> second[i];
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int64_t number1;
  std::vector<int64_t> first;
  int64_t number2;
  std::vector<int64_t> second;
  Read(number1, number2, first, second);
  HashTable second_tab(number2, second);
  std::vector<int64_t> ans(0);
  int64_t count = 0;
  for (int i = 0; i < number1; ++i) {
    if (second_tab.Find(first[i])) {
      ans.push_back(first[i]);
      count++;
      second_tab.Erase(first[i]);
    }
  }
  std::cout << count << "\n";
  for (int i = 0; i < count; ++i) {
    std::cout << ans[i] << " ";
  }
  return 0;
}