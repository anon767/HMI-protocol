TARGETS=canwrapper
SRCDIR=src

# Compiler setup
CXX=g++
CPPFLAGS=-Isrc
CXXFLAGS=-std=gnu++14 -pedantic -Wall -Wextra
LIBS=


all: CPPFLAGS+=-DNDEBUG
all: CXXFLAGS+=-O3
all: $(TARGETS)

debug: CXXFLAGS+=-g
debug: $(TARGETS)

canwrapper:  $(SRCDIR)/CANWrapperImpl.o $(SRCDIR)/util.o
	$(CXX) -o $@ $^ $(LIBS)


%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(SRCDIR)/*.o
	$(RM) canwrapper

all: canwrapper

rebuild: clean all

