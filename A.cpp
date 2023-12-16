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

  void Insert(int64_t val) {
    if (Find(val)) {
      return;
    }
    int64_t index = HashFunc(val);
    Node* new_node = new Node(val);
    Node* this_node = table_[index];

    if (this_node == nullptr) {
      table_[index] = new_node;
      return;
    }

    while (this_node->next != nullptr) {
      if (this_node->val == val) {
        delete new_node;
        return;
      }
      this_node = this_node->next;
    }
    this_node->next = new_node;
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

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string type;
  int number;
  int64_t input;
  std::cin >> number;
  HashTable tab(number);
  for (int i = 0; i < number; ++i) {
    std::cin >> type >> input;
    if (type == "+") {
      tab.Insert(input);
    } else if (type == "-") {
      tab.Erase(input);
    } else {
      std::cout << (tab.Find(input) ? "YES" : "NO") << "\n";
    }
  }
  return 0;
}