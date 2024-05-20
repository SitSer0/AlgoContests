#include <iostream>
#include <queue>
#include <vector>

struct Graph {
  int number;
  int count;
  std::vector<std::vector<std::pair<int, int>>> graph;
  std::vector<bool> used;

  Graph(int number, int count) : number(number), count(count) {}

  void Read() {
    graph.resize(number, std::vector<std::pair<int, int>>(0));
    int start;
    int end;
    int weight;
    for (int i = 0; i < count; ++i) {
      std::cin >> start >> end >> weight;
      graph[start - 1].push_back(std::make_pair(end - 1, weight));
      graph[end - 1].push_back(std::make_pair(start - 1, weight));
    }
  }

  void FindMST() {
    int ans = 0;
    used.resize(number, false);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        que;
    que.push({0, 0});

    while (!que.empty()) {
      std::pair<int, int> current = que.top();
      que.pop();
      int vert = current.second;
      int dst = current.first;

      if (used[vert]) {
        continue;
      }
      used[vert] = true;
      ans += dst;

      for (auto next : graph[vert]) {
        if (!used[next.first]) {
          que.push({next.second, next.first});
        }
      }
    }
    std::cout << ans;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int number;
  int count;
  std::cin >> number >> count;
  Graph graph(number, count);
  graph.Read();
  graph.FindMST();
  return 0;
}
