#     __________                                                 
#   _/ Makefile \________________________________________________________________________ 
#  |                                                                                     \
#  |  COP3530 Project_03                                                Build Automation |
#  |  2022.08.01                                                                         |
#  |                                                                                     |
#  |  SUMMARY:     This is a build automation script that streamlines the debug, test,   |
#  |                    and release process.                                             |
#  |                                                                                     |
#  |               NOTICE:                                                               |
#  |                    a. All commands must be entered in the project root directory!   |
#  |                    b. More filters and sources files can be created; however,       |
#  |                       it is recommended to use extra header files only.             |
#  |                    c. Windows and *nix (Default) support via comment ommitting.     |
#  |                                                                                     |
#  |               Basic work flow:                                                      |
#  |                    1. Compose Source Code                                           |
#  |                    2. Debug Build via 'make' or 'make build_debug'                  |
#  |                    3. Run Debug Build via 'run_d'                                   |
#  |                    4. Test Build via 'make build_test'                              |
#  |                    5. Run All Tests via 'make run_t;                                |
#  |                         5.1. Filter GUI Tests via 'make test_gui'                   |
#  |                         5.2. Filter TRIE Tests via 'make test_trie'                 |
#  |                         5.3. Filter MAP Tests via 'make test_map'                   |
#  |                    6. Release Build via 'make build_release'                        |
#  |                                                                                     |
#  |                                                                                     |
#  |   AUTHOR:     Jack.Exe                                                              |
#  |                                                                                     |
#  \_____________________________________________________________________________________|
 
CXX= g++


#### FILE PATH(S) ####

SOURCE= ./src/*.cpp

# INCLUDE_PATH= -I./include
INCLUDE_PATH= -I.\include

# LIBRARY_PATH= -L./lib
LIBRARY_PATH= -L.\lib

# INCLUDE_PATH= -IC:\MinGW\include
# 
# LIBRARY_PATH= -LC:\MinGW\lib



#### PROGRAM FLAG(S) ####

# DEBUG_FLAGS= -std=c++14 -Wextra -Wall -Wa,-mbig-obj -pedantic -g3 # Windows Support
DEBUG_FLAGS= -std=c++14 -Wextra -Wall -pedantic -g3 # *nix Support

# RELEASE_FLAGS= -std=c++14 -O3 -Wa,-mbig-obj
RELEASE_FLAGS= -std=c++14 -Wl,-subsystem,windows -O3 # *nix Support

LINKER_FLAGS= -lsfml-graphics -lsfml-window -lsfml-system



#### FILE NAME(S) ####

DEBUG_NAME= ./bin/main_debug

TEST_NAME= ./bin/test

RELEASE_NAME= ./main_release



#### BUILD TARGET(S) ####

build_debug:
	$(CXX) $(SOURCE) $(INCLUDE_PATH) $(LIBRARY_PATH) $(DEBUG_FLAGS) $(LINKER_FLAGS) -o $(DEBUG_NAME)

build_test:
	$(CXX) ./test/test.cpp $(INCLUDE_PATH) $(LIBRARY_PATH) $(DEBUG_FLAGS) $(LINKER_FLAGS) -o $(TEST_NAME)

build_release:
	$(CXX) $(SOURCE) $(INCLUDE_PATH) $(LIBRARY_PATH) $(RELEASE_FLAGS) $(LINKER_FLAGS) -o $(RELEASE_NAME)



#### RUN TARGET(S) ####

run_d:
	$(DEBUG_NAME)

run_t:
	$(TEST_NAME)

run_r:
	$(RELEASE_NAME)



#### TEST TARGET(S) ####

test_all:
	$(TEST_NAME)

test_gui:
	 $(TEST_NAME) "[gui]"

test_trie:
	$(TEST_NAME) "[trie]"

test_map:
	$(TEST_NAME) "[map]"



#### CLEAN TARGET ####

# clean: # Windows Support
# 	del .\bin\*.exe
# 	del .\bin\*.o

clean: # *nix Support
	rm ./bin/*
