#include <rendering/Font.hpp>
#include <AppPlatform.hpp>
#include <Options.hpp>
#include <rendering/Textures.hpp>
#include <math.h>
#include <rendering/Tesselator.hpp>
#include <utf8proc.h>
#include <_AssetFile.hpp>
#include <string.h>
#include <cpputils.hpp>
#include <util/Util.hpp>

Font::Font(AppPlatform* platform, Options* options, const std::string& string, Textures* textures){
	this->field_8 = 0;
	this->glyphSizes = 0;
	this->field_81C = 0;
	this->field_4 = 1;
	this->field_C = 10;
	this->field_1820.file = string;
	this->field_1820.options = options;
	this->field_1820.appPlatform = platform;
	this->field_1820.textures = textures;
	this->field_1820.field_18 = 16;
	this->field_1820.field_1C = 16;
	this->field_1820.field_10 = 0;
	this->field_1820.field_14 = 0;
	this->field_1840 = 0;
	this->init(options);
}

float Font::buildChar(int32_t a2, float a3, float a4, bool_t mb){
	int32_t v6;
	float v7, v8, v9, v10, v11, v12, v13, v14, v15;

	if(a2 == 32) return 4.0f;
	if(mb || a2 > 255){
		v6 = this->glyphSizes[a2];
		v7 = (float)(v6 >> 4);
		v8 = ((float)((v6&0xf) + 1) - v7) * 0.5f + 1.0;
	}else{
		v7 = 0;
		v8 = this->charLength[a2];
	}
	v9 = a3-v7;
	v10 = a2&0xf0;
	v11 = (16*(a2&0xf));
	v12 = v11*0.0039062;
	v13 = floor((float)(a3-v7));
	Tesselator::instance.instance.vertexUV(v13, a4+8, 0, v11*0.0039062, (float)(v10+15.99)*0.0039062);
	v14 = (float)(v11 + 15.99) * 0.0039062;
	v15 = floor((float)(v9 + 8.0));
	Tesselator::instance.instance.vertexUV(v15, a4 + 8.0, 0.0, v14, (float)(v10 + 15.99) * 0.0039062);
	Tesselator::instance.instance.vertexUV(v15, a4, 0.0, v14, v10 * 0.0039062);
	Tesselator::instance.instance.vertexUV(v13, a4, 0.0, v12, v10 * 0.0039062);
	return v8;
}

int32_t Font::charWidth(int32_t a2, bool_t a3){
	if(a2 == ' ') return 4;
	if(a2 <= 255 && !a3) return this->charWidths[a2];
	if(this->glyphSizes){
		int32_t r = this->glyphSizes[a2];
		if(r){
			return (int32_t)((r&0xf)+1 - (r>>4))/2 + 1;
		}
	}
	return 0;
}
bool_t Font::containsUnicodeChar(const std::string& a2){
	int32_t i;
	const uint8_t* data = (const uint8_t*) a2.c_str();
	int32_t len = a2.length();

	do{
		int32_t v4 = utf8proc_iterate(data, len, &i);
		if(v4 <= 0) return 0;
		data += v4;
		len -= v4;
	}while(i <= 255);
	return 1;
}
void Font::draw(const char_t* s, float x, float y, int32_t colouwur){
	this->draw(s, x, y, colouwur, 0);
}
void Font::draw(const char_t* s, float x, float y, int32_t col, bool_t shadow){
	this->drawSlow(s, strlen(s), x, y, col, shadow);
}

