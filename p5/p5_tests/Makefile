TESTFILES := $(wildcard **/*.jeff) $(wildcard *.jeff)
TESTS := $(TESTFILES:.jeff=.test)

.PHONY: all

all: $(TESTS)

%.test:
	@echo "Testing $*.jeff"
	@touch $*.err
	@../jeffc $*.jeff -c 2> $*.err ;\
	PROG_EXIT_CODE=$$?;\
	echo "diff error...";\
	diff $*.err $*.err.expected;\
	ERR_EXIT_CODE=$$?;\
	exit $$ERR_EXIT_CODE

clean:
	rm -f *.out *.err
