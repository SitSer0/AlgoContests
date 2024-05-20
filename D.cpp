#include <iostream>
#include <stack>
#include <vector>

struct Graph {
  int number;
  int count;
  std::vector<std::vector<int>> adj;
  std::vector<std::vector<int>> adj_t;
  std::vector<bool> visited;
  std::vector<int> order;
  std::vector<int> comp;
  std::stack<int> st;
  int comp_count = 0;

  Graph(int num, int count)
      : number(num),
        count(count),
        adj(num),
        adj_t(num),
        visited(num, false),
        comp(num, -1) {}

  void Read() {
    int start;
    int end;
    for (int i = 0; i < count; ++i) {
      std::cin >> start >> end;
      adj[start - 1].push_back(end - 1);
      adj_t[end - 1].push_back(start - 1);
    }
  }

  void Dfs1(int vertex) {
    visited[vertex] = true;
    for (int next : adj[vertex]) {
      if (!visited[next]) {
        Dfs1(next);
      }
    }
    st.push(vertex);
  }

  void Dfs2(int vertex, int label) {
    comp[vertex] = label;
    for (int next : adj_t[vertex]) {
      if (comp[next] == -1) {
        Dfs2(next, label);
      }
    }
  }

  void Solve() {
    for (int i = 0; i < number; ++i) {
      if (!visited[i]) {
        Dfs1(i);
      }
    }

    while (!st.empty()) {
      int vert = st.top();
      st.pop();
      if (comp[vert] == -1) {
        Dfs2(vert, comp_count);
        comp_count++;
      }
    }
  }

  void Print() {
    std::cout << comp_count << "\n";
    for (int i = 0; i < number; ++i) {
      std::cout << comp[i] + 1 << " ";
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
  Graph babube(number, count);
  babube.Read();
  babube.Solve();
  babube.Print();
  return 0;
}
