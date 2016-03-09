#
# Sim21 Makefile
#

CC := g++

BASEDIR      := ../
SRCDIR       := ../src
BUILDDIR     := ../build
GCOVBUILDDIR := ../gcov/build
TESTSRCDIR   := src
TESTBUILDDIR := build
TARGET       := bin/RunTests
GCOVTARGET   := bin/gcov_RunTests
INCDIR       := ../include
TESTINCDIR   := include

SRCEXT          := cpp
GCOVEXT_0       := gcno
GCOVEXT_1       := gcda
GCOVEXT_2       := gcov
SOURCES         := $(shell find $(SRCDIR)  -type f -name *.$(SRCEXT))
SOURCES         := $(filter-out ../src/RunSim.cpp, $(SOURCES))
TESTSOURCES     := $(shell find $(TESTSRCDIR)  -type f -name *.$(SRCEXT))
OBJECTS         := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TESTOBJECTS     := $(patsubst $(TESTSRCDIR)/%,$(TESTBUILDDIR)/%,$(TESTSOURCES:.$(SRCEXT)=.o))
GCOVOBJECTS     := $(patsubst $(SRCDIR)/%,$(GCOVBUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
GCOVFILES       := $(shell find $(BASEDIR) -type f -name *.$(GCOVEXT_0))
GCOVFILES       += $(shell find $(BASEDIR) -type f -name *.$(GCOVEXT_1))
GCOVFILES       += $(shell find $(BASEDIR) -type f -name *.$(GCOVEXT_2))
CFLAGS          := -g -O0
LIB             := -std=c++0x
GCOVLIB         := -fprofile-arcs -ftest-coverage
INC             := -I $(INCDIR) -I $(TESTINCDIR)

##
# Standard test binary
##
$(TARGET): $(OBJECTS) $(TESTOBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(CFLAGS) $(LIB)"; $(CC) $^ -o $(TARGET) $(CFLAGS) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<

$(TESTBUILDDIR)/%.o: $(TESTSRCDIR)/%.$(SRCEXT)
	@mkdir -p $(TESTBUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<

##
# gcov test binary
##
gcov: $(GCOVOBJECTS) $(TESTOBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(GCOVTARGET) $(CFLAGS) $(GCOVLIB) $(LIB)"; $(CC) $^ -o $(GCOVTARGET) $(CFLAGS) $(GCOVLIB) $(LIB)

$(GCOVBUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(GCOVBUILDDIR)
	@echo " $(CC) $(CFLAGS) $(GCOVLIB) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(GCOVLIB) $(INC) $(LIB) -c -o $@ $<

$(TESTBUILDDIR)/%.o: $(TESTSRCDIR)/%.$(SRCEXT)
	@mkdir -p $(TESTBUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<

##
# clean
##
clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(OBJECTS) "; $(RM) -r $(OBJECTS)
	@echo " $(RM) -r $(TESTOBJECTS) "; $(RM) -r $(TESTOBJECTS)
	@echo " $(RM) -r $(GCOVOBJECTS) "; $(RM) -r $(GCOVOBJECTS)
	@echo " $(RM) -r $(GCOVFILES) "; $(RM) -r $(GCOVFILES)
	@echo " $(RM) $(TARGET) "; $(RM) $(TARGET)
	@echo " $(RM) $(GCOVTARGET) "; $(RM) $(GCOVTARGET)
