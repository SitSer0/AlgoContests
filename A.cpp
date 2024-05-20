#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

const int cInf = std::numeric_limits<int>::max();
const int cKGoodAns = 2009000999;

struct Graph {
  std::vector<std::vector<std::pair<int, int>>> list;
  int number;
  int count;

  void Read() {
    std::cin >> number >> count;
    list.resize(number);
    int from;
    int to;
    int weight;
    for (int i = 0; i < count; ++i) {
      std::cin >> from >> to >> weight;
      list[from].push_back({to, weight});
      list[to].push_back({from, weight});
    }
  }

  void Dijkstra(int vertex) {
    std::vector<int> dist(number, cInf);
    dist[vertex] = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>>
        pq;
    pq.push({0, vertex});

    while (!pq.empty()) {
      int current_distance = pq.top().first;
      int current_vertex = pq.top().second;
      pq.pop();

      if (current_distance > dist[current_vertex]) {
        continue;
      }

      for (auto& edge : list[current_vertex]) {
        int neighbor = edge.first;
        int weight = edge.second;

        if (current_distance + weight < dist[neighbor]) {
          dist[neighbor] = current_distance + weight;
          pq.push({dist[neighbor], neighbor});
        }
      }
    }

    for (int i = 0; i < number; i++) {
      if (dist[i] == cInf) {
        std::cout << cKGoodAns << " ";
      } else {
        std::cout << dist[i] << " ";
      }
    }
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int lets_go;
  int start;
  std::cin >> lets_go;
  for (int i = 0; i < lets_go; ++i) {
    Graph boy;
    boy.Read();
    std::cin >> start;
    boy.Dijkstra(start);
  }
  return 0;
}