#
# Sim21 Makefile
#

CC := g++

SRCDIR      := src
DEBBUILDDIR := debug/build
RELBUILDDIR := release/build
DEBTARGET   := debug/bin/Sim21
RELTARGET   := release/bin/Sim21

SRCEXT      := cpp
SOURCES     := $(shell find $(SRCDIR)  -type f -name *.$(SRCEXT))
DEBOBJECTS  := $(patsubst $(SRCDIR)/%,$(DEBBUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
RELOBJECTS  := $(patsubst $(SRCDIR)/%,$(RELBUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEBFLAGS    := -g -pg
RELFLAGS    := -O3
LIB         := -std=c++0x
INC         := -I include

$(DEBTARGET) $(RELTARGET): $(DEBOBJECTS) $(RELOBJECTS)
	@echo " Linking debug binary..."
	@echo " $(CC) $(DEBOBJECTS) -o $(DEBTARGET) $(LIB)"; $(CC) $(DEBOBJECTS) $(DEBFLAGS) -o $(DEBTARGET) $(LIB)
	@echo " Linking release binary..."
	@echo " $(CC) $(RELOBJECTS) -o $(RELTARGET) $(LIB)"; $(CC) $(RELOBJECTS) $(RELFLAGS) -o $(RELTARGET) $(LIB)

$(DEBBUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(DEBBUILDDIR)
	@echo " $(CC) $(DEBFLAGS) $(INC) -c -o $@ $<"; $(CC) $(DEBFLAGS) $(INC) $(LIB) -c -o $@ $<

$(RELBUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(RELBUILDDIR)
	@echo " $(CC) $(RELFLAGS) $(INC) -c -o $@ $<"; $(CC) $(RELFLAGS) $(INC) $(LIB) -c -o $@ $<

$(DEBTARGET) $(RELTARGET): $(DEBOBJECTS) $(RELOBJECTS)

clean:
	@echo " Cleaning..."; 
	@echo " $(RM) -r $(DEBOBJECTS) "; $(RM) -r $(DEBOBJECTS)
	@echo " $(RM) -r $(RELOBJECTS) "; $(RM) -r $(RELOBJECTS)
	@echo " $(RM) results/*.csv "; $(RM)  results/*.csv

