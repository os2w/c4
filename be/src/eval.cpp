#include "eval.h"

book::book(const char* fn) {
	std::ifstream i(fn);

	if(!i.fail()) {
		std::size_t sz = 0;

		i.read(reinterpret_cast<char*>(&sz), sizeof(std::size_t));

		for(std::size_t n = 0; n < sz; n++) {
			u64 key;
			int score;
	
			i.read(reinterpret_cast<char*>(&key), sizeof(key));
			i.read(reinterpret_cast<char*>(&score), sizeof(score));
			table[key] = score;
		}

#ifndef NOOUT
		std::cerr << "loaded opening book" << std::endl;
#endif
	} else {
#ifndef NOOUT
		std::cerr << "no opening book found" << std::endl;
#endif
	}

	i.close();
}

cache::cache(std::size_t sz) : size(sz), table(size) {
	
}

cache::cache(const char* fn) {
	std::ifstream i(fn);

	if(!i.fail()) {
		std::size_t sz = 0;
		i.read(reinterpret_cast<char*>(&sz), sizeof(sz));
		size = sz;

		table.resize(size);

		for(std::size_t n = 0; n < sz; n++) {
			table[n].deserialize(i); 
		}
#ifndef NOOUT
		std::cerr << "loaded cache" << std::endl;
#endif
	} else {
		size = CSIZE;
		table.resize(size);
#ifndef NOOUT
		std::cerr << "no cache was loaded" << std::endl;
#endif
	}

	i.close();
}

bool cache::valid(u64 key) {
	return table[key % size].key == key;
}

void cache::set(u64 key, entry e) {
	e.key = key;
	table[key % size] = e;
}

entry cache::get(u64 key) {
	u64 idx = key % size;
	if(table[idx].key == key) return table[idx];
	else return entry{};
}

void cache::write(std::ostream& o) {
	o.write(reinterpret_cast<char*>(&size), sizeof(size));
	for(std::size_t n = 0; n < size; n++) {
		table[n].serialize(o);
	}
}

eval::eval() : movebook("c4book"), table("c4cache") {
	
}

std::vector<std::pair<u64, int>> eval::moves(bool& w, board_t b) {
	std::vector<std::pair<u64, int>> mv;
	u64 U = (b.moves & 1) ? b.b : b.r;
	u64 all = (b.r|b.b);

	w = false;
	for(int i : {3,4,2,1,5,6,0}) {
		u64 v = ((b.r|b.b) >> (7*i)) & 0x3f;
		if(v++==0x3f) continue;
		v <<= (7*i);
		mv.push_back(std::make_pair(v, scorepos(U|v, all)));
		if(win(U|v)) { w = true; return mv; }
	}

	std::sort(mv.begin(), mv.end(), 
		[&](std::pair<u64, int> m1, std::pair<u64, int> m2) {
			return m1.second > m2.second;
		}
	);

	return mv;
}

int eval::negamax(board_t b, int alpha, int beta) {
	u64 h = hash(b);
	int oalpha = alpha;
	const int ops = (SIZE-(b.moves+1))/2+1;

	total++;

	auto o = movebook.table.find(h);
	if(o != movebook.table.end()) return o->second;

	if(alpha < -ops) return -ops;
	if(beta > ops) return ops;

	if(b.moves == SIZE) return 0;

	if(!pnm(b)) return -(SIZE-b.moves)/2;

	bool w = false;
	std::vector<std::pair<u64,int>> mvs = moves(w, b);

	if(w) return ops;

	if(table.valid(h)) {
		entry e = table.get(h);
		if(e.key == h) {	
			switch(e.flag) {
			case LOWER: alpha = std::max(alpha, e.value); break;
			case UPPER: beta = std::min(beta, e.value); break;
			}

			if(alpha >= beta) return e.value;
		}
	}

	seen++;

	int value = -SIZE;
	for(auto mv : mvs) {
		u64 m = mv.first;
		if((b.moves++ & 1)) b.b |= m;
		else b.r |= m;

		value = std::max(value, -negamax(b, -alpha-1, -alpha));	

		if((--b.moves & 1)) b.b &= ~m;
		else b.r &= ~m;

		alpha = std::max(alpha, value);
		if(alpha >= beta) break;
	}

	entry e{};
	if(value <= oalpha) e.flag = UPPER;
	else if(value >= beta) e.flag = LOWER;
	e.value = value;
	table.set(h, e);

	return value;
}

int eval::score(board_t b) {
	int min = -(SIZE-b.moves-1)/2-4;
	int max = -min;

	while(min < max) {
		int med = min + (max - min) / 2;
		if(med <= 0 && min/2 < med) med = min/2;
		else if(med >= 0 && max/2 > med) med = max/2;
		int r = negamax(b, med, med+1);
		if(r <= med) max = r;
		else min = r;
	}

	return min;
}
