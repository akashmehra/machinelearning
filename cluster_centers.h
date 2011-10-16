#ifndef _HPS_AMBULANCE_CLUSTERCENTERS_H_ 
#define _HPS_AMBULANCE_CLUSTERCENTERS_H_

#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <assert.h>
#include <cmath>
#include "cluster.h"

template <typename CoordinateType, typename DistanceType>
class ClusterCenters
{
 private:
  typedef Coordinates<CoordinateType> Point;
  typedef std::vector<Point> Centers;
  Centers m_centers;
  typedef Point& reference_type;
  typedef Point value_type;
  int m_numCenters;
 public:
 ClusterCenters(Centers centers,int num_centers)
 : m_numCenters(num_centers),
   m_centers(centers.begin(), centers.end())
 {}

  //ClusterCenters():centers(){};
  ~ClusterCenters(){}

  //calculates the nearest center to the point and updates the center coordinates.
  DistanceType GetGridDistanceToNearestCenter(const Point& point, Point* center)
  {
    int best_distance = std::numeric_limits<DistanceType>::max();
    for(int i=0;i<m_centers.size();++i)
    {
      DistanceType distance = GetGridDistance(point, m_centers[i]);
      if(distance < best_distance)
      {
	best_distance = distance;
	center = m_centers[i];
      }
    }
    return best_distance;
  }
  
  //calculates Grid Distance between point and center.
  DistanceType GetGridDistance(const Point& point, const Point& center)
  {
    return static_cast<DistanceType>(abs(point.x - center.x) + abs(point.y - center.y));
  }
  //accessors.
  //Get coordinates of the center at an index.
  inline const reference_type GetCenterAt(int idx) const 
  {
    assert(idx >= 0 && idx < m_centers.size());
    return m_centers[idx];
  }
  
  inline int NumCenters()
  {
    return m_centers.size();
  }
  
  //mutators.
  inline void SetCenterAt(int idx, const Point point)
  {
    assert(idx >=0 && idx < m_centers.size());
    m_centers[idx] = point;
  }

  void UpdateCenters(const std::vector<Cluster<CoordinateType, DistanceType> >& clusters, const std::vector<Point>& dataSet)
  {
    assert(clusters.size() == NumCenters());
    for(int idx=0;idx<clusters.size();++idx)
    {
      m_centers[idx] = clusters[idx].GetClusterMean(dataSet);
    }
  }
};

#endif //_HPS_AMBULANCE_CLUSTERCENTERS_H_
