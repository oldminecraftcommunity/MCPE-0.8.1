#pragma once
#include <_types.h>
#include <string>
#include <entity/particles/ParticleType.hpp>

struct Entity;
struct Player;
struct TripodCamera;
struct TileEntity;
struct Particle;
struct LevelListener
{

	virtual ~LevelListener();
	virtual void setTilesDirty(int32_t, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual void tileChanged(int32_t, int32_t, int32_t);
	virtual void tileBrightnessChanged(int32_t, int32_t, int32_t);
	virtual void skyColorChanged();
	virtual void allChanged();
	virtual void takePicture(TripodCamera*, Entity*);
	virtual Particle* addParticle(ParticleType, float, float, float, float, float, float, int32_t);
	virtual void playSound(const std::string&, float, float, float, float, float);
	virtual void playMusic(const std::string&, float, float, float, float);
	virtual void playStreamingMusic(const std::string&, int32_t, int32_t, int32_t);
	virtual void entityAdded(Entity*);
	virtual void entityRemoved(Entity*);
	virtual void levelEvent(Player*, int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual void tileEvent(int32_t, int32_t, int32_t, int32_t, int32_t);
	virtual void tileEntityChanged(int32_t, int32_t, int32_t, TileEntity*);
};
