# Directories
ROOT_DIR:=..
INCLUDE_DIR:=$(ROOT_DIR)/includes
SOURCE_DIR:=.
TEST_DIR:=$(ROOT_DIR)/tests

# The program we will build is defined here
NAME:=spike3
PROGRAM:=$(ROOT_DIR)/$(NAME)

# Some reasonably strict and therefore supportive compilation flags to get us started
CFLAGS:=-Wall -ansi -pedantic -Werror -Wformat -g
CPPFLAGS:=$(CFLAGS)
LDFLAGS:=

# Info for naming tar files
TIMESTAMP:=$(shell date +%Y%m%d-%H%M%S)
DEV:=$(shell whoami)
TARBASE:=$(NAME)-$(TIMESTAMP)-$(DEV)
TARNAME:=$(TARBASE).tar

# Here we support both C and C++ though we'd usually blkect just one or the other
CPP_FILES = $(shell find $(SOURCE_DIR)/ -type f -name '*.cpp')
HDR_FILES:=$(shell find $(INCLUDE_DIR)/ -type f -name '*.h')

CPPOBJ_FILES:=$(patsubst %.cpp,%.o,$(CPP_FILES))

# Set up so changes in any file in ALL_DEP trigger a full rebuild
ALL_DEP:=$(HDR_FILES) Makefile
INCLUDES:=-I $(INCLUDE_DIR)

# Test files info
TEST_FILES:=$(wildcard $(TEST_DIR)/*.blki)
TEST_RESULTS:=$(patsubst $(TEST_DIR)/%.blki,$(TEST_DIR)/%.blko,$(TEST_FILES))

# Dependencies generation
DEPDIR := .d
$(shell mkdir -p $(DEPDIR) >/dev/null)
$(shell mkdir -p $(DEPDIR)/Nodes >/dev/null)
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.Td
POSTCOMPILE = @mv -f $(DEPDIR)/$*.Td $(DEPDIR)/$*.d && touch $@

all:	$(PROGRAM)

$(PROGRAM):	$(CPPOBJ_FILES)
	g++ $(LDFLAGS) $^ -o $@

%.o:	%.cpp
	g++ $(DEPFLAGS) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
	$(POSTCOMPILE)

$(DEPDIR)/%.d:	;
.PRECIOUS:	$(DEPDIR)/%.d

test:	$(PROGRAM) $(TEST_RESULTS)

$(TEST_DIR)/%.blko:	$(TEST_DIR)/%.blki FORCE
	@/bin/echo -n "[Test $(<F) -> $(@F) file: "
	@cd $(TEST_DIR); ./$(PROGRAM) $(<F) 2>/dev/null | diff $(@F) -
	@echo "OK]"

clean:	
	find $(SOURCE_DIR) $(INCLUDE_DIR) -name "*.o" -type f -delete 
	rm -rf $(SOURCE_DIR)/$(DEPDIR)

realclean: clean
	rm -f $(PROGRAM)

tar:	realclean
	cd ..;
	tar cvf ../$(TARNAME) --exclude='*.tgz' --exclude='.git*' --exclude='Debug' --exclude='.cproject' --exclude='.settings' --exclude='.project' .

include $(wildcard $(patsubst %,$(DEPDIR)/%.d,$(basename $(CPP_FILES))))

.PHONY:	FORCE
