#ifndef EECS_MATH_NODE_HH
#define EECS_MATH_NODE_HH
#include <string>
#include <iostream>
#include <list>

namespace EECS
{
  class MathNode
  {
    public:
        MathNode(){}
        MathNode(std::string l1, MathNode* c1)
        {  
          myChildren.push_back(std::make_pair(l1, c1));
        }
        MathNode(std::string l1, MathNode* c1, std::string l2, MathNode* c2)
        { 
          myChildren.push_back(std::make_pair(l1, c1));
          myChildren.push_back(std::make_pair(l2, c2));
        }       
        virtual std::string print()
        { 
            std::string result = "";           
            result += "(";
            for (auto childPair : myChildren) 
            {
                if (childPair.first == "arm1")
                {
                    result += childPair.second->print();
                }
            }        
            result += op();           
            for (auto childPair : myChildren)
            {
                if (childPair.first == "arm2")
                {                
                    result += childPair.second->print();
                }
            }
	    result += ")";
            return result;
        }
        virtual std::string op() = 0;        
    protected:       
        std::list<std::pair<std::string, MathNode*>> 
        myChildren;
  };
  class MultNode : public EECS::MathNode 
  {
    public:
      MultNode(std::string label1, MathNode* child1, std::string label2, MathNode* child2) : MathNode(label1, child1, label2, child2) 
      {              
                
      }
      virtual std::string op(){return " * ";}
  };
  class DivNode : public EECS::MathNode 
  {
    public:
      DivNode(std::string label1, MathNode* child1, std::string label2, MathNode* child2) : MathNode(label1, child1, label2, child2) 
      {    
                
      }
      virtual std::string op(){return " / ";}
  };
  class AddNode : public EECS::MathNode 
  {
    public:
      AddNode(std::string label1, MathNode* child1, std::string label2, MathNode* child2) : MathNode(label1, child1, label2, child2) 
      {    
                
      }
      virtual std::string op(){return " + ";}
  };
  class SubNode : public EECS::MathNode 
  {
    public:
      SubNode(std::string label1, MathNode* child1, std::string label2, MathNode* child2) : MathNode(label1, child1, label2, child2) 
      {    
                
      }
      virtual std::string op(){return " - ";}
  };
  class NegNode : public EECS::MathNode 
  {
    public:
      NegNode(std::string label1, MathNode* child1) : MathNode(label1, child1) 
      {    
                
      }
      virtual std::string op(){return "-";}
  };  
  class IntNode : public EECS::MathNode 
  {
    public:
      IntNode(int valueIn) : value(valueIn), MathNode()
      {
        
      }
      virtual std::string print() override 
      {
        return std::to_string(this->value);
      }
      virtual std::string op(){return "";}
    private:
      int value;
  };
}
#endif
