#pragma once
#include <entity/Animal.hpp>

struct EatTileGoal;
struct Sheep: Animal
{
	static Color4 COLOR[];
	static const int NumColors;
	int32_t eatAnimationTick;
	EatTileGoal* eatTileGoal;

	Sheep(Level*);
	int32_t getColor() const;
	float getHeadEatAngleScale(float);
	float getHeadEatPositionScale(float);
	static int32_t getSheepColor(Random*);
	bool_t isSheared() const;
	void setColor(int32_t);
	void setSheared(bool_t);

	virtual ~Sheep() {
	}

	virtual bool_t interactWithPlayer(Player*);
	virtual void handleEntityEvent(char);
	virtual int32_t getEntityTypeId() const;
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual std::string* getTexture();
	virtual float getBaseSpeed() {
		return 0.25;
	}

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
