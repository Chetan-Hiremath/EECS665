#include "ast.hpp"
#include "symbol_table.hpp"
#include "errors.hpp"
#include "types.hpp"
#include "name_analysis.hpp"
#include "type_analysis.hpp"

namespace jeff{

TypeAnalysis * TypeAnalysis::build(NameAnalysis * nameAnalysis){
	//To emphasize that type analysis depends on name analysis
	// being complete, a name analysis must be supplied for 
	// type analysis to be performed.
	TypeAnalysis * typeAnalysis = new TypeAnalysis();
	auto ast = nameAnalysis->ast;	
	typeAnalysis->ast = ast;

	ast->typeAnalysis(typeAnalysis);
	if (typeAnalysis->hasError){
		return nullptr;
	}

	return typeAnalysis;

}

void ProgramNode::typeAnalysis(TypeAnalysis * ta){

	//pass the TypeAnalysis down throughout
	// the entire tree, getting the types for
	// each element in turn and adding them
	// to the ta object's hashMap
	for (auto global : *myGlobals){
		global->typeAnalysis(ta);
	}

	//The type of the program node will never
	// be needed. We can just set it to VOID
	//(Alternatively, we could make our type 
	// be error if the DeclListNode is an error)
	ta->nodeType(this, BasicType::produce(VOID));
}

void FnDeclNode::typeAnalysis(TypeAnalysis * ta){

	//HINT: you might want to change the signature for
	// typeAnalysis on FnBodyNode to take a second
	// argument which is the type of the current 
	// function. This will help you to know at a 
	// return statement whether the return type matches
	// the current function

	//Note: this function may need extra code

	for (auto stmt : *myBody){
		stmt->typeAnalysis(ta);
	}
}

void StmtNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Implement me in the subclass");
}

void OpenStmtNode::typeAnalysis(TypeAnalysis * ta){
        if (this->handle == nullptr)
        {
          TODO("handle no arguments on a void");
          TODO("handle no arguments on a non-void function");
        }
        else
        {
	  handle->typeAnalysis(ta);
	  const DataType * childType = ta->nodeType(handle);
	  TODO("check that this type is what was supposed to be returned");
	}
}

void CloseStmtNode::typeAnalysis(TypeAnalysis * ta){
        if (this->handle == nullptr)
        {
          TODO("handle no arguments on a void");
          TODO("handle no arguments on a non-void function");
        }
        else
        {
	  handle->typeAnalysis(ta);
	  const DataType * childType = ta->nodeType(handle);
	  TODO("check that this type is what was supposed to be returned");
	}
}

void PostIncStmtNode::typeAnalysis(TypeAnalysis * ta){
        if (this->myLoc == nullptr)
        {
          TODO("handle no arguments on a void");
          TODO("handle no arguments on a non-void function");
        }
        else
        {
	  myLoc->typeAnalysis(ta);
	  const DataType * childType = ta->nodeType(myLoc);
	  TODO("check that this type is what was supposed to be returned");
	}
}

void PostDecStmtNode::typeAnalysis(TypeAnalysis * ta){
        if (this->myLoc == nullptr)
        {
          TODO("handle no arguments on a void");
          TODO("handle no arguments on a non-void function");
        }
        else
        {
	  myLoc->typeAnalysis(ta);
	  const DataType * childType = ta->nodeType(myLoc);
	  TODO("check that this type is what was supposed to be returned");
	}
}

void IfStmtNode::typeAnalysis(TypeAnalysis * ta){
        if (this->myCond == nullptr)
        {
          TODO("handle no arguments on a void");
          TODO("handle no arguments on a non-void function");
        }
        else
        {
	  myCond->typeAnalysis(ta);
	  const DataType * childType = ta->nodeType(myCond);
	  TODO("check that this type is what was supposed to be returned");
	}
}

void IfElseStmtNode::typeAnalysis(TypeAnalysis * ta){
        if (this->myCond == nullptr)
        {
          TODO("handle no arguments on a void");
          TODO("handle no arguments on a non-void function");
        }
        else
        {
	  myCond->typeAnalysis(ta);
	  const DataType * childType = ta->nodeType(myCond);
	  TODO("check that this type is what was supposed to be returned");
	}
}

void WhileStmtNode::typeAnalysis(TypeAnalysis * ta){
        if (this->myCond == nullptr)
        {
          TODO("handle no arguments on a void");
          TODO("handle no arguments on a non-void function");
        }
        else
        {
	  myCond->typeAnalysis(ta);
	  const DataType * childType = ta->nodeType(myCond);
	  TODO("check that this type is what was supposed to be returned");
	}
}

