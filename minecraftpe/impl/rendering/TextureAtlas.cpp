#include <rendering/TextureAtlas.hpp>
#include <NinecraftApp.hpp>
#include <_AssetFile.hpp>
#include <json/reader.h>
#include <rendering/TextureAtlasTextureItem.hpp>


TextureAtlas::TextureAtlas(const std::string& s){
	this->path = s;
}
TextureUVCoordinateSet TextureAtlas::_parseJSON(const Json::Value& v){
	float v17 = (v[2].asFloat() - v[0].asFloat()) * 0.002;
	float v18 = (v[3].asFloat() - v[1].asFloat()) * 0.002;

	TextureUVCoordinateSet t;
	t.width = v[4].asFloat();
	t.height = v[5].asFloat();
	t.minX = v[0].asFloat() + v17;
	t.maxX = v[2].asFloat() - v17;
	t.minY = v[1].asFloat() + v18;
	t.maxY = v[3].asFloat() - v18;
	return t;
}
TextureAtlasTextureItem* TextureAtlas::getTextureItem(const std::string& s){
	return &this->field_4[s];
}
void TextureAtlas::load(struct NinecraftApp* mc){
	Json::Reader reader;
	Json::Value root;
	AssetFile file = mc->platform()->readAssetFile(this->path);
	std::string data((char_t*) file.bytes, file.length);
	if(reader.parse(data, root, 1)){
		Json::Value::iterator v27 = root.begin();
		Json::Value::iterator v28 = root.end();

		while(v27 !=v28){
			{
				Json	::Value v32(*v27);
				std::vector<TextureUVCoordinateSet> v29;
				Json	::Value v6 = v32["additonal_textures"];
				Json::Value::iterator v30 = v6.begin();
				Json::Value::iterator v33 = v6.end();
				while(v30 != v33){
					{
						Json::Value v34(*v30);
						TextureUVCoordinateSet uv = this->_parseJSON(v34);
						v29.emplace_back(uv);
					}
					++v30;
				}
				std::string v25 = v32["name"].asString();
				Json::Value v33_ = v32["uv"];
				TextureUVCoordinateSet v34 = this->_parseJSON(v33_);
				this->field_4[v25] = TextureAtlasTextureItem(v25, v34, v29);
			}
			++v27;
		}
	}

	//TODO free assetfile?
}
