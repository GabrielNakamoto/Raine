#pragma once

#include "Common.h"

namespace Util {

	inline std::string ReadFile(std::string path){
		std::ifstream file(path);
		if(!file.is_open()) {
			std::cout << "Cannot open file with path: " << path << "\n";
		}
		std::string str;
		std::string line;
		while(std::getline(file, line)) {
			str += line + "\n";
		}
		return str;
	}
}