void ReturnStmtNode::typeAnalysis(TypeAnalysis * ta){
        if (this->myExp == nullptr)
        {
          TODO("handle no arguments on a void");
          TODO("handle no arguments on a non-void function");
        }
        else
        {
	  myExp->typeAnalysis(ta);
	  const DataType * childType = ta->nodeType(myExp);
	  TODO("check that this type is what was supposed to be returned");
	}
}

void CallStmtNode::typeAnalysis(TypeAnalysis * ta){
        if (this->myCallExp == nullptr)
        {
          TODO("handle no arguments on a void");
          TODO("handle no arguments on a non-void function");
        }
        else
        {
	  myCallExp->typeAnalysis(ta);
	  const DataType * childType = ta->nodeType(myCallExp);
	  TODO("check that this type is what was supposed to be returned");
	}
}

void ReadStmtNode::typeAnalysis(TypeAnalysis * ta){
	myHandle->typeAnalysis(ta);
	myDst->typeAnalysis(ta);

	const DataType * handleType = ta->nodeType(myHandle);
	const DataType * dstType = ta->nodeType(myDst);

	if (handleType->asError() || dstType->asError()){
		ta->nodeType(this, ErrorType::produce());
	}

	if (handleType == dstType){
		ta->nodeType(this, handleType);
		return;
	}
	
	ta->errAssignOpr(this->pos());
	ta->nodeType(this, BasicType::produce(VOID));

}

void WriteStmtNode::typeAnalysis(TypeAnalysis * ta){
	myHandle->typeAnalysis(ta);
	mySrc->typeAnalysis(ta);

	const DataType * handleType = ta->nodeType(myHandle);
	const DataType * srcType = ta->nodeType(mySrc);

	if (handleType->asError() || srcType->asError()){
		ta->nodeType(this, ErrorType::produce());
	}

	if (handleType == srcType){
		ta->nodeType(this, handleType);
		return;
	}
	
	ta->errAssignOpr(this->pos());
	ta->nodeType(this, BasicType::produce(VOID));

}

void AssignStmtNode::typeAnalysis(TypeAnalysis * ta){
	//TODO: Note that this function is incomplete. 
	// and needs additional code

	//Do typeAnalysis on the subexpressions
	myDst->typeAnalysis(ta);
	mySrc->typeAnalysis(ta);

	const DataType * tgtType = ta->nodeType(myDst);
	const DataType * srcType = ta->nodeType(mySrc);


	// As error returns null if subType is NOT an error type
	// otherwise, it returns the subType itself. It 
	// sort of serves as a way to cast the subtype
	if (tgtType->asError() || srcType->asError()){
		ta->nodeType(this, ErrorType::produce());
	}


	//While incomplete, this gives you one case for 
	// assignment: if the types are exactly the same
	// it is usually ok to do the assignment. One
	// exception is that if both types are function
	// names, it should fail type analysis
	if (tgtType == srcType){
		ta->nodeType(this, tgtType);
		return;
	}
	
	//Some functions are already defined for you to
	// report type errors. Note that these functions
	// also tell the typeAnalysis object that the
	// analysis has failed, meaning that main.cpp
	// will print "Type check failed" at the end
	ta->errAssignOpr(this->pos());


	// Here, we set the type of the assignment
	// to void to indicate no error was found.
	// This step is optional, since you'll never
	// use the type of a statement
	ta->nodeType(this, BasicType::produce(VOID));

}

void ExpNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Override me in the subclass");
}

void PlusNode::typeAnalysis(TypeAnalysis * ta)
{
  myExp1->typeAnalysis(ta);
  myExp2->typeAnalysis(ta);
  const DataType * lhsType = ta->nodeType(myExp1);
  const DataType * rhsType = ta->nodeType(myExp2);  
  if (lhsType->isInt() && rhsType->isInt())
  {
    ta->nodeType(this, BasicType::INT());
    return;
  }
  if (lhsType->asError() && rhsType->asError())
  {
    ta->nodeType(this, ErrorType::produce());
    return;
  }
  TODO("Handle non-error, non-int args");
}

void MinusNode::typeAnalysis(TypeAnalysis * ta)
{
  myExp1->typeAnalysis(ta);
  myExp2->typeAnalysis(ta);
  const DataType * lhsType = ta->nodeType(myExp1);
  const DataType * rhsType = ta->nodeType(myExp2);  
  if (lhsType->isInt() && rhsType->isInt())
  {
    ta->nodeType(this, BasicType::INT());
    return;
  }
  if (lhsType->asError() && rhsType->asError())
  {
    ta->nodeType(this, ErrorType::produce());
    return;
  }
  TODO("Handle non-error, non-int args");
}

