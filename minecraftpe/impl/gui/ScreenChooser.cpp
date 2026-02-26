#include <gui/ScreenChooser.hpp>
#include <gui/screens/Touch_StartMenuScreen.hpp>
#include <gui/screens/Touch_SelectWorldScreen.hpp>
#include <gui/screens/Touch_JoinGameScreen.hpp>
#include <gui/screens/PauseScreen.hpp>
#include <gui/screens/CreativeInventoryScreen.hpp>
#include <gui/screens/Touch_IngameBlockSelectionScreen.hpp>
#include <gui/screens/ChatScreen.hpp>
#include <Minecraft.hpp>

Screen* ScreenChooser::createScreen(ScreenId id){
	switch(id){
		case START_MENU_SCREEN: return new Touch::StartMenuScreen();
		case JOIN_GAME_SCREEN: return new Touch::JoinGameScreen();
		case PAUSE_SCREEN_0: return new PauseScreen(0);
		case PAUSE_SCREEN_1: return new PauseScreen(1);
		case SELECT_WORLD_SCREEN: return new Touch::SelectWorldScreen();
		case INVENTORY_SCREEN:
			if(this->minecraft->isCreativeMode()){
				return new CreativeInventoryScreen();
			}else{
				return new Touch::IngameBlockSelectionScreen();
			}
		case CHAT_SCREEN:
			return new ChatScreen();
	}
	return 0;
}


void ScreenChooser::setScreen(ScreenId id){
	Screen* screen = this->createScreen(id);
	this->minecraft->setScreen(screen);
}
