#pragma once
#include <_types.h>
#include <AppPlatform.hpp>
#include <rendering/model/ModelPart.hpp>

struct Entity;
struct Mob;
struct Model: AppPlatform::Listener
{
	float field_0;
	int8_t field_4, field_5, field_6, field_7;
	std::vector<ModelPart*> parts;
	int8_t field_14, field_15, field_16, field_17;

	Model() : field_0(0), field_4(0), field_5(0){
		this->field_14 = 1;
		AppPlatform::_singleton->addListener(this, 1.0);
	}
	virtual ~Model() {
		AppPlatform::_singleton->removeListener(this);
		for(auto& p: this->parts) {
			if(p) delete p;
		}
	}
	virtual void onAppSuspended() {
		this->clear();
	}
	virtual void clear() {
		for(int i = 0; i < this->parts.size(); ++i) {
			this->parts[i]->meshBuffer.reset();
		}
	}
	virtual void render(){}
	virtual void render(Entity*, float, float, float, float, float, float) {
		this->render();
	}
	virtual void renderHorrible(float, float, float, float, float, float){}
	virtual void setupAnim(float, float, float, float, float, float){}
	virtual void prepareMobModel(Mob*, float, float, float){}
};
