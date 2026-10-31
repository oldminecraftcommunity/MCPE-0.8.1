#pragma once
#include <_types.h>
#include <string>

struct ImageDef{
	std::string texture;
	int32_t xOff, yOff;
	float width, height;
	int32_t texXStart, texYStart, texWidth, texHeight;
	bool initialized;

	ImageDef() {
		this->xOff = 0;
		this->yOff = 0;
		this->texXStart = 0;
		this->width = 16;
		this->height = 16;
		this->texYStart = 0;
		this->texWidth = 1;
		this->texHeight = 1;
		this->initialized = 0;
	}
	ImageDef(const char* tex, int xOff, int yOff, int tx, int ty, int tw, int th) : initialized(1), xOff(xOff), yOff(yOff), width(16), height(16), texXStart(tx), texYStart(ty), texWidth(tw), texHeight(th) {
		this->texture = tex;
	}
	ImageDef(const char* tex, int xOff, int yOff, float w, float h, int tx, int ty, int tw, int th) : initialized(1), xOff(xOff), yOff(yOff), texXStart(tx), texYStart(ty), texWidth(tw), texHeight(th) {
		this->width = w;
		this->height = h;
		this->texture = tex;
	}
};

