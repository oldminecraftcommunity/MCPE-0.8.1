#pragma once
#include <map>
#include <string>
#include <gui/Screen.hpp>
#include <rendering/Font.hpp>
#include <gui/buttons/Button.hpp>
#include <Minecraft.hpp>
#include <rendering/Textures.hpp>
#include <dirent.h>
#include <util/Util.hpp>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <GL/gl.h>

extern struct Animation* selectedAnimation;
struct AnimationState
{
	bool inter, resetArms, interpol;
	int ticks;
	int frame = 0;
	bool active = 0;
};
extern AnimationState animstate;
extern float animtime;
// Trim from the start (in place)
inline void ltrim(std::string& s) {
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
				return !std::isspace(ch);
			}));
}

// Trim from the end (in place)
inline void rtrim(std::string& s) {
	s.erase(std::find_if(s.rbegin(),
						 s.rend(),
						 [](unsigned char ch) {
							 return !std::isspace(ch);
						 })
				.base(),
			s.end());
}
enum BodyPart {
	HEAD_X,
	HEAD_Y,
	HEAD_Z,
	HAT_X,
	HAT_Y,
	HAT_Z,
	BODY_X,
	BODY_Y,
	BODY_Z,
	RIGHTARM_X,
	RIGHTARM_Y,
	RIGHTARM_Z,
	LEFTARM_X,
	LEFTARM_Y,
	LEFTARM_Z,
	RIGHTLEG_X,
	RIGHTLEG_Y,
	RIGHTLEG_Z,
	LEFTLEG_X,
	LEFTLEG_Y,
	LEFTLEG_Z,
	CAPE_X,
	CAPE_Y,
	CAPE_Z
};

inline BodyPart getFromString(std::string ss) {
	if(Util::toLower(ss) == "head_x") return HEAD_X;
	if(Util::toLower(ss) == "head_y") return HEAD_Y;
	if(Util::toLower(ss) == "head_z") return HEAD_Z;
	if(Util::toLower(ss) == "hat_x") return HAT_X;
	if(Util::toLower(ss) == "hat_y") return HAT_Y;
	if(Util::toLower(ss) == "hat_z") return HAT_Z;
	if(Util::toLower(ss) == "body_x") return BODY_X;
	if(Util::toLower(ss) == "body_y") return BODY_Y;
	if(Util::toLower(ss) == "body_z") return BODY_Z;
	if(Util::toLower(ss) == "rightarm_x") return RIGHTARM_X;
	if(Util::toLower(ss) == "rightarm_y") return RIGHTARM_Y;
	if(Util::toLower(ss) == "rightarm_z") return RIGHTARM_Z;
	if(Util::toLower(ss) == "leftarm_x") return LEFTARM_X;
	if(Util::toLower(ss) == "leftarm_y") return LEFTARM_Y;
	if(Util::toLower(ss) == "leftarm_z") return LEFTARM_Z;
	if(Util::toLower(ss) == "rightleg_x") return RIGHTLEG_X;
	if(Util::toLower(ss) == "rightleg_y") return RIGHTLEG_Y;
	if(Util::toLower(ss) == "rightleg_z") return RIGHTLEG_Z;
	if(Util::toLower(ss) == "leftleg_x") return LEFTLEG_X;
	if(Util::toLower(ss) == "leftleg_y") return LEFTLEG_Y;
	if(Util::toLower(ss) == "leftleg_z") return LEFTLEG_Z;
	if(Util::toLower(ss) == "cape_x") return CAPE_X;
	if(Util::toLower(ss) == "cape_y") return CAPE_Y;
	if(Util::toLower(ss) == "cape_z") return CAPE_Z;

	if(Util::toLower(ss) == "head.x") return HEAD_X;
	if(Util::toLower(ss) == "head.y") return HEAD_Y;
	if(Util::toLower(ss) == "head.z") return HEAD_Z;
	if(Util::toLower(ss) == "hat.x") return HAT_X;
	if(Util::toLower(ss) == "hat.y") return HAT_Y;
	if(Util::toLower(ss) == "hat.z") return HAT_Z;
	if(Util::toLower(ss) == "body.x") return BODY_X;
	if(Util::toLower(ss) == "body.y") return BODY_Y;
	if(Util::toLower(ss) == "body.z") return BODY_Z;
	if(Util::toLower(ss) == "rightarm.x") return RIGHTARM_X;
	if(Util::toLower(ss) == "rightarm.y") return RIGHTARM_Y;
	if(Util::toLower(ss) == "rightarm.z") return RIGHTARM_Z;
	if(Util::toLower(ss) == "leftarm.x") return LEFTARM_X;
	if(Util::toLower(ss) == "leftarm.y") return LEFTARM_Y;
	if(Util::toLower(ss) == "leftarm.z") return LEFTARM_Z;
	if(Util::toLower(ss) == "rightleg.x") return RIGHTLEG_X;
	if(Util::toLower(ss) == "rightleg.y") return RIGHTLEG_Y;
	if(Util::toLower(ss) == "rightleg.z") return RIGHTLEG_Z;
	if(Util::toLower(ss) == "leftleg.x") return LEFTLEG_X;
	if(Util::toLower(ss) == "leftleg.y") return LEFTLEG_Y;
	if(Util::toLower(ss) == "leftleg.z") return LEFTLEG_Z;
	if(Util::toLower(ss) == "cape.x") return CAPE_X;
	if(Util::toLower(ss) == "cape.y") return CAPE_Y;
	if(Util::toLower(ss) == "cape.z") return CAPE_Z;
	return HEAD_X;
}

