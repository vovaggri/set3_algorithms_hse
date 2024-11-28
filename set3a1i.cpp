#include <iostream>
#include <random>
#include <algorithm>

struct Circle {
    double x;
    double y;
    double r;
};

bool isInsideCircle(const Circle& circle, double px, double py) {
  double dx = px - circle.x;
  double dy = py - circle.y;

  return (dx * dx + dy * dy) <= (circle.r * circle.r);
}

bool isInsideIntersection(const Circle& c1, const Circle& c2, const Circle& c3, double px, double py) {
  return isInsideCircle(c1, px, py) && isInsideCircle(c2, px, py) && isInsideCircle(c3, px, py);
}

int main() {
  Circle c1;
  Circle c2;
  Circle c3;

  std::cin >> c1.x >> c1.y >> c1.r;
  std::cin >> c2.x >> c2.y >> c2.r;
  std::cin >> c3.x >> c3.y >> c3.r;

  double minX = std::max({c1.x - c1.r, c2.x - c2.r, c3.x - c3.r});
  double maxX = std::min({c1.x + c1.r, c2.x + c2.r, c3.x + c3.r});
  double minY = std::max({c1.y - c1.r, c2.y - c2.r, c3.y - c3.r});
  double maxY = std::min({c1.y + c1.r, c2.y + c2.r, c3.y + c3.r});

  double bounding_box_area = (maxX - minX) * (maxY - minY);

  const int num_samples = 1000000;
  int count_inside = 0;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> distX(minX, maxX);
  std::uniform_real_distribution<> distY(minY, maxY);

  // Монте-Карло
  for (int i = 0; i < num_samples; ++i) {
    double px = distX(gen); // Случайная x-координата
    double py = distY(gen); // Случайная y-координата

    if (isInsideIntersection(c1, c2, c3, px, py)) {
      ++count_inside;
    }
  }

  double area = (static_cast<double>(count_inside) / num_samples) * bounding_box_area;

  std::cout.precision(20);
  std::cout << area << "\n";

  return 0;
}
