#ifndef _HPS_AMBULANCE_CLUSTER_H_
#define _HPS_AMBULANCE_CLUSTER_H_
#include <vector>
#include <algorithm>
#include <assert.h>
#include <map>
#include <functional>
#include <numeric>

template <typename FeatureType>
struct Features
{
  int id;
  FeatureType value;// it could be a std::vector in svm light format, or just prices in dollars or heights and weights of people/animals. We don't need it but just in case.
};

template <typename CoordinateType>
struct Coordinates
{
  CoordinateType x;
  CoordinateType y;
  Coordinates()
  : x(0),
    y(0)
  {}
  Coordinates(CoordinateType x_, CoordinateType y_)
  : x(x_),
    y(y_)
  {}
  Coordinates<CoordinateType> operator+(const Coordinates<CoordinateType>& point)
  {
    return Coordinates(x+point.x, y+point.y);
  }
};

// a struct may end up improving the locality ref.
template <typename CoordinateType, typename DistanceType>
class Cluster
{
 private:
  typedef Coordinates<CoordinateType> Point;
  Point m_center;

  typedef std::vector<Point> Points;
  typedef std::pair<int, DistanceType> KeyValuePair;

  typedef std::map<int, DistanceType> ClusterPointsInfo;
  ClusterPointsInfo m_clusterPoints ;
 
  struct Keys
  {
    int operator()(KeyValuePair tuple)
    {
      return tuple.first;
    }
  };

protected:
  void UpdateClusterCenter(const Point& newCenter)
  {
    m_center = newCenter;
  }
  
  void PushPair(int idx, DistanceType distance)
  {
    assert(idx >= 0 && idx < m_clusterPoints.size());
    // can check if the value already exsits or not.
    m_clusterPoints.insert(std::pair<int, DistanceType>(idx, distance));
  }
 
 public:
  Cluster()
  : m_center(),
    m_clusterPoints()
  {}

  inline const Point& GetClusterCenter() const
  {
    return m_center;
  }
  inline std::vector<int> GetDataPointIndices()
  {
    std::vector<int> keys;
    std::transform(m_clusterPoints.begin(), m_clusterPoints.end(), back_inserter(keys),Keys());
    return keys;
  }
  inline int ClusterSize() 
  {
    return m_clusterPoints.size()+1;
  }
  
  Point GetClusterMean(const Points& dataSet)
  {
    std::vector<int> keys = GetDataPointIndices();
    Points dataPoints(keys.size());
    for(int i=0;i<keys.size();++i)
    {
      dataPoints[i] = dataSet[keys[i]];
    }
    Point mean = std::accumulate(dataPoints.begin(), dataPoints.end(), std::plus<Point>());
    mean.x = mean.x / ClusterSize();
    mean.y = mean.y / ClusterSize();
    return mean;
  }
};

#endif //_HPS_AMBULANCE_CLUSTER_H_
