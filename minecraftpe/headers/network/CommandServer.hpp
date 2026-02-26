#pragma once
#include <_types.h>
#include <vector>
#include <string>
#include <util/OffsetPosTranslator.hpp>
#include <sys/socket.h>

struct ConnectedClient;
struct Minecraft;
struct CameraEntity;
struct Packet;
struct CommandServer
{
	static std::string Ok, Fail;
	bool_t initialized;
	int8_t field_1, field_2, field_3;
	int32_t _socket;
	sockaddr field_8;
	Minecraft* minecraft;
	OffsetPosTranslator posTranslator;
	int32_t* checkpoint;
	int32_t field_30, field_34, field_38;
	CameraEntity* camera;
	std::vector<ConnectedClient> connected;

	CommandServer(Minecraft*);
	void _close();
	void _updateAccept();
	bool_t _updateClient(ConnectedClient&);
	void _updateClients();
	void dispatchPacket(Packet&);
	bool_t handleCheckpoint(bool_t);
	void handleEventPollMessage(ConnectedClient&, const std::string&);
	std::string handleSetSetting(const std::string&, int32_t);
	bool_t init(int16_t);
	std::string parse(ConnectedClient&, const std::string&);
	void tick();
	~CommandServer();
};
