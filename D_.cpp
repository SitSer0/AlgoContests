#include <iostream>
#include <vector>

struct Point {
  int64_t x_cord;
  int64_t y_cord;
  Point() : x_cord(0), y_cord(0) {}
  Point(int64_t x_cord, int64_t y_cord) : x_cord(x_cord), y_cord(y_cord) {}
};

struct Node {
  int64_t val;
  Node* next = nullptr;
  int64_t count;
  Node(int64_t val) : val(val), next(nullptr), count(1) {}
};

class HashTable {
 public:
  HashTable(int64_t number) : size_(number), table_(number, nullptr) {}

  void Insert(int64_t val) {
    if (Find(val) != nullptr) {
      Find(val)->count += 1;
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

  Node* Find(int64_t val) {
    int64_t index = HashFunc(val);
    Node* find_node = table_[index];
    while (find_node != nullptr) {
      if (find_node->val == val) {
        return find_node;
      }
      find_node = find_node->next;
    }
    return nullptr;
  };

  int64_t Count(int64_t val) {
    if (Find(val) == nullptr) {
      return 0;
    }
    return Find(val)->count;
  }

  void Erase(int64_t val) {
    if (Find(val) == nullptr) {
      return;
    }
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

  void Clear() {
    for (Node* head : table_) {
      while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
      }
    }
    table_.resize(size_, nullptr);
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
  int64_t HashFunc(int64_t val) const {
    return ((kA * (val % kP) + kB) % kP) % size_;
  }

  int64_t size_;
  std::vector<Node*> table_;
  const int64_t kA = 17;
  const int64_t kB = 101;
  const int64_t kP = 1000000007;
};

int64_t Distance(Point& p1, Point& p2) {
  return (p1.x_cord - p2.x_cord) * (p1.x_cord - p2.x_cord) +
         (p1.y_cord - p2.y_cord) * (p1.y_cord - p2.y_cord);
}

int main() {
  int64_t number;
  int64_t type;
  std::cin >> number >> type;
  std::vector<Point> points(number, Point());
  for (int64_t i = 0; i < number; ++i) {
    std::cin >> points[i].x_cord >> points[i].y_cord;
  }
  HashTable table(number);
  int64_t ans = 0;
  for (int64_t i = 0; i < number; ++i) {
    for (int64_t j = 0; j < number; ++j) {
      table.Insert(Distance(points[i], points[j]));
    }
    for (int64_t j = 0; j < number; ++j) {
      int64_t count = table.Count(Distance(points[i], points[j]));
      table.Erase(Distance(points[i], points[j]));
      ans += (count) * (count - 1) / 2;
    }
    table.Clear();
  }
  std::cout << (type == 1 ? ans : 0);
  return 0;
}