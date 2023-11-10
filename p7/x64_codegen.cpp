#include <ostream>
#include "3ac.hpp"

namespace jeff{

void IRProgram::allocGlobals(){
	//Choose a label for each global
	for (auto itr : globals)
	{
	  SemSymbol * semSymbol = itr.first;
	  SymOpd * tacSym = itr.second;
	  std::string lbl = "gbl_" + semSymbol->getName();
	  tacSym->setMemoryLoc(lbl);
	}
}

void IRProgram::datagenX64(std::ostream& out){
	out << ".data\n";
	for (auto itr : globals)
	{
	  if (itr.first->getName() == "console")
	  {
	    continue;
	  }
	  SymOpd * tacSym = itr.second;
	  out << tacSym->getMemoryLoc() << ": .quad 0\n";
	}
	for (auto itr : strings)
	{
	  LitOpd * myStrLabel = itr.first;
	  std::string myContent = itr.second;
	  out << myStrLabel->valString() + ": .asciz " << myContent << "\n";
	}
	//Put this directive after you write out strings
	// so that everything is aligned to a quadword value
	// again
	out << ".align 8\n";

}

void IRProgram::toX64(std::ostream& out){
        //DATA PASS
	allocGlobals();
	datagenX64(out);
	
	//CODE PASS
	// Iterate over each procedure and codegen it
	out << ".globl main\n";
	out << ".text\n";
	for (auto p : *procs)
	{
	  p->toX64(out);
	}
}

void Procedure::allocLocals(){
	//Allocate space for locals
	// Iterate over each procedure and codegen it
	int local = 24;
	std::map<SemSymbol* , SymOpd*>::iterator localItr = locals.begin();
	while(localItr != locals.end())
	{
		localItr->second->setMemoryLoc("-" + to_string(local) + "(%rbp)");
		local = local + 8;
		localItr++;
	}
	for (auto tempItr : temps)
	{
		tempItr->setMemoryLoc("-" + to_string(local) + "(%rbp)");
		local = local + 8;
	}
	local = ((8 * formals.size()) - 8);
	for (auto formalItr : formals)
	{
		formalItr->setMemoryLoc(to_string(local) + "(%rbp)");
		local = local - 8;
	}
}

void Procedure::toX64(std::ostream& out){
	//Allocate all locals
	allocLocals();

	enter->codegenLabels(out);
	enter->codegenX64(out);
	out << "#Fn body " << myName << "\n";
	for (auto quad : *bodyQuads){
		quad->codegenLabels(out);
		out << "#" << quad->toString() << "\n";
		quad->codegenX64(out);
	}
	out << "#Fn epilogue " << myName << "\n";
	leave->codegenLabels(out);
	leave->codegenX64(out);
}

void Quad::codegenLabels(std::ostream& out){
	if (labels.empty()){ return; }

	size_t numLabels = labels.size();
	size_t labelIdx = 0;
	for ( Label * label : labels){
		out << label->getName() << ": ";
		if (labelIdx != numLabels - 1){ out << "\n"; }
		labelIdx++;
	}
}

void BinOpQuad::codegenX64(std::ostream& out){
	switch(opr)
	{
		case ADD64:
				src1->genLoadVal(out, A);
				src2->genLoadVal(out, B);
				out << "addq %rbx, %rax\n";
				dst->genStoreVal(out, A);
				break;
		case SUB64:
				src1->genLoadVal(out, A);
				src2->genLoadVal(out, B);
				out << "subq %rbx, %rax\n";
				dst->genStoreVal(out, A);
				break;
		case DIV64:
				out << "movq $0, %rdx\n";
				src1->genLoadVal(out, A);
				src2->genLoadVal(out, B);
				out << "idivq %rbx\n";
				dst->genStoreVal(out, A);
				break;
		case MULT64:
				src1->genLoadVal(out, A);
				src2->genLoadVal(out, B);
				out << "imulq %rbx\n";
				dst->genStoreVal(out, A);
				break;
		case OR64:
				src1->genLoadVal(out, A);
				src2->genLoadVal(out, B);
				out << "orq %rbx, %rax\n";
				dst->genStoreVal(out, A);
				break;
		case AND64:
				src1->genLoadVal(out, A);
				src2->genLoadVal(out, B);
				out << "andq %rbx, %rax\n";
				dst->genStoreVal(out, A);
				break;
		case EQ64:
				src1->genLoadVal(out, A);
				src2->genLoadVal(out, B);
				out << "cmpq %rbx, %rax\n";
				out << "sete %al\n";
				out << "movq %rax, %rbx\n";
				dst->genStoreVal(out, A);
				break;
		case NEQ64:
				src1->genLoadVal(out, A);
				src2->genLoadVal(out, B);
				out << "cmpq %rbx, %rax\n";
				out << "setne %al\n";
				out << "movq %rax, %rbx\n";
				dst->genStoreVal(out, A);
				break;
		case LT64:
				src1->genLoadVal(out, A);
				src2->genLoadVal(out, B);
				out << "cmpq %rbx, %rax\n";
				out << "setl %al\n";
				out << "movq %rax, %rbx\n";
				dst->genStoreVal(out, A);
				break;
		case GT64:
				src1->genLoadVal(out, A);
				src2->genLoadVal(out, B);
				out << "cmpq %rbx, %rax\n";
				out << "setg %al\n";
				out << "movq %rax, %rbx\n";
				dst->genStoreVal(out, A);
				break;
		case LTE64:
				src1->genLoadVal(out, A);
				src2->genLoadVal(out, B);
				out << "cmpq %rbx, %rax\n";
				out << "setle %al\n";
				out << "movq %rax, %rbx\n";
				dst->genStoreVal(out, A);
				break;
		case GTE64:
				src1->genLoadVal(out, A);
				src2->genLoadVal(out, B);
				out << "cmpq %rbx, %rax\n";
				out << "setge %al\n";
				out << "movq %rax, %rbx\n";
				dst->genStoreVal(out, A);
				break;
	}
}

void UnaryOpQuad::codegenX64(std::ostream& out){
	switch(op)
	{
		case NEG64:
				src->genLoadVal(out, B);
				out << "negq %rbx\n";
				dst->genStoreVal(out, B);
				break;
		case NOT64:
				src->genLoadVal(out, B);
				out << "notq %rbx\n";
				dst->genStoreVal(out, B);
				break;
	}
}

void AssignQuad::codegenX64(std::ostream& out){
	src->genLoadVal(out, A);
	dst->genStoreVal(out, A);
}

void ReadQuad::codegenX64(std::ostream& out){
	if (myHandle->locString() != "console")
	{
	  myHandle->genLoadVal(out, SI);
	}
	else
	{
	  out << "movq $0, %rsi\n";
	}
	myDst->genLoadVal(out, DI);
	if (myDstType->isInt())
	{
	  out << "callq stdJeff_readInt\n";
	}
}

void WriteQuad::codegenX64(std::ostream& out){
	if (myHandle->locString() != "console")
	{
	  myHandle->genLoadVal(out, SI);
	}
	else
	{
	  out << "movq $0, %rsi\n";
	}
	mySrc->genLoadVal(out, DI);
	if (mySrcType->isInt())
	{
	  out << "callq stdJeff_writeInt\n";
	}
}

void OpenQuad::codegenX64(std::ostream& out){
	myPath->genLoadVal(out, DI);
	out << "callq stdJeff_openFP\n";
	myPath->genStoreVal(out, A);
}

void CloseQuad::codegenX64(std::ostream& out){
	myHandle->genLoadVal(out, DI);
	out << "callq stdJeff_closeFP\n";
	myHandle->genStoreVal(out, A);
}

void GotoQuad::codegenX64(std::ostream& out){
	out << "jmp " << tgt->getName() << "\n";
}

void IfzQuad::codegenX64(std::ostream& out){
	cnd->genLoadVal(out, L15);
	out << "cmpq $0, %r15\n";
	out << "je " << tgt->getName() << "\n";
}

void NopQuad::codegenX64(std::ostream& out){
	out << "nop" << "\n";
}

void CallQuad::codegenX64(std::ostream& out){
	out << "callq fn_" << sym->getName() << "\n";
}

void EnterQuad::codegenX64(std::ostream& out){
	out << "pushq %rbp # EnterQuad (prologue)\n";
	out << "         movq %rsp, %rbp\n";
	out << "         addq $16, %rbp\n";
	out << "         subq $" << myProc->arSize() << ", %rsp\n";
}

void LeaveQuad::codegenX64(std::ostream& out){
	out << "#leave quad todo\n";
	out << "movq $60, %rax\n";
	out << "syscall\n";
}

void SetArgQuad::codegenX64(std::ostream& out){
	out << "subq $8, %rsp\n";
	opd->genLoadVal(out, SP);
}

void GetArgQuad::codegenX64(std::ostream& out){
	TODO(Implement me if necessary)
	//Nothing is needed.
}

void SetRetQuad::codegenX64(std::ostream& out){
	opd->genLoadVal(out, A);
}

void GetRetQuad::codegenX64(std::ostream& out){
	opd->genStoreVal(out, A);
}

void LocQuad::codegenX64(std::ostream& out){
	TODO(Implement me if necessary)
	//Nothing is needed.
}

void SymOpd::genLoadVal(std::ostream& out, Register reg){
	out << getMovOp() << " $" << getMemoryLoc() << ", " << getReg(reg) << "\n";
}

void SymOpd::genStoreVal(std::ostream& out, Register reg){
	out << getMovOp() << " $" << getReg(reg) << ", " << getMemoryLoc() << "\n";
}

void SymOpd::genLoadAddr(std::ostream& out, Register reg) {
	TODO(Implement me if necessary)
	//Nothing is needed.
}

void AuxOpd::genLoadVal(std::ostream& out, Register reg){
	out << getMovOp() << " $" << getMemoryLoc() << ", " << getReg(reg) << "\n";
}

void AuxOpd::genStoreVal(std::ostream& out, Register reg){
	out << getMovOp() << " $" << getReg(reg) << ", " << getMemoryLoc() << "\n";
}

void AuxOpd::genLoadAddr(std::ostream& out, Register reg){
	TODO(Implement me if necessary)
	//Nothing is needed.
}

void AddrOpd::genStoreVal(std::ostream& out, Register reg){
	TODO(Implement me if necessary)
	//Nothing is needed.
}

void AddrOpd::genLoadVal(std::ostream& out, Register reg){
	TODO(Implement me if necessary)
	//Nothing is needed.
}

void AddrOpd::genStoreAddr(std::ostream& out, Register reg){
	TODO(Implement me if necessary)
	//Nothing is needed.
}

void AddrOpd::genLoadAddr(std::ostream & out, Register reg){
	TODO(Implement me if necessary)
	//Nothing is needed.
}

void LitOpd::genLoadVal(std::ostream & out, Register reg){
	out << getMovOp() << " $" << val << ", " << getReg(reg) << "\n";
}

}
