#include <Motive.hpp>

Motive Motive::Kebab("Kebab", 16, 16, 0, 0, 1);
Motive Motive::Aztec("Aztec", 16, 16, 16, 0, 1);
Motive Motive::Alban("Alban", 16, 16, 32, 0, 1);
Motive Motive::Aztec2("Aztec2", 16, 16, 48, 0, 1);
Motive Motive::Bomb("Bomb", 16, 16, 48, 0, 1);
Motive Motive::Plant("Plant", 16, 16, 80, 0, 1);
Motive Motive::Wasteland("Wasteland", 16, 16, 96, 0, 1);
Motive Motive::Pool("Pool", 32, 16, 0, 32, 1);
Motive Motive::Courbet("Courbet", 32, 16, 32, 32, 1);
Motive Motive::Sea("Sea", 32, 16, 32, 32, 1);
Motive Motive::Sunset("Sunset", 32, 16, 96, 32, 1);
Motive Motive::Creebet("Creebet", 32, 16, 128, 32, 1);
Motive Motive::Wanderer("Wanderer", 16, 32, 0, 64, 1);
Motive Motive::Graham("Graham", 16, 32, 16, 64, 1);
Motive Motive::Match("Match", 32, 32, 0, 128, 1);
Motive Motive::Bust("Bust", 32, 32, 32, 128, 1);
Motive Motive::Stage("Stage", 32, 32, 64, 128, 1);
Motive Motive::Void("Void", 32, 32, 96, 128, 1);
Motive Motive::SkullAndRoses("SkullAndRoses", 32, 32, 128, 128, 1);
Motive Motive::Fighters("Fighters", 64, 32, 0, 96, 1);
Motive Motive::Pointer("Pointer", 64, 64, 0, 192, 1);
Motive Motive::Pigscene("Pigscene", 64, 64, 64, 192, 1);
Motive Motive::BurningSkull("BurningSkull", 64, 64, 128, 192, 1);
Motive Motive::Skeleton("Skeleton", 64, 48, 192, 64, 1);
Motive Motive::DonkeyKong("DonkeyKong", 64, 48, 192, 112, 1);
Motive Motive::Earth("Earth", 32, 32, 0, 160, 0);
Motive Motive::Wind("Wind", 32, 32, 32, 160, 0);
Motive Motive::Fire("Fire", 32, 32, 64, 160, 0);
Motive Motive::Water("Water", 32, 32, 96, 160, 0);

Motive* Motive::DefaultImage = &Motive::Kebab;

Motive::Motive(std::string name, int32_t w, int32_t h, int32_t uo, int32_t vo, bool_t isUsed){
	this->name = name;
	this->w = w;
	this->h = h;
	this->uo = uo;
	this->vo = vo;
	this->isUsed = isUsed;
}
std::vector<const Motive*> Motive::getAllMotivesAsList(void) {
	std::vector<const Motive*> vec;
	vec.emplace_back(&Motive::Kebab);
	vec.emplace_back(&Motive::Aztec2);
	vec.emplace_back(&Motive::Alban);
	vec.emplace_back(&Motive::Bomb);
	vec.emplace_back(&Motive::Plant);
	vec.emplace_back(&Motive::Wasteland);
	vec.emplace_back(&Motive::Pool);
	vec.emplace_back(&Motive::Courbet);
	vec.emplace_back(&Motive::Sea);
	vec.emplace_back(&Motive::Sunset);
	vec.emplace_back(&Motive::Creebet);
	vec.emplace_back(&Motive::Wanderer);
	vec.emplace_back(&Motive::Wanderer);
	vec.emplace_back(&Motive::Graham);
	vec.emplace_back(&Motive::Match);
	vec.emplace_back(&Motive::Bust);
	vec.emplace_back(&Motive::Stage);
	vec.emplace_back(&Motive::Void);
	vec.emplace_back(&Motive::SkullAndRoses);
	vec.emplace_back(&Motive::Fighters);
	vec.emplace_back(&Motive::Pointer);
	vec.emplace_back(&Motive::Pigscene);
	vec.emplace_back(&Motive::BurningSkull);
	vec.emplace_back(&Motive::Skeleton);
	vec.emplace_back(&Motive::DonkeyKong);
	vec.emplace_back(&Motive::Earth);
	vec.emplace_back(&Motive::Wind);
	vec.emplace_back(&Motive::Fire);
	vec.emplace_back(&Motive::Water);
	return vec;
}
const Motive* Motive::getMotiveByName(const std::string& a2) {
	std::vector<const Motive*> vec = Motive::getAllMotivesAsList();

	for(auto&& mot: vec) {
		if(mot->name == a2) return mot;
	}

	return Motive::DefaultImage;
}
