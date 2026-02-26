#pragma once
#include <entity/Zombie.hpp>

struct PigZombie: Zombie
{
	int32_t field_C90, field_C94, field_C98;
	ItemInstance itemInHand;

	PigZombie(Level*);
	int32_t alert(Entity*);

	virtual ~PigZombie();
	virtual void tick();
	virtual bool_t interactWithPlayer(Player*);
	virtual bool_t hurt(Entity*, int32_t);
	virtual int32_t getEntityTypeId() const;
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual std::string* getTexture();
	virtual float getBaseSpeed();
	virtual bool_t canSpawn();
	virtual ItemInstance* getCarriedItem();
	virtual int32_t getDeathLoot();
	virtual void dropDeathLoot();
	virtual const char_t* getAmbientSound();
	virtual std::string getHurtSound();
	virtual std::string getDeathSound();
	virtual bool_t useNewAi();
	virtual Entity* findAttackTarget();
	virtual int32_t getAttackTime();
};
