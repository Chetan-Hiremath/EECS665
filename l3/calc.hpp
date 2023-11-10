#ifndef EECS_MANAGER_HPP
#define EECS_MANAGER_HPP
#include "scanner.hpp"
#include "grammar.hh"
#include "nodes.hpp"

namespace EECS
{
  class Manager 
  {
    public: 
    Manager(const char* filepath)
    {
      std::ifstream* in_stream = new std::ifstream(filepath);
      this->scanner = new EECS::Scanner(in_stream);
      this->parser = new EECS::Parser(scanner, this);
    }
    void parse(const char* filepath);
    private:
      EECS::Scanner* scanner = nullptr;
      EECS::Parser* parser = nullptr;
  }; /* end class manager */       
} /* end namespace EECS */
#endif