void Font::draw(const std::string& s, float x, float y, int32_t col){
	this->draw(s, x, y, col, 0);
}
void Font::draw(const std::string& s, float x, float y, int32_t col, bool_t shadow){
	this->drawSlow(s, x, y, col, shadow);
}
void Font::drawShadow(const char_t* s, float x, float y, int32_t col){
	this->draw(s, x+1, y+1, col, 1);
	this->draw(s, x, y, col);
}
void Font::drawShadow(const std::string& s, float x, float y, int32_t col){
	this->draw(s, x+1, y+1, col, 1);
	this->draw(s, x, y, col);
}
void Font::drawShadow(const std::string& s, float x, float y, int32_t col1, int32_t col2){
	this->draw(s, x+1, y+1, col2); //doesnt have ,1 for some reason?
	this->draw(s, x, y, col1);
}
void Font::drawSlow(const char_t* s, int32_t len, float x, float y, int32_t color, bool_t shadow){
	int32_t col = color;
	const uint8_t* ss;
	float v12, v13, v14;
	bool_t v15;
	int32_t alpha;
	int32_t v17, v18;

	int32_t v24;

	if(!s) return;

	if(shadow) col = (color & 0xff000000) + ((color & 0xfcfcfc) >> 2);
	ss = (const uint8_t*) s;
	v12 = 0;
	v13 = 0;
	v14 = -1;
	v15 = this->containsUnicodeChar(s);
	alpha = (col >> 24) & 0xff;
	if(!alpha) alpha = 255;

	int32_t r = (col >> 16) & 0xff;
	int32_t g = (col >> 8) & 0xff;
	int32_t b = col & 0xff;

	while(1){
		int32_t v18 = utf8proc_iterate(ss, len, &v24);
		if(v18 <= 0) break;
		ss += v18;
		len -= v18;
		v17 = v24/256;
		if(v24/256 != v14 && v24 != ' '){ //' ' == 32
			if(v14 != -1){
				Tesselator::instance.draw(this->field_4);
				Tesselator::instance.addOffset(-x, -y, 0);
			}

			if(v17 || v15) this->setUnicodeTexture(v17);
			else this->setDefaultTexture();

			Tesselator::instance.begin(0);
			Tesselator::instance.color(r, g, b, alpha);
			v14 = v17;
			Tesselator::instance.addOffset(x, y, 0);
		}

		if(v24 == 10){
			v13 = 0;
			v12 += this->field_C;
		}else if(v14 || v15){
			v13 = v13 + this->buildChar(v24, v13, v12, 1);
		}else{
			v13 = v13 + this->buildChar(v24, v13, v12, 0);
		}
	}

	if(v14 != -1){
		Tesselator::instance.draw(this->field_4);
		Tesselator::instance.addOffset(-x, -y, 0);
	}
	this->field_4 = 1;
}
void Font::drawSlow(const std::string& s, float x, float y, int32_t col, bool_t shadow){
	this->drawSlow(s.c_str(), s.length(), x, y, col, shadow);
}
void Font::drawTransformed(const std::string& s, float x, float y, int32_t col, float rot, float a7, bool_t a8, float a9){
	float v9 = a7;
	float pixelLength;
	if(a8 || a9 < 3.4028e38){
		pixelLength = this->getPixelLength(s);
	}else{
		pixelLength = 0;
	}
	if(pixelLength > a9){
		a9 = a7*(float)(a9/pixelLength);
	}
	glMatrixMode(0x1700u);
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glScalef(v9, v9, v9);
	glRotatef(rot, 0.0, 0.0, 1.0);

	if(a8) glTranslatef(-(float)(pixelLength * 0.5), 0.0, 0.0);
	this->draw(s, 1, 1, col, 1);
	this->draw(s, 0, 0, col);
	glPopMatrix();
}
void Font::drawWordWrap(const std::string& a2, float a3, float a4, float a5, int32_t a6, bool_t a7, bool_t a8) {
	int32_t v13 = 0;
	Util::stringSplit(a2, (int32_t)a5, this->charLength, [&a8, &a3, &a7, this, &a4, &a6, &v13](const std::string& ss, float f) {
		if(ss.size()) {
			if(a8) {
				a3 = a3 + (float)(f * 0.5);
			}
			if(a7) {
				this->drawShadow(ss, a3, a4, a6);
			} else {
				this->draw(ss, a3, a4, a6);
			}
		}
		a4 = a4 + this->field_C;
		v13 += this->field_C;
	});
}
std::vector<std::vector<std::string>> Font::getParagraphs(const std::string& a3) {
	std::vector<std::vector<std::string>> a1;
	std::vector<std::string> v13;

	splitString(a3, '\n', v13);
	for(auto&& s: v13) {
		char v15[4097];
		if(s.size() > 0x1000) break;
		strncpy(v15, s.c_str(), s.size());
		v15[s.size()] = 0;
		char* v8 = strtok(v15, " \t\r");
		std::vector<std::string> v14;
		for(char_t* i = v8; i; i = strtok(0, " \t\r")) {
			//TODO
			v14.emplace_back(i);
		}
		a1.emplace_back(v14);
	}
	return a1;
}
float Font::getPixelLength(const std::string& s){
	float v5 = 0;
	const char_t* start = s.data();
	const char_t* end = s.data() + s.length();

	while(start != end){
		char_t c = *start++;
		v5 += this->charLength[(uint8_t)c];
	}
	return v5;
}
int32_t Font::height(const std::string& s, int32_t z) {
	std::vector<std::vector<std::string>> v21 = this->getParagraphs(s);
	int32_t v5 = 0;
	for(auto&& v: v21) {
		if(v.size() == 0) {
			v5 += this->field_C;
		}
		for(int32_t v7 = 0; v7 < v.size();) {
			std::string a2 = v[v7];
			++v7;
			a2 += " ";
			while(v7 < v.size()) {
				if(this->width(a2 + v[v7]) >= z) break;
				a2 += v[v7] + " ";
				++v7;
			}
			v5 += this->field_C;
		}
	}
	return v5;
}

