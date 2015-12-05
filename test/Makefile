#
# Sim21 Makefile
#

CC := g++

SRCDIR   := ../src
BUILDDIR := ../build
TESTSRCDIR   := src
TESTBUILDDIR := build
TARGET   := bin/RunTests
INCDIR   := ../include

SRCEXT   := cpp
SOURCES  := $(shell find $(SRCDIR)  -type f -name *.$(SRCEXT))
SOURCES  := $(filter-out ../src/RunSim.cpp, $(SOURCES))
TESTSOURCES  := $(shell find $(TESTSRCDIR)  -type f -name *.$(SRCEXT))
OBJECTS  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TESTOBJECTS  := $(patsubst $(TESTSRCDIR)/%,$(TESTBUILDDIR)/%,$(TESTSOURCES:.$(SRCEXT)=.o))
CFGLAGS  := -g
LIB      := -std=c++0x
INC      := -I $(INCDIR)

$(TARGET): $(OBJECTS) $(TESTOBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<

$(TESTBUILDDIR)/%.o: $(TESTSRCDIR)/%.$(SRCEXT)
	@mkdir -p $(TESTBUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(OBJECTS) "; $(RM) -r $(OBJECTS)

