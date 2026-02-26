#include <sound/SoundEngine.hpp>
#include <Options.hpp>
#include <entity/Mob.hpp>
#include <math.h>
#include <sounddata.hpp>

SoundEngine::SoundEngine(float a2)
	: SoundSystemSL() {
	this->field_40 = 0;
	this->field_A14 = 0.0;
	this->field_A18 = 0.0;
	this->field_A1C = 0.0;
	this->field_A20 = 0.0;
	this->field_A24 = 1.0 / a2;
	this->minecraft = 0;
}
float SoundEngine::_getVolumeMult(float a2, float a3, float a4) {
	float v5; // s13
	float v6; // s15

	v5 = sqrt((float)((float)((float)((float)(a3 - this->field_A18) * (float)(a3 - this->field_A18)) + (float)((float)(a2 - this->field_A14) * (float)(a2 - this->field_A14))) + (float)((float)(a4 - this->field_A1C) * (float)(a4 - this->field_A1C))));
	v6 = 1.1 - (float)(v5 * this->field_A24);
	if(v6 > 1.0) {
		return 1.0;
	}
	if(v6 <= -1.0) {
		return -1.0;
	}
	return v6;
}
void SoundEngine::destroy(void) {
}
void SoundEngine::enable(bool_t) {
}

void SoundEngine::init(struct Minecraft* a2, struct Options* a3) {
	this->minecraft = a2;
	this->options = a3;
	this->sounds.add("step.cloth", SA_cloth1);
	this->sounds.add("step.cloth", SA_cloth2);
	this->sounds.add("step.cloth", SA_cloth3);
	this->sounds.add("step.cloth", SA_cloth4);
	this->sounds.add("step.grass", SA_grass1);
	this->sounds.add("step.grass", SA_grass2);
	this->sounds.add("step.grass", SA_grass3);
	this->sounds.add("step.grass", SA_grass4);
	this->sounds.add("step.gravel", SA_gravel1);
	this->sounds.add("step.gravel", SA_gravel2);
	this->sounds.add("step.gravel", SA_gravel3);
	this->sounds.add("step.gravel", SA_gravel4);
	this->sounds.add("step.sand", SA_sand1);
	this->sounds.add("step.sand", SA_sand2);
	this->sounds.add("step.sand", SA_sand3);
	this->sounds.add("step.sand", SA_sand4);
	this->sounds.add("step.stone", SA_stone1);
	this->sounds.add("step.stone", SA_stone2);
	this->sounds.add("step.stone", SA_stone3);
	this->sounds.add("step.stone", SA_stone4);
	this->sounds.add("step.wood", SA_wood1);
	this->sounds.add("step.wood", SA_wood2);
	this->sounds.add("step.wood", SA_wood3);
	this->sounds.add("step.wood", SA_wood4);
	this->sounds.add("random.splash", SA_splash);
	this->sounds.add("random.explode", SA_explode);
	this->sounds.add("random.click", SA_click);
	this->sounds.add("random.break", SA_break);
	this->sounds.add("random.burp", SA_burp);
	this->sounds.add("fire.fire", SA_fire);
	this->sounds.add("fire.ignite", SA_ignite);
	this->sounds.add("random.door_open", SA_door_open);
	this->sounds.add("random.door_close", SA_door_close);
	this->sounds.add("random.chestclosed", SA_chestclosed);
	this->sounds.add("random.chestopen", SA_chestopen);
	this->sounds.add("random.pop", SA_pop);
	this->sounds.add("random.pop2", SA_pop2);
	this->sounds.add("random.hurt", SA_hurt);
	this->sounds.add("random.glass", SA_glass1);
	this->sounds.add("random.glass", SA_glass2);
	this->sounds.add("random.glass", SA_glass3);
	this->sounds.add("mob.sheep", SA_sheep1);
	this->sounds.add("mob.sheep", SA_sheep2);
	this->sounds.add("mob.sheep", SA_sheep3);
	this->sounds.add("mob.pig", SA_pig1);
	this->sounds.add("mob.pig", SA_pig2);
	this->sounds.add("mob.pig", SA_pig3);
	this->sounds.add("mob.pigdeath", SA_pigdeath);
	this->sounds.add("mob.cow", SA_cow1);
	this->sounds.add("mob.cow", SA_cow2);
	this->sounds.add("mob.cow", SA_cow3);
	this->sounds.add("mob.cow", SA_cow4);
	this->sounds.add("mob.cowhurt", SA_cowhurt1);
	this->sounds.add("mob.cowhurt", SA_cowhurt2);
	this->sounds.add("mob.cowhurt", SA_cowhurt3);
	this->sounds.add("mob.chicken", SA_chicken2);
	this->sounds.add("mob.chicken", SA_chicken3);
	this->sounds.add("mob.chickenhurt", SA_chickenhurt1);
	this->sounds.add("mob.chickenhurt", SA_chickenhurt2);
	this->sounds.add("mob.zombie", SA_zombie1);
	this->sounds.add("mob.zombie", SA_zombie2);
	this->sounds.add("mob.zombie", SA_zombie3);
	this->sounds.add("mob.zombiedeath", SA_zombiedeath);
	this->sounds.add("mob.zombiehurt", SA_zombiehurt1);
	this->sounds.add("mob.zombiehurt", SA_zombiehurt2);
	this->sounds.add("mob.skeleton", SA_skeleton1);
	this->sounds.add("mob.skeleton", SA_skeleton2);
	this->sounds.add("mob.skeleton", SA_skeleton3);
	this->sounds.add("mob.skeletonhurt", SA_skeletonhurt1);
	this->sounds.add("mob.skeletonhurt", SA_skeletonhurt2);
	this->sounds.add("mob.skeletonhurt", SA_skeletonhurt3);
	this->sounds.add("mob.skeletonhurt", SA_skeletonhurt4);
	this->sounds.add("mob.spider", SA_spider1);
	this->sounds.add("mob.spider", SA_spider2);
	this->sounds.add("mob.spider", SA_spider3);
	this->sounds.add("mob.spider", SA_spider4);
	this->sounds.add("mob.spiderdeath", SA_spiderdeath);
	this->sounds.add("mob.zombiepig.zpig", SA_zpig1);
	this->sounds.add("mob.zombiepig.zpig", SA_zpig2);
	this->sounds.add("mob.zombiepig.zpig", SA_zpig3);
	this->sounds.add("mob.zombiepig.zpig", SA_zpig4);
	this->sounds.add("mob.zombiepig.zpigangry", SA_zpigangry1);
	this->sounds.add("mob.zombiepig.zpigangry", SA_zpigangry2);
	this->sounds.add("mob.zombiepig.zpigangry", SA_zpigangry3);
	this->sounds.add("mob.zombiepig.zpigangry", SA_zpigangry4);
	this->sounds.add("mob.zombiepig.zpigdeath", SA_zpigdeath);
	this->sounds.add("mob.zombiepig.zpighurt", SA_zpighurt1);
	this->sounds.add("mob.zombiepig.zpighurt", SA_zpighurt2);
	this->sounds.add("damage.fallbig", SA_fallbig1);
	this->sounds.add("damage.fallbig", SA_fallbig2);
	this->sounds.add("damage.fallsmall", SA_fallsmall);
	this->sounds.add("random.bow", SA_bow);
	this->sounds.add("random.bowhit", SA_bowhit1);
	this->sounds.add("random.bowhit", SA_bowhit2);
	this->sounds.add("random.bowhit", SA_bowhit3);
	this->sounds.add("random.bowhit", SA_bowhit4);
	this->sounds.add("mob.creeper", SA_creeper1);
	this->sounds.add("mob.creeper", SA_creeper2);
	this->sounds.add("mob.creeper", SA_creeper3);
	this->sounds.add("mob.creeper", SA_creeper4);
	this->sounds.add("mob.creeperdeath", SA_creeperdeath);
	this->sounds.add("random.eat", SA_eat1);
	this->sounds.add("random.eat", SA_eat2);
	this->sounds.add("random.eat", SA_eat3);
	this->sounds.add("random.fuse", SA_fuse);
}
void SoundEngine::play(const std::string& a2, float a3, float a4, float a5, float a6, float a7) {
	float v8;  // s16
	float v12; // s16

	v8 = a6 * this->options->soundVolume;
	if(v8 > 0.0) {
		v12 = v8 * this->_getVolumeMult(a3, a4, a5);
		if(v12 > 1.0) {
			v12 = 1.0;
		} else if(v12 <= 0.0) {
			v12 = 0.0;
		}
		if(this->options->soundVolume != 0.0 && v12 > 0.0) {
			SoundDesc v13;
			if(this->sounds.get(a2, v13)) {
				SoundSystemSL::playAt(v13, a3, a4, a5, v12, a7);
			}
		}
	}
}
void SoundEngine::playUI(const std::string& a2, float a3, float a4) {
	float soundVolume; // s15
	float v6;		   // s16

	soundVolume = this->options->soundVolume;
	v6 = a3 * soundVolume;
	if((float)(a3 * soundVolume) > 0.0) {
		if(v6 > 1.0) {
			if(soundVolume == 0.0) {
				return;
			}
			v6 = 1.0;
			goto LABEL_6;
		}
		if(v6 > 0.0 && soundVolume != 0.0 && v6 > 0.0) {
LABEL_6:
			SoundDesc v8; // [sp+10h] [bp-38h] BYREF
			if(this->sounds.get(a2, v8)) {
				SoundSystemSL::playAt(v8, 0.0, 0.0, 0.0, v6, a4);
			}
		}
	}
}
void SoundEngine::update(struct Mob* a2, float a3) {
	if(this->options->soundVolume != 0.0) {
		if(a2) {
			this->field_A14 = a2->prevX + (float)((float)(a2->posX - a2->prevX) * a3);
			this->field_A18 = a2->prevY + (float)((float)(a2->posY - a2->prevY) * a3);
			this->field_A1C = a2->prevZ + (float)((float)(a2->posZ - a2->prevZ) * a3);
			float v3 = a2->prevYaw + (float)((float)(a2->yaw - a2->prevYaw) * a3);
			this->field_A20 = v3;
			this->setListenerAngle(v3);
		}
	}
}
void SoundEngine::updateOptions(void) {
}
SoundEngine::~SoundEngine() {
}
