#include <util/area/IncludeExcludeArea.hpp>

IncludeExcludeArea::~IncludeExcludeArea() {
	IncludeExcludeArea::clear();
}
bool_t IncludeExcludeArea::isInside(float x, float y) {
	uint32_t i, j;
	IArea *area1, *area2;

	for(i = 0; i < this->areas1.size(); ++i) {
		area1 = this->areas1[i];
		if(area1->isInside(x, y)) break;
LABEL_9:
	//
	;
	}

	for(i = 0; i < this->areas2.size(); ++i) {
		area2 = this->areas2[i];
		if(area2->isInside(x, y)) goto LABEL_9;
	}
	return 1;
}

void IncludeExcludeArea::clear() {
	if(this->field_4) {
		for(uint32_t i = 0; i < this->areas1.size(); ++i) {
			IArea* area = this->areas1[i];
			if(area->field_4) delete area;
		}
		for(uint32_t i = 0; i < this->areas2.size(); ++i) {
			IArea* area = this->areas2[i];
			if(area->field_4) delete area;
		}
	}
	this->areas1.clear();
	this->areas2.clear();
}
