#pragma once
#include <_types.h>
#include <vector>
#include <string>
#include <util/OffsetPosTranslator.hpp>
#ifdef __WIN32__
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif
struct ConnectedClient;
struct Minecraft;
struct CameraEntity;
struct Packet;
struct CommandServer
{
	static std::string Ok, Fail;
	bool_t initialized;
	int32_t _socket;
	sockaddr_in field_8;
	Minecraft* minecraft;
	OffsetPosTranslator posTranslator;
	uint8_t* checkpoint;
	int32_t checkpointXCenter, checkpointYStart, checkpointZCenter;
	CameraEntity* camera;
	std::vector<ConnectedClient> connected;

	CommandServer(Minecraft*);
	void _close();
	void _updateAccept();
	bool _updateClient(ConnectedClient&);
	void _updateClients();
	void dispatchPacket(Packet&);
	bool handleCheckpoint(bool);
	std::string handleEventPollMessage(ConnectedClient&, const std::string&);
	std::string handleSetSetting(const std::string&, int32_t);
	bool init(int16_t);
	std::string parse(ConnectedClient&, const std::string&);
	void tick();
	~CommandServer();
};
