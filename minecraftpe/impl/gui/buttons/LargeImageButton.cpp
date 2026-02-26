#include <gui/buttons/LargeImageButton.hpp>
#include <GL/gl.h>
#include <Minecraft.hpp>
#include <rendering/Textures.hpp>
#include <rendering/Tesselator.hpp>

LargeImageButton::LargeImageButton(int32_t a2, const std::string& s) : ImageButton(a2, s){
	this->setupDefault();
}

LargeImageButton::LargeImageButton(int32_t a2, const std::string& s, ImageDef& img) : ImageButton(a2, s){
	this->image = img;
	this->setupDefault();
}

LargeImageButton::~LargeImageButton(){}
void LargeImageButton::render(struct Minecraft* mc, int32_t x, int32_t y){
	if(this->visible){
		glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
		bool_t active = this->active;
		if(this->active){
			active = this->pressed;
			if(this->pressed){
				active = x >= this->posX && y >= this->posY && x < (this->posX+this->width) && y < (this->posY+this->height);
			}
		}

		this->renderBg(mc, x, y);
		if(this->image.field_0.size()){
			if(mc->texturesPtr->loadAndBindTexture(this->image.field_0)){
				Tesselator::instance.begin(4);
				int32_t col;
				if(this->active){
					col = 0xffffffff;
				}else{
					col = 0xff808080;
				}

				Tesselator::instance.color(col);
				float v13 = this->image.width*0.5;
				float v14 = this->image.height*0.5;
				float v15 = this->field_6C;
				float v16 = ((float)this->posX + (float)this->image.field_4) + v13;
				float v17 = ((float)this->posY + (float)this->image.field_8) + v14;
				float v18;
				if(active){
					v18 = v15-0.025;
					if((v15-0.025) <= 0.95){
						v18 = 0.95;
					}
				}else{
					v18 = v15+0.025;
					if((v15+0.025) >= 1.0){
						v18 = 1.0;
					}
				}

				int32_t v19 = this->image.field_24;
				this->field_6C = v18;
				float v20 = this->field_6C;
				float v21 = v13*v20;
				float v22 = v14*v20;
				if(v19){
					TextureData* td = mc->texturesPtr->loadAndGetTextureData(this->image.field_0);
					if(td){
						int32_t v24 = this->image.field_14;
						int32_t v25;
						if(active) v25 = this->image.field_1C;
						else v25 = 0;

						float width = td->width;
						int32_t v27 = v24+v25;
						int32_t v28 = this->image.field_1C;
						float v29 = (float)v27/width;

						if(active) v28 *= 2;
						int32_t v30 = this->image.field_18;
						float v31 = (float)(v24+v28) / width;
						float height = td->height;
						float v33 = (float)(v30 + this->image.field_20)/height;
						float v34 = v17-v22;

						Tesselator::instance.vertexUV(v16-v21, v17-v22, this->zLayer, v29, (float)v30/height);
						float v35 = v17+v22;
						Tesselator::instance.vertexUV(v16-v21, v35, this->zLayer, v29, v33);
						float v36 = v16+v21;
						Tesselator::instance.vertexUV(v36, v35, this->zLayer, v31, v33);
						Tesselator::instance.vertexUV(v36, v34, this->zLayer, v31, (float)v30/height);
					}
				}else{
					float v37 = v17-v22;
					Tesselator::instance.vertexUV(v16-v21, v17-v22, this->zLayer, 0, 0);
					float v38 = v17+v22;
					Tesselator::instance.vertexUV(v16-v21, v38, this->zLayer, 0, 1);
					float v39 = v16+v21;
					Tesselator::instance.vertexUV(v39, v38, this->zLayer, 1, 1);
					Tesselator::instance.vertexUV(v39, v37, this->zLayer, 1, 0);
				}
				Tesselator::instance.draw(1);
			}
		}
		if(this->active){
			int32_t v40, v41, a5, v42;
			if(this->active || this->text){
				v40 = this->posX;
				v41 = this->width + ((uint32_t)this->width >> 31);
				a5 = this->posY+11;
				v42 = 0xffffa0;
			}else{
				v40 = this->posX;
				a5 = this->posY+11;
				v42 = 0xe0e0e0;
				v41 = this->width + ((uint32_t)this->width >> 31);
			}
			this->drawCenteredString(mc->font, this->maybeTextOnButton, v40+(v41>>1), a5, v42);
		}else{
			this->drawCenteredString(mc->font, this->maybeTextOnButton, this->posX + this->width/2, this->posY+11, 0xffa0a0a0);
		}
	}
}
void LargeImageButton::setupDefault(){
	this->field_6C = 1;
	this->width = 72;
	this->height = 72;
}
