#include <rendering/TextureAtlas.hpp>
#include <NinecraftApp.hpp>
#include <_AssetFile.hpp>
#include <json/reader.h>
#include <rendering/TextureAtlasTextureItem.hpp>


TextureAtlas::TextureAtlas(const std::string& s)
	: path(s) {
}
TextureUVCoordinateSet TextureAtlas::_parseJSON(const Json::Value& v) {
	float minX = v[0].asFloat();
	float minY = v[1].asFloat();
	float maxX = v[2].asFloat();
	float maxY = v[3].asFloat();
	float width = v[4].asFloat();
	float height = v[5].asFloat();

	float v17 = (maxX - minX) * 0.002f;
	float v18 = (maxY - minY) * 0.002f;
	return TextureUVCoordinateSet(minX + v17, minY + v18, maxX - v17, maxY - v18, width, height);
}
TextureAtlasTextureItem* TextureAtlas::getTextureItem(const std::string& s) {
	return &this->field_4[s];
}
void TextureAtlas::load(struct NinecraftApp* mc) {
	Json::Value root;
	Json::Reader reader;
	AssetFile file = mc->platform()->readAssetFile(this->path);
	std::string data((char_t*)file.bytes, file.length);
	if(reader.parse(data, root)) {
		for(auto v32: root) {
			std::vector<TextureUVCoordinateSet> v29;
			for(auto v34 : v32["additonal_textures"]){
				v29.push_back(this->_parseJSON(v34));
			}
			std::string v25 = v32["name"].asString();
			Json::Value v33_ = v32["uv"];
			TextureUVCoordinateSet v34 = this->_parseJSON(v33_);
			this->field_4[v25] = TextureAtlasTextureItem(v25, v34, v29);
		}
	}
}
