# Constants
CC=g++
CFLAGS=-Wall -Wextra -Werror -std=c++17 -fmax-errors=1
OFLAGS=-O2
LDFLAGS=-lgtest -pthread

# Coverage
GCOVFLAGS=--coverage
GCOV_DIR=gcov

# Directories
SRC_DIR=.
LIB_DIR=lib
CONTROLLER_DIR=controller
VIEW_DIR=view
SRC_DIRS= $(SRC_DIR) $(CONTROLLER_DIR) $(VIEW_DIR)
TEST_DIR=tests
OBJ_DIR=obj
OBJ_DIR_GCOV=$(OBJ_DIR)/$(GCOV_DIR)
OBJ_DIR_TEST=$(OBJ_DIR)/$(TEST_DIR)

# Files
SRCS=$(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/s21_*.cc))
OBJS=$(patsubst %.cc,$(OBJ_DIR)/%.o,$(notdir $(SRCS)))
SRCS_TEST=$(wildcard $(TEST_DIR)/s21_*.cc)
OBJS_TEST=$(patsubst $(TEST_DIR)/%.cc,$(OBJ_DIR_TEST)/%.o,$(SRCS_TEST))
OBJS_GCOV=$(patsubst %.cc, $(OBJ_DIR_GCOV)/%.o, $(notdir $(SRCS_TEST)))
LIBS_SRCS=$(wildcard $(LIB_DIR)/s21_*.cc)
LIBS_OBJS=$(patsubst $(LIB_DIR)/%.cc,$(OBJ_DIR)/%.o,$(LIBS_SRCS))
LIBS_OBJS_GCOV=$(patsubst $(LIB_DIR)/%.cc,$(OBJ_DIR_GCOV)/%.o,$(LIBS_SRCS))
LIBS=$(patsubst $(LIB_DIR)/%.cc,%.a,$(LIBS_SRCS))
CLANG_FILES=$(shell find $(SRC_DIR) \( -name "s21_*.cc" -o -name "s21_*.h" \) -print)

# Builds
PROGRAM=s21_Navigator
TEST=test
TEST_GCOV=$(TEST)_gcov
TEST_BUILD=$(TEST)_build
TEST_BUILD_GCOV=$(TEST_BUILD)_gcov

VPATH=$(TEST_DIR):$(SRC_DIRS):$(LIB_DIR)

.PHONY: all $(PROGRAM) $(TEST) $(TEST_BUILD) gcov_report clean clean_gcda rebuild clang_n clang_i valgrind valgrind_mac

all: $(PROGRAM)

open: $(PROGRAM)
	./$< || true

# Main program build
$(PROGRAM): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) $(OFLAGS) $^ -o $(PROGRAM)

$(SRC_DIR)/%.a: $(OBJ_DIR)/%.o
	ar rcs $@ $<

$(OBJ_DIR)/%.o: %.cc
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@

# Tests build
$(TEST): $(TEST_BUILD)
	./$@ || true

$(TEST_BUILD): $(LIBS_OBJS) $(OBJS_TEST)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(OFLAGS) -o $(TEST)

$(OBJ_DIR_TEST)/%.o: %.cc
	@mkdir -p $(OBJ_DIR_TEST)
	$(CC) $(CFLAGS) $(OFLAGS) -c $< -o $@

$(TEST_GCOV): $(TEST_BUILD_GCOV)
	$(MAKE) clean_gcda
	./$@ || true

$(TEST_BUILD_GCOV): $(LIBS_OBJS_GCOV) $(OBJS_GCOV)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) $(GCOVFLAGS) -o $(TEST_GCOV)

$(OBJ_DIR_GCOV)/%.o: %.cc
	@mkdir -p $(OBJ_DIR_GCOV)
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $< -o $@

# Other rules
gcov_report: $(TEST_GCOV)
	mkdir -p $(GCOV_DIR)
	gcovr --html-details -o $(GCOV_DIR)/index.html --filter $(LIB_DIR)/s21_\.\*.cc
	open $(GCOV_DIR)/index.html

lcov_report: $(TEST_GCOV)
	mkdir -p $(GCOV_DIR)
	lcov --capture --directory $(SRC_DIR) --include "$(CURDIR)/$(LIB_DIR)/*.cc" --output-file $(GCOV_DIR)/coverage.info --no-external
	genhtml -o $(GCOV_DIR) $(GCOV_DIR)/coverage.info 
	open $(GCOV_DIR)/index.html

clean:
	rm -rf $(OBJ_DIR) $(GCOV_DIR) $(TEST) $(TEST_GCOV) $(LIBS) $(PROGRAM)

clean_gcda:
	rm -rf $(OBJ_DIR_GCOV)/*.gcda

rebuild: clean all

clang_n:
	clang-format -n --style=Google $(CLANG_FILES)

clang_i:
	clang-format -i --style=Google $(CLANG_FILES)

valgrind: $(TEST_BUILD)
	valgrind --tool=memcheck --leak-check=yes ./$(TEST)

valgrind_mac: $(TEST_BUILD)
	leaks -atExit -- ./$(TEST) | grep LEAK:
