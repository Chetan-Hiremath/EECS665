#include <fstream>
#include "mylexer.hpp"

int main(int argc, char *argv[]){
	std::ifstream * infile = new std::ifstream(argv[1]);
	MyLexer * lex  = new MyLexer(infile);
	int noun_count;
	int verb_count;
	int adjective_count;
	while (true){
		Token * tok;
		int res = lex->produceToken(&tok);
		if (res == ERROR){
			std::cerr << "BAD CHARACTER\n";
			return 1;
		}
		if (res == NOUN) {
                   noun_count++;
		}
		if (res == VERB){
                   verb_count++;
		}
                if (res == ADJECTIVE){
                   adjective_count++;
		}
		
		if (res == END_OF_FILE){
			break;
		}
	}
	fprintf(stdout, "Number of nouns = %d, Number of Verbs = %d, and Number of Adjectives = %d\n", noun_count, verb_count, adjective_count);
}
