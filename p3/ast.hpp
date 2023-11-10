#ifndef JEFF_AST_HPP
#define JEFF_AST_HPP

#include <ostream>
#include <list>
#include "tokens.hpp"
#include <cassert>

namespace jeff{

/* You may find it useful to forward declare AST subclasses
   here so that you can use a class before it's full definition
*/
//class DeclListNode;
class DeclNode;
class TypeNode;
class IDNode;
class ExpNode;
class ProgramNode;
class StmtNode;
class AssignExpNode;
class BinaryExpNode;
class CallExpNode;
class FalseNode;
class IntLitNode;
class LocNode;
class StrLitNode;
class TrueNode;
class UnaryExpNode;
class AssignStmtNode;
class CallStmtNode;
class IfElseStmtNode;
class IfStmtNode;
class PostDecStmtNode;
class PostIncStmtNode;
class ReturnStmtNode;
class WhileStmtNode;
class ArrayTypeNode; 
class BoolTypeNode;
class ArrayTypeNode;
class IntTypeNode;
class VoidTypeNode;
class FileTypeNode;
class AndNode;
class DivideNode;
class EqualsNode;
class GreaterEqNode;
class GreaterNode;
class LessEqNode;
class LessNode;
class MinusNode;
class NotEqualsNode;
class OrNode;
class PlusNode;
class TimesNode;
class IndexNode;
class NegNode;
class NotNode;
class FnDeclNode;
class VarDeclNode;
class FormalDeclNode;


class ASTNode{
public:
	ASTNode(size_t lineIn, size_t colIn): l(lineIn), c(colIn){ }
	virtual void unparse(std::ostream& out, int indent) = 0;
	size_t line(){ return l; }
	size_t col() { return c; }

