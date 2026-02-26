#pragma once
#include <entity/Entity.hpp>

struct Minecart: Entity
{
	std::string field_118;
	int32_t field_11C;
	float field_120, field_124, field_128, field_12C, field_130;
	float field_134, field_138, field_13C;
	Entity* linkedEntity;
	float field_144, field_148, field_14C, field_150, field_154;
	static int32_t EXITS[10][2][3];

	Minecart(Level*);
	Minecart(Level*, float, float, float);
	void applyNaturalSlowdown();
	void comeOffTrack(float);
	static Minecart* createMinecart(Level*, float, float, float, int32_t);
	static void destroy(Entity*);
	std::string getAName();
	std::string* getCustomName();
	float getDamage();
	int32_t getDefaultDisplayData();
	int32_t getDefaultDisplayOffset();
	Tile* getDefaultDisplayTile();
	int32_t getDisplayData();
	int32_t getDisplayOffset();
	Tile* getDisplayTile();
	int32_t getHurtDir();
	int32_t getHurtTime();
	bool_t getPos(Vec3&, float, float, float);
	bool_t getPosOffs(Vec3&, float, float, float, float);
	bool_t hasCustomDisplay();
	bool_t hasCustomName();
	void moveAlongTrack(int32_t, int32_t, int32_t, float, float, int32_t, int32_t);
	void setCustomDisplay(bool_t);
	void setCustomName(const std::string&);
	void setDamage(float);
	void setDisplayData(int32_t);
	void setDisplayOffset(int32_t);
	void setDisplayTile(int32_t);
	void setHurtDir(int32_t);
	void setHurtTime(int32_t);

	virtual ~Minecart();
	virtual void remove();
	virtual void lerpTo(float, float, float, float, float, int32_t);
	virtual void lerpMotion(float, float, float);
	virtual void tick();
	virtual float getRideHeight();
	virtual float getShadowRadius();
	virtual float getShadowHeightOffs();
	virtual void push(Entity*);
	virtual void push(float, float, float);
	virtual bool_t isPickable();
	virtual bool_t isPushable();
	virtual bool_t hurt(Entity*, int32_t);
	virtual void animateHurt();
	virtual int32_t getEntityTypeId() const;
	virtual void readAdditionalSaveData(CompoundTag*);
	virtual void addAdditonalSaveData(CompoundTag*);
	virtual void activateMinecart(int32_t, int32_t, int32_t, bool_t);
	virtual int32_t getType() = 0;
};

