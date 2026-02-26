#include <NinecraftApp.hpp>
#include <rendering/GLBufferPool.hpp>
#include <GLES/gl.h>
#include <GLES/egl.h>
#include <rendering/Tesselator.hpp>
#include <math/Mth.hpp>
#include <tile/material/Material.hpp>
#include <entity/MobCategory.hpp>
#include <item/Item.hpp>
#include <level/biome/Biome.hpp>
#include <rendering/Textures.hpp>
#include <rendering/Font.hpp>
#include <rendering/PerfRenderer.hpp>
#include <tile/Tile.hpp>
#include <rendering/GameRenderer.hpp>
#include <entity/LocalPlayer.hpp>
#include <tile/entity/TileEntity.hpp>
#include <I18n.hpp>
#include <rendering/LevelRenderer.hpp>
#include <rendering/ParticleEngine.hpp>
#include <network/RakNetInstance.hpp>
#include <input/Mouse.hpp>
#include <level/Level.hpp>
#include <network/ServerSideNetworkHandler.hpp>
#include <level/storage/ExternalFileLevelStorageSource.hpp>
#include <rendering/textures/LavaTexture.hpp>
#include <rendering/textures/WaterTexture.hpp>
#include <rendering/textures/FireTexture.hpp>
#include <rendering/textures/WaterSideTexture.hpp>
#include <rendering/textures/LavaSideTexture.hpp>
#include <gui/Screen.hpp>
#include <cpputils.hpp>

std::shared_ptr<TextureAtlas> NinecraftApp::_itemsTextureAtlas;
std::shared_ptr<TextureAtlas> NinecraftApp::_terrainTextureAtlas;
bool NinecraftApp::_hasInitedStatics = 0;

NinecraftApp::NinecraftApp(){
	this->field_D48___ = 1;
	this->field_D4C = 0;
	this->field_D50 = 0;
	this->field_D60 = 0;
	this->field_D64 = 0;
	this->field_D68 = 0;
	//TODO bsd_signal(13);
}

std::shared_ptr<TextureAtlas> NinecraftApp::getTextureAtlas(TextureAtlasId atlas){
	if(atlas) return std::shared_ptr<TextureAtlas>(NinecraftApp::_itemsTextureAtlas);
	return std::shared_ptr<TextureAtlas>(NinecraftApp::_terrainTextureAtlas);
}
void NinecraftApp::handleBackNoReturn(void){
	if(this->field_CF4){
		if(this->currentScreen){
			this->currentScreen->handleBackEvent(this->field_CF4);
		}
	}
}
void NinecraftApp::initGLStates(){
	glEnable(0xBE2u);
	glEnable(0xB71u);
	glEnable(0xB44u);
	glEnable(0xDE1u);
	glDisable(0xB60u);
	glDisable(0xB50u);
	glDisable(0xBC0u);
	glDisable(0xB90u);
	glDisable(0x8037u);
	glDisable(0xB50u);
	glDepthFunc(GL_LEQUAL);
	glDepthRangef(0, 1.0);
	glAlphaFunc(0x204u, 0.5);
	glCullFace(0x405u);
	glShadeModel(0x1D00u);
	glEnableClientState(0x8074u);
	glHint(0xC50u, 0x1101u);
	glHint(0xC54u, 0x1101u);
	glBlendFunc(0x302u, 0x303u);
	glDepthMask(1u);
	glStencilFunc(0x202u, 0, 0xFFu);
	glStencilMask(0xFFu);
	glLightModelf(0xB52u, 0.0);
	glPolygonOffset(-1.0, -1.0);
	this->powerVR = this->platform()->isPowerVR();
}

void NinecraftApp::restartServer(){
	Level* levelPtr; // r3
	Level* v6; // r0
	Entity* v7; // r1
	ServerSideNetworkHandler* serverSideNetworkHandler; // r0

	levelPtr = this->level;
	if(levelPtr) {
		for(int32_t i = levelPtr->playersMaybe.size() - 1; i >= 0; --i) {
			Player* player = levelPtr->playersMaybe.back();
			this->level->removePlayer(player);
			levelPtr->playersMaybe.pop_back();
		}
		this->rakNetInstance->resetIsBroken();
		this->gui.addMessage("server", "This server has restarted!", 200);
		this->hostMultiplayer(19132);
		if ( this->serverSideNetworkHandler )
		{
			serverSideNetworkHandler->levelGenerated(this->level);
		}
	}
}
void NinecraftApp::updateStats(){

}

