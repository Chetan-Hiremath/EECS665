#ifndef JEFF_SYMBOL_TABLE_HPP
#define JEFF_SYMBOL_TABLE_HPP
#include <string>
#include <unordered_map>
#include <list>
#include "ast.hpp"

//Use an alias template so that we can use
// "HashMap" and it means "std::unordered_map"
template <typename K, typename V>
using HashMap = std::unordered_map<K, V>;

using namespace std;

namespace jeff{

//A semantic symbol, which represents a single
// variable, function, etc. Semantic symbols 
// exist for the lifetime of a scope in the 
// symbol table. 
class SemSymbol {
	//TODO add the fields that 
	// each semantic symbol should track
	// (i.e. the kind of the symbol (either a variable or function)
	// and functions to get/set those fields
	public: 
		SemSymbol(char s, DeclNode* d) : symbol(s), declNode(d){}
		char getKind()
		{
			return symbol;
		}
		std::string getType() 
		{ 
			if(symbol == 'v')
			{ 
				return declNode->getTypeNode()->getType();
			} 
			else 
			{ 
				std::string type = " ";
				int typeCount = 0; 
				size_t typeSize = declNode->getFormals()->size();
				for(auto f : *declNode->getFormals())
				{
					type += f->getTypeNode()->getType();
					if(typeCount < static_cast<int>(typeSize))
					{
						type += ",";
					}
					typeCount++;
				}
				type += "->";
				type += declNode->getTypeNode()->getType();
				return type;
			}
		}
	private: 
		char symbol;
		DeclNode* declNode;
};

//A single scope. The symbol table is broken down into a 
// chain of scope tables, and each scope table holds 
// semantic symbols for a single scope. For example,
// the globals scope will be represented by a ScopeTable,
// and the contents of each function can be represented by
// a ScopeTable.
class ScopeTable {
	public:
		ScopeTable();
		bool isPresent(IDNode *id);
		void addSymbol(string idName, SemSymbol *s);
		//TODO: add functions for looking up symbols
		// and/or returning information to indicate
		// that the symbol does not exist within the
		// current scope.
	private:
		HashMap<std::string, SemSymbol *> * symbols;
};

class SymbolTable{
	public:
		SymbolTable();
		void addScope(ScopeTable *tab);
		void dropScope();
		ScopeTable* currentScope();
		bool lookUp(IDNode *id);
		bool isInCurrentScopeAlready(IDNode *id);
		bool isCorrectType(TypeNode *typeNode);
		//TODO: add functions to create a new ScopeTable
		// when a new scope is entered, drop a ScopeTable
		// when a scope is exited, etc. 
	private:
		std::list<ScopeTable *> * scopeTableChain;
};

	
}

#endif
