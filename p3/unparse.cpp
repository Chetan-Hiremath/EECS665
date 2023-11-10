#include "ast.hpp"

namespace jeff{

/*
doIndent is declared static, which means that it can 
only be called in this file (its symbol is not exported).
*/
static void doIndent(std::ostream& out, int indent){
	for (int k = 0 ; k < indent; k++){ out << "\t"; }
}

/*
In this code, the intention is that functions are grouped 
into files by purpose, rather than by class.
If you're used to having all of the functions of a class 
defined in the same file, this style may be a bit disorienting,
though it is legal. Thus, we can have
ProgramNode::unparse, which is the unparse method of ProgramNodes
defined in the same file as DeclNode::unparse, the unparse method
of DeclNodes.
*/


void ProgramNode::unparse(std::ostream& out, int indent){
	/* Oh, hey it's a for-each loop in C++!
	   The loop iterates over each element in a collection
	   without that gross i++ nonsense. 
	 */
	for (auto global : *myGlobals){
		/* The auto keyword tells the compiler
		   to (try to) figure out what the
		   type of a variable should be from 
		   context. here, since we're iterating
		   over a list of DeclNode *s, it's 
		   pretty clear that global is of 
		   type DeclNode *.
		*/
		global->unparse(out, indent);
	}
}

void VarDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myType->unparse(out, 0);
	out << " ";
	this->myId->unparse(out, 0);
	out << ";\n";
}

void IDNode::unparse(std::ostream& out, int indent){
	out << this->myStrVal;
}

void IntTypeNode::unparse(std::ostream& out, int indent){
	out << "int";
}

void BoolTypeNode::unparse(std::ostream& out, int indent){
	out << "bool";
}

void ArrayTypeNode::unparse(std::ostream& out, int indent){
	out << "array";
}

void FileTypeNode::unparse(std::ostream& out, int indent){
	out << "file";
}

void VoidTypeNode::unparse(std::ostream& out, int indent){
	out << "void";
}

void FnDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myType->unparse(out, 0);
	out << " ";
	this->myId->unparse(out, 0);
	out << "(";
	for (auto formal: *myFormals)
		formal->unparse(out, 0);
	out << ") {\n";
	for (auto line: *myBody){
		line->unparse(out, indent + 1);
	}
	out << "}\n";
}

void AssignStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myAssign->unparse(out, 0);
	out<< ";\n";
}

void PostDecStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myExp->unparse(out, 0);
	out<<"--;\n";
}

void PostIncStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myExp->unparse(out, 0);
	out<<"++;\n";
}

void IfStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out<<"if (";
	this->myExp->unparse(out, 0);
	out<<") {\n";
	for (auto stmt: *myStmtList)
		stmt->unparse(out, indent+1);
	doIndent(out, indent);
	out<<"}\n";
}

void IfElseStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out<<"if (";
	this->myExp->unparse(out, 0);
	out<<") {\n";
	for (auto stmt: *myTList)
		stmt->unparse(out, indent+1);
	doIndent(out, indent);
	out<<"} else {\n";
	for (auto stmt: *myFList)
		stmt->unparse(out, indent+1);
	doIndent(out, indent);
	out<<"}\n";
}

void WhileStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out<<"while (";
	this->myExp->unparse(out, 0);
	out<<") {\n";
	for (auto stmt: *myStmtList)
		stmt->unparse(out, indent+1);
	doIndent(out, indent);
	out<<"}\n";
}

void ReturnStmtNode::unparse(std::ostream& out, int indent){
        doIndent(out, indent);
	out<<"return";
	if(!this->empty){
		out<<" ";
		this->myExp->unparse(out, 0);
	}
	out<<";\n";
}

void CallStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myCall->unparse(out, 0);
	out<<";\n";
}

void AssignExpNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myLoc->unparse(out, 0);
	out << " = ";
	this->myExp->unparse(out, 0);
}

void MinusNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->myLhs->unparse(out, 0);
	out << " - ";
	this->myRhs->unparse(out, 0);
	out << ")";
}

void PlusNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->myLhs->unparse(out, 0);
	out << " + ";
	this->myRhs->unparse(out, 0);
	out << ")";
}

void TimesNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->myLhs->unparse(out, 0);
	out << " * ";
	this->myRhs->unparse(out, 0);
	out << ")";
}

void DivideNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->myLhs->unparse(out, 0);
	out << " / ";
	this->myRhs->unparse(out, 0);
	out << ")";
}

void AndNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->myLhs->unparse(out, 0);
	out << " && ";
	this->myRhs->unparse(out, 0);
	out << ")";
}

void OrNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->myLhs->unparse(out, 0);
	out << " || ";
	this->myRhs->unparse(out, 0);
	out << ")";
}

void EqualsNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->myLhs->unparse(out, 0);
	out << " == ";
	this->myRhs->unparse(out, 0);
	out << ")";
}

void NotEqualsNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->myLhs->unparse(out, 0);
	out << " != ";
	this->myRhs->unparse(out, 0);
	out << ")";
}

void GreaterNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->myLhs->unparse(out, 0);
	out << " > ";
	this->myRhs->unparse(out, 0);
	out << ")";
}

void GreaterEqNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->myLhs->unparse(out, 0);
	out << " >= ";
	this->myRhs->unparse(out, 0);
	out << ")";
}

void LessNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->myLhs->unparse(out, 0);
	out << " < ";
	this->myRhs->unparse(out, 0);
	out << ")";
}

void LessEqNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	this->myLhs->unparse(out, 0);
	out << " <= ";
	this->myRhs->unparse(out, 0);
	out << ")";
}

void NotNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	out << "!";
	this->myExp->unparse(out, 0);
	out << ")";
}

void NegNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "(";
	out << "-";
	this->myExp->unparse(out, 0);
	out << ")";
}

void FormalDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myType->unparse(out, 0);
	out << " ";
	this->myId->unparse(out, 0);
}

void IntLitNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << myInt;
}

void StrLitNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << myStr;
}

void TrueNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "True";	
}

void FalseNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "False";
}

void LocNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myId->unparse(out, 0);
}

void IndexNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myId->unparse(out, 0);
	out<<"[";
	this->myExp->unparse(out, 0);
	out<<"]";
}

void CallExpNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myId->unparse(out, 0);
	out << "(";
	for (auto formal : *myFormals)
		formal->unparse(out, 0);
	out << ")";
}

} // End namespace jeff
