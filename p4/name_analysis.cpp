#include "ast.hpp"
#include "symbol_table.hpp"
#include "errors.hpp"

namespace jeff{

//TODO here is a subset of the nodes needed to do nameAnalysis, 
// you should add the rest to allow for a complete treatment
// of any AST

bool ASTNode::nameAnalysis(SymbolTable * symTab){
	throw new ToDoError("This function should have"
		"been overriden in the subclass!");
}

bool ProgramNode::nameAnalysis(SymbolTable * symTab){
	ScopeTable * mainScope = new ScopeTable();
	symTab->addScope(mainScope);
	bool res = true;
	for (auto global : *myGlobals){
		res = global->nameAnalysis(symTab) && res;
	}
	return res;
}

bool VarDeclNode::nameAnalysis(SymbolTable *symTab) {
	bool nameAnalysisOk = true;
	if( (symTab->isInCurrentScopeAlready(this->ID())) && (!symTab->isCorrectType(this->getTypeNode()))) 
	{ 
		Report myReport;
		myReport.fatal(this->ID()->line(), this->ID()->col(), "Bad declaration type");
		myReport.fatal(this->ID()->line(), this->ID()->col(), "More than 1 declaration of an id in a scope");
		nameAnalysisOk = false;
	}
	else if(symTab->isInCurrentScopeAlready(this->ID()))
	{ 
		Report myReport;
		myReport.fatal(this->ID()->line(), this->ID()->col(), "More than 1 declaration of an id in a scope");
		nameAnalysisOk = false;
	}
	else if(!symTab->isCorrectType(this->getTypeNode())) 
	{
		Report myReport;
		myReport.fatal(this->ID()->line(), this->ID()->col(), "Bad declaration type");
		nameAnalysisOk = false;
	}
	else
	{
		SemSymbol *s = new SemSymbol('v', this);
		symTab->currentScope()->addSymbol(this->ID()->getName(),s);
		nameAnalysisOk = true;
	}
	return nameAnalysisOk;
}

bool FnDeclNode::nameAnalysis(SymbolTable *symTab){
	bool nameAnalysisOk = true;
	if (symTab->isInCurrentScopeAlready(this->ID())) 
	{ 
		Report myReport;
		myReport.fatal(this->ID()->line(), this->ID()->col(), "More than 1 declaration of an id in a scope");
		nameAnalysisOk = false;
		for (auto formals : *myFormals)
		{
			nameAnalysisOk = formals->nameAnalysis(symTab);
		}	
		ScopeTable *newScope = new ScopeTable();
		symTab->addScope(newScope);
		for (auto body : *myBody)
		{
			nameAnalysisOk = body->nameAnalysis(symTab);
		}
	}
	else 
	{ 
		SemSymbol *s = new SemSymbol('f', this);
		symTab->currentScope()->addSymbol(this->ID()->getName(), s);
		nameAnalysisOk = true;
		for (auto formals : *myFormals)
		{
			nameAnalysisOk = formals->nameAnalysis(symTab);
		}
		ScopeTable *newScope = new ScopeTable();
		symTab->addScope(newScope);
		for (auto body : *myBody)
		{
			nameAnalysisOk = body->nameAnalysis(symTab);
		}
	}
	symTab->dropScope();
	return nameAnalysisOk;
}

bool IDNode::nameAnalysis(SymbolTable *symTab) { 
	if(symTab->lookUp(this)) 
	{
		return true;
	}
	else 
	{
		Report myReport;
		myReport.fatal(line(), col(), "Use of an undeclared id");
		return false;
	}
}


bool IndexNode::nameAnalysis(SymbolTable *symTab)
{
	if ((id->nameAnalysis(symTab)) && (exp->nameAnalysis(symTab)))
	{
		return true;
	}
	else
	{
		return false;
	}
}



bool WhileStmtNode::nameAnalysis(SymbolTable *symTab) 
{
	bool one, two;
	one = this->myCond->nameAnalysis(symTab);
	ScopeTable *scope = new ScopeTable();
	symTab->addScope(scope);
	for (auto body : *myBody)
	{
		two = body->nameAnalysis(symTab);
	}
	symTab->dropScope();
	return (one && two);
}

bool ReturnStmtNode::nameAnalysis(SymbolTable *symTab) {
	bool nameAnalysisIsOk = false;
	nameAnalysisIsOk = this->myExp->nameAnalysis(symTab);
	return nameAnalysisIsOk;
}

bool CallExpNode::nameAnalysis(SymbolTable *symTab) {
	bool nameAnalysisIsOk = false;
	bool one,two;
	one = this->myID->nameAnalysis(symTab);
	for(auto args : *myArgs) {
		two = args->nameAnalysis(symTab);
	}
	return (one && two);
}

bool PlusNode::nameAnalysis(SymbolTable *symTab) {
	bool one,two;
	one = this->myExp1->nameAnalysis(symTab);
	two = this->myExp2->nameAnalysis(symTab);
	return (one && two);
}

bool MinusNode::nameAnalysis(SymbolTable *symTab)
{
	bool one, two;
	one = this->myExp1->nameAnalysis(symTab);
	two = this->myExp2->nameAnalysis(symTab);
	return (one && two);
}

bool TimesNode::nameAnalysis(SymbolTable *symTab)
{
	bool one, two;
	one = this->myExp1->nameAnalysis(symTab);
	two = this->myExp2->nameAnalysis(symTab);
	return (one && two);
}

bool DivideNode::nameAnalysis(SymbolTable *symTab)
{
	bool one, two;
	one = this->myExp1->nameAnalysis(symTab);
	two = this->myExp2->nameAnalysis(symTab);
	return (one && two);
}

bool AndNode::nameAnalysis(SymbolTable *symTab)
{
	bool one, two;
	one = this->myExp1->nameAnalysis(symTab);
	two = this->myExp2->nameAnalysis(symTab);
	return (one && two);
}

bool OrNode::nameAnalysis(SymbolTable *symTab) {
	bool one, two;
	one = this->myExp1->nameAnalysis(symTab);
	two = this->myExp2->nameAnalysis(symTab);
	return (one && two);
}

bool EqualsNode::nameAnalysis(SymbolTable *symTab)
{
	bool one, two;
	one = this->myExp1->nameAnalysis(symTab);
	two = this->myExp2->nameAnalysis(symTab);
	return (one && two);
}

bool NotEqualsNode::nameAnalysis(SymbolTable *symTab)
{
	bool one, two;
	one = this->myExp1->nameAnalysis(symTab);
	two = this->myExp2->nameAnalysis(symTab);
	return (one && two);
}

bool LessNode::nameAnalysis(SymbolTable *symTab)
{
	bool one, two;
	one = this->myExp1->nameAnalysis(symTab);
	two = this->myExp2->nameAnalysis(symTab);
	return (one && two);
}

bool LessEqNode::nameAnalysis(SymbolTable *symTab)
{
	bool one,two;
	one = this->myExp1->nameAnalysis(symTab);
	two = this->myExp2->nameAnalysis(symTab);
	return (one && two);
}

bool GreaterNode::nameAnalysis(SymbolTable* symTab)
{
	bool one, two;
	one = this->myExp1->nameAnalysis(symTab);
	two = this->myExp2->nameAnalysis(symTab);
	return (one && two);
}

bool GreaterEqNode::nameAnalysis(SymbolTable *symTab)
{
	bool one, two;
	one = this->myExp1->nameAnalysis(symTab);
	two = this->myExp2->nameAnalysis(symTab);
	return (one && two);
}

bool NegNode::nameAnalysis(SymbolTable * symTab)
{
	bool one;
	one = this->myExp->nameAnalysis(symTab);
	return (one);
}

bool NotNode::nameAnalysis(SymbolTable * symTab)
{
	bool one;
	one = this->myExp->nameAnalysis(symTab);
	return (one);
}

bool IntTypeNode::nameAnalysis(SymbolTable * symTab)
{
	// Name analysis may never even recurse down to IntTypeNode,
	// but if it does, just return true to indicate that 
	// name analysis has not failed, and add nothing to the symbol table
	return true;
}

bool VoidTypeNode::nameAnalysis(SymbolTable * symTab) 
{
	return true;
}

bool BoolTypeNode::nameAnalysis(SymbolTable * symTab)
{
	return true;
}

bool FileTypeNode::nameAnalysis(SymbolTable * symTab) 
{
	return true;
}

bool ArrayTypeNode::nameAnalysis(SymbolTable * symTab) 
{
	return true;
}

bool CallStmtNode::nameAnalysis(SymbolTable * symTab) 
{ 
	bool one;
	one = this->myCallExp->nameAnalysis(symTab);
	return one;
}

bool IfStmtNode::nameAnalysis(SymbolTable *symTab) 
{
	bool nameAnalysisIsOk = false;
	nameAnalysisIsOk = this->myCond->nameAnalysis(symTab);
	ScopeTable *scope = new ScopeTable();
	symTab->addScope(scope);
	for (auto body : *myBody)
	{
		nameAnalysisIsOk = body->nameAnalysis(symTab);
	}
	symTab->dropScope();
	return nameAnalysisIsOk;	
}

bool AssignExpNode::nameAnalysis(SymbolTable *symTab)
{
	bool one,two;
	one = this->myDst->nameAnalysis(symTab);
	two = this->mySrc->nameAnalysis(symTab);
	return (one && two);
}

bool IfElseStmtNode::nameAnalysis(SymbolTable *symTab) 
{
	bool one, two, three;
	one = myCond->nameAnalysis(symTab);
	ScopeTable *scope = new ScopeTable();
	symTab->addScope(scope);
	for(auto btrue : *myBodyTrue) 
	{
		two = btrue->nameAnalysis(symTab);
	}
	for(auto bfalse : * myBodyFalse) 
	{
		three = bfalse->nameAnalysis(symTab);
	}
	symTab->dropScope();
	return (one && two && three);
}

bool PostDecStmtNode::nameAnalysis(SymbolTable *symTab) 
{
	return myLoc->nameAnalysis(symTab);
}

bool PostIncStmtNode::nameAnalysis(SymbolTable *symTab)
{
	return myLoc->nameAnalysis(symTab);
}

bool AssignStmtNode::nameAnalysis(SymbolTable *symTab) 
{
	return myExp->nameAnalysis(symTab);
}

bool FormalDeclNode::nameAnalysis(SymbolTable *symTab) 
{
	bool nameAnalysisOk = false;
	if ((symTab->isInCurrentScopeAlready(this->ID())) && (!symTab->isCorrectType(this->getTypeNode())))
	{ 
		Report myReport;
		myReport.fatal(this->ID()->line(), this->ID()->col(), "Bad declaration type");
		myReport.fatal(this->ID()->line(), this->ID()->col(), "More than 1 declaration of an id in a scope");
		nameAnalysisOk = false;
	}
	else if (symTab->isInCurrentScopeAlready(this->ID())) { 
		Report myReport;
		myReport.fatal(this->ID()->line(), this->ID()->col(), "More than 1 declaration of an id in a scope");
		nameAnalysisOk = false;
	}
	else if (!symTab->isCorrectType(this->getTypeNode())) {
		Report myReport;
		myReport.fatal(this->ID()->line(), this->ID()->col(), "Bad declaration type");
		nameAnalysisOk = false;
	}
	else {
		SemSymbol *s = new SemSymbol('v', this);
		symTab->currentScope()->addSymbol(this->ID()->getName(), s);
		nameAnalysisOk = true;
	}
	return nameAnalysisOk;
}

}

