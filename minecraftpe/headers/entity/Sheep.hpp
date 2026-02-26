#pragma once
#include <entity/Animal.hpp>

struct EatTileGoal;
struct Sheep: Animal
{
	int32_t field_C88;
	EatTileGoal* eatTileGoal;

	Sheep(Level*);
	int32_t getColor();
	float getHeadEatAngleScale(float);
	float getHeadEatPositionScale(float);
	static int32_t getSheepColor(Random*);
	bool_t isSheared();
	void setColor(int32_t);
	void setSheared(bool_t);

	virtual ~Sheep();
	virtual bool_t interactWithPlayer(Player*);
	virtual void handleEntityEvent(int8_t);
	virtual int32_t getEntityTypeId() const;
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual std::string* getTexture();
	virtual float getBaseSpeed();
	virtual int32_t getMaxHealth();
	virtual void aiStep();
	virtual void finalizeMobSpawn();
	virtual void ate();
	virtual int32_t getDeathLoot();
	virtual void dropDeathLoot();
	virtual void jumpFromGround();
	virtual void newServerAiStep();
	virtual const char_t* getAmbientSound();
	virtual std::string getHurtSound();
	virtual std::string getDeathSound();
	virtual bool_t useNewAi();
	virtual bool_t shouldHoldGround();
	virtual Mob* getBreedOffspring(Animal*);
};
