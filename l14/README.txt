This tarball includes demonstrations of some LLVM features. 

SETUP
In order to run these demonstrations, you'll need access to an LLVM installation. 
On your own Linux (or WSL-enabled Windows) machine, you can probably get LLVM 
via your package manager. For Debian-like systems, run

sudo apt install llvm

On the Cycle servers, you can use Drew's installation of llvm, by putting
/home/a807d786/llvm_tools/ into your path. 


EMITTING LLVM BITCODE
	The LLVM project represents a suite of utilities, formats, and libraries
	for code analysis and transformation. However, it is most commonly 
	recognized for its compiler frameworks. While LLVM Compilers are 
	capable of translating to binary in one shot, we're interested in
	interposing on the pipeline. To that end, we'd like to emit LLVM's
	high-level intermediate code, known as bitcode, in human-readable
	format. For this (from this directory), you can invoke

	clang emit/fact.c -S -emit-llvm
	
	To use the LLVM C frontend to transform the C source file
	fact.c (which is a simple factorial implementation). The
	corresponding bitcode file will be named fact.ll. 
	Feel free to examine the bitcode manually. 

BUILT-IN BITCODE ANALYSES
	LLVM's opt tool can be used to process bitcode in a variety of ways,
	including optimization (hence the name), or for the purpose of 
	pure analysis (i.e. no alterations to the code). There are a number
	of interesting built-in analyses in opt. For example, you can run

	opt -dot-callgraph -dot-dom -dot-cfg fact.ll

	To generate several files in a single invocation:
	* callgraph.dot is the callgraph for fact.ll
	* cfg.fact.dot is the control-flow graph for the fact function
	* dom.fact.dot is the dominator tree for the fact function
	Note that all of these functions are in dot format, and thus can
	be visualized using the dot tool (part of the graphviz package):
	dot -Tpng callgraph.dot -o callgraph.png
	dot -Tpng dom.fact.dot -o dom.fact.png
	dot -Tpng cfg.fact.dot -o cfg.fact.png
	
DEVELOPING A CUSTOM ANALYSIS
	Besides the built-in analyses, opt can load a custom analysis
	or transformation pass. A useful design feature of the system
	is that these passes can be loaded into opt at invocation time,
	rather than requiring that the opt binary be rebuilt.

	The current directory this README is in is an example of a 
	bare-bones optimization pass. Because the build-system is 
	CMake-based, you'll need cmake to invoke it (apt install cmake
	should suffice). In-place builds using CMake are generally discouraged,
	so you should create a new directory for build artifacts, then
	invoke make in that directory. From the current directory, invoke:
	
	mkdir build
	cd build
	cmake ../src
	make

	In additon to the CMake boilerplate, you will now have a dynamically-
	linked library that can be attached to opt, called libCoolPass.so.
	You should check out the source code that was compiled into the 
	pass, present in src/Pass.cpp. The pass simply visits each function 
	in the given bitcode, printing out the function name and the 
	number of formal parameters that it takes. The code is fairly terse
	(at least considering how much it is doing), clocking in at under 80
	lines of code, including comments.

	You should try to run opt using this pass. There are two relevant
	arguments:
	* the --load-pass-plugin option, which takes a path 
	* the -passes optiion, which indicates which arguments should be run.

	The command to invoke is 

	opt --load-pass-plugin=./libCoolPass.so ../fact.ll -passes=cool-pass -S > /dev/null

	Note that you may have to adjust the paths to point to your fact.ll
	and your libCoolPass.so. The -S option tells opt to emit human-readable
	bitcode (which is piped to /dev/null, discarding it). 
	Since our pass doesn't alter the bitcode, we aren't interested in it.
	However, if you wanted to alter a single bitcode file using opt, you'd 
	see the new version in the opt output
	altered


