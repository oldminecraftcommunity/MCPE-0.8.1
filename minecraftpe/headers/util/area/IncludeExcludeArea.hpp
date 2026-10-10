#pragma once
#include <util/area/IArea.hpp>
#include <vector>

struct IncludeExcludeArea: IArea
{
	std::vector<IArea*> includeAreas;
	std::vector<IArea*> excludeAreas;

	virtual ~IncludeExcludeArea() {
		IncludeExcludeArea::clear();
		//TODO i wonder how to force std::vector<IArea *>::~vector to be sub_XXXXX here
	}
	virtual bool_t isInside(float x, float y) {
		for(uint32_t i = 0; i < this->includeAreas.size(); ++i) {
			if(this->includeAreas[i]->isInside(x, y)) {
				for (uint32_t j = 0; j < this->excludeAreas.size(); ++j) {
					if (this->excludeAreas[j]->isInside(x, y)) goto LABEL_9;
				}
				return 1;
			}
			LABEL_9:
			//
			;
		}
		return 0;
	}
	void clear() {
		if (this->field_4) {
			for (uint32_t i = 0; i < this->includeAreas.size(); ++i) {
				IArea* area = this->includeAreas[i];
				if (area->field_4) delete area;
			}
			for (uint32_t i = 0; i < this->excludeAreas.size(); ++i) {
				IArea* area = this->excludeAreas[i];
				if (area->field_4) delete area;
			}
		}
		this->includeAreas.clear();
		this->excludeAreas.clear();
	}
};
