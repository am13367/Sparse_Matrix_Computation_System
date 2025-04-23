# Set g++ as the C++ compiler
CC=g++

# Enforce C++ 2011 as the language standard
CFLAGS=-std=c++11 

# Enable all standard warnings, uninitialized variable warnings, 
# and treat all warnings as errors
CFLAGS+= -Wall -Wuninitialized -Werror

# Link with math library
CXXFLAGS+= -lm

# NOTE: comment following line temporarily if 
# your development environment is failing
# due to these settings - it is important that 
# you fix your environment at some point.
CXXFLAGS+=-fsanitize=address -fsanitize=undefined

# C++ source files to consider in the compilation
#CPP_FILES=linkedmatrix.cpp matcomp.cpp main.cpp
# C++ header files to consider in the compilation
#HEADERS=linkedmatrix.h matcomp.h
# Object Files
OBJS=linkedmatrix.o matcomp.o main.o
# Target
TARGET=matcomp

$(TARGET): $(OBJS)
	@echo "Linking: $(OBJS) -> $@"
	$(CC) $(FLAGS) $(OBJS) -o $(TARGET)
linkedmatrix.o:	linkedmatrix.h linkedmatrix.cpp
	@echo "Compiling: $^ -> $@"
	$(CC) $(FLAGS) -c linkedmatrix.cpp
matcomp.o: matcomp.h matcomp.cpp
	@echo "Compiling: $^ -> $@"
	$(CC) $(FLAGS) -c  matcomp.cpp
main.o:	main.cpp
	@echo "Compiling: $< -> $@"
	$(CC) $(FLAGS) -c  main.cpp
clean:
	@echo "Deleting: $(OBJS) $(TARGET)"
	rm -rf $(OBJS) $(TARGET)
