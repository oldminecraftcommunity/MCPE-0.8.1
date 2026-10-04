#include <network/CommandServer.hpp>
#include <entity/CameraEntity.hpp>
#include <entity/LocalPlayer.hpp>
#include <Minecraft.hpp>
#include <network/RakNetInstance.hpp>
#include <level/Level.hpp>
#include <network/ConnectedClient.hpp>
#include <nbt/Tag.hpp>
#include <ICreator.hpp>
#include <network/ConnectedClient.hpp>
#include <network/packet/AdventureSettingsPacket.hpp>
#include <level/chunk/LevelChunk.hpp>
#include <string.h>
#include <errno.h>

std::string CommandServer::Ok = "\n", CommandServer::Fail = "Fail\n";
CommandServer::CommandServer(Minecraft* a2) :
	initialized(0), _socket(0), minecraft(a2), checkpoint(0),
	checkpointXCenter(0), checkpointYStart(0), checkpointZCenter(0){

	this->camera = new CameraEntity(a2->level);
	TilePos res = a2->level->getSharedSpawnPos();
	this->posTranslator.x = -res.x;
	this->posTranslator.y = -res.y;
	this->posTranslator.z = -res.z;
}
void CommandServer::_close() {
	if(this->initialized) {
		if(this->_socket > 0) {
#ifdef __WIN32__
			closesocket(this->_socket);
#else
			close(this->_socket);
#endif
		}
		this->initialized = 0;
		this->_socket = 0;
	}
}

static bool setNonBlocking(int a1){
	int v2; // r2
#ifdef _WIN32
	unsigned long mode = 1;
	return (ioctlsocket(a1, FIONBIO, &mode) == 0);
#else
	v2 = fcntl(a1, F_GETFL, 0);
	return v2 >= 0 && fcntl(a1, F_SETFL, v2 | O_NONBLOCK) == 0;
#endif
}

void CommandServer::_updateAccept(){
	int sock = accept(this->_socket, 0, 0);
	if(sock == -1) {
		int v4 = errno;
	} else {
		if(sock >= 0) {
			setNonBlocking(sock);
		}
		this->connected.emplace_back(ConnectedClient(sock));
		this->connected.back().time = this->minecraft->level->getTime();
	}
}
static std::string _CommandServer_success;
static char _updateClient_buf[2];
bool CommandServer::_updateClient(ConnectedClient& client){
	int v3 = 33;
	std::string v20;
skip_return:
	while(--v3){
		if(client.field_4.size()) {
			memcpy(_updateClient_buf, client.field_4.c_str(), client.field_4.size());
			client.field_4.clear();
		}
		bool iret;
		char v19;
		int recvs = 1023;
start_loop:
		while(1) {
			int v8 = recv(client.sock, &v19, 1, 0);
			int err;
			if(v8 == 1) {
				_updateClient_buf[0] = v19;
				_updateClient_buf[1] = 0;
				if(v19 == '\n') {
					std::string v21 = this->parse(client, v20);
					if(_CommandServer_success != v21) {
						const char* str = v21.c_str();
						int toSend = v21.size();
						while(toSend) {
							int sent = send(client.sock, str, toSend, 0);
							if(sent <= 0) {
								int err2 = errno;
								if(err2 != 4) {
									if(err2 == 11) break;
									return 0;
								}
								sent = 0;
							}
							toSend -= sent;
							str += sent;
						}
					}
					goto skip_return;
				}
				goto skip_error;
			} else if(v8 == 0) {
				iret = 1;
				break;
			} else if(v8 != -1) {
				iret = 0;
				break;
			}

			err = errno;
			if(err != 4) {
				iret = err != 11;
				break;
			}
skip_error:
			if(--recvs == 0) {
				iret = 0;
				break;
			}
		}
		client.field_4 = _updateClient_buf;
		return !iret;
	}

	return 1;
}
void CommandServer::_updateClients(){
	int v2 = this->connected.size() - 1;
	while(v2 >= 0) {
		if(!this->_updateClient(this->connected[v2])) {
			this->connected.pop_back();
		}
		--v2;
	}
}
void CommandServer::dispatchPacket(Packet& a2) {
	if(this->minecraft->serverSideNetworkHandler) {
		if(this->minecraft->player) {
			this->minecraft->rakNetInstance->send(a2);
		}
	}
}
bool CommandServer::handleCheckpoint(bool load) {
	if(!this->checkpoint) {
		if(load) {
			return 0;
		}
		this->checkpoint = new uint8_t[0xBB00u];
	}

	int offset = 0;
	for(int z = this->checkpointZCenter - 2; z <= this->checkpointZCenter + 2; ++z) {
		for(int x = this->checkpointXCenter - 2; x <= this->checkpointXCenter + 2; ++x) {
			LevelChunk* c = this->minecraft->level->getChunk(x, z);
			if(c) {
				int o = offset;
				offset += 30720;
				if(load) {
					c->setBlocksAndData(this->checkpoint, 0, this->checkpointYStart, 0, 16, this->checkpointYStart + 48, 16, o);
				} else {
					c->getBlocksAndData(this->checkpoint, 0, this->checkpointYStart, 0, 16, this->checkpointYStart + 48, 16, o);
				}
			}
		}
	}
	return 1;
}
std::string CommandServer::handleEventPollMessage(ConnectedClient& client, const std::string& event) {
	ICreator* creator = this->minecraft->getCreator();
	if(!creator) {
		return CommandServer::Fail;
	}
	if(std::operator==(event, "events.clear")) {
		int time = this->minecraft->level->getTime();
		client.time = time;
		return _CommandServer_success;
	}
	if(!std::operator==(event, "events.block.hits")) {
		return CommandServer::Fail;
	}
	std::stringstream st;
	creator->getEventList()->write(st, this->posTranslator, client.time);
	client.time = this->minecraft->level->getTime();
	st << "\n";
	return st.str();

}

