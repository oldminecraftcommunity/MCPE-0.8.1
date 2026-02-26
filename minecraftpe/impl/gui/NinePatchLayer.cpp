#include <gui/NinePatchLayer.hpp>
#include <rendering/Textures.hpp>
#include <rendering/Tesselator.hpp>

NinePatchLayer::NinePatchLayer(const NinePatchDescription& desc, const std::string& str, Textures* tex, float w, float h) : GuiElement(1, 1, 0, 0, 24, 24), patchDescription(desc){
	this->width2 = -1;
	this->height2 = -1;
	this->field_64 = str;
	this->textures = tex;
	this->excluded = 0;
	this->setSize(w, h);
}

void NinePatchLayer::d(Tesselator& t, const NinePatchLayer::CachedQuad& q){
	t.vertexUV(q.field_0, q.field_C, q.field_10, q.field_14, q.field_20);
	t.vertexUV(q.field_4, q.field_C, q.field_10, q.field_18, q.field_20);
	t.vertexUV(q.field_4, q.field_8, q.field_10, q.field_18, q.field_1C);
	t.vertexUV(q.field_0, q.field_8, q.field_10, q.field_14, q.field_1C);
}
void NinePatchLayer::draw(struct Tesselator& t, float x, float y){
	this->textures->loadAndBindTexture(this->field_64);
	t.begin(36);
	int32_t v8 = 1;
	t.addOffset(x, y, 0);
	for(int32_t i = 0; i != 9; ++i){
		if((this->excluded & v8) == 0) {
			this->d(t, this->cachedQuads[i]);
		}
		v8 *= 2;
	}
	t.addOffset(-x, -y, 0);
	t.draw(1);


}
NinePatchLayer* NinePatchLayer::exclude(int32_t a2){
	this->setExcluded((1 << a2) | this->excluded);
	return this;
}
void NinePatchLayer::getPatchInfo(int32_t a2, int32_t a3, float& a4, float& a5, float& a6, float& a7){
	switch(a2){
		case 0:
			a4 = 0;
			a5 = this->patchDescription.field_20;
			break;
		case 1:
			a4 = this->patchDescription.field_20;
			a5 = this->width2 - this->patchDescription.field_24;
			break;
		case 2:
			a4 = this->width2 - this->patchDescription.field_24;
			a5 = this->width2;
			break;
	}

	switch(a3){
		case 0:
			a6 = 0;
			a7 = this->patchDescription.field_28;
			break;
		case 1:
			a6 = this->patchDescription.field_28;
			a7 = this->height2 - this->patchDescription.field_2C;
			break;
		case 2:
			a6 = this->height2 - this->patchDescription.field_2C;
			a7 = this->height2;
			break;
	}
}
NinePatchLayer* NinePatchLayer::setExcluded(int32_t a2){
	this->excluded = a2;
	return this;
}

NinePatchLayer::~NinePatchLayer(){

}

void NinePatchLayer::buildQuad(int32_t n){
	NinePatchLayer::CachedQuad* cq = &this->cachedQuads[n];
	int32_t v4 = n/3;
	int32_t v5 = n%3;

	cq->field_14 = *(&this->patchDescription.field_0 + v5);
	cq->field_18 = *(&this->patchDescription.field_4 + v5);
	cq->field_1C = *(&this->patchDescription.field_10 + v4);
	cq->field_20 = *(&this->patchDescription.field_14 + v4);
	cq->field_10 = 0;

	this->getPatchInfo(v5, v4, cq->field_0, cq->field_4, cq->field_8, cq->field_C);
}

void NinePatchLayer::setSize(float w, float h){
	if(w != this->width2 || h != this->height2){
		int32_t v4 = 0;
		int32_t v5;
		this->width2 = w;
		this->height2 = h;
		do{
			v5 = v4++;
			this->buildQuad(v5);
		}while(v4 != 9);
	}
}
