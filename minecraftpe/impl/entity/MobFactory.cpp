#include <entity/MobFactory.hpp>
#include <entity/Chicken.hpp>
#include <entity/Cow.hpp>
#include <entity/Pig.hpp>
#include <entity/Sheep.hpp>
#include <entity/Zombie.hpp>
#include <entity/Creeper.hpp>
#include <entity/Skeleton.hpp>
#include <entity/Spider.hpp>
#include <entity/PigZombie.hpp>

Mob* MobFactory::CreateMob(int32_t type, Level* level) {
	Mob* v3; // r4

	switch(type) {
		case 10:
			v3 = new Chicken(level);
			break;
		case 11:
			v3 = new Cow(level);
			break;
		case 12:
			v3 = new Pig(level);
			break;
		case 13:
			v3 = new Sheep(level);
			break;
		case 32:
			v3 = new Zombie(level);
			break;
		case 33:
			v3 = new Creeper(level);
			break;
		case 34:
			v3 = new Skeleton(level);
			break;
		case 35:
			v3 = new Spider(level);
			break;
		case 36:
			v3 = new PigZombie(level);
			break;
		default:
			v3 = 0;
			break;
	}
	if(v3) {
		v3->postInit();
	}
	return v3;
}
std::string MobFactory::GetMobNameID(int32_t type) {
	switch(type) {
		case 10:
			return "entity.Chicken";

		case 11:
			return "entity.Cow";

		case 12:
			return "entity.Pig";

		case 13:
			return "entity.Sheep";

		case 32:
			return "entity.Zombie";

		case 33:
			return "entity.Creeper";

		case 34:
			return "entity.Skeleton";

		case 35:
			return "entity.Spider";

		case 36:
			return "entity.PigZombie";
		default:
			return "";
	}
}
Mob* MobFactory::getStaticTestMob(int32_t a2, Level* a3) {
	static std::map<int32_t, Mob*> _mobs;
	static Level* lastLevel;

	bool_t v4;
	if(a2) v4 = 0;
	else v4 = a3 == 0;

	Level* ll = lastLevel;
	lastLevel = a3;
	if(!v4 && a3 == ll) {
		goto LABEL_9;
	}
	for(auto& mp: _mobs) {
		if(mp.second) delete mp.second;
	}
	_mobs.clear();
	if(v4) return 0;

LABEL_9:
	if(_mobs.count(a2) != 0) {
		return _mobs.at(a2);
	}
	Mob* m = MobFactory::CreateMob(a2, a3);
	_mobs.insert({a2, m});
	return m;
}
