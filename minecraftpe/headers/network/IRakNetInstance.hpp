#pragma once
#include <_types.h>
#include <string>
#include <RakPeer.h>
#include <vector>
#include <network/PingedCompatibleServer.hpp>
struct Packet;
struct NetEventCallback;
struct IRakNetInstance
{
	virtual ~IRakNetInstance();
	virtual bool_t host(const std::string&, int32_t, int32_t);
	virtual bool_t connect(const char_t*, int32_t);
	virtual void setIsLoggedIn(bool_t);
	virtual void pingForHosts(int32_t);
	virtual void stopPingForHosts();
	virtual std::vector<PingedCompatibleServer>* getServerList();
	virtual void clearServerList();
	virtual void disconnect();
	virtual void announceServer(const std::string&);
	virtual RakNet::RakPeer* getPeer();
	virtual bool_t isMyLocalGuid(const RakNet::RakNetGUID&);
	virtual void runEvents(NetEventCallback*);
	virtual void send(Packet&);
	virtual void send(const RakNet::RakNetGUID&, Packet&);
	virtual void send(Packet*);
	virtual void send(const RakNet::RakNetGUID&, Packet*);
	virtual bool_t isServer();
	virtual bool_t isProbablyBroken();
	virtual void resetIsBroken();
};
