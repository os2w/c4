#include "bits.h"

int get(u64 board, int x, int y) {
  u64 v = board & ((1ULL << y) << (7 * x));
  return (x < 0 || y < 0) ? 0 : !!v;
}

void pboard(board_t b) {
  int x, y, t1, t2;
  puts("     6   5   4   3   2   1   0  ");
  puts("   +---+---+---+---+---+---+---+");
  for(y = HEIGHT-1; y >= 0; y--) {
    printf("%d  |", y);
    for(x = WIDTH-1; x >= 0; x--) {
      t1=get(b.r,x,y);
      t2=get(b.b,x,y);
      printf(" %c |", (t1 && !t2) ? 'R' : (!t1 && t2) ? 'B' : ' ');
    }
    puts("\n   +---+---+---+---+---+---+---+");
  }
  printf("r: %llX, b: %llX\n",b.r,b.b);
}

void combine(u64& s, u64 k) {
	std::hash<u64> h;
	const u64 mul = 0x9ddfea08eb382d69ULL;
	u64 a = (h(k) ^ s) * mul;
	a ^= (a >> 47);
	u64 b = (s ^ a) * mul;
	b ^= (b >> 47);
	s = b * mul;
}

u64 hash(board_t k) {
	u64 s = 0;
	combine(s, k.r);
	combine(s, k.b);
	return s;
}

void drop(board_t& b, int col) {
	u64 v = ((b.r|b.b) >> (7*col)) & 0x3f;
	if(v++ == 0x3f) return;
	v <<= (7*col);
	if(!(b.moves++ & 1)) b.r |= v;
	else b.b |= v;
}

bool win(u64 b) {
	int d[4] = {1, 7, 6, 8};
	long bb;

	for(int i : d) {
		bb = b & (b >> i);
		if((bb & (bb >> (2*i))) != 0) return true;
	}

	return false;
}

u64 pwm(u64 b, u64 m) {
	u64 r, p;

	r = (b<<1) & (b<<2) & (b<<3); // vertical

#define P(o) \
	p = (b<<(o)) & (b<<2*(o)); \
	r |= p & (b<<3*(o)); \
	r |= p & (b>>(o)); \
	p = (b>>(o)) & (b>>2*(o)); \
	r |= p & (b<<(o)); \
	r |= p & (b>>3*(o));

	P(HEIGHT+1); // horizontal
	P(HEIGHT);   // diagonals
	P(HEIGHT+2); //

	r &= ~m;
	r &= 0xFDFBF7EFDFBFULL;

#undef P

	return r;
}

int scorepos(u64 b, u64 m) {
	u64 r = pwm(b, m);
	return __builtin_popcountll(r);
}
