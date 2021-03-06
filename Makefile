.PHONY: default
default: build ;

help:
	@echo "Without and target, the daemon, library and tools will be built."
	@echo "The following additional makefile targets are supported:"
	@echo ""
	@echo " help	- display this help message."
	@echo " clean	- cleans all build files."
	@echo " build	- builds the daemon, library and tools."
	@echo " doc	- build the doxygen."
	@echo " all	- builds the daemon, library and tools, conducts unit tests, and generates the doxygen."
	@echo " install - installs the daemon, library and tools."
	@echo " test 	- build and run the unit tests."

clean:
	rm -rf build; rm -rf build_test; rm -rf deps;

doc:
	doxygen DoxyFile
	
build:
	mkdir -p build; cd build; cmake .. -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc; make build; cd ..;

test:
	mkdir -p build_test; cd build_test; cmake .. -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCOV=ON; make testbuild; cd ..;

all: build test doc

install: build
	cd build; make install; cd ..;


