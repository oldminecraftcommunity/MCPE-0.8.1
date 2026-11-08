#include <gui/NinePatchFactory.hpp>
#include <rendering/Textures.hpp>
#include <util/IntRectangle.hpp>
#include <gui/NinePatchLayer.hpp>

NinePatchFactory::NinePatchFactory(Textures* tex, const std::string& data) : textures(tex), imagePath(data), width(1), height(1){
	TextureData* td = tex->loadAndGetTextureData(data);
	if(td){
		this->width = td->image.width;
		this->height = td->image.height;
	}
}

NinePatchLayer* NinePatchFactory::createSymmetrical(const IntRectangle& rect, int32_t a, int32_t b, float c, float d){
	NinePatchDescription desc = NinePatchDescription::createSymmetrical(this->width, this->height, rect, a, b);
	return new NinePatchLayer(desc, this->imagePath, this->textures, c, d);
}
