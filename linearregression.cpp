#include <iostream>
#include "linearregression.h"

int main(int argc, char* argv[])
{
  LinearRegression<float,float> lr;
  std::vector<float> te;
  std::vector<float> l;
  std::vector<float> theta;
  std::vector<std::vector<float> > tes;
  lr.gradient(tes,l,&theta);
  lr.hypothesis(theta,te);
  return 0;
}

