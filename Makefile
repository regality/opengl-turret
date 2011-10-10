# Makefile
CC = g++
CCFLAGS = -O3 
GL_FLAGS = -lGL -lglut -lGLU
EXECNAME = turret
HFILES = $(wildcard objects/*.h)
SRCS = $(wildcard objects/*.cpp)
OBJS = $(patsubst objects/%,objects/obj/%,$(patsubst %.cpp,%.o,$(SRCS)))

all : $(EXECNAME) main.o $(OBJS)

run : all
	./$(EXECNAME)

$(EXECNAME) : $(OBJS) main.o
	$(CC) $(CCFLAGS) -o $@ main.o $(OBJS) $(GL_FLAGS)

main.o : main.cpp depends.h
	$(CC) $(CCFLAGS) -c main.cpp $(GL_FLAGS)

depends.h : $(OBJFILES) $(HFILES)
	@echo generating dependancy file
	@echo $(HFILES) | tr ' ' '\n' | \
      awk '{print "#include \"" $$$$0 "\""}' > $@ 

objects/obj/%.o : objects/%.cpp objects/%.h
	g++ $(CC_FLAGS) -c -o $@ $< $(GL_FLAGS)

newobject:
	@cat objects/Nothing.cpp | sed 's/Nothing/$(name)/g' > objects/$(name).cpp
	@cat objects/Nothing.h   | sed 's/Nothing/$(name)/g' > objects/$(name).h
	@echo created object \'$(name)\'

clean :
	rm -rf $(OBJS) $(EXECNAME) main.o depends.h
