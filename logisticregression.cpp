#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include <iostream>

class IRegression
{
  public: virtual float gradient(std::vector<T>* theta,
                                 std::vector<T>* trainingExamples,
                                 std::vector<T>* labels) = 0;
          virtual float hypothesis(std::vector<T>* theta,
                                   std::vector<T>* trainingExamples,
                                   std::vector<T>* labels) = 0;
};

class LogisticRegression : public IRegression
{
  public:
    float gradient(std::vector<T>* theta,
                   std::vector<T>* trainingExamples,
                   std::vector<T>* labels) 
    {
      std::cout << "" << std::endl;
    }
    
    float hypothesis(std::vector<T>* theta,
                     std::vector<T>* trainingExamples,
                     std::vector<T>* labels) 
    {
      std::cout << "" << std::endl;
    }
};

int main(int argc, char* argv[])
{
  LogisticRegression<float>* lr;
 
  return 0;
}
