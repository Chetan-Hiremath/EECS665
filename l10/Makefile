all:
	as code.s -o code.o
	ld code.o -o code.exe
	objdump -Dwrt code.exe > code.dump
	@./code.exe ;\
	RET=$$?. ;\
           echo "ret code $$RET" ;\
           exit 0
	
clean:
	rm -rf code.o code.exe code.dump
