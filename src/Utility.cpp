#include "Utility.h"

int randomNumber(int min, int max)
{
  std::random_device rd;


  std::mt19937 gen(rd());

  std::uniform_int_distribution<int> dist(min,max);

  int number = dist(gen);

  return number;
}
