#include "calc.hpp"
#include <cassert>
#include <fstream>

void EECS::Manager::parse(const char* filepath)
{
       std::ifstream in_stream(filepath);  
       this->scanner = new EECS::Scanner(&in_stream);
       this->parser = new EECS::Parser(*scanner, *this);
       std::cout << "It's getting ready to parse!!\n";
       parser->parse();
       return;
}       

int main(const int argc, const char *argv[])
{
        assert(argc > 1);   
        EECS::Manager manager;
        manager.parse(argv[1]);
}
