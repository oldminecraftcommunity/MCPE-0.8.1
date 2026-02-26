#pragma once
#include <gui/GuiElement.hpp>
#include <RakString.h>
#include <ExternalServer.hpp>

struct PlayScreen;
struct Minecraft;
struct LevelSummary;
struct PingedCompatibleServer;

struct ImageWithBackground;
struct Button;
struct LocalServerListItemElement: GuiElement
{
	float field_24, field_28;
	Button* field_2C;
	Button * field_30;
	ImageWithBackground* deleteElementButton;
	ExternalServer* server;
	PingedCompatibleServer* field_3C;
	LevelSummary* levelSummary;
	std::string field_44;
	int32_t field_48;
	bool_t isEditing;
	int8_t field_4D, field_4E, field_4F;
	int32_t field_50;
	PlayScreen* field_54;
	int field_58;


	LocalServerListItemElement(Minecraft*, ExternalServer, bool_t, PlayScreen*);
	LocalServerListItemElement(Minecraft*, const LevelSummary&, bool_t);
	LocalServerListItemElement(const PingedCompatibleServer&);
	std::string getLastPlayedString();
	void init(Minecraft*);

	virtual ~LocalServerListItemElement();
	virtual void tick(Minecraft*);
	virtual void render(Minecraft*, int32_t, int32_t);
	virtual void mouseClicked(Minecraft*, int32_t, int32_t, int32_t);
	virtual void mouseReleased(Minecraft*, int32_t, int32_t, int32_t);
};
