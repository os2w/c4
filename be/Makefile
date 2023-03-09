CXX := g++
CXXFLAGS := -Wall -Wextra -O3
CXXDBGFLAGS := -g -fsanitize=address
CXXPERFFLAGS := $(CXXFLAGS) -pg

SOLVER_SRC_DIR := ./src
SOLVER_BIN_DIR := ./bin
SOLVER_SRC := $(wildcard $(SOLVER_SRC_DIR)/*.cpp)
SOLVER_BIN_NAME := $(SOLVER_BIN_DIR)/c4
TESTBIN_NAME := $(SOLVER_BIN_DIR)/c4test

BOOK_SRC_DIR := ./book
BOOK_BIN_DIR := ./bin
BOOK_SRC := $(wildcard $(BOOK_SRC_DIR)/*.cpp)
BOOK_BIN_NAME := $(BOOK_BIN_DIR)/makebook

TEST_SH := ./test.sh

CACHE_NAME := c4cache
BOOK_NAME := c4book

.PHONY: solver test debug book clean

default: solver

all: solver test book

solver: $(SOLVER_SRC)
	$(CXX) $(CXXFLAGS) -o $(SOLVER_BIN_NAME) $(SOLVER_SRC)

test: $(SOLVER_SRC)
	$(CXX) -DTESTING $(CXXFLAGS) -o $(TESTBIN_NAME) $(SOLVER_SRC)

noouttest: $(SOLVER_SRC)
	$(CXX) -DNOOUT -DTESTING $(CXXFLAGS) -o $(TESTBIN_NAME) $(SOLVER_SRC)

debug: $(SOLVER_SRC)
	$(CXX) $(CXXDBGFLAGS) -o $(SOLVER_BIN_NAME) $(SOLVER_SRC)

perf: $(SOLVER_SRC)
	$(CXX) -DTESTING $(CXXPERFFLAGS) -o $(TESTBIN_NAME) $(SOLVER_SRC)

book: $(BOOK_SRC)
	$(CXX) $(CXXFLAGS) -o $(BOOK_BIN_NAME) $(BOOK_SRC) $(SOLVER_SRC_DIR)/bits.cpp -I$(SOLVER_SRC_DIR)

clean:
	@$(RM) $(SOLVER_BIN_NAME) $(TESTBIN_NAME) $(BOOK_BIN_NAME) $(CACHE_NAME) $(BOOK_NAME)
