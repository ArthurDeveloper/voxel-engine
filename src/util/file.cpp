#include "file.h"

std::string file::read(std::string path) {
    std::ifstream file;
	file.open(path);

	std::stringstream stream;

	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			stream << line << "\n";
		}
		file.close();
	}

	return stream.str();
}