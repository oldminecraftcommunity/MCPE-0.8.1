#include <OptionsFile.hpp>
#include <stdlib.h>

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
std::vector<std::string> OptionsFile::getOptionStrings();
