#include "symbol_table.hpp"
namespace jeff{

ScopeTable::ScopeTable(){
	symbols = new HashMap<std::string, SemSymbol *>(); 
}

SymbolTable::SymbolTable(){
	//TODO: implement the list of hashtables approach
	// to building a symbol table:
	// Upon entry to a scope a new scope table will be 
	// entered into the front of the chain and upon exit the 
	// latest scope table will be removed from the front of 
	// the chain.
	scopeTableChain = new std::list<ScopeTable *>();
}

void SymbolTable::addScope(ScopeTable *tab){
	this->scopeTableChain->push_front(tab);
}


void SymbolTable::dropScope(){
	this->scopeTableChain->pop_front();
}

bool ScopeTable::isPresent(IDNode *id){
	bool isPresent = false;
	if ((this->symbols->find(id->getName())) != this->symbols->end()) {
		isPresent = true; 
	}
	return isPresent;
}


bool SymbolTable::lookUp(IDNode *id){
	bool isPresent = false;
	for(auto scopeT : *scopeTableChain){
		isPresent = scopeT->isPresent(id);
	}
	return isPresent;
}

bool SymbolTable::isInCurrentScopeAlready(IDNode *id){
	bool isPresent = false;
	isPresent = this->currentScope()->isPresent(id);
	return isPresent;
}

bool SymbolTable::isCorrectType(TypeNode *typeNode) {
	bool isCorrectType = false;
	if (!(typeNode->getType() == "void")){
		isCorrectType = true;
		return isCorrectType;
	}
	return isCorrectType;
}

ScopeTable* SymbolTable::currentScope()
{
	return this->scopeTableChain->front();
}


void ScopeTable::addSymbol(string idName, SemSymbol *s){
	this->symbols->insert(std::make_pair(idName, s));
}

}
