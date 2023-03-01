#include "test.h"

int main(int argc, char** argv)
{
#ifdef TESTING
	(void)argc; (void)argv;
	test te;
	te.testall();
#else
	if(argc != 4) {
		std::cerr << "usage: " << argv[0] << " [red board] [blue board] [num moves]" << std::endl;
		return 0;
	}

	eval ev;
	u64 r = std::strtoull(argv[1], NULL, 10);
	u64 b = std::strtoull(argv[2], NULL, 10);
	int moves = std::atoi(argv[3]);

	board_t bo{r,b,moves};

	int score = ev.score(bo);
	std::cout << r << " " << b << " " << score << std::endl;
#endif

	return 0;
}
