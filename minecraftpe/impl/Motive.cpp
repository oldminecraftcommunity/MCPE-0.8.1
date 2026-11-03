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

Motive::Motive(std::string name, int32_t w, int32_t h, int32_t uo, int32_t vo, bool_t isUsed) : name(name), w(w), h(h), uo(uo), vo(vo), isUsed(isUsed){

}
std::vector<const Motive*> Motive::getAllMotivesAsList(void) {
	std::vector<const Motive*> vec;
	vec.push_back(&Motive::Kebab);
	vec.push_back(&Motive::Aztec2);
	vec.push_back(&Motive::Alban);
	vec.push_back(&Motive::Bomb);
	vec.push_back(&Motive::Plant);
	vec.push_back(&Motive::Wasteland);
	vec.push_back(&Motive::Pool);
	vec.push_back(&Motive::Courbet);
	vec.push_back(&Motive::Sea);
	vec.push_back(&Motive::Sunset);
	vec.push_back(&Motive::Creebet);
	vec.push_back(&Motive::Wanderer);
	vec.push_back(&Motive::Graham);
	vec.push_back(&Motive::Match);
	vec.push_back(&Motive::Bust);
	vec.push_back(&Motive::Stage);
	vec.push_back(&Motive::Void);
	vec.push_back(&Motive::SkullAndRoses);
	vec.push_back(&Motive::Fighters);
	vec.push_back(&Motive::Pointer);
	vec.push_back(&Motive::Pigscene);
	vec.push_back(&Motive::BurningSkull);
	vec.push_back(&Motive::Skeleton);
	vec.push_back(&Motive::DonkeyKong);
	vec.push_back(&Motive::Earth);
	vec.push_back(&Motive::Wind);
	vec.push_back(&Motive::Fire);
	vec.push_back(&Motive::Water);
	return vec;
}
const Motive* Motive::getMotiveByName(const std::string& a2) {
	std::vector<const Motive*> vec = Motive::getAllMotivesAsList();

	for(auto&& mot: vec) {
		if(mot->name == a2) return mot;
	}

	return Motive::DefaultImage;
}
