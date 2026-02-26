#include <I18n.hpp>
#include <item/ItemInstance.hpp>
#include <tile/Tile.hpp>
#include <util/Util.hpp>
#include <AppPlatform.hpp>
#include <_AssetFile.hpp>
#include <sstream>

std::map<std::string, std::string> I18n::_strings;
void I18n::loadLanguage(struct AppPlatform* a1, const std::string& a2) {
	I18n::_strings.clear();
	I18n::fillTranslations(a1, "lang/en_US.lang", 1);
	if(a2 == "en_US") {
		I18n::fillTranslations(a1, "lang/" + a2 + ".lang", 1);
	}
}

const char_t* _d6e03d98[] = {"wood", "iron", "stone", "diamond", "gold", "brick", "emerald", "lapis", "cloth"};

std::string I18n::getDescriptionString(const struct ItemInstance& a2) {
	std::string v15 = a2.getDescriptionId();
	std::string v16 = v15;
	if(a2.tileClass == Tile::cloth && Tile::cloth) {
		if(a2.getAuxValue()) {
			return I18n::get("desc.wool");
		} else {
			return I18n::get("desc.woolstring");
		}
	}
	if(Tile::fenceGate == a2.tileClass && a2.tileClass) {
		return I18n::get("desc.fence");
	}
	if(Tile::stoneSlabHalf == a2.tileClass && a2.tileClass) {
		return I18n::get("desc.slab");
	}
	v16 = Util::toLower(v16);
	if(v16[0] == 't') {
		v16 = *Util::stringReplace(v16, "tile.", "desc.", -1);
	}
	if(v16[0] == 'i') {
		v16 = *Util::stringReplace(v16, "item.", "desc.", -1);
	}

	std::string v17;
	if(!I18n::get(v16, v17)) {
		std::string _d6e09320[] = {"tile.workbench", "craftingtable", "tile.quartzBlockChiseled", "quartzBlockChiseled", "tile.quartzBlockPillar", "quartzBlockPillar"};
		Util::removeAll(v16, _d6e03d98, 9);
		if(!I18n::get(v16, v17)) {
			int32_t v9 = 0;
			while(1) {
				if(v15 == _d6e09320[v9]) {
					if(I18n::get(_d6e09320[v9 + 1] + "desc.", v17)) break; //TODO check
				}
				v9 += 2;
				if(v9 == 6) {
					return v15 + " : couldn't find desc";
				}
			}
		}
	}
	return v17;
}
bool_t I18n::get(const std::string& a1, std::string& a2) {
	auto&& v3 = I18n::_strings.find(a1);
	if(v3 == I18n::_strings.end()) {
		return 0;
	}
	a2 = v3->second;
	return 1;
}
std::string I18n::get(const std::string& a2) {
	auto&& v3 = I18n::_strings.find(a2);
	if(v3 == I18n::_strings.end()) {
		return a2 + '<';
	}
	return v3->second;
}
void I18n::fillTranslations(struct AppPlatform* a1, const std::string& a2, bool_t a3) {
	AssetFile v13 = a1->readAssetFile(a2);
	if(v13.bytes) {
		if(v13.length >= 0) {
			std::string v9((char*)v13.bytes, v13.length);
			std::stringstream v17(v9);
			for(std::string v10; std::getline(v17, v10);) {
				size_t v5 = v10.find('=');
				if(v5 != -1) {
					std::string key = Util::stringTrim(v10.substr(0, v5));
					auto&& v7 = I18n::_strings.find(key);
					if(v7 == I18n::_strings.end()) {
						std::string value = Util::stringTrim(v10.substr(v5 + 1));
						I18n::_strings.insert({key, value});
					}
				}
			}
			delete[] v13.bytes;
		}
	}
}
