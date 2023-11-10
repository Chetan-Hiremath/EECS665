all:
	flex --c++ --yyclass=MyLexer --noyywrap -o lexer.cpp parts_of_speech.l
	g++ entry.cpp lexer.cpp -o parts_of_speech
	./parts_of_speech test.input