NinecraftApp::~NinecraftApp(void){
	this->teardown();
}
bool_t NinecraftApp::onLowMemory(void){
	//TODO check
	if(glBufferPool.buffers.size() == 0) return 0;
	while(glBufferPool.buffers.back() != glBufferPool.buffers.front()){
		uint32_t s = glBufferPool.buffers.at(0);
		glDeleteBuffers(1, &s);
		glBufferPool.buffers.pop_front();
	}
	return 1;
}
void NinecraftApp::onAppResumed(void){
	this->initGLStates();
	Tesselator::instance.init();
	Minecraft::onAppResumed();
}
void NinecraftApp::update(void){
	//TODO mutex lock
	//TODO multitouch
	++this->field_D4C;
	//TODO MultiTouch::commit(vecEndPtr);
	Minecraft::update();
	if(this->context.field_10){
		//TODO eglSwapBuffers(this->context.field_0, this->context.field_8);
	}
	Mouse::reset2();
	if(this->level){
		if(this->rakNetInstance->isProbablyBroken()){
			if(this->rakNetInstance->isServer()){
				this->restartServer();
			}
		}
	}
	this->updateStats();
}
bool_t NinecraftApp::handleBack(bool_t a2){
	if(!this->field_CF4){
		if(this->level){
			if(!this->currentScreen){
				this->pauseGame(1);
				return 0;
			}
			if(!this->currentScreen->handleBackEvent(0)){
				if(this->player->currentContainer){
					this->player->closeContainer();
				}else{
					this->setScreen(0);
				}
			}

		}else{
			if(this->currentScreen){
				this->currentScreen->handleBackEvent(a2);
			}
		}
	}
	return 1;
}
void NinecraftApp::handleBack(void){
	//TODO
}
void NinecraftApp::init(void){
	const char* v43[] = {"/games", "/com.mojang", "/minecraftpe"};
	createTree(this->dataPathMaybe.c_str(), v43, 3);
	this->field_D00 = this->dataPathMaybe + "/games" + "/com.mojang" + "/minecraftpe";

	int32_t x = 0;
	do{
		float v7 = sin((float)x / 10430.0);
		Mth::_sin[x] = v7;
		++x;
	}while(x != 65536);
	if(!NinecraftApp::_hasInitedStatics){
		std::string v40 = "images/";
		NinecraftApp::_hasInitedStatics = 1;
		NinecraftApp::_terrainTextureAtlas = std::shared_ptr<TextureAtlas>(new TextureAtlas(v40+"terrain.meta"));
		NinecraftApp::_itemsTextureAtlas = std::shared_ptr<TextureAtlas>(new TextureAtlas(v40+"items.meta"));
		NinecraftApp::_terrainTextureAtlas->load(this);
		NinecraftApp::_itemsTextureAtlas->load(this);
		Material::initMaterials();
		MobCategory::initMobCategories();
		Tile::initTiles(NinecraftApp::_terrainTextureAtlas);
		Item::initItems(NinecraftApp::_itemsTextureAtlas);
		Biome::initBiomes();
		TileEntity::initTileEntities();
	}
	this->initGLStates();
	Tesselator::instance.init();
	I18n::loadLanguage(this->platform(), "en_US");
	Minecraft::init();
	this->levelStorageSource = new ExternalFileLevelStorageSource(this->dataPathMaybe, this->field_CC4);
	this->field_CFC = 0;
	this->texturesPtr = new Textures(&this->options, this->platform());
	this->texturesPtr->addDynamicTexture(new FireTexture());
	this->texturesPtr->addDynamicTexture(new WaterTexture(*NinecraftApp::_terrainTextureAtlas->getTextureItem("still_water")->getUV(0)));
	this->texturesPtr->addDynamicTexture(new WaterSideTexture());
	this->texturesPtr->addDynamicTexture(new LavaTexture());
	this->texturesPtr->addDynamicTexture(new LavaSideTexture(*NinecraftApp::_terrainTextureAtlas->getTextureItem("flowing_lava")->getUV(0)));
	this->gui.texturesLoaded(this->texturesPtr);
	this->field_190 = 0;
	this->levelRenderer = new LevelRenderer(this, std::shared_ptr<TextureAtlas>(NinecraftApp::_terrainTextureAtlas));
	this->gameRenderer = new GameRenderer(this);
	this->particleEngine = new ParticleEngine(this->level, this->texturesPtr);
	this->font = new Font(this->platform(), &this->options, "font/default8.png", this->texturesPtr);
	this->perfRenderer = new PerfRenderer(this, this->font);
	this->checkGLError("Init complete");
	this->updateStatusUserAttributes();
	this->options.validateVersion();
	this->screenChooser.setScreen(START_MENU_SCREEN);
}

void NinecraftApp::teardown(void){
	Minecraft::teardown();
}
