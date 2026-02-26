#pragma once
#include <_types.h>
#include <RakString.h>

struct PingedCompatibleServer
{
	RakNet::RakString field_0;
	RakNet::SystemAddress field_4;
	int32_t field_18;
	int8_t field_1C, field_1D, field_1E, field_1F;
	PingedCompatibleServer();
	PingedCompatibleServer(const PingedCompatibleServer&);
	PingedCompatibleServer& operator=(const PingedCompatibleServer&);
};