struct Frame
{
	std::map<BodyPart, float> data;
	int duration;

	Frame(int duration, std::map<BodyPart, float> data) {
		this->duration = duration;
		this->data = data;
	}
};
struct Animation
{
	std::string name;
	std::vector<Frame> frames;
	bool interuptible, resetArms, interpolable;
	Animation() {
	}
	Animation(std::string name, std::vector<Frame> frames, bool i, bool r, bool ip) {
		this->name = name;
		this->frames = frames;
		this->interpolable = ip;
		this->interuptible = i;
		this->resetArms = r;
	}
};

struct StyledButton: Button
{
	StyledButton(int id, int x, int y, int width, int height, std::string text)
		: Button(id, x, y, width, height, text) {
	}

	bool hovered(int mouseX, int mouseY) {
		return mouseX >= this->posX && mouseY >= this->posY && mouseX < this->posX + this->width && mouseY < this->posY + this->height;
	}

	virtual void render(struct Minecraft* mc, int32_t mx, int32_t my) {
		bool enabled1 = this->hovered(mx, my) && this->active;
		int offset = enabled1 ? 1 : 0;

		this->fill(this->posX - offset, this->posY - offset, this->posX + this->width + offset, this->posY + this->height + offset, enabled1 ? 0x70000000 : 0x80000000);
	}
};

struct StyledButtonWithText: StyledButton
{
	StyledButtonWithText(int id, int x, int y, int width, int height, std::string text)
		: StyledButton(id, x, y, width, height, text) {
	}

	virtual void render(struct Minecraft* mc, int32_t mx, int32_t my) {
		StyledButton::render(mc, mx, my);
		drawCenteredString(mc->font, this->maybeTextOnButton, this->posX + this->width / 2, this->posY + this->height / 2 + 1 - 4, this->active ? this->hovered(mx, my) ? 0xffffa0 : 0xffffff : 0x888888);
	}
};

