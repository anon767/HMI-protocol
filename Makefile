TARGETS=reversegearcontroller displaycontroller
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


reversegearcontroller: $(SRCDIR)/Infrastructure/util.o $(SRCDIR)/Infrastructure/CANWrapperImpl.o $(SRCDIR)/Domain/ReverseGearController.o
	$(CXX) -o $@ $^ $(LIBS)

displaycontroller:  $(SRCDIR)/Infrastructure/util.o $(SRCDIR)/Infrastructure/CANWrapperImpl.o $(SRCDIR)/Domain/DisplayController.o
	$(CXX) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(SRCDIR)/Infrastructure/*.o
	$(RM) $(SRCDIR)/Domain/*.o
	$(RM) reversegearcontroller displaycontroller

all: reversegearcontroller displaycontroller

rebuild: clean all

