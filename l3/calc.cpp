#include "calc.hpp"
#include <cassert>

void EECS::Manager::parse(const char* filepath)
{
       std::ifstream in_stream(filepath);  
       std::cout << "It's getting ready to parse!!\n";
       parser->parse();
       return;
}       

int main(const int argc, const char *argv[])
{
        assert(argc > 1);   
        EECS::Manager manager(argv[1]);
        manager.parse(argv[1]);
}
