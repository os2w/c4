#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>
#include <cstring>
#include <string>
#include <vector>
#include <utility>
#include <climits>
#include <algorithm>
#include <functional>
#include <map>
#include <list>
#include <chrono>

#define WIDTH 7
#define HEIGHT 6
#define SIZE (WIDTH*HEIGHT)

#define EXACT 0
#define UPPER 1
#define LOWER 2

typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef struct board {
	u64 r;
	u64 b;
	int moves;
} board_t;

struct entry {
	int flag;
	int value;
	u64 key;	

	std::ostream& serialize(std::ostream& o) {
		o.write(reinterpret_cast<char*>(&flag), sizeof(flag));
		o.write(reinterpret_cast<char*>(&value), sizeof(value));
		o.write(reinterpret_cast<char*>(&key), sizeof(key));

		return o;
	}

	std::istream& deserialize(std::istream& i) {
		i.read(reinterpret_cast<char*>(&flag), sizeof(flag));
		i.read(reinterpret_cast<char*>(&value), sizeof(value));
		i.read(reinterpret_cast<char*>(&key), sizeof(key));

		return i;
	}
};
