nothing:
	g++ -O0 -g prog.c -o prog
	g++ -c -O0 -g string.c

asan:
	g++ -O0 -g -fsanitize=address -fno-omit-frame-pointer prog.c -o prog

static:
	gcc -Warray-bounds -c prog2.c

clean:
	rm -f a.out