extern bool hasAnimInSlot[];
extern Animation sanims[];
inline bool getAnimationFileForSlot(Animation* anim, int id) {
	if(!hasAnimInSlot[id]) return 0;
	*anim = sanims[id];
	return 1;
}
inline void setAnimationFileInSlot(int slot, std::string anim) {
	hasAnimInSlot[slot] = 1;
	int l = 0;
	std::fstream f(std::string("/home/gh/Documents/Names081/animations_for_freehij/") + anim);
	std::string str;
	std::string name = "Unnamed";
	std::vector<Frame> frames;
	std::map<BodyPart, float> frameData;
	bool inter = 0, reset = 0, inp = 0;
	bool startedFrame = 0;
	int dur;
	while(std::getline(f, str)) {
		++l;
		ltrim(str);
		rtrim(str);
		if(str.empty()) continue;
		if(Util::toLower(str).rfind("name=", 0) == 0) {
			name = str.substr(5);
		} else if(Util::toLower(str).rfind("frame ", 0) == 0) {
			if(startedFrame) {
				frames.push_back(Frame(dur, frameData));
			}
			std::string ss = str.substr(6);
			ltrim(ss);
			rtrim(ss);
			dur = std::stoi(ss);

			frameData.clear();
			startedFrame = 1;
		} else if(Util::toLower(str).rfind("interruptible", 0) == 0) {
			inter = 1;
		} else if(Util::toLower(str).rfind("resetarms", 0) == 0) {
			reset = 1;
		} else if(Util::toLower(str).rfind("interpolate", 0) == 0) {
			inp = 1;
		} else {
			std::stringstream test(str.c_str());
			std::string segment;
			std::vector<std::string> seglist;

			while(std::getline(test, segment, '=')) {
				seglist.push_back(segment);
			}
			BodyPart pt = getFromString(seglist[0]);
			frameData[pt] = std::stof(seglist[1]);
		}
	}
	if(startedFrame) {
		frames.push_back(Frame(dur, frameData));
	}
	sanims[slot] = Animation(name, frames, inter, reset, inp);
}

struct AnimationButton: StyledButtonWithText
{
	bool hasanim;
	Animation animation;
	AnimationButton()
		: StyledButtonWithText(0, 0, 0, 0, 0, "") {
	}
	AnimationButton(int id, int x, int y)
		: StyledButtonWithText(id, x, y, 50, 50, "") {
		bool a = getAnimationFileForSlot(&this->animation, id);
		hasanim = a;
		if(!a) this->maybeTextOnButton = "None";
		else this->maybeTextOnButton = this->animation.name;
	}
};
struct FolderButton: StyledButton
{
	FolderButton(int id, int x, int y)
		: StyledButton(id, x, y, 10, 10, "") {
	}
	virtual void render(struct Minecraft* mc, int32_t mx, int32_t my) {
		StyledButton::render(mc, mx, my);
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glBindTexture(GL_TEXTURE_2D, mc->texturesPtr->loadAndBindTexture("fa/textures/gui/folder.png"));
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glScalef(1.0f / 32, 1.0f / 32, 1);
		if(this->hovered(mx, my)) {
			glColor3f(0.24705882352941178F, 0.24705882352941178F, 0.1568627450980392F);
		} else {
			glColor3f(0.24705882352941178F, 0.24705882352941178F, 0.24705882352941178F);
		}
		this->blit((this->posX + 2) * 32, (this->posY + 2) * 32, 16, 16, 0, 0, 256, 256);
		if(this->hovered(mx, my)) {
			glColor3f(1.0F, 1.0F, 0.6275F);
		} else {
			glColor3f(1.0F, 1.0F, 1.0F);
		}
		this->blit((this->posX + 1) * 32, (this->posY + 1) * 32, 16, 16, 0, 0, 256, 256);
		glScalef(32, 32, 1);
		glDisable(GL_BLEND);
		glPopAttrib();
	}
};
struct Screen* createAnimScreen();
struct FileSelectionScreen: Screen
{
	std::vector<StyledButtonWithText*> controls;
	int slotID;
	FolderButton fb;
	StyledButtonWithText bk;
	StyledButtonWithText rm;
	FileSelectionScreen(int slotid)
		: fb(1, 106, 2)
		, bk(2, 2, 2, 50, 10, "Back")
		, rm(3, 54, 2, 50, 10, "Remove") {
		this->slotID = slotid;
	}

	virtual ~FileSelectionScreen() {
		for(StyledButtonWithText* b: controls) {
			delete b;
		}
		controls.clear();
	}


	virtual void setupPositions() {
		for(StyledButtonWithText* b: controls) {
			delete b;
		}
		controls.clear();
		this->buttons.clear();
		this->field_2C.clear();

		this->buttons.emplace_back(&fb);
		this->buttons.emplace_back(&bk);
		this->buttons.emplace_back(&rm);
		this->field_2C.emplace_back(&fb);
		this->field_2C.emplace_back(&bk);
		this->field_2C.emplace_back(&rm);

		int i = 0;
		DIR* d = opendir("/home/gh/Documents/Names081/animations_for_freehij/");
		struct dirent* ent;
		while((ent = readdir(d)) != NULL) {
			if("." != std::string(ent->d_name) && ".." != std::string(ent->d_name)) {
				if(Util::getExtension(std::string(ent->d_name)) == ".fa") {
					StyledButtonWithText* sb = new StyledButtonWithText(i + 10, this->width / 4, i * 16 + 14, this->width / 2, 14, std::string(ent->d_name));

					this->buttons.emplace_back(sb);
					this->field_2C.emplace_back(sb);
					this->controls.emplace_back(sb);
					++i;
				}
			}
		}
	}

