#include <iostream>
#include <vector>
using namespace std;

/*
my position is x. o are coins. Find coins
distance( (2,1) => (1,3)) => 3 (manhattan distance)
-------------------------
| . | x | . | . | . | . |
-------------------------
| . | . | . | . | . | . |
-------------------------
| . | . | . | . | . | . |
-------------------------
| o | . | . | . | . | . |
-------------------------
| . | . | . | . | . | . |
-------------------------
*/

class Point {
public:
  int x, y;
  Point();
  Point(int, int);
};

Point::Point() {}
Point::Point(int x, int y) : x(x), y(y) {}

int getDistance(Point &p1, Point &p2) {
  return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

Point closestCoin(Point yourPosition, vector<Point> coinPositions) {
  Point result;

  if (coinPositions.empty()) {
    return Point(-1, -1);
  }
  int min_dist = getDistance(yourPosition, coinPositions[0]);
  result = coinPositions[0];
  int dist;
  for (auto &p : coinPositions) {
    dist = getDistance(yourPosition, p);
    if (dist < min_dist) {
      min_dist = dist;
      result = p;
    }
  }
  return result;
}

int main() {
  vector<Point> coinPositions;
  coinPositions.push_back(Point(3, 3));
  coinPositions.push_back(Point(5, 5));

  Point res = closestCoin(Point(1, 1), coinPositions);
  cout << res.x << ", " << res.y << endl;

  return 0;
}