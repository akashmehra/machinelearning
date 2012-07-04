#include <iostream>
#include "transformation2d.h"
int main(int argc, char* argv[])
{
  ml::Point2d<int> p(2,1);
  ml::Point2d<int> p2;
  ml::Transform2d<int>::reflection(p,ml::Y_AXIS,&p2);
  std::cout << "Point: (" << p.x << "," << p.y << ")" << std::endl;
  std::cout << "Point: (" << p2.x << "," << p2.y << ")" << std::endl;
  return 0;
}
