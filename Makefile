GCC=g++-4.9 -std=c++14

OBJ = command_parser.o 
PROG = example


all: $(OBJ)
	$(GCC) $(OBJ) example.cpp -o $(PROG)

%.o: %.cpp %.hpp
	$(GCC) -c  $< -o $@

%:%.cpp
	$(GCC) $< -o $@

clean:
	$(RM)  $(OBJ)  $(PROG)