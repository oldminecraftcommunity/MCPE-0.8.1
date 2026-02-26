#pragma once
#include <_types.h>
#include <string>
#include <unordered_map>
#include <ExternalServer.hpp>

struct ExternalServerFile
{
	std::unordered_map<int32_t, ExternalServer> field_0;
	std::string fileName;

	ExternalServerFile(const std::string&);
	void addServer(const std::string&, const std::string&, int32_t);
	void editServer(int32_t, const std::string&, const std::string&, int32_t);
	std::unordered_map<int32_t, ExternalServer>* getExternalServers();
	void load();
	void removeServer(int32_t);
	void save();
};
