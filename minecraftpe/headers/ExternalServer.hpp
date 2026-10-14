#pragma once
#include <_types.h>
#include <string>

struct ExternalServer
{
	int32_t id;
	std::string name, ip;
	int32_t port;

	ExternalServer() {
	}
	ExternalServer(const ExternalServer& a2) {
		this->id = a2.id;
		this->name = a2.name;
		this->ip = a2.ip;
		this->port = a2.port;
	}
	ExternalServer(int32_t a2, const std::string& a3, const std::string& a4, int32_t a5) {
		this->id = a2;
		this->name = a3;
		this->ip = a4;
		this->port = a5;
	}
	//~ExternalServer();
};
