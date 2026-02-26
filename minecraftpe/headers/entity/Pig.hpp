#pragma once
#include <entity/Animal.hpp>

struct Pig: Animal
{
	Pig(Level*);
	bool_t hasSaddle();
	void setSaddle(bool_t);

	virtual ~Pig();
	virtual bool_t interactWithPlayer(Player*);
	virtual int32_t getEntityTypeId() const;
	virtual float getBaseSpeed();
	virtual int32_t getMaxHealth();
	virtual bool_t canBeControlledByRider();
	virtual int32_t getDeathLoot();
	virtual const char_t* getAmbientSound();
	virtual std::string getHurtSound();
	virtual std::string getDeathSound();
	virtual bool_t useNewAi();
	virtual bool_t isFood(const ItemInstance*);
	virtual Mob* getBreedOffspring(Animal*);
};
