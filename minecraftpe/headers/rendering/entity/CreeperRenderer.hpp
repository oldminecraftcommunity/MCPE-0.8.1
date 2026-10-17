#pragma once
#include <rendering/entity/MobRenderer.hpp>
#include <math/Mth.hpp>
#include <entity/Creeper.hpp>
#include <unigl.hpp>

struct CreeperRenderer: MobRenderer
{
	CreeperRenderer(Model* a2, float a3) :
			MobRenderer(a2, a3) {
	}

	virtual ~CreeperRenderer() {
	}
	virtual int32_t getOverlayColor(Mob* a2, float a3, float a4) {
		float sw = ((Creeper*) (a2))->getSwelling(a4);
		int result = (int) (sw * 10.0f) & 1;
		if (result) {
			int v6 = (int32_t) ((sw * 0.2f) * 255.0f);
			if (v6 < 0) {
				v6 = 0;
			} else if (v6 >= 255) {
				v6 = 255;
			}

			return (v6 << 24) | 0xFFFFFF;
		}
		return result;
	}
	virtual void scale(Mob* a2, float a3) {
		float sw = ((Creeper*) (a2))->getSwelling(a3);
		float v4 = Mth::sin(sw * 100.0f) * sw * 0.01f + 1.0f;
		if (sw < 0.0f) {
			sw = 0.0f;
		} else if (sw > 1.0f) {
			sw = 1.0f;
		}

		glScalef(
			((sw * sw) * (sw * sw) * 0.4f + 1.0f) * v4,
			((sw * sw) * (sw * sw) * 0.1f + 1.0f) / v4,
			((sw * sw) * (sw * sw) * 0.4f + 1.0f) * v4
		);
	}
};
