# Directories
ROOT_DIR:=..
INCLUDE_DIR:=$(ROOT_DIR)/includes
TEST_DIR:=$(ROOT_DIR)/tests

# The program we will build is defined here
NAME:=spike1
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

# Here we support both C and C++ though we'd usually expect just one or the other
C_FILES:=$(wildcard *.c)
CPP_FILES:=$(wildcard *.cpp)
HDR_FILES:=$(wildcard $(INCLUDE_DIR)/*.h)
TCC_FILES:=$(wildcard $(INCLUDE_DIR)/*.tcc)

COBJ_FILES:=$(patsubst %.c,%.o,$(C_FILES))
CPPOBJ_FILES:=$(patsubst %.cpp,%.o,$(CPP_FILES))

# Set up so changes in any file in ALL_DEP trigger a full rebuild
ALL_DEP:=$(HDR_FILES) $(TCC_FILES) Makefile
INCLUDES:=-I $(INCLUDE_DIR)

# Test files info
TEST_FILES:=$(wildcard $(TEST_DIR)/*.lexi)
TEST_RESULTS:=$(patsubst $(TEST_DIR)/%.lexi,$(TEST_DIR)/%.lexo,$(TEST_FILES))

all:	$(PROGRAM)

$(PROGRAM):	$(CPPOBJ_FILES) $(COBJ_FILES)
	g++ $(LDFLAGS) $^ -o $@

%.o:	%.c $(ALL_DEP)
	gcc $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o:	%.cpp $(ALL_DEP)
	g++ $(CPPFLAGS) $(INCLUDES) -c $< -o $@

test:	$(PROGRAM) $(TEST_RESULTS)

$(TEST_DIR)/%.lexo:	$(TEST_DIR)/%.lexi FORCE
	@/bin/echo -n "[Test $(<F) -> $(@F) file: "
	@cd $(TEST_DIR); ./$(PROGRAM) $(<F) | diff $(@F) -
	@echo "OK]"

clean:	
	rm -f *.o *~ $(INCLUDE_DIR)/*~

realclean: clean
	rm -f $(PROGRAM)

tar:	realclean
	cd ..;tar cvf ../$(TARNAME) --exclude='*.tgz' --exclude='.git*' --exclude='Debug' --exclude='.cproject' --exclude='.settings' --exclude='.project' .

.PHONY:	FORCE
