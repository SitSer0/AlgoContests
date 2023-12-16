#include <iostream>

const int kMax = 1000000001;
const int kMod = 1000000000;

class AVLTree {
 public:
  AVLTree() : root_(nullptr) {}

  ~AVLTree() { delete root_; }

  void Add(int val) { root_ = Insert(root_, val); }

  int Next(int val) {
    int result = Next(root_, val, kMax, -1);
    return result == kMax ? -1 : result;
  }

 private:
  struct Node {
    int key;
    int height;
    Node* left;
    Node* right;
    Node(int key) : key(key), height(1), left(nullptr), right(nullptr) {}
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

  Node* Insert(Node* node, int key) {
    if (node == nullptr) {
      return new Node(key);
    }

    if (key < node->key) {
      node->left = Insert(node->left, key);
    } else if (key > node->key) {
      node->right = Insert(node->right, key);
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

  int Next(Node* node, int val, int min, int min_key) {
    if (node == nullptr) {
      return min_key;
    }

    if (node->key >= val) {
      if (node->key - val < min) {
        min = node->key - val;
        min_key = node->key;
      }
      return Next(node->left, val, min, min_key);
    }
    return Next(node->right, val, min, min_key);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int number;
  int val;
  int last_next = 0;
  char type;
  AVLTree tree;
  std::cin >> number;
  for (int i = 0; i < number; ++i) {
    std::cin >> type >> val;
    if (type == '+') {
      tree.Add((val + last_next) % kMod);
      last_next = 0;
    } else if (type == '?') {
      last_next = tree.Next(val);
      std::cout << last_next << "\n";
    }
  }
}