#include <rendering/Textures.hpp>
#include <rendering/textures/DynamicTexture.hpp>
#include <Options.hpp>
#include <AppPlatform.hpp>
#include <string.h>

int32_t Textures::textureChanges = 0;

Textures::Textures(Options* options, AppPlatform* platform){
	this->options = options;
	this->platform = platform;
	this->currentTexture = 0;
}

void Textures::_loadTexImage(const ImageData& data){
	int32_t v3 = data.field_C;
	printf("%d\n", (uint32_t)(v3-5));
	if((uint32_t)(v3-5) > 2){
		switch(v3){
			case 2:
				glTexImage2D(GL_TEXTURE_2D, data.lod, GL_RGB, data.width, data.height, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, data.pixels);
				break;
			case 4:
				glTexImage2D(GL_TEXTURE_2D, data.lod, GL_RGBA, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_SHORT_4_4_4_4, data.pixels);
				break;
			case 3:
				glTexImage2D(GL_TEXTURE_2D, data.lod, GL_RGBA, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_SHORT_5_5_5_1, data.pixels);
				break;
			default:
				if(v3){
					if(v3 == 1){
						glTexImage2D(GL_TEXTURE_2D, data.lod, GL_RGB, data.width, data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.pixels);
					}
				}
				else{
					glTexImage2D(GL_TEXTURE_2D, data.lod, GL_RGBA, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.pixels);
				}
				break;
		}
	}
}

void Textures::addDynamicTexture(DynamicTexture* a2){
	this->dynamicTextures.emplace_back(a2);
	a2->tick();
}

int32_t Textures::assignTexture(const std::string& s, TextureData& d, bool_t b){
	int32_t v8;

	glGenTextures(1, &d.glTexId);
	this->bind(d.glTexId);
	if(b){
		glTexParameteri(GL_TEXTURE_2D, 0x2802u, 33071);
		glTexParameteri(GL_TEXTURE_2D, 0x2803u, 33071);
		glTexParameteri(GL_TEXTURE_2D, 0x2801u, 9729);
		v8 = 9729;
	}
	else{
		glTexParameteri(GL_TEXTURE_2D, 0x2802u, 10497);
		glTexParameteri(GL_TEXTURE_2D, 0x2803u, 10497);
		glTexParameteri(GL_TEXTURE_2D, 0x2801u, 9728);
		v8 = 9728;
	}

	glTexParameteri(GL_TEXTURE_2D, 0x2800u, v8);
	this->_loadTexImage(d);
	if(d.images.begin() != d.images.end()){
		if(AppPlatform::TEXTURE_MAX_LEVEL){
			glTexParameteri(GL_TEXTURE_2D, AppPlatform::TEXTURE_MAX_LEVEL, 4);
		}

		for(ImageData data : d.images){
			this->_loadTexImage(data); //creates a copy
		}

		 glTexParameteri(GL_TEXTURE_2D, 0x2801u, 9986);
	}

	TextureData& td = this->textures[s];
	td.width = d.width;
	td.height = d.height;
	td.pixels = d.pixels;
	td.field_C = d.field_C;
	td.field_10 = d.field_10;
	td.lod = d.lod;
	td.field_18 = d.field_18;
	td.glTexId = d.glTexId;
	td.images = d.images;

	return d.glTexId;
}

void Textures::bind(uint32_t t){
	if(t){
		if(this->currentTexture != t){
			glBindTexture(GL_TEXTURE_2D, t);
			this->currentTexture = t;
			++Textures::textureChanges;
		}
	}
}

void Textures::clear(bool_t a2){
	//XXX pain (need to check)
	for(auto&& p: this->textures) {
		if(p.second.glTexId) {
			glDeleteTextures(1, &p.second.glTexId);
			p.second.glTexId = 0;
		}
	}

	this->currentTexture = 0;
	if(a2){
		for(auto&& p: this->textures) {
			if(!p.second.field_18) {
				free(p.second.pixels);
			}
		}
		this->textures.clear();
	}
}

