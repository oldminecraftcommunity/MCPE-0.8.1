#pragma once
#include <_types.h>

struct MouseHandler{
	float field_0, field_4;
	int32_t field_8;
	struct ITurnInput* turnInput;

	MouseHandler(struct ITurnInput*);
	MouseHandler(void);
	void grab();
	void poll();
	void release();
	void setTurnInput(struct ITurnInput*);
	~MouseHandler();
};