void TimesNode::typeAnalysis(TypeAnalysis * ta)
{
  myExp1->typeAnalysis(ta);
  myExp2->typeAnalysis(ta);
  const DataType * lhsType = ta->nodeType(myExp1);
  const DataType * rhsType = ta->nodeType(myExp2);  
  if (lhsType->isInt() && rhsType->isInt())
  {
    ta->nodeType(this, BasicType::INT());
    return;
  }
  if (lhsType->asError() && rhsType->asError())
  {
    ta->nodeType(this, ErrorType::produce());
    return;
  }
  TODO("Handle non-error, non-int args");
}

void DivideNode::typeAnalysis(TypeAnalysis * ta)
{
  myExp1->typeAnalysis(ta);
  myExp2->typeAnalysis(ta);
  const DataType * lhsType = ta->nodeType(myExp1);
  const DataType * rhsType = ta->nodeType(myExp2);  
  if (lhsType->isInt() && rhsType->isInt())
  {
    ta->nodeType(this, BasicType::INT());
    return;
  }
  if (lhsType->asError() && rhsType->asError())
  {
    ta->nodeType(this, ErrorType::produce());
    return;
  }
  TODO("Handle non-error, non-int args");
}

void AndNode::typeAnalysis(TypeAnalysis * ta)
{
  myExp1->typeAnalysis(ta);
  myExp2->typeAnalysis(ta);
  const DataType * lhsType = ta->nodeType(myExp1);
  const DataType * rhsType = ta->nodeType(myExp2);  
  if (lhsType->isBool() && rhsType->isBool())
  {
    ta->nodeType(this, BasicType::BOOL());
    return;
  }
  if (lhsType->asError() && rhsType->asError())
  {
    ta->nodeType(this, ErrorType::produce());
    return;
  }
  TODO("Handle non-error, non-bool args");
}

void OrNode::typeAnalysis(TypeAnalysis * ta)
{
  myExp1->typeAnalysis(ta);
  myExp2->typeAnalysis(ta);
  const DataType * lhsType = ta->nodeType(myExp1);
  const DataType * rhsType = ta->nodeType(myExp2);  
  if (lhsType->isBool() && rhsType->isBool())
  {
    ta->nodeType(this, BasicType::BOOL());
    return;
  }
  if (lhsType->asError() && rhsType->asError())
  {
    ta->nodeType(this, ErrorType::produce());
    return;
  }
  TODO("Handle non-error, non-bool args");
}

void EqualsNode::typeAnalysis(TypeAnalysis * ta)
{
  myExp1->typeAnalysis(ta);
  myExp2->typeAnalysis(ta);
  const DataType * lhsType = ta->nodeType(myExp1);
  const DataType * rhsType = ta->nodeType(myExp2);  
  if (lhsType->isInt() && rhsType->isInt())
  {
    ta->nodeType(this, BasicType::BOOL());
    return;
  }
  if (lhsType->asError() && rhsType->asError())
  {
    ta->nodeType(this, ErrorType::produce());
    return;
  }
  TODO("Handle non-error, non-bool args");
}

void NotEqualsNode::typeAnalysis(TypeAnalysis * ta)
{
  myExp1->typeAnalysis(ta);
  myExp2->typeAnalysis(ta);
  const DataType * lhsType = ta->nodeType(myExp1);
  const DataType * rhsType = ta->nodeType(myExp2);  
  if (lhsType->isInt() && rhsType->isInt())
  {
    ta->nodeType(this, BasicType::BOOL());
    return;
  }
  if (lhsType->asError() && rhsType->asError())
  {
    ta->nodeType(this, ErrorType::produce());
    return;
  }
  TODO("Handle non-error, non-bool args");
}

void LessNode::typeAnalysis(TypeAnalysis * ta)
{
  myExp1->typeAnalysis(ta);
  myExp2->typeAnalysis(ta);
  const DataType * lhsType = ta->nodeType(myExp1);
  const DataType * rhsType = ta->nodeType(myExp2);  
  if (lhsType->isInt() && rhsType->isInt())
  {
    ta->nodeType(this, BasicType::BOOL());
    return;
  }
  if (lhsType->asError() && rhsType->asError())
  {
    ta->nodeType(this, ErrorType::produce());
    return;
  }
  TODO("Handle non-error, non-bool args");
}

