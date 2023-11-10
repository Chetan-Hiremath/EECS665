#include "ast.hpp"

namespace jeff{

IRProgram * ProgramNode::to3AC(TypeAnalysis * ta){
	IRProgram * prog = new IRProgram(ta);
	prog->gatherGlobal(consoleSym);
	for (auto global : *myGlobals){
		global->to3AC(prog);
	}
	return prog;
}

void FnDeclNode::to3AC(IRProgram * prog){
	SemSymbol * sym = ID()->getSymbol();
	Procedure * proc = prog->makeProc(sym->getName());
	if (sym == nullptr && proc == nullptr)
	{
		throw new InternalError("null sym and proc");
	}
	proc->gatherLocal(sym);
}

void FnDeclNode::to3AC(Procedure * proc){
	//This never needs to be implemented,
	// the function only exists because of
	// inheritance needs (A function declaration
	// never occurs within another function)
	throw new InternalError("FnDecl at a local scope");
}

void FormalDeclNode::to3AC(IRProgram * prog){
	//This never needs to be implemented,
	// the function only exists because of
	// inheritance needs (A formal never
	// occurs at global scope)
	throw new InternalError("Formal at a global scope");
}

void FormalDeclNode::to3AC(Procedure * proc){
	SemSymbol * sym = ID()->getSymbol();
	if (sym == nullptr)
	{
		throw new InternalError("null sym");
	}
	proc->gatherFormal(sym);
}

Opd * IntLitNode::flatten(Procedure * proc){
	const DataType * type = proc->getProg()->nodeType(this);
	return new LitOpd(std::to_string(myNum), 8);
}

Opd * StrLitNode::flatten(Procedure * proc){
	Opd * res = proc->getProg()->makeString(myStr);
	return res;
}

Opd * TernaryExpNode::flatten(Procedure * proc){
	Label * elseLabel = proc->makeLabel();
	Quad * elseNop = new NopQuad();
	elseNop->addLabel(elseLabel);
	Label * afterLabel = proc->makeLabel();
	Quad * afterNop = new NopQuad();
	afterNop->addLabel(afterLabel);
	Opd * res = cond->flatten(proc);
	Quad * jmpFalse = new IfzQuad(res, elseLabel);
	proc->addQuad(jmpFalse);	
	Quad * skipStmt = new IfzQuad(res, afterLabel);
	proc->addQuad(skipStmt);
	proc->addQuad(elseNop);
	proc->addQuad(afterNop);
	return res;
}

Opd * TrueNode::flatten(Procedure * proc){
	return new LitOpd("1", 8);
}

Opd * FalseNode::flatten(Procedure * proc){
	return new LitOpd("0", 8);
}

Opd * CallExpNode::flatten(Procedure * proc){
	Quad * callQuad = new CallQuad(myID->getSymbol());
	proc->addQuad(callQuad);
	SemSymbol * idSym = myID->getSymbol();
	Opd * res = proc->makeTmp(8);
	Quad * getRet = new GetRetQuad(res);
	proc->addQuad(getRet);
	return res;
}

Opd * NegNode::flatten(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * lhsType = prog->nodeType(myExp);
	lhsType->isInt();
	AuxOpd * res = proc->makeTmp(8);
	Opd * lhsOpd = myExp->flatten(proc);
	Quad * q = new UnaryOpQuad(res, UnaryOp::NEG64, lhsOpd);
	proc->addQuad(q);
	return res;
}

Opd * NotNode::flatten(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * lhsType = prog->nodeType(myExp);
	lhsType->isBool();
	AuxOpd * res = proc->makeTmp(8);
	Opd * lhsOpd = myExp->flatten(proc);
	Quad * q = new UnaryOpQuad(res, UnaryOp::NOT64, lhsOpd);
	proc->addQuad(q);
	return res;
}

Opd * IndexNode::flatten(Procedure * proc){
	Opd * res = id->flatten(proc);
	return res;
}

Opd * PlusNode::flatten(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * lhsType = prog->nodeType(myExp1);
	lhsType->isInt();
	const DataType * rhsType = prog->nodeType(myExp2);
	rhsType->isInt();
	AuxOpd * res = proc->makeTmp(8);
	Opd * lhsOpd = myExp1->flatten(proc);
	Opd * rhsOpd = myExp2->flatten(proc);
	Quad * q = new BinOpQuad(res, BinOp::ADD64, lhsOpd, rhsOpd);
	proc->addQuad(q);
	return res;
}

Opd * MinusNode::flatten(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * lhsType = prog->nodeType(myExp1);
	lhsType->isInt();
	const DataType * rhsType = prog->nodeType(myExp2);
	rhsType->isInt();
	AuxOpd * res = proc->makeTmp(8);
	Opd * lhsOpd = myExp1->flatten(proc);
	Opd * rhsOpd = myExp2->flatten(proc);
	Quad * q = new BinOpQuad(res, BinOp::SUB64, lhsOpd, rhsOpd);
	proc->addQuad(q);
	return res;
}

Opd * TimesNode::flatten(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * lhsType = prog->nodeType(myExp1);
	lhsType->isInt();
	const DataType * rhsType = prog->nodeType(myExp2);
	rhsType->isInt();
	AuxOpd * res = proc->makeTmp(8);
	Opd * lhsOpd = myExp1->flatten(proc);
	Opd * rhsOpd = myExp2->flatten(proc);
	Quad * q = new BinOpQuad(res, BinOp::MULT64, lhsOpd, rhsOpd);
	proc->addQuad(q);
	return res;
}

Opd * DivideNode::flatten(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * lhsType = prog->nodeType(myExp1);
	lhsType->isInt();
	const DataType * rhsType = prog->nodeType(myExp2);
	rhsType->isInt();
	AuxOpd * res = proc->makeTmp(8);
	Opd * lhsOpd = myExp1->flatten(proc);
	Opd * rhsOpd = myExp2->flatten(proc);
	Quad * q = new BinOpQuad(res, BinOp::DIV64, lhsOpd, rhsOpd);
	proc->addQuad(q);
	return res;
}

Opd * AndNode::flatten(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * lhsType = prog->nodeType(myExp1);
	lhsType->isBool();
	const DataType * rhsType = prog->nodeType(myExp2);
	rhsType->isBool();
	AuxOpd * res = proc->makeTmp(8);
	Opd * lhsOpd = myExp1->flatten(proc);
	Opd * rhsOpd = myExp2->flatten(proc);
	Quad * q = new BinOpQuad(res, BinOp::AND64, lhsOpd, rhsOpd);
	proc->addQuad(q);
	return res;
}

Opd * OrNode::flatten(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * lhsType = prog->nodeType(myExp1);
	lhsType->isBool();
	const DataType * rhsType = prog->nodeType(myExp2);
	rhsType->isBool();
	AuxOpd * res = proc->makeTmp(8);
	Opd * lhsOpd = myExp1->flatten(proc);
	Opd * rhsOpd = myExp2->flatten(proc);
	Quad * q = new BinOpQuad(res, BinOp::OR64, lhsOpd, rhsOpd);
	proc->addQuad(q);
	return res;
}

Opd * EqualsNode::flatten(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * lhsType = prog->nodeType(myExp1);
	lhsType->isInt();
	const DataType * rhsType = prog->nodeType(myExp2);
	rhsType->isInt();
	AuxOpd * res = proc->makeTmp(8);
	Opd * lhsOpd = myExp1->flatten(proc);
	Opd * rhsOpd = myExp2->flatten(proc);
	Quad * q = new BinOpQuad(res, BinOp::EQ64, lhsOpd, rhsOpd);
	proc->addQuad(q);
	return res;
}

Opd * NotEqualsNode::flatten(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * lhsType = prog->nodeType(myExp1);
	lhsType->isInt();
	const DataType * rhsType = prog->nodeType(myExp2);
	rhsType->isInt();
	AuxOpd * res = proc->makeTmp(8);
	Opd * lhsOpd = myExp1->flatten(proc);
	Opd * rhsOpd = myExp2->flatten(proc);
	Quad * q = new BinOpQuad(res, BinOp::NEQ64, lhsOpd, rhsOpd);
	proc->addQuad(q);
	return res;
}

Opd * LessNode::flatten(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * lhsType = prog->nodeType(myExp1);
	lhsType->isInt();
	const DataType * rhsType = prog->nodeType(myExp2);
	rhsType->isInt();
	AuxOpd * res = proc->makeTmp(8);
	Opd * lhsOpd = myExp1->flatten(proc);
	Opd * rhsOpd = myExp2->flatten(proc);
	Quad * q = new BinOpQuad(res, BinOp::LT64, lhsOpd, rhsOpd);
	proc->addQuad(q);
	return res;
}

Opd * GreaterNode::flatten(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * lhsType = prog->nodeType(myExp1);
	lhsType->isInt();
	const DataType * rhsType = prog->nodeType(myExp2);
	rhsType->isInt();
	AuxOpd * res = proc->makeTmp(8);
	Opd * lhsOpd = myExp1->flatten(proc);
	Opd * rhsOpd = myExp2->flatten(proc);
	Quad * q = new BinOpQuad(res, BinOp::GT64, lhsOpd, rhsOpd);
	proc->addQuad(q);
	return res;
}

Opd * LessEqNode::flatten(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * lhsType = prog->nodeType(myExp1);
	lhsType->isInt();
	const DataType * rhsType = prog->nodeType(myExp2);
	rhsType->isInt();
	AuxOpd * res = proc->makeTmp(8);
	Opd * lhsOpd = myExp1->flatten(proc);
	Opd * rhsOpd = myExp2->flatten(proc);
	Quad * q = new BinOpQuad(res, BinOp::LTE64, lhsOpd, rhsOpd);
	proc->addQuad(q);
	return res;
}

Opd * GreaterEqNode::flatten(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * lhsType = prog->nodeType(myExp1);
	lhsType->isInt();
	const DataType * rhsType = prog->nodeType(myExp2);
	rhsType->isInt();
	AuxOpd * res = proc->makeTmp(8);
	Opd * lhsOpd = myExp1->flatten(proc);
	Opd * rhsOpd = myExp2->flatten(proc);
	Quad * q = new BinOpQuad(res, BinOp::GTE64, lhsOpd, rhsOpd);
	proc->addQuad(q);
	return res;
}

void AssignStmtNode::to3AC(Procedure * proc){
	Opd * res = mySrc->flatten(proc);
}

void PostIncStmtNode::to3AC(Procedure * proc){
	Opd * opd = this->myLoc->flatten(proc);
	LitOpd * litOpd = new LitOpd("1", 8);
	BinOpQuad * quad = new BinOpQuad(opd, ADD64, opd, litOpd);
	proc->addQuad(quad);
}

void PostDecStmtNode::to3AC(Procedure * proc){
	Opd * opd = this->myLoc->flatten(proc);
	LitOpd * litOpd = new LitOpd("1", 8);
	BinOpQuad * quad = new BinOpQuad(opd, SUB64, opd, litOpd);
	proc->addQuad(quad);
}

void WriteStmtNode::to3AC(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * type = prog->nodeType(mySrc);
	Opd * handle = this->myHandle->flatten(proc);
	Opd * src = this->mySrc->flatten(proc);
	ReadQuad * quad = new ReadQuad(handle, src, type);
	proc->addQuad(quad);
}

void ReadStmtNode::to3AC(Procedure * proc){
	IRProgram * prog = proc->getProg();
	const DataType * type = prog->nodeType(myDst);
	Opd * handle = this->myHandle->flatten(proc);
	Opd * dst = this->myDst->flatten(proc);
	ReadQuad * quad = new ReadQuad(handle, dst, type);
	proc->addQuad(quad);
}

void IfStmtNode::to3AC(Procedure * proc){
	Opd * cond = myCond->flatten(proc);
	Label * afterLabel = proc->makeLabel();
	Quad * afterNop = new NopQuad();
	afterNop->addLabel(afterLabel);
	Quad * skipStmt = new IfzQuad(cond, afterLabel);
	proc->addQuad(skipStmt);
	proc->addQuad(afterNop);
}

void IfElseStmtNode::to3AC(Procedure * proc){
	Label * elseLabel = proc->makeLabel();
	Quad * elseNop = new NopQuad();
	elseNop->addLabel(elseLabel);
	Label * afterLabel = proc->makeLabel();
	Quad * afterNop = new NopQuad();
	afterNop->addLabel(afterLabel);
	Opd * cond = myCond->flatten(proc);
	Quad * jmpFalse = new IfzQuad(cond, elseLabel);
	proc->addQuad(jmpFalse);	
	Quad * skipStmt = new IfzQuad(cond, afterLabel);
	proc->addQuad(skipStmt);
	proc->addQuad(elseNop);
	proc->addQuad(afterNop);
}

void WhileStmtNode::to3AC(Procedure * proc){
	Quad * headNop = new NopQuad();
	Label * headLabel = proc->makeLabel();
	headNop->addLabel(headLabel);
	Label * afterLabel = proc->makeLabel();
	Quad * afterQuad = new NopQuad();
	afterQuad->addLabel(afterLabel);
	proc->addQuad(headNop);
	Opd * cond = myCond->flatten(proc);
	Quad * jmpFalse = new IfzQuad(cond, afterLabel);
	proc->addQuad(jmpFalse);
	Quad * loopBack = new IfzQuad(cond, headLabel);
	proc->addQuad(loopBack);
	proc->addQuad(afterQuad);
}

void CallStmtNode::to3AC(Procedure * proc){
	Opd * res = myCallExp->flatten(proc);
	if (res != nullptr)
	{
	  Quad * last = proc->popQuad();
	}
}

void ReturnStmtNode::to3AC(Procedure * proc){
	Opd * res;
	if (myExp != nullptr)
	{
		res = myExp->flatten(proc);
		Quad * setRet = new SetRetQuad(res);
		proc->addQuad(setRet);
	}
	Label * leaveLbl = proc->getLeaveLabel();
	Quad * jmpLeave = new IfzQuad(res, leaveLbl);
	proc->addQuad(jmpLeave);	
}

void OpenStmtNode::to3AC(Procedure * proc){
	IRProgram * prog = proc->getProg();
	Opd * handle = this->handle->flatten(proc);
	std::string path;
	bool readonly = true;
	OpenQuad * quad = new OpenQuad(handle, path, readonly);
	proc->addQuad(quad);	
}

void CloseStmtNode::to3AC(Procedure * proc){
	IRProgram * prog = proc->getProg();
	Opd * handle = this->handle->flatten(proc);
	CloseQuad * quad = new CloseQuad(handle);
	proc->addQuad(quad);
}

void VarDeclNode::to3AC(Procedure * proc){
	SemSymbol * sym = ID()->getSymbol();
	assert(sym != nullptr);
	proc->gatherLocal(sym);
}

void VarDeclNode::to3AC(IRProgram * prog){
	SemSymbol * sym = ID()->getSymbol();
	assert(sym != nullptr);
	prog->gatherGlobal(sym);
}

//We only get to this node if we are in a stmt
// context (DeclNodes protect descent)
Opd * IDNode::flatten(Procedure * proc){
	SemSymbol * sym = this->getSymbol();
	Opd * res = proc->getSymOpd(sym);
	if (!res)
	{
	  throw new InternalError("NULL identifier symbol");
	}
	return res;
}

}
