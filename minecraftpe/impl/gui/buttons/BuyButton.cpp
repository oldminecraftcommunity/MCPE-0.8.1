#include <gui/buttons/BuyButton.hpp>
#include <util/ImageDef.hpp>
#include <Minecraft.hpp>
#include <string>
#include <util/Util.hpp>
#include <rendering/Textures.hpp>
#include <rendering/Tesselator.hpp>

BuyButton::BuyButton(int32_t n) : ImageButton(n, ""){
	ImageDef img;
	img.field_0 = "";
	img.field_4 = 0;
	img.field_8 = 0;
	img.field_14 = 64;
	img.field_18 = 182;
	img.field_1C = 190;
	img.field_20 = 55;
	img.width = 75;
	img.height = 21.711;
	this->setImageDef(img, 1);
}

BuyButton::~BuyButton(){}

void BuyButton::render(Minecraft* mc, int32_t x, int32_t y){
	int32_t color;
	glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
	bool_t sel = 0;
	if(this->active){
		sel = x >= this->posX && y >= this->posY && x < (this->posX+this->width) && y < (this->posY+this->height);
	}
	this->renderBg(mc, x, y);
	std::string s;
	if(this->image.field_0.size()){
		s = this->image.field_0;
	}else{
		s = Util::EMPTY_STRING;
	}

	if(mc->texturesPtr->loadAndBindTexture(s)){
		Tesselator::instance.begin(4);
		if(this->active){
			if(sel || this->text) color = 0xFFCCCCCC;
			else color = 0xFFFFFFFF;
		}else{
			color = 0xFF808080;
		}
		Tesselator::instance.color(color);
		int32_t v13 = this->posX;
		int32_t v14 = this->image.field_4;
		int32_t v15 = this->posY;
		int32_t v16 = this->image.field_8;
		float v17 = this->image.width*0.5;
		float v18 = this->image.height*0.5;
		float v19, v20;
		if(sel){
			v19 = v17*0.95;
			v20 = v18*0.95;
		}else{
			v20 = this->image.height*0.5;
			v19 = this->image.width*0.5;
		}

		TextureData* td = mc->texturesPtr->loadAndGetTextureData(s);

		if(this->image.field_24){
			if(td){
				float width = td->width;
				float v23 = (v13+v14) + v17;
				int32_t v24 = this->image.field_18;
				float v25 = (float)this->image.field_14/width;
				float v26 = (float)(this->image.field_14 + this->image.field_1C) / width;
				float height = (float) td->height;
				float v28 = (float)(v24 + this->image.field_20) / height;
				float v29 = (float)((float)v15 + (float)v16) + v18;
				float v30 = v29 - v20;

				Tesselator::instance.vertexUV(v23-v19, v29-v20, this->zLayer, v25, (float)v24/height);
				float v31 = v29+v20;
				Tesselator::instance.vertexUV(v23-v19, v31, this->zLayer, v25, v28);
				float v32 = v23+v19;
				Tesselator::instance.vertexUV(v32, v31, this->zLayer, v26, v28);
				Tesselator::instance.vertexUV(v32, v30, this->zLayer, v26, (float)v24/height);
			}
		}
		Tesselator::instance.draw(1);
	}
}
