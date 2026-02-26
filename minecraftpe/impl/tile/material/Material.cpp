#include <tile/material/Material.hpp>
#include <tile/material/GasMaterial.hpp>
#include <tile/material/DecorationMaterial.hpp>
#include <tile/material/LiquidMaterial.hpp>
#include <tile/material/WebMaterial.hpp>
#include <_types.h>

Material* Material::air, *Material::dirt;
Material* Material::wood, *Material::stone;
Material* Material::metal, *Material::water;
Material* Material::lava, *Material::leaves;
Material* Material::plant, *Material::replaceable_plant;
Material* Material::sponge;
Material* Material::cloth, *Material::fire;
Material* Material::sand, *Material::decoration;
Material* Material::glass, *Material::explosive;
Material* Material::coral, *Material::ice;
Material* Material::topSnow, *Material::snow;
Material* Material::cactus, *Material::clay;
Material* Material::vegetable, *Material::portal;
Material* Material::cake, *Material::web;

void Material::initMaterials(void){
	Material::air = new GasMaterial();
	Material::air->replaceable = 1;

	Material::dirt = new Material();

	Material::wood = new Material();
	Material::wood->flammable = 1;

	Material::stone = new Material();
	Material::stone->alwaysDestroyable = 0;

	Material::metal = new Material();
	Material::metal->alwaysDestroyable = 0;

	Material::water = new LiquidMaterial();
	Material::water->replaceable = 1;

	Material::lava = new LiquidMaterial();
	Material::lava->replaceable = 1;

	Material::leaves = new Material();
	Material::leaves->flammable = 1;
	Material::leaves->translucent = 1;

	Material::plant = new DecorationMaterial();

	Material::replaceable_plant = new DecorationMaterial();
	Material::replaceable_plant->replaceable = 1;
	Material::replaceable_plant->flammable = 1;

	Material::sponge = new Material();

	Material::cloth = new Material();
	Material::cloth->flammable = 1;

	Material::fire = new GasMaterial();
	Material::fire->replaceable = 1;

	Material::sand = new Material();

	Material::decoration = new DecorationMaterial();

	Material::glass = new Material();
	Material::glass->translucent = 1;

	Material::explosive = new Material();
	Material::explosive->flammable = 1;
	Material::explosive->translucent = 1;

	Material::coral = new Material();

	Material::ice = new Material();
	Material::ice->translucent = 1;

	Material::topSnow = new DecorationMaterial();
	Material::topSnow->translucent = 1;
	Material::topSnow->replaceable = 1;
	Material::topSnow->alwaysDestroyable = 0;

	Material::snow = new Material();
	Material::snow->alwaysDestroyable = 0;

	Material::cactus = new Material();
	Material::cactus->translucent = 1;

	Material::clay = new Material();

	Material::vegetable = new Material();

	Material::portal = new Material();

	Material::cake = new Material();

	Material::web = new WebMaterial();
}
void Material::teardownMaterials(void){
	if(Material::air){
		delete Material::air;
		Material::air = 0;
	}

	if(Material::dirt){
		delete Material::dirt;
		Material::dirt = 0;
	}

	if(Material::wood){
		delete Material::wood;
		Material::wood = 0;
	}

	if(Material::stone){
		delete Material::stone;
		Material::stone = 0;
	}

	if(Material::metal){
		delete Material::metal;
		Material::metal = 0;
	}

	if(Material::water){
		delete Material::water;
		Material::water = 0;
	}

	if(Material::lava){
		delete Material::lava;
		Material::lava = 0;
	}

	if(Material::leaves){
		delete Material::leaves;
		Material::leaves = 0;
	}

	if(Material::plant){
		delete Material::plant;
		Material::plant = 0;
	}

	if(Material::replaceable_plant){
		delete Material::replaceable_plant;
		Material::replaceable_plant = 0;
	}

	if(Material::sponge){
		delete Material::sponge;
		Material::sponge = 0;
	}

	if(Material::cloth){
		delete Material::cloth;
		Material::cloth = 0;
	}

	if(Material::fire){
		delete Material::fire;
		Material::fire = 0;
	}

	if(Material::sand){
		delete Material::sand;
		Material::sand = 0;
	}

	if(Material::decoration){
		delete Material::decoration;
		Material::decoration = 0;
	}

	if(Material::glass){
		delete Material::glass;
		Material::glass = 0;
	}

	if(Material::explosive){
		delete Material::explosive;
		Material::explosive = 0;
	}

	if(Material::coral){
		delete Material::coral;
		Material::coral = 0;
	}

	if(Material::ice){
		delete Material::ice;
		Material::ice = 0;
	}

	if(Material::topSnow){
		delete Material::topSnow;
		Material::topSnow = 0;
	}

	if(Material::snow){
		delete Material::snow;
		Material::snow = 0;
	}

	if(Material::cactus){
		delete Material::cactus;
		Material::cactus = 0;
	}

	if(Material::clay){
		delete Material::clay;
		Material::clay = 0;
	}

	if(Material::vegetable){
		delete Material::vegetable;
		Material::vegetable = 0;
	}

	if(Material::portal){
		delete Material::portal;
		Material::portal = 0;
	}

	if(Material::cake){
		delete Material::cake;
		Material::cake = 0;
	}

	if(Material::web){
		delete Material::web;
		Material::web = 0;
	}
}

bool_t Material::isLiquid(void) const{
	return 0;
}
bool_t Material::letsWaterThrough(void) const{
	if(this->isLiquid()) return 0;
	return this->isSolid() ^ 1;
}
bool_t Material::isSolid(void) const{
	return 1;
}
bool_t Material::blocksLight(void) const{
	return 1;
}
bool_t Material::isSolidBlocking(void) const{
	if(this->translucent) return 0;
	return this->blocksMotion();
}

bool_t Material::isAlwaysDestroyable(void) const {
	return this->alwaysDestroyable;
}
bool_t Material::blocksMotion(void) const{
	return 1;
}
bool_t Material::isFlammable(void) const{
	return this->flammable;
}
bool_t Material::isReplaceable(void) const{
	return this->replaceable;
}

Material::Material(void){
	this->alwaysDestroyable = 1;
	this->flammable = this->translucent = this->replaceable = 0;
}
