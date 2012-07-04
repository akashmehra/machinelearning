#ifndef ml_transformation2d_h
#define ml_transformation2d_h

#include <vector>
#include <algorithm>
#include <assert.h>
#include <math.h>
namespace ml
{

enum Axis
{
  X_AXIS,
  Y_AXIS,
};
template<typename T>
struct Point2d
{
  T x;
  T y;
  Point2d(){}
  Point2d(T x_, T y_)
  :x(x_),
  y(y_)
  {}
};

template<typename T>
class Transform2d
{
  private:
    static inline void rotateXAxis(const Point2d<T>& point, Point2d<T>* pointR)
    {
      pointR->x = point.x;
      pointR->y = -point.y;
    }
    static inline void rotateYAxis(const Point2d<T>& point, Point2d<T>* pointR)
    {
      pointR->x = -point.x;
      pointR->y = point.y;
    }
  public:
    static void rotation(const Point2d<T>& point, float angle,Point2d<T>* pointR);
    static void reflection(const Point2d<T>& point, Axis axis, Point2d<T>* pointR);
};

template<typename T>
void Transform2d<T>::rotation(const Point2d<T>& point, float angle, Point2d<T>* pointR)
{
  pointR->x = point.x * cos(angle) - point.y * sin(angle);
  pointR->y = point.x * sin(angle) + point.y * cos(angle); 
}

template<typename T>
void Transform2d<T>::reflection(const Point2d<T>& point, Axis axis, Point2d<T>* pointR)
{
  switch(axis)
  {
  case X_AXIS:
    rotateXAxis(point,pointR);
    break;
  case Y_AXIS:
    rotateYAxis(point,pointR);
    break;
  }
}

}
#endif // ml_transformation2d_h
