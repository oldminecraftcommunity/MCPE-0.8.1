#include <rendering/model/ModelPart.hpp>
#include <unigl.hpp>
#include <rendering/Tesselator.hpp>
#include <rendering/model/Cube.hpp>
#include <rendering/model/Model.hpp>
#include <algorithm>
#include <math/Mth.hpp>

ModelPart::ModelPart(struct Model* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6) : noFaceCull(0), texOffsetX(a3), texOffsetY(a4), parent(a2){
	this->_init(a5, a6);
}
ModelPart::ModelPart(int32_t a2, int32_t a3, int32_t tw, int32_t th) : noFaceCull(0), texOffsetX(a2), texOffsetY(a3), parent(0){
	this->_init(tw, th);
}
ModelPart::ModelPart(const std::string& a2): noFaceCull(0), field_38(a2), texOffsetX(0), texOffsetY(0), parent(0) {
	this->_init(64, 32);
}
void ModelPart::_init(int32_t texWidth, int32_t texHeight) {
	this->zOffset = 0;
	this->yOffset = 0;
	this->xOffset = 0;
	this->zRotAngle = 0;
	this->yRotAngle = 0;
	this->xRotAngle = 0;
	this->texWidth = texWidth;
	this->texHeight = texHeight;
	this->field_50 = 0;
	this->mirror = 0;
	this->field_4C = 0;
	this->field_1D = 1;
	this->meshBuffer.reset();
}
ModelPart* ModelPart::addBox(float a2, float a3, float a4, int32_t a5, int32_t a6, int32_t a7) {
	this->cubes.push_back(new Cube(this, this->texOffsetX, this->texOffsetY, a2, a3, a4, a5, a6, a7, 0.0f));
	return this;
}
void ModelPart::addBox(float a2, float a3, float a4, int32_t a5, int32_t a6, int32_t a7, float a8) {
	this->cubes.push_back(new Cube(this, this->texOffsetX, this->texOffsetY, a2, a3, a4, a5, a6, a7, a8));
}
ModelPart* ModelPart::addBox(const std::string& a2, float a3, float a4, float a5, int32_t a6, int32_t a7, int32_t a8) {
	std::string path = this->field_38 + "." + a2;
	Cube* c = new Cube(this, this->texOffsetX, this->texOffsetY, a3, a4, a5, a6, a7, a8, 0.0);
	this->cubes.push_back(c->setId(path));
	return this;
}
void ModelPart::addChild(ModelPart* a2) {
	this->children.push_back(a2);
}
void ModelPart::compile(float a2) {
	Tesselator::instance.begin(24 * this->cubes.size());
	for(auto& c: this->cubes) {
		c->compile(Tesselator::instance, a2);
	}
	this->meshBuffer = Tesselator::instance.end();
}
void ModelPart::draw(float a2) {
	MeshBuffer* mb = &this->meshBuffer;

	if(mb->arrayBuffer == 0 || mb->arraysCount <= 3 || mb->drawMode == 0 || mb->vertexFormat == 0) {
		this->compile(a2);
	}
	if(this->noFaceCull) {
		glDisable(GL_CULL_FACE);
		glEnable(GL_ALPHA_TEST);
		mb->render();
		glDisable(GL_ALPHA_TEST);
		glEnable(GL_CULL_FACE);
	} else {
		mb->render();
	}
}
void ModelPart::drawSlow(float) {
}
void ModelPart::mimic(const ModelPart* a2) {
	this->xOffset = a2->xOffset;
	this->yOffset = a2->yOffset;
	this->zOffset = a2->zOffset;
	this->xRotAngle = a2->xRotAngle;
	this->yRotAngle = a2->yRotAngle;
	this->zRotAngle = a2->zRotAngle;
}
ModelPart& ModelPart::operator=(const ModelPart& a2) {
	this->reset();
	if(this->field_38.size() != 0 || a2.field_38.size() != 0) this->field_38 = a2.field_38; //TODO check;
	this->texOffsetX = a2.texOffsetX;
	this->texOffsetY = a2.texOffsetY;
	this->texWidth = a2.texWidth;
	this->texHeight = a2.texHeight;
	this->mirror = a2.mirror;
	this->setModel(a2.parent);
	this->cubes.assign(a2.cubes.begin(), a2.cubes.end());
	this->mimic(&a2);
	return *this;
}
void ModelPart::render(float a2) {
	if(!this->field_4C && this->field_1D) {
		if(this->xRotAngle != 0 || this->yRotAngle != 0 || this->zRotAngle != 0) {
			glPushMatrix();
			glTranslatef(a2 * this->xOffset, a2 * this->yOffset, a2 * this->zOffset);

			if(this->zRotAngle != 0.0f) glRotatef(Mth::rad2deg(this->zRotAngle), 0.0f, 0.0f, 1.0f);
			if(this->yRotAngle != 0.0f) glRotatef(Mth::rad2deg(this->yRotAngle), 0.0f, 1.0f, 0.0f);
			if(this->xRotAngle != 0.0f) glRotatef(Mth::rad2deg(this->xRotAngle), 1.0f, 0.0f, 0.0f);

			this->draw(a2);
			if(!this->children.empty()) {
				for(int i = 0; i < this->children.size(); ++i) {
					this->children[i]->render(a2);
				}
			}

			glPopMatrix();
			return;
		}
		if(this->xOffset != 0.0f || this->yOffset != 0.0f || this->zOffset != 0.0f) {
			glPushMatrix();
			glTranslatef(a2 * this->xOffset, a2 * this->yOffset, a2 * this->zOffset);
			this->draw(a2);
			if(!this->children.empty()) {
				for(int i = 0; i < this->children.size(); ++i) {
					this->children[i]->render(a2);
				}
			}
			glPopMatrix();
			return;
		}
		this->draw(a2);
		if(!this->children.empty()) {
			for(int i = 0; i < this->children.size(); ++i) {
				this->children[i]->render(a2);
			}
		}
	}
}
void ModelPart::renderHorrible(float a2) {
	if(!this->field_4C && this->field_1D) {
		if(this->xRotAngle != 0.0f || this->yRotAngle != 0.0f || this->zRotAngle != 0.0f) {
			glPushMatrix();
			glTranslatef(a2 * this->xOffset, a2 * this->yOffset, a2 * this->zOffset);
			if(this->zRotAngle != 0.0) {
				glRotatef(Mth::rad2deg(this->zRotAngle), 0.0f, 0.0f, 1.0f);
			}
			if(this->yRotAngle != 0.0) {
				glRotatef(Mth::rad2deg(this->yRotAngle), 0.0f, 1.0f, 0.0f);
			}
			if(this->xRotAngle != 0.0) {
				glRotatef(Mth::rad2deg(this->xRotAngle), 1.0f, 0.0f, 0.0f);
			}

			this->drawSlow(a2);
			glPopMatrix();
			return;
		}
		if(this->xOffset != 0.0f || this->yOffset != 0.0f || this->zOffset != 0.0f) {
			glPushMatrix();
			glTranslatef(a2 * this->xOffset, a2 * this->yOffset, a2 * this->zOffset);
			this->drawSlow(a2);
			glPopMatrix();
			return;
		}
		this->drawSlow(a2);
	}
}
void ModelPart::reset(void) {
	for(int i = 0; i < this->cubes.size(); ++i){
		if(this->cubes[i]) delete this->cubes[i];
	}

	this->cubes.clear();
	this->setModel(0);
	this->meshBuffer.reset();
}
void ModelPart::setModel(Model* a2) {
	if(this->parent) {
		auto&& ptr = std::find(this->parent->parts.begin(), this->parent->parts.end(), this);
		if(ptr != this->parent->parts.end()) this->parent->parts.erase(ptr);
	}

	if(a2) {
		a2->parts.push_back(this);
	}
	this->parent = a2;
}
void ModelPart::setPos(float x, float y, float z) {
	this->xOffset = x;
	this->yOffset = y;
	this->zOffset = z;
}
ModelPart* ModelPart::setTexSize(int32_t a2, int32_t a3) {
	this->texWidth = a2;
	this->texHeight = a3;
	return this;
}
ModelPart* ModelPart::texOffs(int32_t a2, int32_t a3) {
	this->texOffsetX = a2;
	this->texOffsetY = a3;
	return this;
}
void ModelPart::translateTo(float a2) {
	if(this->xRotAngle == 0.0f && this->yRotAngle == 0.0f && this->zRotAngle == 0.0f) {
		if(this->xOffset != 0.0f || this->yOffset != 0.0f || this->zOffset != 0.0f) {
			glTranslatef(this->xOffset * a2, a2 * this->yOffset, a2 * this->zOffset);
		}
	} else {
		glTranslatef(a2 * this->xOffset, a2 * this->yOffset, a2 * this->zOffset);
		if(this->zRotAngle != 0.0) {
			glRotatef(Mth::rad2deg(this->zRotAngle), 0.0f, 0.0f, 1.0f);
		}
		if(this->yRotAngle != 0.0) {
			glRotatef(Mth::rad2deg(this->yRotAngle), 0.0f, 1.0f, 0.0f);
		}
		if(this->xRotAngle != 0.0) {
			glRotatef(Mth::rad2deg(this->xRotAngle), 1.0f, 0.0f, 0.0f);
		}
	}
}
ModelPart::~ModelPart() {
	this->reset();
}
