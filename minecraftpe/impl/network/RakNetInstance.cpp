#include <network/RakNetInstance.hpp>
#include <GetTime.h>
#include <network/MinecraftPackets.hpp>
#include <network/NetEventCallback.hpp>
#include <network/Packet.hpp>

static RakNet::SystemAddress _D6E0A1B0;

RakNetInstance::RakNetInstance() {
	this->rakPeerInstance = 0;
	this->_isServer = 0;
	this->loggedIn = 0;
	this->isPingingHostsMaybe = 0; //XXX doesnt seem to exist in mcpe
	this->rakPeerInstance = (RakNet::RakPeer*)RakNet::RakPeerInterface::GetInstance();
	this->rakPeerInstance->SetTimeoutTime(20000, _D6E0A1B0);
	this->rakPeerInstance->SetOccasionalPing(1);
}
int32_t RakNetInstance::handleUnconnectedPong(const RakNet::RakString& a2, const RakNet::Packet* a3, const char_t* a4, bool_t a5) {
	RakNet::RakString v29(a4);
	int v9;
	if(a2.GetLength() < v29.GetLength() || (v9 = v29.StrCmp(a2.SubStr(0, v29.GetLength())), v9)) {
		v9 = -1;
	} else {
		int v11;
		while(1) {
			if(v9 >= this->serverList.size()) {
				PingedCompatibleServer v31;
				v31.field_4 = a3->systemAddress;
				v31.field_1C = 0;
				v31.field_18 = RakNet::GetTimeMS();
				v31.field_0 = a2.SubStr(v29.GetLength(), a2.GetLength() - v29.GetLength());
				if(a5) {
					this->serverList.insert(this->serverList.begin(), v31); //TODO check
				} else {
					this->serverList.emplace_back(v31);
				}
				v9 = this->serverList.size() - 1;
				return v9;
			}
			v11 = v9;
			if(this->serverList[v9].field_4 == a3->systemAddress) {
				break;
			}
			++v9;
		}

		PingedCompatibleServer* v12 = &this->serverList[v11];
		v12->field_18 = RakNet::GetTimeMS();
		if(a2.GetLength() == v29.GetLength()) {
			v12->field_0 = "";
		} else {
			v12->field_0 = a2.SubStr(v29.GetLength(), a2.GetLength() - v29.GetLength());
		}
	}
	return v9;
}

