#include <iostream>
#define GLUE(a,b) std::a##b
void report (int line)
{
  std::cout << "Error at line " << line << std::endl;
  std::cout << "Error in func " << __func__ << std::endl;
}

int main()
{
  report(__LINE__);
  report(__LINE__);
  report(__LINE__);
  report(__LINE__);
  report(__LINE__);
  std::cout << "Error in file " << __FILE__ << std::endl;
} 
