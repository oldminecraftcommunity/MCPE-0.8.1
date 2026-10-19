#pragma once
#include <_types.h>
#include <RakString.h>

struct PingedCompatibleServer
{
	RakNet::RakString field_0;
	RakNet::SystemAddress field_4;
	int32_t field_18;
	int8_t field_1C;

	PingedCompatibleServer(){}
	PingedCompatibleServer(const PingedCompatibleServer& a2) = default;
	PingedCompatibleServer& operator=(const PingedCompatibleServer& a2) = default;
};
