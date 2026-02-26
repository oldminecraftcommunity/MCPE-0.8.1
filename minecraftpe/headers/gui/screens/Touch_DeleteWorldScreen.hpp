#pragma once
#include <gui/screens/ConfirmScreen.hpp>
#include <level/LevelSummary.hpp>

namespace Touch {
	struct DeleteWorldScreen: ConfirmScreen
	{
		LevelSummary levelSummary;

		DeleteWorldScreen(const LevelSummary&);

		virtual ~DeleteWorldScreen();
		virtual void postResult(bool_t);
	};
}
