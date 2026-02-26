#pragma once
#include <input/ITouchScreenModel.hpp>
#include <vector>

struct IArea;
struct TouchAreaModel: ITouchScreenModel
{
	struct Area
	{
		IArea* area;
		int32_t field_4;
		Area(IArea* area);
	};

	std::vector<TouchAreaModel::Area*> areas;

	void addArea(int32_t, IArea*);
	void clear();

	virtual ~TouchAreaModel();
	virtual int32_t getPointerId(const MouseAction&);
	virtual int32_t getPointerId(int32_t, int32_t, int32_t);
};
