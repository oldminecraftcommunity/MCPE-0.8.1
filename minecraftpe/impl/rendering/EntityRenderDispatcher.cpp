#include <rendering/EntityRenderDispatcher.hpp>
#include <entity/Mob.hpp>
#include <level/Level.hpp>
#include <math/Mth.hpp>
#include <rendering/entity/EntityRenderer.hpp>
#include <tile/Tile.hpp>
#include <rendering/ItemInHandRenderer.hpp>
#include <rendering/entity/ItemRenderer.hpp>
#include <rendering/entity/HumanoidMobRenderer.hpp>
#include <rendering/entity/PigRenderer.hpp>
#include <rendering/model/PigModel.hpp>
#include <rendering/model/CowModel.hpp>
#include <rendering/entity/ChickenRenderer.hpp>
#include <rendering/model/ChickenModel.hpp>
#include <rendering/entity/SheepRenderer.hpp>
#include <rendering/model/SheepModel.hpp>
#include <rendering/entity/HumanoidMobRenderer.hpp>
#include <rendering/model/SkeletonModel.hpp>
#include <rendering/entity/CreeperRenderer.hpp>
#include <rendering/model/CreeperModel.hpp>
#include <rendering/entity/SpiderRenderer.hpp>
#include <rendering/entity/TntRenderer.hpp>
#include <rendering/entity/ArrowRenderer.hpp>
#include <rendering/entity/PlayerRenderer.hpp>
#include <rendering/entity/ItemSpriteRenderer.hpp>
#include <item/Item.hpp>
#include <rendering/entity/PaintingRenderer.hpp>
#include <rendering/entity/FallingTileRenderer.hpp>
#include <rendering/entity/MinecartRenderer.hpp>

EntityRenderDispatcher* EntityRenderDispatcher::instance = 0;
float EntityRenderDispatcher::xOff = 0, EntityRenderDispatcher::yOff = 0, EntityRenderDispatcher::zOff = 0;

