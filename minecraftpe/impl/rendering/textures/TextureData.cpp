#include <rendering/textures/TextureData.hpp>

TextureData::TextureData(TextureData&& data){
	this->width = data.width;
	this->height = data.height;
	this->pixels = data.pixels;
	this->field_C = data.field_C;
	this->field_10 = data.field_10;
	this->lod = data.lod;
	this->field_18 = data.field_18;
	this->glTexId = data.glTexId;
	this->images = data.images;
}

TextureData::TextureData(){
	this->width = 0;
	this->height = 0;
	this->pixels = 0;
	this->field_C = 0;
	this->field_10 = 0;
	this->lod = 0;
	this->field_18 = 0;
	this->glTexId = 0;
}