	virtual void buttonClicked(Button* a2) {
		if(a2->buttonID >= 10) {
			setAnimationFileInSlot(this->slotID, a2->maybeTextOnButton);
		} else if(a2->buttonID == 3) {
			setAnimationFileInSlot(this->slotID, "");
		}
		if(a2->buttonID != 1) this->minecraft->setScreen(createAnimScreen());
	}
};

inline void selectAnimation(Animation* anim) {
	selectedAnimation = anim;
	animstate.active = 1;
	animstate.frame = 0;
	animstate.inter = anim->interuptible;
	animstate.interpol = anim->interpolable;
	animstate.resetArms = anim->resetArms;
}

struct AnimSelScreen: Screen
{
	bool selectionmode = false;
	StyledButtonWithText edit, exit, stop, settings;
	AnimationButton animbuttons[5];

	AnimSelScreen()
		: edit(11, 2, 2, 50, 10, "Edit")
		, exit(12, 54, 2, 50, 10, "Exit")
		, stop(13, 106, 2, 50, 10, "Stop")
		, settings(14, 158, 2, 50, 10, "Settings") {
	}


	virtual void setupPositions(void) {
		this->buttons.clear();
		this->field_2C.clear();
		int centerX = this->width / 2;
		int centerY = this->height / 2;
		int offset = 60;
		for(int i = 0; i < 5; i++) {
			int x = centerX - 25;
			int y = centerY - 25;
			if(i == 0) y -= offset;
			else if(i == 1) x -= offset;
			else if(i == 2) x += offset;
			else if(i == 3) {
				x -= offset / 2;
				y += offset;
			} else {
				x += offset / 2;
				y += offset;
			}

			this->animbuttons[i] = AnimationButton(i, x, y);
			this->buttons.emplace_back(this->animbuttons + i);
			this->field_2C.emplace_back(this->animbuttons + i);


			for(int i = 0; i < 5; ++i) {
				if(!this->animbuttons[i].hasanim) {
					this->animbuttons[i].active = this->selectionmode;
				}
			}
		}

		this->buttons.emplace_back(&this->edit);
		this->field_2C.emplace_back(&this->edit);
		this->buttons.emplace_back(&this->exit);
		this->field_2C.emplace_back(&this->exit);
		this->buttons.emplace_back(&this->stop);
		this->field_2C.emplace_back(&this->stop);
		this->buttons.emplace_back(&this->settings);
		this->field_2C.emplace_back(&this->settings);
	}

	void toggleSelectionMode() {
		this->selectionmode = !this->selectionmode;
		for(int i = 0; i < 5; ++i) {
			if(!this->animbuttons[i].hasanim) {
				this->animbuttons[i].active = this->selectionmode;
			}
		}
	}

	virtual void buttonClicked(Button* a2) {
		if(a2->buttonID < 6) {
			AnimationButton* b = &this->animbuttons[a2->buttonID];
			if(this->selectionmode) {
				this->minecraft->setScreen(new FileSelectionScreen(a2->buttonID));
			} else {
				selectAnimation(&this->animbuttons[a2->buttonID].animation);
			}
		} else {
			if(a2->buttonID == 11) {
				this->toggleSelectionMode();
			}
			if(a2->buttonID == 12) {
				this->minecraft->setScreen(0);
			}
			if(a2->buttonID == 13) {
			}
			if(a2->buttonID == 14) {
			}
		}
	}

	virtual void render(int32_t mx, int32_t my, float pt) {
		Screen::render(mx, my, pt);
		this->font->drawShadow("Fraem Animation (fri klif edition)", 2, this->height - 12, 0xaaaaaa);
	}
};
inline struct Screen* createAnimScreen() {
	return new AnimSelScreen();
}
