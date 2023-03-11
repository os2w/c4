#pragma once

#include "def.h"

int get(u64, int, int);

void pboard(board_t);

void combine(u64&, u64);
u64 hash(board_t);	

void drop(board_t&, int);
bool win(u64);

u64 pwm(u64, u64);
int scorepos(u64, u64);
