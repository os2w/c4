#include "eval.h"

class test {
public:
	eval ev;
	typedef std::chrono::high_resolution_clock clock;

	std::ifstream file;

	std::size_t savg = 0;
	std::size_t tavg = 0;

	void testone(int&, int&, std::string);
	void testall();
};
