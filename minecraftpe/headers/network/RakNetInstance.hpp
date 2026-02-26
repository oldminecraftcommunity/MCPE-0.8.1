#pragma once
#include <network/IRakNetInstance.hpp>


struct RakNetInstance : IRakNetInstance{
	RakNet::RakPeer* rakPeerInstance;
	RakNet::RakNetGUID field_8;
	int8_t field_14, field_15, field_16, field_17;
	std::vector<PingedCompatibleServer> serverList;
	bool_t isPingingHostsMaybe;
	int8_t field_25, field_26, field_27;
	int32_t field_28, field_2C;
	bool_t _isServer, loggedIn;
	int8_t field_32, field_33;
	int8_t field_34, field_35, field_36, field_37;

	//TODO
	RakNetInstance();
	int32_t handleUnconnectedPong(const RakNet::RakString&, const RakNet::Packet*, const char_t*, bool_t);

	virtual ~RakNetInstance();
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
