#include <entity/player/SimpleFoodData.hpp>
#include <item/FoodItem.hpp>
#include <entity/Player.hpp>

SimpleFoodData::SimpleFoodData(void) {
	this->currentLevel = 0;
}
void SimpleFoodData::eat(FoodItem* it) {
	this->eat(it->healAmount);
}
void SimpleFoodData::eat(int32_t heal) {
	int32_t v2 = heal + this->currentLevel;
	if(v2 >= 20) this->currentLevel = 20;
	else this->currentLevel = v2;
}
void SimpleFoodData::tick(Player* player) {
	if(this->currentLevel && player->isHurt()) {
		player->heal(this->currentLevel);
		this->currentLevel = 0;
	}
}