int32_t Textures::crispBlend(int32_t a, int32_t b){
	int32_t v3 = b >> 24;
	int32_t v4 = a >> 24;
	int32_t v5 = (a >> 24) + (b >> 24);
	if(v5) v5 = 255;
	else v3 = 1;

	if(!((a >> 24) + (b >> 24))) v4 = v3;

	return ((int32_t)((b&0xff) * v3 + v4 * (a&0xff)) / (int32_t)(v4 + v3)) | (v5 << 24) | (((int32_t)(((b&0xff0000) >> 16) * v3 + v4 * ((a&0xff0000) >> 16)) / (int32_t)(v4 + v3)) << 16) | (((int32_t)(v3 * ((b&0xff00) >> 8) + v4 * ((a&0xff00) >> 8)) / (int32_t)(v4 + v3)) << 8);
}

int32_t Textures::loadAndBindTexture(const std::string& s){
	int32_t t = this->loadTexture(s, 1, 0);
	if(t) this->bind(t);
	return t;
}

TextureData* Textures::loadAndGetTextureData(const std::string& s){
	int32_t t = this->loadTexture(s, 1, 0);
	if(t) return &this->textures[s];
	return 0;
}

int32_t Textures::loadTexture(const std::string& s, bool_t a, bool_t b){
	//XXX pain (need to check)
	if(this->textures.count(s) <= 0){
		TextureData data = this->platform->loadTexture(s, a);
		return this->assignTexture(s, data, b);
	}else{
		if(this->textures[s].glTexId) return this->textures[s].glTexId;
		return this->assignTexture(s, this->textures[s], b);
	}

}

void Textures::reloadAll(){}

int32_t Textures::smoothBlend(int32_t a, int32_t b){
	return ((int32_t)((a & 0xFEFEFE) + (b & 0xFEFEFE)) >> 1) + ((int32_t)((b >> 24) + (a >> 24)) >> 1 << 24);
}
static char_t byte_D6E06B78[0x1000];

void Textures::tick(bool_t a2) {
	for(int32_t i = 0; i < this->dynamicTextures.size(); ++i) {
		this->dynamicTextures[i]->tick();
	}
	if(a2) {
		for(int32_t i = 0; i < this->dynamicTextures.size(); ++i) {
			DynamicTexture* v7 = this->dynamicTextures[i];
			v7->bindTexture(this);
			if(v7->field_18 == 1) {
				glTexSubImage2D(0xDE1u, 0, (int32_t)(float)(v7->uv.minX * v7->uv.width), (int32_t)(float)(v7->uv.minY * v7->uv.height), (int32_t)(float)((float)((float)(v7->uv.maxX - v7->uv.minX) * v7->uv.width) + 0.49), (int32_t)(float)((float)((float)(v7->uv.maxY - v7->uv.minY) * v7->uv.height) + 0.49) + 1, 0x1908u, 0x1401u, v7->data);
			} else if(v7->field_18 == 2) {
				uint8_t* data = v7->data;
				char_t* v10 = &byte_D6E06B78[0x40]; //TODO figure out what is this
				int32_t v11 = 0;
				do {
					memcpy(v10 - 0x40, &data[v11], 0x40);
					memcpy(v10, &data[v11], 0x40); //0.7.2 has memcpys here
					v10 += 0x80;
					v11 = ((int16_t)v11 + 64) & 0x3FF;
				}
				while ( v10 < &byte_D6E06B78[0x1000] );
				glTexSubImage2D(0xDE1u, 0, (int)(float)(v7->uv.minX * v7->uv.width), (int)(float)(v7->uv.minY * v7->uv.height), 2 * (int)(float)((float)((float)(v7->uv.maxX - v7->uv.minX) * v7->uv.width) + 0.49), 2 * (int)(float)((float)((float)(v7->uv.maxY - v7->uv.minY) * v7->uv.height) + 0.49), 0x1908u, 0x1401u, byte_D6E06B78);
			}
		}

	}
	//TODO dynamic texture ticking
}

Textures::~Textures(){
	this->clear(1);

	for(int v2 = 0; v2 < this->dynamicTextures.size(); ++v2) {
		DynamicTexture* v3 = this->dynamicTextures[v2];
		if(v3) {
			delete v3;
		}
	}

}
