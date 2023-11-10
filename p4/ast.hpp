#ifndef JEFF_AST_HPP
#define JEFF_AST_HPP

#include <ostream>
#include <sstream>
#include <string.h>
#include <list>
#include "tokens.hpp"

namespace jeff {

class NameAnalysis;

class SymbolTable;
class SemSymbol;

class DeclNode;
class VarDeclNode;
class StmtNode;
class AssignExpNode;
class FormalDeclNode;
class TypeNode;
class StructTypeNode;
class ExpNode;
class LocNode;
class IDNode;

class ASTNode{
public:
	ASTNode(size_t lineIn, size_t colIn) : l(lineIn), c(colIn){ }
	virtual void unparse(std::ostream&, int) = 0;
	size_t line() { return l; }
	size_t col() { return c; }
	std::string pos(){ return "[" + std::to_string(line()) + "," + std::to_string(col()) + "]";}
	virtual bool nameAnalysis(SymbolTable *);
protected:
	size_t l;
	size_t c;
};

class ProgramNode : public ASTNode{
public:
	ProgramNode(std::list<DeclNode *> * globalsIn)
	: ASTNode(1,1), myGlobals(globalsIn){}
	void unparse(std::ostream&, int) override;
	virtual bool nameAnalysis(SymbolTable *) override;
private:
	std::list<DeclNode *> * myGlobals;
};

class ExpNode : public ASTNode{
public:
	ExpNode(size_t lIn, size_t cIn) : ASTNode(lIn, cIn){ }
	virtual void unparseNested(std::ostream& out);
	virtual void unparse(std::ostream& out, int indent) override = 0;
	virtual bool nameAnalysis(SymbolTable * symTab) override = 0;
};

class LocNode : public ExpNode{
public:
	LocNode(size_t lIn, size_t cIn) : ExpNode(lIn, cIn){}
	void unparse(std::ostream& out, int indent) override = 0;
	void unparseNested(std::ostream& out) override;
	bool nameAnalysis(SymbolTable * symTab) override = 0;
};

class IDNode : public LocNode{
public:
	IDNode(size_t lIn, size_t cIn, std::string nameIn)
	: LocNode(lIn, cIn), name(nameIn), mySymbol(nullptr){}
	std::string getName(){ return name; }
	SemSymbol* getSym() {return mySymbol; }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
private:
	std::string name;
	SemSymbol* mySymbol;
};

class IndexNode : public LocNode{ 
public:
	IndexNode(size_t l, size_t c, IDNode * idIn, ExpNode * expIn)
	: LocNode(l, c), id(idIn), exp(expIn){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
private:
	IDNode * id;
	ExpNode * exp;
};


class TypeNode : public ASTNode{
public:
	TypeNode(size_t l, size_t c) : ASTNode(l, c){ }
	void unparse(std::ostream&, int) override = 0;
	virtual bool nameAnalysis(SymbolTable * symTab) override = 0;
	virtual std::string getType() = 0; 
};

class StmtNode : public ASTNode{
public:
	StmtNode(size_t lIn, size_t cIn) : ASTNode(lIn, cIn){ }
	virtual void unparse(std::ostream& out, int indent) override = 0;
	virtual bool nameAnalysis(SymbolTable * symTab) override = 0;
};

class DeclNode : public StmtNode{
public:
	DeclNode(size_t l, size_t c) : StmtNode(l, c){ }
	void unparse(std::ostream& out, int indent) override = 0;
	virtual bool nameAnalysis(SymbolTable *symTab) override = 0; 
	virtual TypeNode* getTypeNode() = 0;		
	virtual IDNode* ID() = 0;
	virtual std::list<FormalDeclNode *> * getFormals() = 0; 
};

class VarDeclNode : public DeclNode{
public:
	VarDeclNode(size_t lIn, size_t cIn, TypeNode * typeIn, IDNode * IDIn)
	: DeclNode(lIn, cIn), myType(typeIn), myID(IDIn){ }
	void unparse(std::ostream& out, int indent) override;
	IDNode *ID() override { return myID; }
	TypeNode * getTypeNode() override { return myType; }
	virtual bool nameAnalysis(SymbolTable *) override;
	std::list<FormalDeclNode *> * getFormals() override {
		return myFormals;
	}
private:
	TypeNode * myType;
	IDNode * myID;
	std::list<FormalDeclNode *> * myFormals;
};

class FormalDeclNode : public VarDeclNode{
public:
	FormalDeclNode(size_t lIn, size_t cIn, TypeNode * type, IDNode * id) 
	: VarDeclNode(lIn, cIn, type, id){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
};

class FnDeclNode : public DeclNode{
public:
	FnDeclNode(size_t lIn, size_t cIn, 
	  TypeNode * retTypeIn, IDNode * idIn,
	  std::list<FormalDeclNode *> * formalsIn,
	  std::list<StmtNode *> * bodyIn)
	: DeclNode(lIn, cIn), 
	  myID(idIn), myRetType(retTypeIn),
	  myFormals(formalsIn), myBody(bodyIn){ }
	IDNode * ID() override { return myID; }
	TypeNode * getTypeNode() override { return myRetType; }
	std::list<FormalDeclNode *> * getFormals() override {
		return myFormals;
	}
	void unparse(std::ostream& out, int indent) override;
	virtual bool nameAnalysis(SymbolTable *) override;
private:
	IDNode * myID;
	TypeNode * myRetType;
	std::list<FormalDeclNode *> * myFormals;
	std::list<StmtNode *> * myBody;
};

class AssignStmtNode : public StmtNode{
public:
	AssignStmtNode(size_t l, size_t c, AssignExpNode * expIn)
	: StmtNode(l, c), myExp(expIn){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
private:
	AssignExpNode * myExp;
};

class PostDecStmtNode : public StmtNode{
public:
	PostDecStmtNode(size_t l, size_t c, LocNode * locIn)
	: StmtNode(l, c), myLoc(locIn){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
private:
	LocNode * myLoc;
};

class PostIncStmtNode : public StmtNode{
public:
	PostIncStmtNode(size_t l, size_t c, LocNode * locIn)
	: StmtNode(l, c), myLoc(locIn){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
private:
	LocNode * myLoc;
};

class IfStmtNode : public StmtNode{
public:
	IfStmtNode(size_t l, size_t c, ExpNode * condIn,
	  std::list<StmtNode *> * bodyIn)
	: StmtNode(l, c), myCond(condIn), myBody(bodyIn){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
private:
	ExpNode * myCond;
	std::list<StmtNode *> * myBody;
};

class IfElseStmtNode : public StmtNode{
public:
	IfElseStmtNode(size_t l, size_t c, ExpNode * condIn, 
	  std::list<StmtNode *> * bodyTrueIn,
	  std::list<StmtNode *> * bodyFalseIn)
	: StmtNode(l, c), myCond(condIn),
	  myBodyTrue(bodyTrueIn), myBodyFalse(bodyFalseIn) { }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
private:
	ExpNode * myCond;
	std::list<StmtNode *> * myBodyTrue;
	std::list<StmtNode *> * myBodyFalse;
};

class WhileStmtNode : public StmtNode{
public:
	WhileStmtNode(size_t l, size_t c, ExpNode * condIn, 
	  std::list<StmtNode *> * bodyIn)
	: StmtNode(l, c), myCond(condIn), myBody(bodyIn){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
private:
	ExpNode * myCond;
	std::list<StmtNode *> * myBody;
};

class ReturnStmtNode : public StmtNode{
public:
	ReturnStmtNode(size_t l, size_t c, ExpNode * exp)
	: StmtNode(l, c), myExp(exp){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
private:
	ExpNode * myExp;
};

class CallExpNode : public ExpNode{
public:
	CallExpNode(size_t l, size_t c, IDNode * id,
	  std::list<ExpNode *> * argsIn)
	: ExpNode(l, c), myID(id), myArgs(argsIn){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
private:
	IDNode * myID;
	std::list<ExpNode *> * myArgs;
};

class BinaryExpNode : public ExpNode{
public:
	BinaryExpNode(size_t lIn, size_t cIn, ExpNode * lhs, ExpNode * rhs)
	: ExpNode(lIn, cIn), myExp1(lhs), myExp2(rhs) { }
	virtual bool nameAnalysis(SymbolTable * symTab) override = 0;
protected:
	ExpNode * myExp1;
	ExpNode * myExp2;
};

class PlusNode : public BinaryExpNode{
public:
	PlusNode(size_t l, size_t c, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(l, c, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
};

class MinusNode : public BinaryExpNode{
public:
	MinusNode(size_t l, size_t c, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(l, c, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
};

class TimesNode : public BinaryExpNode{
public:
	TimesNode(size_t l, size_t c, ExpNode * e1In, ExpNode * e2In)
	: BinaryExpNode(l, c, e1In, e2In){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
};

class DivideNode : public BinaryExpNode{
public:
	DivideNode(size_t lIn, size_t cIn, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(lIn, cIn, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
};

class AndNode : public BinaryExpNode{
public:
	AndNode(size_t l, size_t c, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(l, c, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
};

class OrNode : public BinaryExpNode{
public:
	OrNode(size_t l, size_t c, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(l, c, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
};

class EqualsNode : public BinaryExpNode{
public:
	EqualsNode(size_t l, size_t c, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(l, c, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
};

class NotEqualsNode : public BinaryExpNode{
public:
	NotEqualsNode(size_t l, size_t c, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(l, c, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
};

class LessNode : public BinaryExpNode{
public:
	LessNode(size_t lineIn, size_t colIn, 
		ExpNode * exp1, ExpNode * exp2)
	: BinaryExpNode(lineIn, colIn, exp1, exp2){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
};

class LessEqNode : public BinaryExpNode{
public:
	LessEqNode(size_t l, size_t c, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(l, c, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
};

class GreaterNode : public BinaryExpNode{
public:
	GreaterNode(size_t lineIn, size_t colIn, 
		ExpNode * exp1, ExpNode * exp2)
	: BinaryExpNode(lineIn, colIn, exp1, exp2){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
};

class GreaterEqNode : public BinaryExpNode{
public:
	GreaterEqNode(size_t l, size_t c, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(l, c, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
};

class UnaryExpNode : public ExpNode {
public:
	UnaryExpNode(size_t lIn, size_t cIn, ExpNode * expIn) 
	: ExpNode(lIn, cIn){
		this->myExp = expIn;
	}
	virtual void unparse(std::ostream& out, int indent) override = 0;
	virtual bool nameAnalysis(SymbolTable * symTab) override = 0;
protected:
	ExpNode * myExp;
};

class NegNode : public UnaryExpNode{
public:
	NegNode(size_t l, size_t c, ExpNode * exp)
	: UnaryExpNode(l, c, exp){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
};

class NotNode : public UnaryExpNode{
public:
	NotNode(size_t lIn, size_t cIn, ExpNode * exp)
	: UnaryExpNode(lIn, cIn, exp){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
};

class FileTypeNode : public TypeNode{
public:
	FileTypeNode(size_t l, size_t c) : TypeNode(l, c){}
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	std::string getType() override {
		return "file";
	}
};

class VoidTypeNode : public TypeNode{
public:
	VoidTypeNode(size_t l, size_t c) : TypeNode(l, c){}
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	std::string getType() override {
		return "void";
	}
};

class IntTypeNode : public TypeNode{
public:
	IntTypeNode(size_t l, size_t c): TypeNode(l, c){}
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	std::string getType() override {
		return "int";
	}
};

class BoolTypeNode : public TypeNode{
public:
	BoolTypeNode(size_t l, size_t c): TypeNode(l, c){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	std::string getType() override {
		return "bool";
	}
};

class ArrayTypeNode : public TypeNode{
public:
	ArrayTypeNode(size_t l, size_t c, TypeNode * base, size_t len): TypeNode(l, c), myLen(len), myBase(base){}
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	std::string getType() override {
		return "array";
	}
private:
	size_t myLen;
	TypeNode * myBase;
};

class AssignExpNode : public ExpNode{
public:
	AssignExpNode(size_t l, size_t c, LocNode * dstIn, ExpNode * srcIn)
	: ExpNode(l, c), myDst(dstIn), mySrc(srcIn){ }
	void unparse(std::ostream& out, int indent) override;
	virtual bool nameAnalysis(SymbolTable * symTab) override;
	LocNode* getDST() { return myDst; }
	ExpNode * getSRC() { return mySrc; }
private:
	LocNode * myDst;
	ExpNode * mySrc;
};

class IntLitNode : public ExpNode{
public:
	IntLitNode(size_t l, size_t c, const int numIn)
	: ExpNode(l, c), myNum(numIn){ }
	virtual void unparseNested(std::ostream& out) override{
		unparse(out, 0);
	}
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override { return true; }
private:
	const int myNum;
};

class StrLitNode : public ExpNode{
public:
	StrLitNode(size_t l, size_t c, const std::string strIn)
	: ExpNode(l, c), myStr(strIn){ }
	virtual void unparseNested(std::ostream& out) override{
		unparse(out, 0);
	}
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable *) override { return true; }
private:
	 const std::string myStr;
};


class TrueNode : public ExpNode{
public:
	TrueNode(size_t l, size_t c): ExpNode(l, c){ }
	virtual void unparseNested(std::ostream& out) override{
		unparse(out, 0);
	}
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable *symTab) override { return true; }
};

class FalseNode : public ExpNode{
public:
	FalseNode(size_t l, size_t c): ExpNode(l, c){ }
	virtual void unparseNested(std::ostream& out) override{
		unparse(out, 0);
	}
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable *symTab) override { return true; }
};

class CallStmtNode : public StmtNode{
public:
	CallStmtNode(size_t l, size_t c, CallExpNode * expIn)
	: StmtNode(l, c), myCallExp(expIn){};
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
private:
	CallExpNode * myCallExp;
};

} //End namespace jeffc

#endif

