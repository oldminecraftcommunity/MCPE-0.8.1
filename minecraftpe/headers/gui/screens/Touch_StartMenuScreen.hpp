#pragma once
#include <_types.h>
#include <gui/Screen.hpp>
#include <gui/buttons/Touch_TButton.hpp>
#include <gui/buttons/BuyButton.hpp>

extern char_t* gSplashes[];
struct ImageWithBackground;

namespace Touch{
	struct StartMenuScreen : Screen{
		static int32_t currentSplash;

		Touch::TButton playButton;
		Touch::TButton playOnRealmsButton;
		ImageWithBackground* settingsButtonMaybe;
		BuyButton buyButton;
		std::string field_138;
		std::string field_13C;
		int32_t field_140;
		int32_t field_144;
		int32_t field_148;
		int32_t field_14C;
		double field_150;


		StartMenuScreen(void);
		void _updateLicense();
		static void chooseRandomSplash();
		void setupPlayButtons(bool_t);

		virtual ~StartMenuScreen();
		virtual void render(int32_t, int32_t, float);
		virtual void init();
		virtual void setupPositions();
		virtual bool_t handleBackEvent(bool_t);
		virtual void tick();
		virtual bool_t isInGameScreen();
		virtual void buttonClicked(struct Button *);
	};
}
