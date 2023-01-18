


#------------------------------------------------------------------------------
# Target 
#------------------------------------------------------------------------------
EXEC = demo

#CFLAGS = -g -O0 -I /opt/homebrew/Cellar/freerdp/2.9.0/include/freerdp2 -I /opt/homebrew/Cellar/freerdp/2.9.0/include/winpr2/
#LDFLAGS = -L /opt/homebrew/Cellar/freerdp/2.9.0/lib -lfreerdp2 -lfreerdp-client2 -lwinpr2
CFLAGS = -g -O0 -I /usr/local/include/winpr2/ -I /usr/local/include/freerdp2/
LDFLAGS = -L /usr/local/lib -lfreerdp2 -lfreerdp-client2 -lwinpr2

CC = gcc


#------------------------------------------------------------------------------
# Directories
#------------------------------------------------------------------------------
DIR_SRC = ./src/
DIR_BUILD = ./build/
DIR_BUILD_OBJ = $(DIR_BUILD)/obj/
DIR_BUILD_BIN = $(DIR_BUILD)/bin/

#------------------------------------------------------------------------------
# File suffixes
#------------------------------------------------------------------------------

EXT_CODE = .c
EXT_HEADERS = .h
EXT_OBJECT = .o
.SUFFIXES:
.SUFFIXES: $(EXT_CODE) $(EXT_HEADERS) $(EXT_OBJECT)
#------------------------------------------------------------------------------
# Search Paths
#------------------------------------------------------------------------------

VPATH =
vpath
vpath %$(EXT_CODE) $(DIR_SRC)
vpath %$(EXT_HEADERS) $(DIR_SRC)
vpath %$(EXT_OBJECT) $(DIR_BUILD_OBJ)

#------------------------------------------------------------------------------
# Macros
#------------------------------------------------------------------------------

# Get every code file in the source directory
FILES_SRC = $(foreach dir,$(DIR_SRC),$(wildcard $(DIR_SRC)*$(EXT_CODE)))

# Get only the file name of the source files
FILES_SRC_REL = $(notdir $(FILES_SRC))

# Replaces the code extension by the object extension
FILES_SRC_O = $(subst $(EXT_CODE),$(EXT_OBJECT),$(FILES_SRC_REL))

# Prefix all code files with the object directory
FILES_SRC_BUILD  = $(addprefix $(DIR_BUILD_OBJ),$(FILES_SRC_O))

# Prefix all executables with the build directory
FILES_EXEC_BUILD = $(addprefix $(DIR_BUILD_BIN),$(EXEC))


#------------------------------------------------------------------------------
# Other targets
#------------------------------------------------------------------------------

default: $(FILES_EXEC_BUILD)

-include .depend

$(DIR_BUILD_OBJ)%$(EXT_OBJECT): %$(EXT_CODE)
	$(CC) -c -o $@ $< $(CFLAGS)

$(FILES_EXEC_BUILD): $(FILES_SRC_BUILD)
	$(CC) -o $@ $^ $(LDFLAGS)

dep depend:
	@$(CC) $(CFLAGS) -M -MM $(FILES_SRC) > .depend
	@sed -i "s@\(^\w\)@$(DIR_BUILD_OBJ)\1@" .depend

clean:
	rm -fr $(FILES_EXEC_BUILD) $(FILES_SRC_BUILD)

distclean: clean
	rm -fr .depend
