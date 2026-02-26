#pragma once
#include <gui/GuiElement.hpp>
#include <Options.hpp>
struct Minecraft;
struct Screen;
struct Button;
namespace Touch {
	struct TButton;
}

struct TextBox: GuiElement
{
	static char_t* numberChars; //"0123456789"
	static char_t* extendedAcsii; //"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890?^" "~'-_.,;<>!",0x22,"#&()=` []{}",0


	int32_t key;
	Touch::TButton* doneButton;
	Button* field_2C;
	int8_t field_30, field_31, field_32, field_33;
	const Options::Option* option;
	std::string text, field_3C;
	bool_t field_40;
	int8_t field_41, field_42, field_43;
	int32_t field_44;
	const char_t* validChars;
	uint32_t field_4C;
	void (Screen::*field_50)(int32_t);
	int32_t field_54;
	Screen* field_58;
	bool_t field_5C;
	int8_t field_5D, field_5E, field_5F;
	int32_t field_60;

	TextBox(Minecraft*, const Options::Option*, const std::string&);
	TextBox(Minecraft*, const std::string&, int32_t, const char_t*, int32_t, Screen*, void (Screen::*)(int32_t), int32_t, int32_t); //TODO seems to have one less argument according to demangled function name
	int32_t getKey();
	std::string* getText();
	void setText(const std::string&);
	void setValidChars(const char_t*, uint32_t);
	void updateText(Minecraft*);

	virtual ~TextBox();
	virtual void tick(Minecraft*);
	virtual void render(Minecraft*, int32_t, int32_t);
	virtual void topRender(Minecraft*, int32_t, int32_t);
	virtual void mouseClicked(Minecraft*, int32_t, int32_t, int32_t);
	virtual void mouseReleased(Minecraft*, int32_t, int32_t, int32_t);
	virtual void focusuedMouseClicked(Minecraft*, int32_t, int32_t, int32_t);
	virtual void focusuedMouseReleased(Minecraft*, int32_t, int32_t, int32_t);
	virtual void keyPressed(Minecraft*, int32_t);
	virtual void keyboardNewChar(Minecraft*, std::string, bool_t);
	virtual bool_t backPressed(Minecraft*, bool_t);
	virtual bool_t suppressOtherGUI();
	virtual void setTextboxText(const std::string&);
	virtual void setFocus(Minecraft*);
	virtual bool_t loseFocus(Minecraft*);
};
