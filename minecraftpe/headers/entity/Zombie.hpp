#pragma once
#include <entity/Monster.hpp>

struct Zombie: Monster
{
	int32_t field_C84;
	bool_t usingNewAI;
	int8_t field_C89, field_C8A, field_C8B;

	Zombie(Level*);
	void setUseNewAi(bool_t);

	virtual ~Zombie();
	virtual int32_t getEntityTypeId() const;
	virtual void die(Entity*);
	virtual float getBaseSpeed();
	virtual int32_t getMaxHealth();
	virtual int32_t getArmorValue();
	virtual void aiStep();
	virtual int32_t getDeathLoot();
	virtual const char_t* getAmbientSound();
	virtual std::string getHurtSound();
	virtual std::string getDeathSound();
	virtual bool_t useNewAi();
	virtual int32_t getAttackDamage(Entity*);
};
