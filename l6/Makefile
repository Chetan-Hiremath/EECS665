TESTFILES := $(wildcard *.input)
TESTS := $(TESTFILES:.input=.test)

.PHONY: all clean

all: prog test
	echo "All Done!" 

prog: blah.o
	g++ $< -o $@

%.o: %.cpp
	g++ $< -c -o $@

clean:
	rm -f *.o prog

test: $(TESTS)

%.test:
	@echo "Running case $*"
	@./prog $*.input 1> $*.out 2> $*.err
	@diff $*.out.expected $*.out 
	@diff $*.err.expected $*.err
	@echo "Case $* passed"
