#
# Sim21 Makefile
#

CC := g++

SRCDIR     := src
BUILDDIR   := build
TARGET     := bin/Sim21
TESTDIR    := test
TESTTARGET := test/RunTests

SRCEXT   := cpp
SOURCES  := $(shell find $(SRCDIR)  -type f -name *.$(SRCEXT))
TESTSRC  := $(shell find $(TESTDIR) -type f -name *.$(SRCEXT))
OBJECTS  := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
TESTS    := $(patsubst $(TESTDIR)/%,$(BUILDDIR)/%,$(TESTSRC:.$(SRCEXT)=.o)) 
CFGLAGS  := -g
LIB := -std=c++0x
INC := -I include

$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(OBJECTS) "; $(RM) -r $(OBJECTS)

