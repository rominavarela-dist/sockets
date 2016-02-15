##########################################################
program_NAME = client
CXXFLAGS+=

##########################################################
### all .c, .cpp and .o
program_SRC_DIRS += ./src/
program_SRCS +=  $(foreach dir,$(program_SRC_DIRS),$(wildcard $(dir)*.c))
program_SRCS +=  $(foreach dir,$(program_SRC_DIRS),$(wildcard $(dir)*.cc))
program_SRCS +=  $(foreach dir,$(program_SRC_DIRS),$(wildcard $(dir)*.cpp))

##########################################################
### -I ./include
###  directory with .h, .hpp
###  include<>
program_INCLUDE_DIRS =
#  include
CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir))

##########################################################
### LINK
### .a .so .lib .dll
# dirs
program_LIBRARY_DIRS =
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))

# links
###  linux:   lib***.a = -l***
###  windows: lib***.lib = -lib***.lib
program_LIBRARIES =

LDFLAGS += $(foreach lib,$(program_LIBRARIES),-l$(lib))


##########################################################
all:
	g++ $(CXXFLAGS) $(program_SRCS) $(LDFLAGS) $(CPPFLAGS) -o $(program_NAME)

run:
	./$(program_NAME)