void updateAdventureSettingFlag(Minecraft* mc, AdventureSettingsPacket::Flags flag, bool value) {
	AdventureSettingsPacket v10;
	v10.flags = 0;
	v10.set(AdventureSettingsPacket::AS_ALLOW_INTERACT, mc->level->adventureSettings.allowInteract);
	v10.set(AdventureSettingsPacket::AS_ENABLE_PVP, mc->level->adventureSettings.enablePVP);
	v10.set(AdventureSettingsPacket::AS_ENABLE_PVE, mc->level->adventureSettings.enablePVE);
	v10.set(AdventureSettingsPacket::AS_FIELD_3, mc->level->adventureSettings.field_3);
	v10.set(AdventureSettingsPacket::AS_NO_DAYLIGHT_CYCLE, mc->level->adventureSettings.daylightCycle);
	v10.set(AdventureSettingsPacket::AS_FIELD_5, mc->level->adventureSettings.field_5);
	v10.set(flag, value);
	mc->level->adventureSettings.allowInteract = v10.flags & 1;
	mc->level->adventureSettings.enablePVP = (v10.flags & 2) != 0;
	mc->level->adventureSettings.enablePVE = (v10.flags & 4) != 0;
	mc->level->adventureSettings.field_3 = (v10.flags & 8) != 0;
	mc->level->adventureSettings.field_5 = (v10.flags & 32) != 0;
	mc->level->adventureSettings.daylightCycle = ((v10.flags ^ 16) & 16) != 0;
	mc->rakNetInstance->send(v10);
}

std::string CommandServer::handleSetSetting(const std::string& a2, int32_t a3) {
	bool v5 = a3 ? 1 : 0;
	if(a2 == "autojump") this->minecraft->player->allowAutojump = a3;
	if(a2 == "nametags_visible"){
		updateAdventureSettingFlag(this->minecraft, AdventureSettingsPacket::Flags::AS_FIELD_5, v5);
	}
	if(a2 == "world_immutable"){
		updateAdventureSettingFlag(this->minecraft, AdventureSettingsPacket::Flags::AS_ALLOW_INTERACT, v5);
	}
	//the original method might be slightly different?
	return _CommandServer_success; //TODO - figure out what is the actual return here - seems to reference some thing close to Tag::NullString
}
bool CommandServer::init(int16_t a2) {
	this->_close();
	this->_socket = socket(2, 1, 0);
	if(this->_socket < 0) {
		puts("Failed creating socket - 1");
		return 0;
	}
	setNonBlocking(this->_socket);
	memset(&this->field_8, 0, sizeof(this->field_8));
	this->field_8.sin_family = AF_INET;
	this->field_8.sin_port = htons(a2);
	const int v7 = 1;
	setsockopt(this->_socket, SOL_SOCKET, SO_REUSEADDR, (const char*) &v7, sizeof(v7));
	if(bind(this->_socket, (sockaddr*) &this->field_8, sizeof(this->field_8)) < 0){
		puts("Failed binding socket - 2");
		return 0;
	}
	if(listen(this->_socket, 128) < 0){
		puts("Failed listening on socket - 3");
		return 0;
	}
	this->initialized = 1;
	return 1;
}
std::string CommandServer::parse(ConnectedClient&, const std::string&) {
	printf("CommandServer::parse - not implemented\n");
	//TODO implement
	return CommandServer::Fail;
}
int commandServerTick;
void CommandServer::tick() {
	if(this->initialized) {
		this->_updateAccept();
		this->_updateClients();
		++commandServerTick;
		if(this->minecraft->viewEntity == this->camera) {
			this->minecraft->viewEntity->tick();
		}
	}
}
CommandServer::~CommandServer() {
	if(this->camera) delete this->camera;
	if(this->checkpoint) delete[] this->checkpoint;
}
