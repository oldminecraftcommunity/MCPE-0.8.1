#include <OptionsFile.hpp>
#include <stdlib.h>
#include <sstream>
#include <string.h>

void OptionsFile::save(const std::vector<std::string>& a2) {
	FILE* v3 = fopen(this->filename.c_str(), "w");
	if(v3) {
		for(auto&& s: a2) {
			fprintf(v3, "%s\n", s.c_str());
		}
		fclose(v3);
	}
}
void OptionsFile::setSettingsFolderPath(const std::string& a2) {
	this->filename = a2 + "/options.txt";
}
std::vector<std::string> OptionsFile::getOptionStrings() {
	std::vector<std::string> res;
	FILE* v3 = fopen(this->filename.c_str(), "r");
	if(v3) {
		char s[128];
		while(fgets(s, 128, v3)) {
			if(strlen(s) > 2) {
				std::stringstream v8(s);
				while(!v8.eof()) { //TODO check
					std::string v7;
					std::getline(v8, v7, ':');
					v7.erase(v7.find_last_not_of(" \n\r\t", -1) + 1, -1);
					if(!(v7 == "")) {
						res.push_back(v7);
					}
				}
			}
		}
		fclose(v3);
	}

	return res;
}
