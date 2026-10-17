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
	ExternalServer(const ExternalServer& a2) = default;
	ExternalServer(ExternalServer&& a2) = default;
	ExternalServer(int32_t a2, const std::string& a3, const std::string& a4, int32_t a5)
		: id(a2)
		, name(a3)
		, ip(a4)
		, port(a5) {
	}

	ExternalServer& operator=(const ExternalServer& server) = default;

};
