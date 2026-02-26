#include <gui/NinePatchFactory.hpp>
#include <rendering/Textures.hpp>
#include <util/IntRectangle.hpp>
#include <gui/NinePatchLayer.hpp>

NinePatchFactory::NinePatchFactory(Textures* tex, const std::string& data){
	this->textures = tex;
	this->imagePath = data;
	this->width = this->height = 1;
	TextureData* td = this->textures->loadAndGetTextureData(data);
	if(td){
		this->width = td->width;
		this->height = td->height;
	}
}

NinePatchLayer* NinePatchFactory::createSymmetrical(const IntRectangle& rect, int32_t a, int32_t b, float c, float d){
	NinePatchDescription desc = NinePatchDescription::createSymmetrical(this->width, this->height, rect, a, b);
	return new NinePatchLayer(desc, this->imagePath, this->textures, c, d);
}