void LessEqNode::typeAnalysis(TypeAnalysis * ta)
{
  myExp1->typeAnalysis(ta);
  myExp2->typeAnalysis(ta);
  const DataType * lhsType = ta->nodeType(myExp1);
  const DataType * rhsType = ta->nodeType(myExp2);  
  if (lhsType->isInt() && rhsType->isInt())
  {
    ta->nodeType(this, BasicType::BOOL());
    return;
  }
  if (lhsType->asError() && rhsType->asError())
  {
    ta->nodeType(this, ErrorType::produce());
    return;
  }
  TODO("Handle non-error, non-bool args");
}

void GreaterNode::typeAnalysis(TypeAnalysis * ta)
{
  myExp1->typeAnalysis(ta);
  myExp2->typeAnalysis(ta);
  const DataType * lhsType = ta->nodeType(myExp1);
  const DataType * rhsType = ta->nodeType(myExp2);  
  if (lhsType->isInt() && rhsType->isInt())
  {
    ta->nodeType(this, BasicType::BOOL());
    return;
  }
  if (lhsType->asError() && rhsType->asError())
  {
    ta->nodeType(this, ErrorType::produce());
    return;
  }
  TODO("Handle non-error, non-bool args");
}

void GreaterEqNode::typeAnalysis(TypeAnalysis * ta)
{
  myExp1->typeAnalysis(ta);
  myExp2->typeAnalysis(ta);
  const DataType * lhsType = ta->nodeType(myExp1);
  const DataType * rhsType = ta->nodeType(myExp2);  
  if (lhsType->isInt() && rhsType->isInt())
  {
    ta->nodeType(this, BasicType::BOOL());
    return;
  }
  if (lhsType->asError() && rhsType->asError())
  {
    ta->nodeType(this, ErrorType::produce());
    return;
  }
  TODO("Handle non-error, non-bool args");
}

void NegNode::typeAnalysis(TypeAnalysis * ta)
{
  myExp->typeAnalysis(ta);
  const DataType * lhsType = ta->nodeType(myExp);
  if (lhsType->isInt())
  {
    ta->nodeType(this, BasicType::INT());
    return;
  }
  if (lhsType->asError())
  {
    ta->nodeType(this, ErrorType::produce());
    return;
  }
  TODO("Handle non-error, non-int args");
}

void NotNode::typeAnalysis(TypeAnalysis * ta)
{
  myExp->typeAnalysis(ta);
  const DataType * lhsType = ta->nodeType(myExp);
  if (lhsType->isBool())
  {
    ta->nodeType(this, BasicType::BOOL());
    return;
  }
  if (lhsType->asError())
  {
    ta->nodeType(this, ErrorType::produce());
    return;
  }
  TODO("Handle non-error, non-bool args");
}

void TrueNode::typeAnalysis(TypeAnalysis * ta)
{
	ta->nodeType(this, BasicType::produce(BOOL));
}

void FalseNode::typeAnalysis(TypeAnalysis * ta)
{
	ta->nodeType(this, BasicType::produce(BOOL));
}

void DeclNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Override me in the subclass");
}

void FormalDeclNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Override me in the subclass");
}

void VarDeclNode::typeAnalysis(TypeAnalysis * ta){
	// VarDecls always pass type analysis, since they 
	// are never used in an expression. You may choose
	// to type them void (like this), as discussed in class
	ta->nodeType(this, BasicType::produce(VOID));
}

void IDNode::typeAnalysis(TypeAnalysis * ta){
	// IDs never fail type analysis and always
	// yield the type of their symbol (which
	// depends on their definition)
	ta->nodeType(this, this->getSymbol()->getDataType());
}

void IndexNode::typeAnalysis(TypeAnalysis * ta){
	ta->nodeType(this, this->getSymbol()->getDataType());
}

void IntLitNode::typeAnalysis(TypeAnalysis * ta){
	// IntLits never fail their type analysis and always
	// yield the type INT
	ta->nodeType(this, BasicType::produce(INT));
}

void StrLitNode::typeAnalysis(TypeAnalysis * ta){
	ta->nodeType(this, BasicType::produce(STRING));
}

void FileTypeNode::typeAnalysis(TypeAnalysis * ta){
	ta->nodeType(this, BasicType::produce(FILE));
}

void VoidTypeNode::typeAnalysis(TypeAnalysis * ta){
	ta->nodeType(this, BasicType::produce(VOID));
}

void BoolTypeNode::typeAnalysis(TypeAnalysis * ta){
	ta->nodeType(this, BasicType::produce(BOOL));
}

void IntTypeNode::typeAnalysis(TypeAnalysis * ta){
	ta->nodeType(this, BasicType::produce(INT));
}

void ArrayTypeNode::typeAnalysis(TypeAnalysis * ta){
	ta->nodeType(this, getType());
}

}