	std::string pos(){ return "[" + std::to_string(line()) + "," + std::to_string(col()) + "]";
	}

protected:
	size_t l; 
	size_t c; 
};

class ExpNode : public ASTNode{
protected:
	ExpNode(size_t l, size_t c) : ASTNode(l, c){}
};

class ProgramNode : public ASTNode{
public:
	ProgramNode(std::list<DeclNode *> * globalsIn) : ASTNode(1, 1), myGlobals(globalsIn){}
	void unparse(std::ostream& out, int indent) override;
private:
	std::list<DeclNode * > * myGlobals;
};

class StmtNode : public ASTNode{
public:
	StmtNode(size_t l, size_t c) : ASTNode(l ,c) {}
	virtual void unparse(std::ostream& out, int indent) = 0;
};

class IDNode : public ExpNode{
public:
	IDNode(IDToken * token) : ExpNode(token->line(), token->col()), myStrVal(token->value()){
		myStrVal = token->value();
	}
	virtual void unparse(std::ostream& out, int indent);
private:
	std::string myStrVal;
};

/**  \class TypeNode
* Superclass of nodes that indicate a data type. For example, in 
* the declaration "int a", the int part is the type node (a is an IDNode
* and the whole thing is a DeclNode).
**/
class TypeNode : public ASTNode{
protected:
	TypeNode(size_t lineIn, size_t colIn) 
	: ASTNode(lineIn, colIn){
	}
public:
	virtual void unparse(std::ostream& out, int indent) = 0;
private:
	bool IsReference;
};

class LocNode : public ExpNode{
public:
	LocNode(IDNode* id) : ExpNode(id->line(), id->col()), myId(id){}
	void unparse(std::ostream& out, int indent);

private:
	IDNode* myId;
};

class AssignExpNode : public ExpNode{
public:
	AssignExpNode(LocNode* loc, ExpNode* srcExp) : ExpNode(loc->line(), loc->col()), myLoc(loc), myExp(srcExp){}
	void unparse(std::ostream& out, int indent);
private:
	LocNode* myLoc;
	ExpNode* myExp;
};

class BinaryExpNode : public ExpNode{
public:
	BinaryExpNode(ExpNode* lhs, ExpNode* rhs) : ExpNode(lhs->line(), lhs->col()){}
	virtual void unparse(std::ostream& out, int indent) = 0;
};

class CallExpNode : public ExpNode{
public:
	CallExpNode(IDNode* id, std::list<ExpNode*>* paramList) : ExpNode(id->line(), id->col()), myId(id), myFormals(paramList){}
	void unparse(std::ostream& out, int indent);

private:
	IDNode* myId;
	std::list<ExpNode*>* myFormals;
};

class IntLitNode : public ExpNode{
public:
	IntLitNode(size_t l, size_t c, IntLitToken* intIn) : ExpNode(l, c){
		myInt = intIn->num();
	}
	void unparse(std::ostream& out, int indent);
private:
	int myInt;
};

class StrLitNode : public ExpNode{
public:
	StrLitNode(size_t l, size_t c, StrToken* strIn) : ExpNode(l, c){
		myStr = strIn->str();
	}
	void unparse(std::ostream& out, int indent);
private:
	std::string myStr;
};

class TrueNode : public ExpNode{
public:
	TrueNode(Token* token) : ExpNode(token->line(), token->col()){}
	void unparse(std::ostream& out, int indent);
};

class FalseNode : public ExpNode{
public:
	FalseNode(Token* token) : ExpNode(token->line(), token->col()){}
	void unparse(std::ostream& out, int indent);
};

class UnaryExpNode : public ExpNode{
public:
	UnaryExpNode(ExpNode* exp) : ExpNode(exp->line(), exp->col()){}
};

class AssignStmtNode : public StmtNode{
public:
	AssignStmtNode(AssignExpNode* assignment) : StmtNode(assignment->line(), assignment->col()), myAssign(assignment){}
	virtual void unparse(std::ostream& out, int indent) override;
private:
	AssignExpNode* myAssign;
};

class CallStmtNode : public StmtNode{
public:
	CallStmtNode(CallExpNode* call) : StmtNode(call->line(), call->col()), myCall(call){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	CallExpNode* myCall;
};

class DeclNode : public StmtNode{
public:
	DeclNode(size_t l, size_t c) : StmtNode(l, c) {}
	virtual void unparse(std::ostream& out, int indent) = 0;
};

class IfElseStmtNode : public StmtNode{
public:
	IfElseStmtNode(ExpNode* exp, std::list<StmtNode*>* trueList, std::list<StmtNode*>* falseList) : StmtNode(exp->line(), exp->col()),
		myExp(exp), myTList(trueList), myFList(falseList){}
	virtual void unparse(std::ostream& out, int indent) override;
private:
	ExpNode* myExp;
	std::list<StmtNode*>* myTList;
	std::list<StmtNode*>* myFList;
};

class IfStmtNode : public StmtNode{
public:
	IfStmtNode(ExpNode* exp, std::list<StmtNode*>* stmtList) : StmtNode(exp->line(), exp->col()), myExp(exp), myStmtList(stmtList){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myExp;
	std::list<StmtNode*>* myStmtList;
};

class PostDecStmtNode : public StmtNode{
public:
	PostDecStmtNode(ExpNode* decId) : StmtNode(decId->line(), decId->col()), myExp(decId){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myExp;
};

class PostIncStmtNode : public StmtNode{
public:
	PostIncStmtNode(ExpNode* incId) : StmtNode(incId->line(), incId->col()), myExp(incId){}
	virtual void unparse(std::ostream& out, int indent) override;
private:
	ExpNode* myExp;
};

class ReturnStmtNode : public StmtNode{
public:
	ReturnStmtNode(ExpNode* returnId, bool emptyIn) : StmtNode(returnId->line(), returnId->col()), myExp(returnId), empty(emptyIn){}
	ReturnStmtNode(size_t l, size_t c, bool emptyIn) : StmtNode(l, c), empty(emptyIn){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myExp;
	bool empty;
};

class WhileStmtNode : public StmtNode{
public:
	WhileStmtNode(ExpNode* condition, std::list<StmtNode*>* body) : StmtNode(condition->line(), condition->col()), myExp(condition), myStmtList(body){}
	virtual void unparse(std::ostream& out, int indent) override;
private:
	ExpNode* myExp;
	std::list<StmtNode*>* myStmtList;
};

class BoolTypeNode : public TypeNode{
public:
	BoolTypeNode(size_t l, size_t c) : TypeNode(l, c){}
	void unparse(std::ostream& out, int indent);
};

class FileTypeNode : public TypeNode{
public:
	FileTypeNode(size_t l, size_t c) : TypeNode(l, c){}
	void unparse(std::ostream& out, int indent);
};

class ArrayTypeNode : public TypeNode{
public:
	ArrayTypeNode(size_t l, size_t c) : TypeNode(l, c){}
	void unparse(std::ostream& out, int indent);
};

class IntTypeNode : public TypeNode{
public:
	IntTypeNode(size_t l, size_t c): TypeNode(l, c){}
	void unparse(std::ostream& out, int indent);
};

class VoidTypeNode : public TypeNode{
public:
	VoidTypeNode(size_t l, size_t c) : TypeNode(l, c){}
	void unparse(std::ostream& out, int indent);
};

class AndNode : public BinaryExpNode{
public: 
	AndNode(ExpNode* lhs, ExpNode* rhs) : BinaryExpNode(lhs, rhs), myLhs(lhs), myRhs(rhs){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myLhs;
	ExpNode* myRhs;
};

class DivideNode : public BinaryExpNode{
public: 
	DivideNode(ExpNode* lhs, ExpNode* rhs) : BinaryExpNode(lhs, rhs), myLhs(lhs), myRhs(rhs){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myLhs;
	ExpNode* myRhs;
};

class EqualsNode : public BinaryExpNode{
public: 
	EqualsNode(ExpNode* lhs, ExpNode* rhs) : BinaryExpNode(lhs, rhs), myLhs(lhs), myRhs(rhs){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myLhs;
	ExpNode* myRhs;
};

class GreaterEqNode : public BinaryExpNode{
public: 
	GreaterEqNode(ExpNode* lhs, ExpNode* rhs) : BinaryExpNode(lhs, rhs), myLhs(lhs), myRhs(rhs){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myLhs;
	ExpNode* myRhs;
};

class GreaterNode : public BinaryExpNode{
public: 
	GreaterNode(ExpNode* lhs, ExpNode* rhs) : BinaryExpNode(lhs, rhs), myLhs(lhs), myRhs(rhs){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myLhs;
	ExpNode* myRhs;
};

class LessEqNode : public BinaryExpNode{
public: 
	LessEqNode(ExpNode* lhs, ExpNode* rhs) : BinaryExpNode(lhs, rhs), myLhs(lhs), myRhs(rhs){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myLhs;
	ExpNode* myRhs;
};

class LessNode : public BinaryExpNode{
public: 
	LessNode(ExpNode* lhs, ExpNode* rhs) : BinaryExpNode(lhs, rhs), myLhs(lhs), myRhs(rhs){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myLhs;
	ExpNode* myRhs;
};

class MinusNode : public BinaryExpNode{
public: 
	MinusNode(ExpNode* lhs, ExpNode* rhs) : BinaryExpNode(lhs, rhs), myLhs(lhs), myRhs(rhs){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myLhs;
	ExpNode* myRhs;
};

class NotEqualsNode : public BinaryExpNode{
public: 
	NotEqualsNode(ExpNode* lhs, ExpNode* rhs) : BinaryExpNode(lhs, rhs), myLhs(lhs), myRhs(rhs){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myLhs;
	ExpNode* myRhs;
};

class OrNode : public BinaryExpNode{
public: 
	OrNode(ExpNode* lhs, ExpNode* rhs) : BinaryExpNode(lhs, rhs), myLhs(lhs), myRhs(rhs){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myLhs;
	ExpNode* myRhs;
};

class PlusNode : public BinaryExpNode{
public: 
	PlusNode(ExpNode* lhs, ExpNode* rhs) : BinaryExpNode(lhs, rhs), myLhs(lhs), myRhs(rhs){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myLhs;
	ExpNode* myRhs;
};

class TimesNode : public BinaryExpNode{
public: 
	TimesNode(ExpNode* lhs, ExpNode* rhs) : BinaryExpNode(lhs, rhs), myLhs(lhs), myRhs(rhs){}
	virtual void unparse(std::ostream& out, int indent) override;

private:
	ExpNode* myLhs;
	ExpNode* myRhs;
};

class IndexNode : public LocNode{
public:
	IndexNode(IDNode* accessId, ExpNode* offset) : LocNode(accessId), myId(accessId), myExp(offset){}
	void unparse(std::ostream& out, int indent);

private:
	IDNode* myId;
	ExpNode* myExp;
};

class NegNode : public UnaryExpNode{
public:
	NegNode(ExpNode* exp) : UnaryExpNode(exp), myExp(exp){}
	void unparse(std::ostream& out, int indent);

private:
	ExpNode* myExp;
};

class NotNode : public UnaryExpNode{
public:
	NotNode(ExpNode* exp) : UnaryExpNode(exp), myExp(exp){}
	void unparse(std::ostream& out, int indent);

private:
	ExpNode* myExp;
};

class FnDeclNode : public DeclNode{
public:
	FnDeclNode(TypeNode* type, IDNode* id, std::list<FormalDeclNode*>* formals, std::list<StmtNode*>* body):
	DeclNode(type->line(), type->col()), myType(type), myId(id), myFormals(formals), myBody(body){}
	void unparse(std::ostream& out, int indent);

private:
	TypeNode* myType;
	IDNode* myId;
	std::list<FormalDeclNode*>* myFormals;
	std::list<StmtNode*>* myBody;
};

/** A variable declaration.
**/
class VarDeclNode : public DeclNode{
public:
	VarDeclNode(size_t l, size_t c, TypeNode * type, IDNode * id) : DeclNode(type->line(), type->col()), myType(type), myId(id){}
	void unparse(std::ostream& out, int indent);
private:
	TypeNode * myType;
	IDNode * myId;
};

class FormalDeclNode : public DeclNode{
public:
	FormalDeclNode(TypeNode* type, IDNode* id) : DeclNode(type->line(), type->col()), myType(type), myId(id){}
	void unparse(std::ostream& out, int indent);

private:
	TypeNode * myType;
	IDNode * myId;
};

} //End namespace jeff

#endif
