#ifndef JEFF_NAME_ERROR_REPORTING_HH
#define JEFF_NAME_ERROR_REPORTING_HH

#include "errors.hpp"

namespace jeff {

class NameErr{
public:
static bool undeclID(size_t l, size_t c){
	Report::fatal(l, c, "Undeclared identifier");
	return false;
}
static bool badVarType(size_t l, size_t c){
	Report::fatal(l, c, "Invalid type in declaration");
	return false;
}
static bool multiDecl(size_t l, size_t c){
	Report::fatal(l, c, "Multiply declared identifier");
	return false;
}
};

} //End namespace jeff

#endif
