all: bounds div_by_zero malloc

div0float_unchecked: 
	g++ div_by_zero.cpp -o div0float_unchecked
	
div0float_checked: 
	g++ -fsanitize=float-divide-by-zero div_by_zero.cpp -o div0float_checked

bounds_unchecked:
	g++ -O0 bounds.cpp -o bounds_unchecked
	
bounds_checked:
	g++ -O0 -fsanitize=bounds bounds.cpp -o bounds_checked
	
malloc_unchecked: 
	g++ malloc.cpp -fsanitize=undefined -o malloc_unchecked
	
malloc_checked: 
	g++ malloc.cpp -fsanitize=address -o malloc_checked
