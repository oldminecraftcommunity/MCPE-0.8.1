#include <gui/buttons/ImageButton.hpp>
#include <GL/gl.h>
#include <string>
#include <Minecraft.hpp>
#include <rendering/Textures.hpp>
#include <rendering/Tesselator.hpp>


ImageButton::ImageButton(int32_t a2, const std::string& a3) : Button(a2, a3), color(Color4::WHITE){
	this->image.width = 16;
	this->image.field_0 = "";
	this->image.field_4 = 0;
	this->image.field_8 = 0;
	this->image.field_14 = 0;
	this->image.field_18 = 0;
	this->image.field_24 = 0;
	this->image.height = 16;
	this->image.field_1C = 1;
	this->image.field_20 = 1;
	this->yOffset = 16;
	this->setupDefault();
}
ImageButton::ImageButton(int32_t a2, const std::string & a3, const struct ImageDef& a4) : Button(a2, a3), color(Color4::WHITE){
	this->image = a4;
	this->yOffset = 16;
	this->setupDefault();

}
void ImageButton::setImageDef(const ImageDef& a4, bool_t b){
	this->image = a4;
	if(b){
		this->width = a4.width;
		this->height = a4.height;
	}
}

//do i even have to fill then somehow~?
ImageButton::~ImageButton(){

}
void ImageButton::render(struct Minecraft* mc, int32_t x, int32_t y){
	if(this->visible){
		glColor4f(this->color.r, this->color.g, this->color.b, this->color.a);
		bool_t active = this->active;
		if(this->active){
			active = this->pressed;
			if(this->pressed){
				active = x >= this->posX && y >= this->posY && x < (this->posX+this->width) && y < (this->posY+this->height);
			}
		}
		bool_t second = this->isSecondImage(active);
		this->renderBg(mc, x, y);
		if(this->image.field_0.size()){
			if(mc->texturesPtr->loadAndBindTexture(this->image.field_0)){
				Tesselator::instance.begin(4);
				int32_t col;
				if(this->active) col = 0xffffffff;
				else col = 0xff808080;
				Tesselator::instance.color(col);
				float v14 = (float)(this->image.width*0.5) * ((float)this->width/this->image.width);
				float v15 = (float)(this->image.height*0.5) * ((float)this->height/this->image.height);
				float v16 = ((float)this->posX + (float)this->image.field_4)+v14;
				float v17 = ((float)this->posY + (float)this->image.field_8)+v15;
				if(this->field_64){
					if(active){
						v14 *= 0.95;
						v15 *= 0.95;
					}
				}
				if(this->image.field_24){
					TextureData* td = mc->texturesPtr->loadAndGetTextureData(this->image.field_0);
					if(td){
						int32_t v20;
						int32_t v19 = this->image.field_14;
						if(second) v20 = this->image.field_1C;
						else v20 = 0;

						float width = td->width;
						int32_t v22 = v19+v20;
						int32_t v23 = this->image.field_1C;
						float v24 = (float)v22 / width;
						if(second) v23 *= 2;
						int32_t v25 = this->image.field_18;
						float v26 = (float)(v19 + v23) / width;
						float height = td->height;
						float v28 = (float)(v25+this->image.field_20) / height;
						float v29 = v17-v15;
						Tesselator::instance.vertexUV(v16-v14, v17-v15, this->zLayer, v24, (float)v25/height);
						float v30 = v17+v15;
						Tesselator::instance.vertexUV(v16-v14, v30, this->zLayer, v24, v28);
						float v31 = v16+v14;
						Tesselator::instance.vertexUV(v31, v30, this->zLayer, v26, v28);
						Tesselator::instance.vertexUV(v31, v29, this->zLayer, v26, (float)v25/height);
					}
				}else{
					float v32 = v17-v15;
					Tesselator::instance.vertexUV(v16-v14, v17-v15, this->zLayer, 0, 0);
					float v33 = v17+v15;
					Tesselator::instance.vertexUV(v16-v14, v33, this->zLayer, 0, 1);
					float v34 = v16+v14;
					Tesselator::instance.vertexUV(v34, v33, this->zLayer, 1, 1);
					Tesselator::instance.vertexUV(v34, v32, this->zLayer, 1, 0);
				}
				Tesselator::instance.draw(1);

			}
		}

		if(this->active){
			int32_t v35, v36, a5, v37;
			if(active || this->text){
				v35 = this->width + ((uint32_t)this->width >> 31);
				v36 = this->posX;
				a5 = this->posY + this->yOffset + 1;
				v37 = 0xffffa0;
			}else{
				v36 = this->posX;
				v35 = this->width + ((uint32_t)this->width >> 31);
				a5 = this->posY + this->yOffset;
				v37 = 0xe0e0e0;
			}
			this->drawCenteredString(mc->font, this->maybeTextOnButton, v36+(v35>>1), a5, v37);
		}else{
			this->drawCenteredString(mc->font, this->maybeTextOnButton, this->posY+this->width/2, this->posY+this->yOffset, 0xffa0a0a0);
		}
	}
}
void ImageButton::renderBg(struct Minecraft*, int32_t, int32_t){}
void ImageButton::setYOffset(int32_t a2){
	this->yOffset = a2;
}
void ImageButton::setupDefault(void){
	this->width = 48;
	this->height = 48;
	this->field_64 = 1;
}
bool_t ImageButton::isSecondImage(bool_t a2){
	return a2;
}
