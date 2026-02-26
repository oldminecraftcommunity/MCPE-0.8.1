#include <level/ServerLevel.hpp>
#include <entity/Player.hpp>
#include <network/packet/SetTimePacket.hpp>
#include <network/RakNetInstance.hpp>
#include <network/packet/SetHealthPacket.hpp>

ServerLevel::ServerLevel(LevelStorage* a2, const std::string& a3, const LevelSettings& a4, int32_t a5, Dimension* a6)
	: Level(a2, a3, a4, 0, a5, a6) {
	this->_allPlayersSleeping = 0;
}
bool_t ServerLevel::allPlayersSleeping() {
	if(!this->_allPlayersSleeping || this->isClientMaybe) return 0;
	for(auto&& p: this->playersMaybe) {
		if(!p->isSleepingLongEnough()) return 0;
	}
	return 1;
}
void ServerLevel::awakenAllPlayers() {
	if(!this->allPlayersSleeping()) { //inlined
		if(this->_allPlayersSleeping) {
			this->levelEvent(0, 9800, 0, 0, 0, 0);
			for(auto&& p: this->playersMaybe) {
				p->setAllPlayersSleeping();
			}
		}
	}
}
ServerLevel::~ServerLevel() {
}
void ServerLevel::tick() {
	Level::tick();
	if(this->allPlayersSleeping()) {
		int32_t v2 = this->levelData.getTime() + 19200;
		this->levelData.setTime(v2 - v2 % 19200);
		int32_t v5 = this->levelData.getTime();
		bool_t v4 = (uint32_t)this->levelData.stopTime >> 31;
		SetTimePacket v7(v5, v4);
		this->rakNetInstance->send(v7);
		this->awakenAllPlayers();
	}
}
void ServerLevel::updateSleepingPlayerList() {
	for(auto&& p: this->playersMaybe) {
		if(p->isSleeping()) {
			p->stopSleepInBed(0, 0, 1);
			p->health = p->prevHealthMaybe = 20;
		}
	}
	SetHealthPacket v6(20);
	this->rakNetInstance->send(v6);
}
