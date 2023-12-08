#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

struct Event {
  int x0;
  int y1;
  int y2;
  int type;
  Event(int x0, int y1, int y2, int type)
      : x0(x0), y1(y1), y2(y2), type(type) {}
};

struct Vertex {
  int count;
  int64_t ans;
};

bool Comp(const Event& aa, const Event& bb) {
  if (aa.x0 != bb.x0) {
    return aa.x0 < bb.x0;
  }
  return aa.type > bb.type;
}

class SegmentTree {
 public:
  SegmentTree(const std::vector<int>& arr) : arr_(arr), size_(arr.size()) {
    tree_.resize(4 * size_);
  }

  void Add(int y1, int y2, int value) {
    left_ = y1;
    right_ = y2 - 1;
    Update(0, 0, size_ - 2, value);
  }

  int64_t Ans() { return tree_[0].ans; }

 private:
  std::vector<Vertex> tree_;
  std::vector<int> arr_;
  int left_;
  int right_;
  int size_;

  static int LeftChild(int vertex) { return 2 * vertex + 1; }
  static int RightChild(int vertex) { return 2 * vertex + 2; }

  void Update(int vertex, int start, int end, int value) {
    if (start > right_ || end < left_) {
      return;
    }
    if (start >= left_ && end <= right_) {
      tree_[vertex].count += value;
    } else {
      int mid = (start + end) / 2;
      Update(LeftChild(vertex), start, mid, value);
      Update(RightChild(vertex), mid + 1, end, value);
    }
    if (tree_[vertex].count > 0) {
      tree_[vertex].ans = arr_[std::min(end + 1, size_)] - arr_[start];
    } else {
      tree_[vertex].ans =
          tree_[LeftChild(vertex)].ans + tree_[RightChild(vertex)].ans;
    }
  }
};

void Read(int& number, std::vector<Event>& events, std::vector<int>& cord_y) {
  std::cin >> number;
  for (int i = 0; i < number; ++i) {
    int x1;
    int y1;
    int x2;
    int y2;
    std::cin >> x1 >> y1 >> x2 >> y2;
    events.emplace_back(x1, y1, y2, 1);
    events.emplace_back(x2, y1, y2, -1);
    cord_y.push_back(y1);
    cord_y.push_back(y2);
  }
  std::sort(cord_y.begin(), cord_y.end());
  cord_y.erase(std::unique(cord_y.begin(), cord_y.end()), cord_y.end());
}

int main() {
  int number;
  std::vector<Event> events;
  std::vector<int> cord_y;
  Read(number, events, cord_y);
  std::map<int, int> y_to_cord;
  for (size_t i = 0; i < cord_y.size(); ++i) {
    y_to_cord[cord_y[i]] = i;
  }
  for (int i = 0; i < 2 * number; ++i) {
    events[i].y1 = y_to_cord[events[i].y1];
    events[i].y2 = y_to_cord[events[i].y2];
  }
  std::sort(events.begin(), events.end(), Comp);
  SegmentTree tree(cord_y);
  int64_t area = 0;
  int last_x = 0;
  for (int i = 0; i < 2 * number; ++i) {
    area += (events[i].x0 - last_x) * tree.Ans();
    tree.Add(events[i].y1, events[i].y2, events[i].type);
    last_x = events[i].x0;
  }
  std::cout << area;
  return 0;
}