#include <ExternalServerFile.hpp>
#include <sstream>
#include <string.h>
#include <vector>
#include <stdlib.h>

ExternalServerFile::ExternalServerFile(const std::string& a2) {
	this->fileName = a2 + "/external_servers.txt";
}
void ExternalServerFile::addServer(const std::string& a2, const std::string& a3, int32_t a4) {
	int32_t i;
	for(i = 1; i <= 59999 && this->servers.find(i) != this->servers.end(); ++i) {
	}

	{
		ExternalServer v10(i, a2, a3, a4);
		ExternalServer v12(v10);
		this->servers[i] = v12;
		//~v12, ~v10
	}
	this->save();
}
void ExternalServerFile::editServer(int32_t a2, const std::string& a3, const std::string& a4, int32_t a5) {
	auto v8 = this->servers.find(a2);
	if(v8 != this->servers.end()) {
		v8->second.ip = a3;
		v8->second.ip = a4;
		v8->second.port = a5;
	}
	this->save();
}
std::unordered_map<int32_t, ExternalServer>* ExternalServerFile::getExternalServers() {
	return &this->servers;
}
void ExternalServerFile::load() {
	FILE* v4 = fopen(this->fileName.c_str(), "r");
	if(v4) {
		char_t s[128];
		while(fgets(s, 128, v4)) {
			if(strlen(s) > 2) {
				std::stringstream v15(s);
				std::vector<std::string> v11;
				while(!v15.eof()) { //TODO check
					std::string v13;
					std::getline(v15, v13, ':');
					unsigned int last_not_of = v13.find_last_not_of(" \n\r\t", -1u);
					v13.erase(last_not_of + 1, -1u);
					if(v13 == "") {
						break;
					}

					v11.push_back(v13);
				}

				if(v11.size() == 4) {
					int v6 = strtol(v11[0].c_str(), 0, 0);
					std::string v8 = v11[1];
					std::string v9 = v11[2];
					int v7 = strtol(v11[3].c_str(), 0, 0);
					if(v7 && v6){
						this->servers.insert({v6, ExternalServer(v6, v8, v9, v7)}); //TODO check
					}
				}
			}
		}

		fclose(v4);
	}
}
void ExternalServerFile::removeSevrer(int32_t i) {
	auto v8 = this->servers.find(i);
	if(v8 != this->servers.end()) {
		this->servers.erase(v8);
	}
	this->save();
}

void ExternalServerFile::save() {
	FILE* v2 = fopen(this->fileName.c_str(), "w");
	if(v2) {
		for(auto& it: this->servers) {
			ExternalServer v5(it.second);
			fprintf(v2, "%d:%s:%s:%d\n", v5.id, v5.name.c_str(), v5.ip.c_str(), v5.port);
		}
		fclose(v2);
	}
}