void Font::init(Options*){
	TextureData* data = this->field_1820.textures->loadAndGetTextureData(this->field_1820.file);
	if(data){
		int32_t v7 = this->field_1820.field_18;
		int32_t v8 = 0;
		int32_t v9 = this->field_1820.field_1C * v7;
		while(v8 < v9){
			int32_t v10 = this->field_1820.field_10 + 8*(v8%v7) + data->width*8*(v8/v7) + this->field_1820.field_14;
			int32_t v11 = 7;
			do{
				int32_t v12 = 0;
				int32_t v13 = 8;
				while(1){
					bool_t v27 = data->pixels[4*v12 + 4*v11 + 4*v10] == 0;
					if(!--v13) break;
					v12 += data->width;
					if(!v27) goto SET_CHAR_LENGTH;
				}
				if(data->pixels[4*v12 + 4*v11 + 4*v10]) break;
			}while(v11-- != 0);
			SET_CHAR_LENGTH:
			if(v8 == ' '){ //' ' == 32
				v11 = 2;
			}
			int32_t width = v11+2;
			this->charWidths[v8] = width;
			this->charLength[v8] = width;
			++v8;
		}
		for(uint32_t i = 0; i != 32; ++i){
			int32_t v18 = 85*((i>>3) & 1);
			int32_t v19 = v18 + 170 * ((i>>2) & 1);
			int32_t v20 = v18 + 170 * ((i>>1) & 1);
			int32_t v21 = v18 + 170 * (i & 1);
			if(i == 6) v19 = (v19 & 0x00) | ((v19 + 85) & 0xff);
			else if((int32_t)i > 15){
				v19 >>= 2;
				v20 >>= 2;
				v21 >>= 2;
			}
			this->field_1844[i] = ((v20 & 0xff00) << 8) | ((v19 & 0xff) << 16) | v21;
		}
		if(this->glyphSizes) delete[] this->glyphSizes;
		AssetFile file = this->field_1820.appPlatform->readAssetFile("images/font/glyph_sizes.bin");
		if(file.length == 65536){
			this->glyphSizes = file.bytes;
		}else{
			this->glyphSizes = 0;
			if(file.bytes) delete file.bytes;
		}
	}
}
void Font::setDefaultTexture(void){
	this->field_1820.textures->loadAndBindTexture(this->field_1820.file);
}
void Font::setUnicodeTexture(int32_t g){
	char_t v5[32];
	sprintf(v5, "font/glyph_%02X.png", g);
	this->field_1820.textures->loadAndBindTexture(v5);
}
int32_t Font::width(const std::string& s){
	bool_t hasUnicode = this->containsUnicodeChar(s);
	int32_t v6, v10;
	int32_t v13;
	int32_t len = s.length();
	const uint8_t* data = (const uint8_t*) s.c_str();
	v6 = 0;

	LABEL_5:
	v10 = 0;
	while(1){
		int32_t v11 = utf8proc_iterate(data, len, &v13);
		if(v11 <= 0) break;
		data += v11;
		len -= v11;
		int32_t v9 = this->charWidth(v13, hasUnicode);
		if(v13 == 10){
			if(v6 < v10) v6 = v10;
			goto LABEL_5;
		}
		if(v9 > 0) v10 += v9;
	}
	if(v10 < v6) return v6;
	return v10;
}
Font::~Font(){
	if(this->glyphSizes) delete[] this->glyphSizes;
}
