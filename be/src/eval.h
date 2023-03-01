#pragma once

#include "def.h"
#include "bits.h"

#ifndef CSIZE
#define CSIZE 8000000
#endif

class book {
public:
	book(const char*);
	
	std::map<u64, int> table;
};

class cache {
public:
	cache(std::size_t);
	cache(const char* fn);

	std::size_t size;

	bool valid(u64);
	void set(u64, entry);
	entry get(u64);

	void write(std::ostream&);

	std::vector<entry> table;
};

class eval {
public:
	eval();
	
	book movebook;
	cache table;

	std::size_t seen = 0;
	std::size_t total = 0;
		
	u64 best(int, board_t);

	int negamax(board_t, int, int);

	int optsearch(board_t);

	int score(board_t);

	std::vector<u64> moves(bool&, board_t);
};
