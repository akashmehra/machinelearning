#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <assert.h>

template <typename T, typename E>
class IRegression
{
  public:
    virtual float gradient(const std::vector<std::vector<E> >& trainingExamples,
                           const std::vector<T>& labels,
                           std::vector<T>* theta) = 0;

    virtual float hypothesis(const std::vector<T>& theta,
                             const std::vector<T>& trainingExample) = 0;
};

template <typename T, typename E>
class LinearRegression : public IRegression<T,E>
{
  public:
    float gradient(const std::vector<std::vector<E> >& trainingExamples,
                   const std::vector<T>& labels,
                   std::vector<T>* theta)
    {
      float sum = 0.0f;
      for(int i = 0; i < trainingExamples.size();++i)
      {
        assert(theta->size() == trainingExamples[i].size());
        assert(labels.size() == trainingExamples[i].size());
        for(int j = 0;j < theta->size();++j)
        {
          sum += (this->hypothesis(*theta,trainingExamples[i]) - labels[i])*trainingExamples[i][j];
        }
      }
      int m = theta->size();
      return (sum/m);
    }
    
    float hypothesis(const std::vector<T>& theta,
                     const std::vector<T>& trainingExample)
    {
      assert(theta.size() == trainingExample.size());
      float value = 0.0f;
      for(int idx = 0;idx < theta.size();++idx)
      {
        value += (theta.at(idx) * trainingExample.at(idx));
      }
      return value;
    }
};

