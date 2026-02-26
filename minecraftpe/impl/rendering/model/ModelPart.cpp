#include <rendering/model/ModelPart.hpp>
#include <GL/gl.h>
#include <rendering/Tesselator.hpp>
#include <rendering/model/Cube.hpp>
#include <rendering/model/Model.hpp>
#include <algorithm>
ModelPart::ModelPart() : ModelPart(0, 0, 64, 32){

}
ModelPart::ModelPart(struct Model* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6) {
	this->field_0 = 0;
	this->texOffsetX = a3;
	this->texOffsetY = a4;
	this->field_38 = "";
	this->parent = a2;
	this->_init(a5, a6);
}
ModelPart::ModelPart(int32_t a2, int32_t a3, int32_t tw, int32_t th) {
	this->field_0 = 0;
	this->texOffsetX = a2;
	this->texOffsetY = a3;
	this->field_38 = "";
	this->parent = 0;
	this->_init(tw, th);
}
ModelPart::ModelPart(const std::string& a2) {
	this->field_0 = 0;
	this->field_38 = a2;
	this->texOffsetX = 0;
	this->texOffsetY = 0;
	this->parent = 0;
	this->_init(64, 32);
}
void ModelPart::_init(int32_t texWidth, int32_t texHeight) {
	this->zOffset = 0.0;
	this->yOffset = 0.0;
	this->xOffset = 0.0;
	this->zRotAngle = 0.0;
	this->yRotAngle = 0.0;
	this->xRotAngle = 0.0;
	this->texWidth = (float)texWidth;
	this->field_50 = 0;
	this->mirror = 0;
	this->field_1D = 1;
	this->field_4C = 0;
	this->texHeight = (float)texHeight;
	this->meshBuffer.reset();
}
void ModelPart::addBox(float a2, float a3, float a4, int32_t a5, int32_t a6, int32_t a7) {
	this->cubes.emplace_back(new Cube(this, this->texOffsetX, this->texOffsetY, a2, a3, a4, a5, a6, a7, 0.0));
}
void ModelPart::addBox(float a2, float a3, float a4, int32_t a5, int32_t a6, int32_t a7, float a8) {
	this->cubes.emplace_back(new Cube(this, this->texOffsetX, this->texOffsetY, a2, a3, a4, a5, a6, a7, a8));
}
void ModelPart::addBox(const std::string& a2, float a3, float a4, float a5, int32_t a6, int32_t a7, int32_t a8) {
	std::string path = this->field_38 + "." + a2;
	Cube* c = new Cube(this, this->texOffsetX, this->texOffsetY, a3, a4, a5, a6, a7, a8, 0.0);
	this->cubes.emplace_back(c->setId(path));
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
	MeshBuffer* p_meshBuffer; // r5

	p_meshBuffer = &this->meshBuffer;
	if(!this->meshBuffer.arrayBuffer || this->meshBuffer.arraysCount <= 3 || !this->meshBuffer.drawMode || !this->meshBuffer.vertexFormat) {
		this->compile(a2);
	}
	if(this->field_0) {
		glDisable(0xB44u);
		glEnable(0xBC0u);
		p_meshBuffer->render();
		glDisable(0xBC0u);
		glEnable(0xB44u);
	} else {
		p_meshBuffer->render();
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
	float zRotAngle; // s15
	float yRotAngle; // s15
	float xRotAngle; // s15

	if(!this->field_4C && this->field_1D) {
		if(this->xRotAngle != 0.0 || this->yRotAngle != 0.0 || this->zRotAngle != 0.0) {
			glPushMatrix();
			glTranslatef(a2 * this->xOffset, a2 * this->yOffset, a2 * this->zOffset);
			zRotAngle = this->zRotAngle;
			if(zRotAngle != 0.0) {
				glRotatef(zRotAngle * 57.296, 0.0, 0.0, 1.0);
			}
			yRotAngle = this->yRotAngle;
			if(yRotAngle != 0.0) {
				glRotatef(yRotAngle * 57.296, 0.0, 1.0, 0.0);
			}
			xRotAngle = this->xRotAngle;
			if(xRotAngle != 0.0) {
				glRotatef(xRotAngle * 57.296, 1.0, 0.0, 0.0);
			}
			this->draw(a2);
			if(this->children.begin() != this->children.end()) {
				for(auto& p: this->children) {
					p->render(a2);
				}
			}
LABEL_14:
			glPopMatrix();
			return;
		}
		if(this->xOffset != 0.0 || this->yOffset != 0.0 || this->zOffset != 0.0) {
			glPushMatrix();
			glTranslatef(a2 * this->xOffset, a2 * this->yOffset, a2 * this->zOffset);
			this->draw(a2);
			if(this->children.begin() != this->children.end()) {
				for(auto& p: this->children) {
					p->render(a2);
				}
			}
			goto LABEL_14;
		}
		this->draw(a2);
		if(this->children.begin() != this->children.end()) {
			for(auto& p: this->children) {
				p->render(a2);
			}
		}
	}
}
void ModelPart::renderHorrible(float a2) {
	float zRotAngle; // s15
	float yRotAngle; // s15
	float xRotAngle; // s15

	if(!this->field_4C && this->field_1D) {
		if(this->xRotAngle != 0.0 || this->yRotAngle != 0.0 || this->zRotAngle != 0.0) {
			glPushMatrix();
			glTranslatef(a2 * this->xOffset, a2 * this->yOffset, a2 * this->zOffset);
			zRotAngle = this->zRotAngle;
			if(zRotAngle != 0.0) {
				glRotatef(zRotAngle * 57.296, 0.0, 0.0, 1.0);
			}
			yRotAngle = this->yRotAngle;
			if(yRotAngle != 0.0) {
				glRotatef(yRotAngle * 57.296, 0.0, 1.0, 0.0);
			}
			xRotAngle = this->xRotAngle;
			if(xRotAngle != 0.0) {
				glRotatef(xRotAngle * 57.296, 1.0, 0.0, 0.0);
			}
			goto LABEL_16;
		}
		if(this->xOffset != 0.0 || this->yOffset != 0.0 || this->zOffset != 0.0) {
			glPushMatrix();
			glTranslatef(a2 * this->xOffset, a2 * this->yOffset, a2 * this->zOffset);
LABEL_16:
			this->drawSlow(a2);
			glPopMatrix();
			return;
		}
		this->drawSlow(a2);
	}
}
void ModelPart::reset(void) {
	for(auto& c: this->cubes) {
		if(c) delete c;
	}
	this->cubes.clear();
	this->setModel(0);
	this->meshBuffer.reset();
}
void ModelPart::setModel(Model* a2) {
	if(this->parent) {
		auto&& ptr = std::find(this->parent->parts.begin(), this->parent->parts.end(), this);
		if(ptr != this->parent->parts.end()) {
			this->parent->parts.erase(ptr); //TODO check
		}
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
	float zRotAngle; // s15
	float yRotAngle; // s15
	float xRotAngle; // s15
	float xOffset; // s14

	if(this->xRotAngle == 0.0 && this->yRotAngle == 0.0 && this->zRotAngle == 0.0) {
		xOffset = this->xOffset;
		if(xOffset != 0.0 || this->yOffset != 0.0 || this->zOffset != 0.0) {
			glTranslatef(xOffset * a2, a2 * this->yOffset, a2 * this->zOffset);
		}
	} else {
		glTranslatef(a2 * this->xOffset, a2 * this->yOffset, a2 * this->zOffset);
		zRotAngle = this->zRotAngle;
		if(zRotAngle != 0.0) {
			glRotatef(zRotAngle * 57.296, 0.0, 0.0, 1.0);
		}
		yRotAngle = this->yRotAngle;
		if(yRotAngle != 0.0) {
			glRotatef(yRotAngle * 57.296, 0.0, 1.0, 0.0);
		}
		xRotAngle = this->xRotAngle;
		if(xRotAngle != 0.0) {
			glRotatef(xRotAngle * 57.296, 1.0, 0.0, 0.0);
		}
	}
}
ModelPart::~ModelPart() {
	this->reset();
}
