#pragma once
#include <input/ITouchScreenModel.hpp>
#include <vector>
#include <input/Mouse.hpp>
#include <util/area/IArea.hpp>

struct IArea;
struct TouchAreaModel: ITouchScreenModel
{
	struct Area
	{
		IArea* area;
		int32_t field_4;
		Area(IArea* area) {
			this->area = area;
			this->field_4 = 0;
		}
	};

	std::vector<TouchAreaModel::Area*> areas;

	void addArea(int32_t a2, IArea* a3) {
		TouchAreaModel::Area* v6 = new TouchAreaModel::Area(a3);
		v6->field_4 = a2;
		this->areas.push_back(v6);
	}
	void clear() {
		for(int32_t i = 0; i < this->areas.size(); ++i) {
			TouchAreaModel::Area* area = this->areas[i];
			if(area->area) {
				if(area->area->field_4) {
					delete area->area;
				}
			}

			delete area;
			int n = this->areas.size();
		}
		this->areas.clear();
	}

	virtual ~TouchAreaModel() {
		this->clear();
	}
	virtual int32_t getPointerId(const MouseAction& a2) {
		return this->getPointerId(a2.field_0, a2.field_2, (uint8_t)a2.field_A);
	}
	virtual int32_t getPointerId(int32_t a2, int32_t a3, int32_t a4) {
		for(int32_t v7 = 0; v7 < this->areas.size(); ++v7) {
			TouchAreaModel::Area* area = this->areas[v7];
			if(area->area->isInside(a2, a3)) {
				return area->field_4;
			}
		}
		return a4;
	}
};
