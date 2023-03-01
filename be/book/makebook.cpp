#include <def.h>
#include <bits.h>

#define BOOKFILE "c4book"

int main(int argc, char** argv) {
	if(argc != 2) {
		std::cerr << "usage: " << argv[0] << " [test file]" << std::endl;
		return 0;
	}

	std::ifstream i(argv[1]);
	std::ofstream o(BOOKFILE);

	if(i.fail()) {
		std::cerr << "failed to open test file " << argv[1] << std::endl;
		i.close();
		o.close();
		return 0;
	}

	if(o.fail()) {
		std::cerr << "could not create file " << BOOKFILE << std::endl;
		i.close();
		o.close();
		return 0;
	}

	i.unsetf(std::ios_base::skipws);
	std::size_t sz = std::count(
		std::istream_iterator<char>(i),
		std::istream_iterator<char>(),
		'\n');

	i.clear();
	i.seekg(0);

	o.write(reinterpret_cast<char*>(&sz), sizeof(sz));

	std::string s;
	while(std::getline(i, s)) {
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

		u64 key = hash(b);

		o.write(reinterpret_cast<char*>(&key), sizeof(key));
		o.write(reinterpret_cast<char*>(&score), sizeof(score));
	}

	std::cout << sz << " entries written in book" << std::endl;

	i.close();
	o.close();
	return 0;
}
