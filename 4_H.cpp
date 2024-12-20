#include <algorithm>
#include <iostream>
#include <vector>

struct Point {
  int64_t x;
  int64_t y;
  Point() : x(0), y(0) {}
  Point(int64_t x, int64_t y) : x(x), y(y) {}
  friend std::istream& operator>>(std::istream& in, Point& point);
};

std::istream& operator>>(std::istream& in, Point& point) {
  int64_t x = 0;
  int64_t y = 0;
  in >> x >> y;
  point.x = x;
  point.y = y;
  return in;
}

struct Vector {
  int64_t x;
  int64_t y;
  Vector() : x(0), y(0) {}
  Vector(const Point& first, const Point& second)
      : x(second.x - first.x), y(second.y - first.y) {}
};

int64_t Cross(const Vector& first, const Vector& second) {
  int64_t product = first.x * second.y - first.y * second.x;
  return product;
}

bool ComparePoints(const Point& a, const Point& b) {
  if (a.x * b.y == a.y * b.x) {
    return (a.x * a.x + a.y * a.y < b.x * b.x + b.y * b.y);
  }
  return (a.x * b.y < a.y * b.x);
}

void ConvexHull(int n, std::vector<Point>& points, std::vector<Point>& shell) {
  for (int64_t i = 1; i < n; ++i) {
    if (points[i].x < points[0].x ||
        (points[i].x == points[0].x && points[i].y < points[0].y)) {
      std::swap(points[i], points[0]);
    }
  }
  int64_t start_x = points[0].x;
  int64_t start_y = points[0].y;
  for (int64_t i = 0; i < n; ++i) {
    points[i].x = points[i].x - start_x;
    points[i].y = points[i].y - start_y;
  }
  std::sort(points.begin() + 1, points.end(), ComparePoints);
  for (int64_t i = 0; i < n; ++i) {
    points[i].x = points[i].x + start_x;
    points[i].y = points[i].y + start_y;
  }
  shell.push_back(points[0]);
  shell.push_back(points[1]);
  for (int64_t i = 2; i < n; i++) {
    while (shell.size() >= 2 &&
           (Cross(Vector(shell[shell.size() - 2], shell[shell.size() - 1]),
                  Vector(shell[shell.size() - 1], points[i])) >= 0)) {
      shell.pop_back();
    }
    shell.push_back(points[i]);
  }
}

void PolygonArea(std::vector<Point>& points) {
  size_t n = points.size();
  int64_t square = -points[0].x * points[n - 1].y;
  for (size_t i = 0; i < n - 1; ++i) {
    square += (points[i].x * points[i + 1].y);
    square -= (points[i].y * points[i + 1].x);
  }
  square += points[n - 1].x * points[0].y;
  if (std::abs(square) % 2 == 0) {
    std::cout << std::abs(square) / 2 << ".0";
  } else {
    std::cout << (std::abs(square) - 1) / 2 << ".5";
  }
}

int main() {
  int n = 0;
  std::cin >> n;
  std::vector<Point> points(n);
  std::vector<Point> hull;
  for (int64_t i = 0; i < n; ++i) {
    std::cin >> points[i];
  }
  ConvexHull(n, points, hull);
  std::cout << hull.size() << "\n";
  for (auto& i : hull) {
    std::cout << i.x << " " << i.y << "\n";
  }
  PolygonArea(hull);
}