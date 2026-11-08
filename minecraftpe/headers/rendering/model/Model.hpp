#pragma once
#include <_types.h>
#include <AppPlatform.hpp>
#include <rendering/model/ModelPart.hpp>

struct Entity;
struct Mob;
struct Model: AppPlatform::Listener
{
	float field_0;
	bool riding, field_5;
	std::vector<ModelPart*> parts;
	bool field_14;

	Model() : field_0(0), riding(0), field_5(0){
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
