#ifndef EECS665_AST
#define EECS665_AST
#include <list>

namespace EECS {

class OpNode;

class ProgramNode{
public:
	std::list<OpNode *> * ops;
	void print(){ }
};

enum OpTypes{
	CALCULATE, ORATE
};

class OpNode{
public:
	OpNode(){}
};

class CalculateNode : public OpNode
{

};

class OrateNode : public OpNode
{

};

class MathNode{
};

class AddNode : public MathNode
{

};

class SubNode : public MathNode
{

};

class MultNode : public MathNode
{

};

class DivNode : public MathNode
{

};

} //End namespace
#endif


