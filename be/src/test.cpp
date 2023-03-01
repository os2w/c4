#include "test.h"

void test::testone(int& good, int& bad, std::string s) {
	std::vector<std::string> toks;
	std::istringstream is(s);
	std::copy(
		std::istream_iterator<std::string>(is),
		std::istream_iterator<std::string>(),
		std::back_inserter(toks));
	int score = std::atoi(toks[1].c_str());
	board_t b{0,0,0};

	for(char c : toks[0])
		drop(b, c - '1');

	auto t1 = clock::now();
	int sc = ev.score(b);
	auto t2 = clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
	float opt = (float)(ev.seen)/(float)(ev.total); 
	std::cout << toks[0] << " " << sc << " " << score << " " << (sc==score?"ok":"bad");
	std::cout << " (seen: " << ev.seen << ", time: " << duration << " ms, opt: " << opt << "%)" << std::endl;

	savg += ev.seen;
	tavg += duration;

	if(sc == score) good++;
	else bad++;
}

void test::testall() {
	int good=0, bad=0;

	std::string s;
	while(std::getline(std::cin, s)) {
		testone(good, bad, s);
		ev.seen = ev.total = 0;
	}

	std::cout << "avg time per solve: " <<
		((float)tavg/(float)(good+bad)) << " ms" <<
		"\navg nodes seen per solve: " <<
		((float)savg/(float)(good+bad)) << " nodes" << std::endl;

	std::cout << "passes: " << good << 
		"\nfails: " << bad << 
		"\ngrade: " << ((float)good/(float)(good+bad))*100 << "%" << std::endl;

	std::ofstream o("c4cache");
	ev.table.write(o);
	o.close();
}
