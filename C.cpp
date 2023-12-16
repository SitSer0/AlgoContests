#include <iostream>
#include <vector>

struct Name {
  std::string string;

  Name(const std::string& str) : string(str) {}

  bool operator>(const Name& another) const { return string > another.string; }

  bool operator<(const Name& another) const { return string < another.string; }

  bool operator==(const Name& another) const {
    return string == another.string;
  }
};

class AVLTree {
 public:
  AVLTree() : root_(nullptr) {}

  ~AVLTree() { delete root_; }

  void Add(Name key, Name name) { root_ = Insert(root_, key, name); }

  std::string Find(Name name) { return Find(root_, name); }

 private:
  struct Node {
    Name key;
    Name name;
    int height;
    Node* left;
    Node* right;
    Node(Name key, Name name)
        : key(key), name(name), height(1), left(nullptr), right(nullptr) {}
    ~Node() {
      delete left;
      delete right;
    }
  };

  Node* root_;

  static int Height(Node* node) {
    if (node == nullptr) {
      return 0;
    }
    return node->height;
  }

  static int BalanceFactor(Node* node) {
    if (node == nullptr) {
      return 0;
    }
    return Height(node->left) - Height(node->right);
  }

  static Node* RightRotate(Node* node) {
    Node* new_root = node->left;
    Node* left_right = new_root->right;

    new_root->right = node;
    node->left = left_right;

    node->height = std::max(Height(node->left), Height(node->right)) + 1;
    new_root->height =
        std::max(Height(new_root->left), Height(new_root->right)) + 1;

    return new_root;
  }

  static Node* LeftRotate(Node* node) {
    Node* new_root = node->right;
    Node* right_left = new_root->left;

    new_root->left = node;
    node->right = right_left;

    node->height = std::max(Height(node->left), Height(node->right)) + 1;
    new_root->height =
        std::max(Height(new_root->left), Height(new_root->right)) + 1;

    return new_root;
  }

  Node* Insert(Node* node, Name key, Name name) {
    if (node == nullptr) {
      return new Node(key, name);
    }

    if (key < node->key) {
      node->left = Insert(node->left, key, name);
    } else if (key > node->key) {
      node->right = Insert(node->right, key, name);
    } else {
      return node;
    }

    node->height = std::max(Height(node->left), Height(node->right)) + 1;

    int balance = BalanceFactor(node);

    if (balance > 1 && key < node->left->key) {
      return RightRotate(node);
    }

    if (balance < -1 && key > node->right->key) {
      return LeftRotate(node);
    }

    if (balance > 1 && key > node->left->key) {
      node->left = LeftRotate(node->left);
      return RightRotate(node);
    }

    if (balance < -1 && key < node->right->key) {
      node->right = RightRotate(node->right);
      return LeftRotate(node);
    }

    return node;
  }
  std::string Find(Node* node, Name name) {
    if (node == nullptr) {
      return "-1";
    }
    if (node->key == name) {
      return node->name.string;
    }
    if (node->left == nullptr || node->key < name) {
      return Find(node->right, name);
    }
    return Find(node->left, name);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int number;
  int count;
  std::string key;
  std::string name;
  AVLTree tree1;
  AVLTree tree2;
  std::cin >> number;
  for (int i = 0; i < number; ++i) {
    std::cin >> key >> name;
    tree1.Add(Name(key), Name(name));
    tree2.Add(Name(name), Name(key));
  }
  std::cin >> count;
  std::string f1;
  std::string f2;
  for (int i = 0; i < count; ++i) {
    std::cin >> name;
    f1 = tree1.Find(name);
    f2 = tree2.Find(name);
    if (f1 == "-1") {
      std::cout << f2 << "\n";
    } else {
      std::cout << f1 << "\n";
    }
  }
  return 0;
}