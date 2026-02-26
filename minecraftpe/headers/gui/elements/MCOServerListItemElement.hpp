#pragma once
#include <gui/GuiElement.hpp>
#include <network/mco/MCOServerListItem.hpp>
#include <functional>

struct ImageWithBackground;
namespace Touch {
	struct TButton;
}
struct Button;
struct Minecraft;

struct MCOServerListItemElement: GuiElement
{
	float field_24;
	float field_28;
	Button* field_2C;
	MCOServerListItem field_30;
	int32_t field_74;
	ImageWithBackground* field_78;
	Touch::TButton* field_7C;
	std::function<void (MCOServerListItem&, bool_t)> field_80;
	int8_t field_90, field_91, field_92, field_93;
	int32_t field_94;

	MCOServerListItemElement(Minecraft*, struct MCOServerListItem&, bool_t, std::function<void (MCOServerListItem&, bool_t)>);

	virtual ~MCOServerListItemElement();
	virtual void tick(Minecraft*);
	virtual void render(Minecraft*, int32_t, int32_t);
	virtual void mouseClicked(Minecraft*, int32_t, int32_t, int32_t);
	virtual void mouseReleased(Minecraft*, int32_t, int32_t, int32_t);

};