EntityRenderDispatcher::EntityRenderDispatcher() {
	this->assign(ITEM_ENTITY, new ItemRenderer());
	this->assign(HUMANOID, new HumanoidMobRenderer(0, 0));
	this->assign(PIG, new PigRenderer(new PigModel(0.0), 0.7));
	this->assign(COW, new MobRenderer(new CowModel(), 0));
	this->assign(CHICKEN, new ChickenRenderer(new ChickenModel(), 0));
	this->assign(SHEEP, new SheepRenderer(new SheepModel(0), new SheepModel(1), 0));
	this->assign(SKELETON, new HumanoidMobRenderer(new SkeletonModel(), 0.5));
	this->assign(ZOMBIE, new HumanoidMobRenderer(new ZombieModel(), 0.5));
	this->assign(CREEPER, new CreeperRenderer(new CreeperModel(0), 0.5));
	this->assign(SPIDER, new SpiderRenderer(new SpiderModel(), 1.0));
	this->assign(TNT, new TntRenderer());
	this->assign(ARROW, new ArrowRenderer());
	this->assign(PLAYER, new PlayerRenderer(new HumanoidModel(0, 0), 0));
	this->assign(THROWNEGG, new ItemSpriteRenderer(Item::egg));
	this->assign(THROWNSNOWBALL, new ItemSpriteRenderer(Item::snowBall));
	this->assign(PAINTING, new PaintingRenderer());
	this->assign(FALLINGTILE, new FallingTileRenderer());
	this->assign(MINECART, new MinecartRenderer());
	for(auto&& p: this->renderers) {
		p->init(this);
	}
}
void EntityRenderDispatcher::assign(EntityRendererId a2, EntityRenderer* a3) {
	int32_t v4 = 0;
	while(this->renderers[v4].get() != a3) {
		if(++v4 == 22) {
			this->renderers[a2] = std::shared_ptr<EntityRenderer>(a3);
			return;
		}
	}
	this->renderers[a2] = std::shared_ptr<EntityRenderer>(a3);
}
void EntityRenderDispatcher::destroy() {
	if(EntityRenderDispatcher::instance) {
		delete EntityRenderDispatcher::instance;
		EntityRenderDispatcher::instance = 0;
	}
}
float EntityRenderDispatcher::distanceToSqr(float x, float y, float z) {
	return (float)((float)((float)(y - this->field_24) * (float)(y - this->field_24)) + (float)((float)(x - this->field_20) * (float)(x - this->field_20))) + (float)((float)(z - this->field_28) * (float)(z - this->field_28));
}
Font* EntityRenderDispatcher::getFont() {
	return this->font;
}
EntityRenderDispatcher* EntityRenderDispatcher::getInstance() {
	if(!EntityRenderDispatcher::instance) {
		EntityRenderDispatcher::instance = new EntityRenderDispatcher();
	}
	return EntityRenderDispatcher::instance;
}
EntityRenderer* EntityRenderDispatcher::getRenderer(Entity* a2) {
	if(a2->entityRenderId == UNKNOWN) {
		return this->getRenderer(a2->queryEntityRenderer());
	}
	return this->getRenderer(a2->entityRenderId);
}
EntityRenderer* EntityRenderDispatcher::getRenderer(EntityRendererId a2) {
	return this->renderers[a2].get();
}
void EntityRenderDispatcher::prepare(Level* a2, Font* a3, Mob* a4, Options* a5, float a6) {
	int32_t v9;	 // r9
	int32_t v10; // r8
	int32_t v11; // r0
	int32_t v12; // r9
	int32_t v13; // r8
	int32_t v14; // r0
	int8_t v15;	 // r0

	this->level = a2;
	this->cameraEntity = a4;
	this->options = a5;
	this->font = a3;
	if(a4->isSleeping()) {
		v9 = Mth::floor(a4->posX);
		v10 = Mth::floor(a4->posY);
		v11 = Mth::floor(a4->posZ);
		if(a2->getTile(v9, v10, v11) == Tile::bed->blockID) {
			v12 = Mth::floor(a4->posX);
			v13 = Mth::floor(a4->posY);
			v14 = Mth::floor(a4->posZ);
			v15 = a2->getData(v12, v13, v14);
			this->field_18 = 0.0;
			this->field_14 = (float)(90 * (v15 & 3) + 180);
		}
	} else {
		this->field_14 = a4->prevYaw + (float)((float)(a4->yaw - a4->prevYaw) * a6);
		this->field_18 = a4->prevPitch + (float)((float)(a4->pitch - a4->prevPitch) * a6);
	}
	this->field_20 = a4->prevPosX + (float)((float)(a4->posX - a4->prevPosX) * a6);
	this->field_24 = a4->prevPosY + (float)((float)(a4->posY - a4->prevPosY) * a6);
	this->field_28 = a4->prevPosZ + (float)((float)(a4->posZ - a4->prevPosZ) * a6);
}
void EntityRenderDispatcher::render(Entity* e, float a3) {
	this->render(e, (float)(e->prevPosX + (float)((float)(e->posX - e->prevPosX) * a3)) - EntityRenderDispatcher::xOff, (float)(e->prevPosY + (float)((float)(e->posY - e->prevPosY) * a3)) - EntityRenderDispatcher::yOff, (float)(e->prevPosZ + (float)((float)(e->posZ - e->prevPosZ) * a3)) - EntityRenderDispatcher::zOff, e->prevYaw + (float)((float)(e->yaw - e->prevYaw) * a3), a3);
}
void EntityRenderDispatcher::render(Entity* e, float a3, float a4, float a5, float a6, float a7) {
	EntityRenderer* r = this->getRenderer(e);
	if(r) {
		r->render(e, a3, a4, a5, a6, a7);
		r->postRender(e, a3, a4, a5, a6, a7);
	}
}
void EntityRenderDispatcher::setLevel(Level* a2) {
	this->level = a2;
}
void EntityRenderDispatcher::setMinecraft(Minecraft* a2) {
	this->minecraft = a2;
}
EntityRenderDispatcher::~EntityRenderDispatcher(){
		//should automatically generate stuff to remove std::shared_ptr
}
