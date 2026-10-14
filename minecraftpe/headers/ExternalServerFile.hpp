#pragma once
#include <ExternalServer.hpp>
#include <string>
#include <unordered_map>

struct ExternalServerFile
{
	std::unordered_map<int32_t, ExternalServer> servers;
	std::string fileName;

	ExternalServerFile(const std::string&);
	void addServer(const std::string&, const std::string&, int32_t);
	void editServer(int32_t, const std::string&, const std::string&, int32_t);
	std::unordered_map<int32_t, ExternalServer>* getExternalServers();
	void load();
	void removeSevrer(int32_t);
	void save();
};
