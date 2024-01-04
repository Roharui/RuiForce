
#include <iostream>

#include "driver.hpp"
#include "genann.h"

int main(void)
{
  try
  {
    Driver driver;
    driver.Run();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}