RakNetInstance::~RakNetInstance() {
	if(this->rakPeerInstance) {
		this->rakPeerInstance->Shutdown(100, 0, LOW_PRIORITY);
		RakNet::RakPeerInterface::DestroyInstance(this->rakPeerInstance);
		this->rakPeerInstance = 0;
	}
}
bool_t RakNetInstance::host(const std::string& a2, int32_t port, int32_t maxConnections) {
	RakNet::RakPeer* rakPeerInstance; // r0
	int32_t v8;						  // r0
	int16_t v11;					  // [sp+32h] [bp-26h]

	if(this->rakPeerInstance->IsActive()) {
		this->rakPeerInstance->Shutdown(500, 0, LOW_PRIORITY);
	}
	RakNet::SocketDescriptor v10(port, 0);
	rakPeerInstance = this->rakPeerInstance;
	v11 = 2;
	rakPeerInstance->SetMaximumIncomingConnections(maxConnections);
	this->rakPeerInstance->SetTimeoutTime(10000u, RakNet::SystemAddress());
	v8 = this->rakPeerInstance->Startup(maxConnections, &v10, 1u, -99999);
	this->_isServer = 1;
	this->isPingingHostsMaybe = 0;
	return v8 == 0;
}
bool_t RakNetInstance::connect(const char_t* a2, int32_t a3) {
	this->loggedIn = 0;
	RakNet::SocketDescriptor v9(0, 0);
	if(this->rakPeerInstance->IsActive()) {
		this->rakPeerInstance->Shutdown(500, 0, PacketPriority::LOW_PRIORITY);
	}
	bool_t v7 = this->rakPeerInstance->Startup(4, &v9, 1);
	this->_isServer = 0;
	this->isPingingHostsMaybe = 0;
	return !v7 && (this->rakPeerInstance->Connect(a2, a3, 0, 0, 0, 0, 12, 500, 10000) == 0);
}
void RakNetInstance::setIsLoggedIn(bool_t a2) {
	this->loggedIn = a2;
}
void RakNetInstance::pingForHosts(int32_t a2) {
	int32_t v4;	 // r5
	uint16_t v5; // r2

	if(!this->rakPeerInstance->IsActive()) {
		RakNet::SocketDescriptor v6(0, 0);
		this->rakPeerInstance->Startup(4u, &v6, 1u, -99999);
	}
	this->field_28 = a2;
	this->isPingingHostsMaybe = 1;
	v4 = 0;
	this->field_2C = RakNet::GetTimeMS();
	do {
		v5 = v4++ + a2;
		this->rakPeerInstance->Ping("255.255.255.255", v5, 0, 0);
	} while(v4 != 4);
}
void RakNetInstance::stopPingForHosts() {
	if(this->isPingingHostsMaybe) {
		this->rakPeerInstance->Shutdown(0, 0, LOW_PRIORITY);
		this->isPingingHostsMaybe = 0;
	}
}
std::vector<PingedCompatibleServer>* RakNetInstance::getServerList() {
	return &this->serverList;
}
void RakNetInstance::clearServerList() {
	this->serverList.clear();
}
void RakNetInstance::disconnect() {
	if(this->rakPeerInstance->IsActive()) {
		this->rakPeerInstance->Shutdown(500);
	}
	this->loggedIn = 0;
	this->_isServer = 0;
	this->isPingingHostsMaybe = 0;
}
void RakNetInstance::announceServer(const std::string& a2) {
	if(this->_isServer) {
		if(this->rakPeerInstance->IsActive()) {
			/*sub start*/
			RakNet::RakString v4;
			v4 += "MCCPP;Demo;";
			v4 += a2.c_str();
			RakNet::BitStream v5;
			v4.Serialize(&v5);
			this->rakPeerInstance->SetOfflinePingResponse((char_t*)v5.GetData(), v5.GetNumberOfBytesUsed());
			/*sub end*/
		}
	}
}
RakNet::RakPeer* RakNetInstance::getPeer() {
	return this->rakPeerInstance;
}
bool_t RakNetInstance::isMyLocalGuid(const RakNet::RakNetGUID& a2) {
	if(this->rakPeerInstance->IsActive()) {
		return this->rakPeerInstance->GetMyGUID() == a2;
	}
	return 0;
}
void RakNetInstance::runEvents(NetEventCallback* a2) {
	while(1) {
		RakNet::Packet* v8 = this->rakPeerInstance->Receive();
		if(!v8) break;
		int pid = v8->data[0];
		RakNet::BitStream v19(v8->data + 1, v8->length - 1, 0);
		if(a2) {
			if(pid > 128) {
				if(pid - 129 <= 3 || this->_isServer && a2->allowIncomingPacketId(v8->guid, pid - 129) || this->loggedIn) {
					Packet* packet = MinecraftPackets::createPacket(pid);
					if(packet) {
						packet->read(&v19);
						packet->handle(v8->guid, a2);
						delete packet;
					}
				}
			} else {
				switch(pid) {
					case 0x10:
						this->field_8 = v8->guid;
						a2->onConnect(v8->guid);
						break;
					case 0x11:
						a2->onUnableToConnect();
						break;
					case 0x13:
						a2->onNewClient(v8->guid);
						break;
					case 0x15:
					case 0x16:
						a2->onDisconnect(v8->guid);
						break;
					case 0x1C:
						{
							RakNet::RakString v18;
							unsigned int v17;
							v19.Read<unsigned int>(v17);
							v18.Deserialize(&v19);
							if(this->handleUnconnectedPong(v18, v8, "MCCPP;Demo;", 0) < 0) {
								int v7 = this->handleUnconnectedPong(v18, v8, "MCCPP;MINECON;", 1);
								if(v7 >= 0) {
									this->serverList[v7].field_1C = 1;
								}
							}
							break;
						}
					default:
						break;
				}
			}
		}
		this->rakPeerInstance->DeallocatePacket(v8);
	}
	if(this->isPingingHostsMaybe) {
		if(RakNet::GetTimeMS() - this->field_2C > 1000) {
			for(auto&& v10 = this->serverList.begin(); v10 != this->serverList.end();) {
				if(RakNet::GetTimeMS() - v10->field_18 <= 3000) {
					++v10;
				} else {
					v10 = this->serverList.erase(v10);
				}
			}
			this->pingForHosts(this->field_28);
		}
	}
}
void RakNetInstance::send(Packet& a2) {
	RakNet::BitStream v14;
	a2.write(&v14);
	if(this->_isServer) {
		RakNet::SystemAddress v13;
		v13 = _D6E0A1B0;
		this->rakPeerInstance->Send(&v14, a2.packetPriorityMaybe, a2.packetReliabilityMaybe, 0, v13, 1, 0);
	} else {
		this->rakPeerInstance->Send(&v14, a2.packetPriorityMaybe, a2.packetReliabilityMaybe, 0, RakNet::AddressOrGUID(this->field_8), 0, 0);
	}
}
void RakNetInstance::send(const RakNet::RakNetGUID& a2, Packet& a3) {
	RakNet::BitStream v11;
	a3.write(&v11);
	this->rakPeerInstance->Send(&v11, a3.packetPriorityMaybe, a3.packetReliabilityMaybe, 0, RakNet::AddressOrGUID(a2), 0, 0);
}
void RakNetInstance::send(Packet* a2) {
	this->send(*a2);
	if(a2) delete a2;
}
void RakNetInstance::send(const RakNet::RakNetGUID& a2, Packet* a3) {
	this->send(a2, *a3);
	if(a3) {
		delete a3;
	}
}
bool_t RakNetInstance::isServer() {
	return this->_isServer;
}

//TODO used instead of field_4 of RakNet::RakPeer
//which does not seem to exist - mojang modifed raknet?
static int32_t _RakPeer_field_4 = 0;

bool_t RakNetInstance::isProbablyBroken() {
	return _RakPeer_field_4 < -100;
}
void RakNetInstance::resetIsBroken() {
	_RakPeer_field_4 = 0;
}
