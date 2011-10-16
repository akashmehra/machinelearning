#ifndef _HPS_AMBULANCE_KMEANS_H_
#define _HPS_AMBULANCE_KMEANS_H_
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <assert.h>
#include <cmath>
#include "cluster_centers.h"

template <typename CoordinateType, typename DistanceType>
class ClusteringAlgorithms
{
 private:
  typedef Coordinates<CoordinateType> Point;
  typedef std::vector<Point> Points;
  typedef std::vector<Cluster<CoordinateType, DistanceType> > Clusters;
  int m_numCenters;
  Points m_dataSet;
  ClusterCenters<CoordinateType, DistanceType> m_clusterCenters;
  Clusters m_clusters;
  int m_iterations;
 public:
 ClusteringAlgorithms(int num_centers, int num_iterations, const Points& dataSet)
  : m_numCenters(num_centers),
    m_clusters(),
    m_iterations(num_iterations)
  {
    m_dataSet = dataSet;
  }
  ~ClusteringAlgorithms()
  {}
  CoordinateType RandPoint()
  {
    int randIdx = static_cast<int>(rand() % m_dataSet.size());
    return m_dataSet[randIdx];
  }
  void initCenters()
  {
    assert(m_numCenters > 0);
    Points centers(m_numCenters);
    for(int i=0;i<centers.size();++i)
    {
      centers[i] = RandPoint();
    }
    m_clusterCenters(centers, m_numCenters);
  }
  Clusters Kmeans()
  {
    initCenters();
    for(int i = 1; i<= m_iterations; ++i)
    {
      Cluster<CoordinateType, DistanceType> cluster;
      for(int j=0;j<m_dataSet.size();++j)
      {
	Point center;
	DistanceType bestDistance = m_clusterCenters.GetGridDistanceToNearestCenter(m_dataSet[j],&center);
	cluster.UpdateClusterCenter(center);
	cluster.PushPair(j);
      }
      m_clusterCenters.UpdateCenters(m_clusters, m_dataSet);
    }
  }
  
  
};
#endif //_HPS_AMBULANCE_KMEANS_H_
