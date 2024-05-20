#include <algorithm>
#include <iostream>
#include <map>
#include <set>
#include <vector>

struct Graph {
  int number;
  std::vector<std::vector<std::pair<int, int>>> graph;
  std::vector<bool> used;
  std::vector<int> tin;
  std::vector<int> low;
  std::set<int> bridges;
  std::map<std::pair<int, int>, int> edge_count;
  int timer = 0;

  Graph(int number)
      : number(number),
        graph(number),
        used(number, false),
        tin(number, -1),
        low(number, -1) {}

  void AddEdge(int start, int end, int index) {
    graph[start].push_back({end, index});
    graph[end].push_back({start, index});
    edge_count[{std::min(start, end), std::max(start, end)}]++;
  }

  void Dfs(int vert, int last = -1) {
    used[vert] = true;
    tin[vert] = low[vert] = timer++;
    for (auto next : graph[vert]) {
      if (next.first == last) {
        continue;
      }
      if (used[next.first]) {
        low[vert] = std::min(low[vert], tin[next.first]);
      } else {
        Dfs(next.first, vert);
        low[vert] = std::min(low[vert], low[next.first]);
        if (low[next.first] > tin[vert]) {
          auto edge = std::make_pair(std::min(vert, next.first),
                                     std::max(vert, next.first));
          if (edge_count[edge] == 1) {
            bridges.insert(next.second);
          }
        }
      }
    }
  }

  void FindBridges() {
    for (int i = 0; i < number; ++i) {
      if (!used[i]) {
        Dfs(i);
      }
    }
  }

  void PrintBridges() {
    std::cout << bridges.size() << "\n";
    for (auto bridge : bridges) {
      std::cout << bridge << " ";
    }
    std::cout << "\n";
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int number;
  int count;
  std::cin >> number >> count;
  Graph graph(number);

  for (int i = 0; i < count; ++i) {
    int start;
    int end;
    std::cin >> start >> end;
    graph.AddEdge(start - 1, end - 1, i + 1);
  }

  graph.FindBridges();
  graph.PrintBridges();

  return 0;
}
