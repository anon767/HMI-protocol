TARGETS=canwrapper applicationcontroller hmicontroller
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

canwrapper:  $(SRCDIR)/Infrastructure/CANWrapperImpl.o $(SRCDIR)/Infrastructure/util.o
	$(CXX) -o $@ $^ $(LIBS)

applicationcontroller:  $(SRCDIR)/Domain/ApplicationController.o
	$(CXX) -o $@ $^ $(LIBS)

hmicontroller:  $(SRCDIR)/Domain/HMIController.o
	$(CXX) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(SRCDIR)/Infrastructure/*.o
	$(RM) $(SRCDIR)/Domain/*.o
	$(RM) canwrapper applicationcontroller hmicontroller

all: applicationcontroller hmicontroller

rebuild: clean all

