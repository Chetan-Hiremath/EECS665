#include <stdlib.h>
#include <iostream>

class ToDoError{
public:
        ToDoError(){}
};

int bar(){
  int *p = nullptr;
  int a = rand();
  a = 1;
  if (a == 1){
    throw new ToDoError();
    *p = 2;
    return 1;
  } else {
    return 2;
  }
}

int foo(){
        int a = 7;
        return bar();
}

int main(int argc, char * argv[]){
         std::cout << "There are " << argc << " args\n";
         foo();
}
