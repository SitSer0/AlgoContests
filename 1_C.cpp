#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

class AhoCorasick {
 public:
  struct Node {
    std::unordered_map<char, int> children;
    int fail = 0;
    std::vector<int> output;
  };

  explicit AhoCorasick(const std::vector<std::string>& patterns) {
    Build(patterns);
    BuildLinks();
  }

  void Search(const std::string& text, std::vector<std::vector<int>>& results) {
    int current_state = 0;

    for (int i = 0; i < static_cast<int>(text.size()); ++i) {
      char ch = text[i];

      while (current_state != 0 &&
             !nodes_[current_state].children.contains(ch)) {
        current_state = nodes_[current_state].fail;
      }
      if (nodes_[current_state].children.contains(ch)) {
        current_state = nodes_[current_state].children[ch];
      }

      for (int pattern_index : nodes_[current_state].output) {
        results[pattern_index].push_back(i - patterns_[pattern_index].size() +
                                         1);
      }
    }
  }

 private:
  std::vector<Node> nodes_;
  std::vector<std::string> patterns_;

  void Build(const std::vector<std::string>& patterns) {
    this->patterns_ = patterns;
    nodes_.emplace_back();

    for (int i = 0; i < static_cast<int>(patterns.size()); ++i) {
      int current_state = 0;
      for (char ch : patterns[i]) {
        if (!nodes_[current_state].children.contains(ch)) {
          nodes_[current_state].children[ch] = static_cast<int>(nodes_.size());
          nodes_.emplace_back();
        }
        current_state = nodes_[current_state].children[ch];
      }
      nodes_[current_state].output.push_back(i);
    }
  }

  void BuildLinks() {
    std::queue<int> q;
    for (const auto& pair : nodes_[0].children) {
      q.push(pair.second);
      nodes_[pair.second].fail = 0;
    }

    while (!q.empty()) {
      int state = q.front();
      q.pop();

      for (const auto& pair : nodes_[state].children) {
        char ch = pair.first;
        int child_state = pair.second;

        q.push(child_state);
        int fail_state = nodes_[state].fail;

        while (fail_state != 0 && !nodes_[fail_state].children.contains(ch)) {
          fail_state = nodes_[fail_state].fail;
        }

        if (nodes_[fail_state].children.contains(ch)) {
          nodes_[child_state].fail = nodes_[fail_state].children[ch];
        } else {
          nodes_[child_state].fail = 0;
        }

        if (!nodes_[nodes_[child_state].fail].output.empty()) {
          nodes_[child_state].output.insert(
              nodes_[child_state].output.end(),
              nodes_[nodes_[child_state].fail].output.begin(),
              nodes_[nodes_[child_state].fail].output.end());
        }
      }
    }
  }
};

int main() {
  std::string s;
  std::cin >> s;

  int n;
  std::cin >> n;

  std::vector<std::string> patterns(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> patterns[i];
  }

  AhoCorasick ac(patterns);

  std::vector<std::vector<int>> results(n);
  ac.Search(s, results);

  for (int i = 0; i < n; ++i) {
    std::cout << results[i].size() << " ";
    for (int index : results[i]) {
      std::cout << index + 1 << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}