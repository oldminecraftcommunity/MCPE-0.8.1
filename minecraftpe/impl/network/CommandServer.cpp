#include <network/CommandServer.hpp>
#include <entity/CameraEntity.hpp>
#include <entity/LocalPlayer.hpp>
#include <Minecraft.hpp>
#include <network/RakNetInstance.hpp>
#include <level/Level.hpp>
#include <network/ConnectedClient.hpp>
#include <nbt/Tag.hpp>

//not used in 0.8.1, pain to implement
std::string CommandServer::Ok = "\n", CommandServer::Fail = "Fail\n";
CommandServer::CommandServer(Minecraft* a2) {
	this->initialized = 0;
	this->_socket = 0;
	this->minecraft = a2;
	this->checkpoint = 0;
	this->field_30 = 0;
	this->field_34 = 0;
	this->field_38 = 0;
	this->camera = new CameraEntity(a2->level);
	TilePos res = a2->level->getSharedSpawnPos();
	this->posTranslator.x = -res.x;
	this->posTranslator.y = -res.y;
	this->posTranslator.z = -res.z;
}
void CommandServer::_close() {
	if(this->initialized) {
		if(this->_socket > 0) {
			close(this->_socket);
		}
		this->initialized = 0;
		this->_socket = 0;
	}
}
void CommandServer::_updateAccept(){
	printf("CommandServer::_updateAccept - not implemented\n");
	//TODO implement
}
bool_t CommandServer::_updateClient(ConnectedClient&){

	printf("CommandServer::_updateClient - not implemented\n");
	//TODO implement
	return 0;
}
void CommandServer::_updateClients(){

	printf("CommandServer::_updateClients - not implemented\n");
	//TODO implement
}
void CommandServer::dispatchPacket(Packet& a2) {
	if(this->minecraft->serverSideNetworkHandler) {
		if(this->minecraft->player) {
			this->minecraft->rakNetInstance->send(a2);
		}
	}
}
bool_t CommandServer::handleCheckpoint(bool_t a2){

	printf("CommandServer::handleCheckpoint - not implemented\n");
	//TODO implement
	return 0;
}
void CommandServer::handleEventPollMessage(ConnectedClient&, const std::string&){

	printf("CommandServer::handleEventPollMessage - not implemented\n");
	//TODO implement
}
std::string CommandServer::handleSetSetting(const std::string& a2, int32_t a3) {
	bool_t v5 = a3 ? 1 : 0;
	if(a2 == "autojump") this->minecraft->player->allowAutojump = a3;
	if(a2 == "nametags_visible"){

	}
	//TODO updateAdventureSettingFlag
	printf("CommandServer::handleSetSetting - not implemented\n");
	//TODO implement
	return Tag::NullString;
}
bool_t CommandServer::init(int16_t a2) {
	this->_close();
	this->_socket = socket(2, 1, 0);
	if(this->_socket < 0) {
		puts("Failed creating socket - 1");
		return 0;
	}
	printf("CommandServer::init - not implemented\n");
	//TODO implement
	this->initialized = 1;
	return 0; //1;
}
std::string CommandServer::parse(ConnectedClient&, const std::string&) {
	printf("CommandServer::parse - not implemented\n");
	//TODO implement
	return CommandServer::Fail;
}
void CommandServer::tick() {
	if(this->initialized) {
		this->_updateAccept();
		this->_updateClients();
		if(this->minecraft->viewEntityMaybe == this->camera) {
			this->minecraft->viewEntityMaybe->tick();
		}
	}
}
CommandServer::~CommandServer() {
	if(this->camera) delete this->camera;
	if(this->checkpoint) delete[] this->checkpoint;
}
