#pragma once
#include <_types.h>

struct AdventureSettings{
	int8_t daylightCycle;
	int8_t enablePVPMaybe;
	int8_t enablePVEMaybe;
	int8_t field_3;
	int8_t allowInteract;
	int8_t field_5;
	char align1, align2;

	AdventureSettings();
};
