#include <iostream>

class Treap {
 public:
  Treap() : root_(nullptr) {}

  ~Treap() { Clear(root_); }

  void Add(int val) { Insert(val); }

  void Delete(int val) { Remove(val); }

  void Exists(int val) { std::cout << (Find(val) ? "true" : "false") << "\n"; }

  void Next(int val) {
    Node* res = NextNode(root_, val, nullptr);
    if (res != nullptr) {
      std::cout << res->key << "\n";
    } else {
      std::cout << "none\n";
    }
  }

  void Prev(int val) {
    Node* res = PrevNode(root_, val, nullptr);
    if (res != nullptr) {
      std::cout << res->key << "\n";
    } else {
      std::cout << "none\n";
    }
  }

  void Kth(int val) {
    Node* res = KthNode(root_, val);
    if (res != nullptr) {
      std::cout << res->key << "\n";
    } else {
      std::cout << "none\n";
    }
  }

 private:
  struct Node {
    int key;
    int prior;
    int size;
    Node* left;
    Node* right;
    Node(int key)
        : key(key), prior(rand()), size(1), left(nullptr), right(nullptr) {}
  };

  void Clear(Node* root) {
    if (root == nullptr) {
      return;
    }
    Clear(root->left);
    Clear(root->right);
    delete root;
  }

  Node* root_;

  static int Size(Node* node) {
    if (node == nullptr) {
      return 0;
    }
    return node->size;
  }

  static void UpdateSize(Node* node) {
    if (node == nullptr) {
      return;
    }
    node->size = 1 + Size(node->left) + Size(node->right);
  }

  std::pair<Node*, Node*> Split(Node* node, int key) {
    if (node == nullptr) {
      return {nullptr, nullptr};
    }
    if (key > node->key) {
      auto right_tree = Split(node->right, key);
      node->right = right_tree.first;
      UpdateSize(node);
      return {node, right_tree.second};
    }
    auto left_tree = Split(node->left, key);
    node->left = left_tree.second;
    UpdateSize(node);
    return {left_tree.first, node};
  }

  Node* Merge(Node* node1, Node* node2) {
    if (node1 == nullptr) {
      return node2;
    }
    if (node2 == nullptr) {
      return node1;
    }
    if (node1->prior > node2->prior) {
      node1->right = Merge(node1->right, node2);
      UpdateSize(node1);
      return node1;
    }
    node2->left = Merge(node1, node2->left);
    UpdateSize(node2);
    return node2;
  }

  void Insert(int key) {
    if (Find(key)) {
      return;
    }
    auto treaps = Split(root_, key);
    Node* new_node = new Node(key);
    root_ = Merge(Merge(treaps.first, new_node), treaps.second);
  }

  void Remove(int key) {
    if (!Find(key)) {
      return;
    }
    std::pair<Node*, Node*> under_key = Split(root_, key);
    std::pair<Node*, Node*> above_key = Split(under_key.second, key + 1);
    delete above_key.first;
    root_ = Merge(under_key.first, above_key.second);
  }

  bool Find(int key) {
    Node* current = root_;
    while (current != nullptr) {
      if (key < current->key) {
        current = current->left;
      } else if (key > current->key) {
        current = current->right;
      } else {
        return true;
      }
    }
    return false;
  }

  Node* NextNode(Node* node, int key, Node* best) {
    if (node == nullptr) {
      return best;
    }
    if (node->key > key) {
      if (best == nullptr || node->key < best->key) {
        best = node;
      }
      return NextNode(node->left, key, best);
    }
    return NextNode(node->right, key, best);
  }

  Node* PrevNode(Node* node, int key, Node* best) {
    if (node == nullptr) {
      return best;
    }
    if (node->key < key) {
      if (best == nullptr || node->key > best->key) {
        best = node;
      }
      return PrevNode(node->right, key, best);
    }
    return PrevNode(node->left, key, best);
  }

  Node* KthNode(Node* node, int kth) {
    if (node == nullptr) {
      return nullptr;
    }
    int left_size = Size(node->left);
    if (kth < left_size) {
      return KthNode(node->left, kth);
    }
    if (kth == left_size) {
      return node;
    }
    return KthNode(node->right, kth - left_size - 1);
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::string type;
  int val;
  Treap tree;
  while (std::cin >> type >> val) {
    if (type == "insert") {
      tree.Add(val);
    } else if (type == "delete") {
      tree.Delete(val);
    } else if (type == "exists") {
      tree.Exists(val);
    } else if (type == "next") {
      tree.Next(val);
    } else if (type == "prev") {
      tree.Prev(val);
    } else if (type == "kth") {
      tree.Kth(val);
    }
  }
  return 0;
}