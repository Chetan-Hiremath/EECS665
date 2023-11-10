#include <iostream>

void func(int a)
{
  std::cout << "in fn with a\n";
}
void func(int a, int b)
{
  std::cout << "in fn with a and b\n";
}
void func(bool c)
{
  std::cout << "in fn with c\n";
}
int main()
{
  func(1);
  func(1,2);
  func(true);
}
