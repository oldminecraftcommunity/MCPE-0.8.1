#include <rendering/GameRenderer.hpp>
#include <GL/glu.h>
#include <Minecraft.hpp>
#include <entity/LocalPlayer.hpp>
#include <entity/player/gamemode/GameMode.hpp>
#include <gui/Screen.hpp>
#include <input/IInputHolder.hpp>
#include <input/KeyboardInput.hpp>
#include <input/Mouse.hpp>
#include <input/Multitouch.hpp>
#include <level/Level.hpp>
#include <level/dimension/Dimension.hpp>
#include <math.h>
#include <math/Mth.hpp>
#include <rendering/EntityRenderDispatcher.hpp>
#include <rendering/ItemInHandRenderer.hpp>
#include <rendering/LevelRenderer.hpp>
#include <rendering/ParticleEngine.hpp>
#include <rendering/Textures.hpp>
#include <rendering/frustum/Frustum.hpp>
#include <rendering/frustum/FrustumCuller.hpp>
#include <rendering/states/DisableState.hpp>
#include <rendering/states/EnableClientState.hpp>
#include <rendering/states/EnableState.hpp>
#include <tile/Tile.hpp>
#include <tile/material/Material.hpp>

int32_t t_keepPic = -1;
GameRenderer::GameRenderer(struct Minecraft* a2)
	: field_74(0, 0, 0, 0)
	, field_84(0, 0, 0, 0) {
	this->minecraft = a2;
	this->field_C = 0;
	this->viewVector.x = 1;
	this->field_4C = 1;
	this->field_34 = 4;
	this->field_38 = 4;
	this->field_58 = 1;
	this->field_5C = 1;
	this->field_8 = 0;
	this->viewVector.y = 0;
	this->viewVector.z = 0;
	this->field_1C = 0;
	this->field_20 = 0;
	this->field_24 = 0;
	this->field_28 = 0;
	this->field_2C = 0;
	this->field_30 = 0;
	this->field_3C = 0;
	this->field_40 = 0;
	this->field_44 = 0;
	this->field_48 = 0;
	this->field_50 = 0;
	this->field_54 = 0;
	this->field_60 = 0;
	this->field_64 = 0;
	this->fov = 0;
	this->field_6C = 0;
	this->field_70 = 0;
	this->enableScissorTest = 0;
	this->scissorRect.minX = 0;
	this->scissorRect.minY = 0;
	this->field_150 = 0;
	this->scissorRect.width = 1;
	this->scissorRect.height = 1;
	this->field_94 = 0;
	this->field_98 = 0;
	this->field_9C = 0;
	this->field_A0 = 0;
	this->field_A4 = 0;
	this->field_A8 = 0;
	this->field_AC = 0;
	this->field_130 = 0;
	this->field_134 = 0;
	this->field_138 = 0;
	this->field_154 = 0.0;
	this->saveMatrices();
	this->itemInHandRenderer = new ItemInHandRenderer(a2);
	EntityRenderDispatcher* entityRenderer = EntityRenderDispatcher::getInstance();
	entityRenderer->itemInHandRenderer = this->itemInHandRenderer;
	entityRenderer->textures = a2->texturesPtr;
}
void GameRenderer::bobHurt(float a2) {
	Player* viewEntityMaybe; // r4
	int hurtTime;			 // s17
	float v5;				 // r0
	float v6;				 // r4
	float v7;				 // s16

	viewEntityMaybe = (Player*)this->minecraft->viewEntityMaybe;
	hurtTime = viewEntityMaybe->hurtTime;
	if(viewEntityMaybe->health <= 0) {
		glRotatef(40.0 - (float)(8000.0 / (float)((float)((float)viewEntityMaybe->deathTime + a2) + 200.0)), 0.0, 0.0, 1.0);
	}
	if(viewEntityMaybe->hurtTime > 0) {
		v5 = Mth::sin((float)((float)((float)((float)((float)((float)hurtTime - a2) / (float)viewEntityMaybe->field_148) * (float)((float)((float)hurtTime - a2) / (float)viewEntityMaybe->field_148)) * (float)((float)((float)hurtTime - a2) / (float)viewEntityMaybe->field_148)) * (float)((float)((float)hurtTime - a2) / (float)viewEntityMaybe->field_148)) * 3.1416);
		v6 = viewEntityMaybe->field_14C;
		v7 = v5;
		glRotatef(-v6, 0.0, 1.0, 0.0);
		glRotatef(-(float)(v7 * 14.0), 0.0, 0.0, 1.0);
		glRotatef(v6, 0.0, 1.0, 0.0);
	}
}
void GameRenderer::bobView(float a2) {
	Player* viewEntityMaybe; // r3
	float v5;				 // s16
	float v6;				 // s17
	GLfloat v7;				 // s19
	float v8;				 // s18
	float v9;				 // r0
	float v10;				 // r0
	float v11;				 // r0

	if(this->minecraft->viewEntityMaybe->isPlayer()) {
		viewEntityMaybe = (Player*)this->minecraft->viewEntityMaybe;
		v5 = viewEntityMaybe->field_C74 + (float)((float)(viewEntityMaybe->field_C78 - viewEntityMaybe->field_C74) * a2);
		v6 = -(float)((float)(viewEntityMaybe->field_BC + (float)((float)(viewEntityMaybe->field_BC - viewEntityMaybe->field_B8) * a2)) * 3.1416);
		v7 = viewEntityMaybe->field_158 + (float)((float)(viewEntityMaybe->field_15C - viewEntityMaybe->field_158) * a2);
		v8 = Mth::sin(v6);
		v9 = Mth::cos(v6);
		glTranslatef((float)(v8 * v5) * 0.5, -fabsf(v9 * v5), 0.0);
		v10 = Mth::sin(v6);
		glRotatef((float)(v10 * v5) * 3.0, 0.0, 0.0, 1.0);
		v11 = Mth::cos(v6 - 0.2);
		glRotatef(fabsf(v11 * v5) * 5.0, 1.0, 0.0, 0.0);
		glRotatef(v7, 1.0, 0.0, 0.0);
	}
}
float GameRenderer::getFov(float a2, bool_t a3) {
	float v4;			  // s16
	Minecraft* minecraft; // r1
	Mob* viewEntityMaybe; // r5
	float v8;			  // s14

	v4 = 70.0;
	minecraft = this->minecraft;
	viewEntityMaybe = minecraft->viewEntityMaybe;
	if(a3) {
		v4 = (float)(this->field_5C + (float)((float)(this->field_58 - this->field_5C) * a2)) * 70.0;
	}
	if(viewEntityMaybe->isUnderLiquid(Material::water)) {
		v4 = 60.0;
	}
	if(viewEntityMaybe->health <= 0) {
		v8 = 1.0 - (float)(500.0 / (float)((float)((float)viewEntityMaybe->deathTime + a2) + 500.0));
		v4 = v4 / (float)((float)(v8 + v8) + 1.0);
	}
	return (float)(v4 + this->field_64) + (float)((float)(this->field_60 - this->field_64) * a2);
}
void GameRenderer::moveCameraToPlayer(float a2) {
	Mob* viewEntityMaybe; // r4
	float posX;			  // s19
	float prevX;		  // s21
	float posY;			  // s20
	float prevY;		  // s22
	float posZ;			  // s24
	float prevZ;		  // s23
	float v11;			  // s18
	Level* v12;			  // r8
	int v13;			  // r10
	int v14;			  // r9
	int v15;			  // r0
	Level* v16;			  // r7
	int v17;			  // r9
	int v18;			  // r8
	int v19;			  // r0
	char v20;			  // r0
	float v21;			  // r1
	float v22;			  // r0
	float v23;			  // s17
	int v24;			  // r6
	float v25;			  // s19
	GLfloat v26;		  // s20
	float v27;			  // r2
	float v28;			  // s22
	float yaw;			  // s20
	float v30;			  // s23
	float v31;			  // s21
	float pitch;		  // s19
	float v33;			  // s24
	float v34;			  // s22
	float v35;			  // s28
	float v36;			  // s25
	float v37;			  // s28
	float v38;			  // s29
	float v39;			  // s17
	float v40;			  // s27
	Level* level;		  // r8
	float v42;			  // s26
	float v43;			  // s25
	float v44;			  // r0
	Minecraft* minecraft; // r3
	Minecraft* v46;		  // r3

	viewEntityMaybe = this->minecraft->viewEntityMaybe;
	posX = viewEntityMaybe->posX;
	prevX = viewEntityMaybe->prevX;
	posY = viewEntityMaybe->posY;
	prevY = viewEntityMaybe->prevY;
	posZ = viewEntityMaybe->posZ;
	prevZ = viewEntityMaybe->prevZ;
	v11 = viewEntityMaybe->ridingHeight - 1.62;
	glRotatef(this->field_70 + (float)((float)(this->field_6C - this->field_70) * a2), 0.0, 0.0, 1.0);
	if(!viewEntityMaybe->isPlayer() || !viewEntityMaybe->isSleeping()) {
		minecraft = this->minecraft;
		if(!minecraft->options.thirdPerson) {
			this->field_154 = 0.0;
			glTranslatef(0.0, 0.0, -0.1);
			goto LABEL_17;
		}
		v23 = this->field_38 + (float)((float)(this->field_34 - this->field_38) * a2);
		this->field_154 = v23;
		v24 = (uint8_t)minecraft->options.field_F1;
		if(minecraft->options.field_F1) {
			v25 = *(float*)&this->field_40 + (float)((float)(*(float*)&this->field_3C - *(float*)&this->field_40) * a2);
			v26 = *(float*)&this->field_48 + (float)((float)(*(float*)&this->field_44 - *(float*)&this->field_48) * a2);
			glTranslatef(0.0, 0.0, -v23);
			glRotatef(v26, 1.0, 0.0, 0.0);
			v22 = v25;
			v21 = 0.0;
			v27 = 1.0;
LABEL_9:
			glRotatef(v22, v21, v27, 0.0);
			goto LABEL_17;
		}
		v28 = prevY + (float)((float)(posY - prevY) * a2);
		yaw = viewEntityMaybe->yaw;
		v30 = prevZ + (float)((float)(posZ - prevZ) * a2);
		v31 = prevX + (float)((float)(posX - prevX) * a2);
		pitch = viewEntityMaybe->pitch;
		v33 = (float)(pitch / 180.0) * 3.1416;
		v34 = v28 - v11;
		v35 = Mth::sin((float)(yaw / 180.0) * 3.1416);
		v36 = Mth::cos(v33);
		v37 = (float)-(float)(v35 * v36) * v23;
		v38 = (float)(Mth::cos((float)(yaw / 180.0) * 3.1416) * v36) * v23;
		v39 = -(float)(Mth::sin(v33) * v23);
		do {
			v40 = (float)(2 * (v24 & 1) - 1) * 0.1;
			level = this->minecraft->level;
			v42 = (float)((v24 & 2) - 1) * 0.1;
			v43 = (float)(2 * (v24 >> 2) - 1) * 0.1;
			HitResult result = level->clip(Vec3(v31 + v40, v34 + v42, v30 + v43), Vec3((float)((float)(v31 - v37) + v40) + v43, (float)(v34 - v39) + v42, (float)(v30 - v38) + v43), 0, 0);
			if(result.hitType != 2) {
				v44 = result.hitVec.distanceTo(Vec3(v31, v34, v30));
				if(v44 < this->field_154) {
					this->field_154 = v44;
				}
			}
			++v24;
		} while(v24 != 8);
		glRotatef(viewEntityMaybe->pitch - pitch, 1.0, 0.0, 0.0);
		glRotatef(viewEntityMaybe->yaw - yaw, 0.0, 1.0, 0.0);
		glTranslatef(0.0, 0.0, -this->field_154);
		glRotatef(yaw - viewEntityMaybe->yaw, 0.0, 1.0, 0.0);
		v21 = 1.0;
		v22 = pitch - viewEntityMaybe->pitch;
LABEL_16:
		v27 = 0.0;
		goto LABEL_9;
	}
	v11 = v11 + 1.0;
	glTranslatef(0.0, 0.3, 0.0);
	v46 = this->minecraft;
	if(!v46->options.field_F1) {
		v12 = v46->level;
		v13 = Mth::floor(viewEntityMaybe->posX);
		v14 = Mth::floor(viewEntityMaybe->posY);
		v15 = Mth::floor(viewEntityMaybe->posZ);
		if(v12->getTile(v13, v14, v15) == Tile::bed->blockID) {
			v16 = this->minecraft->level;
			v17 = Mth::floor(viewEntityMaybe->posX);
			v18 = Mth::floor(viewEntityMaybe->posY);
			v19 = Mth::floor(viewEntityMaybe->posZ);
			v20 = v16->getData(v17, v18, v19);
			glRotatef((float)(90 * (v20 & 3)), 0.0, 1.0, 0.0);
		}
		glRotatef((float)(viewEntityMaybe->prevYaw + (float)((float)(viewEntityMaybe->yaw - viewEntityMaybe->prevYaw) * a2)) + 180.0, 0.0, -1.0, 0.0);
		v21 = -1.0;
		v22 = viewEntityMaybe->prevPitch + (float)((float)(viewEntityMaybe->pitch - viewEntityMaybe->prevPitch) * a2);
		goto LABEL_16;
	}
LABEL_17:
	if(!this->minecraft->options.field_F1) {
		glRotatef(viewEntityMaybe->prevPitch + (float)((float)(viewEntityMaybe->pitch - viewEntityMaybe->prevPitch) * a2), 1.0, 0.0, 0.0);
		glRotatef((float)(viewEntityMaybe->prevYaw + (float)((float)(viewEntityMaybe->yaw - viewEntityMaybe->prevYaw) * a2)) + 180.0, 0.0, 1.0, 0.0);
	}
	glTranslatef(0.0, v11, 0.0);
}
void GameRenderer::pick(float a2) {
	if(this->minecraft) {
		if(this->minecraft->levelRenderer) {
			if(this->minecraft->viewEntityMaybe) {
				if(this->minecraft->viewEntityMaybe->isAlive()) {
					float v6 = this->minecraft->gameMode->getPickRange();
					Vec3 v72(0, 0, 0);
					bool updated;
					if(!this->minecraft->useTouchscreen() || this->minecraft->options.useJoypad) {
						bool isLiquidClipItem;
						if(this->minecraft->player && this->minecraft->player->getSelectedItem()) {
							isLiquidClipItem = this->minecraft->player->getSelectedItem()->isLiquidClipItem();
						} else {
							isLiquidClipItem = 0;
						}
						updated = 1;
						this->minecraft->selectedObject = this->minecraft->viewEntityMaybe->pick(v6, a2, isLiquidClipItem);
						this->viewVector = this->minecraft->viewEntityMaybe->getViewVector(a2);
					} else {
						updated = this->updateFreeformPickDirection(a2, v72, this->viewVector);
					}

					float minY = this->minecraft->viewEntityMaybe->boundingBox.minY;
					float minZ = this->minecraft->viewEntityMaybe->boundingBox.minZ;
					float maxX = this->minecraft->viewEntityMaybe->boundingBox.maxX;
					float minX = this->minecraft->viewEntityMaybe->boundingBox.minX;
					float v77 = minY;
					float v78 = minZ;
					float v79 = maxX;
					float maxZ = this->minecraft->viewEntityMaybe->boundingBox.maxZ;
					float maxY = this->minecraft->viewEntityMaybe->boundingBox.maxY;
					float v81 = maxZ;
					Vec3 mobpos = this->minecraft->viewEntityMaybe->getPos(a2);

					if(this->minecraft->options.thirdPerson) {
						mobpos = v72;
						minX = v72.x - 0.5;
						v77 = v72.y - 0.5;
						v79 = v72.x + 0.5;
						maxY = v72.y + 0.5;
						v78 = v72.z - 0.5;
						v81 = v72.z + 0.5;
					}
					float v24;
					if(this->minecraft->selectedObject.hitType == 2) {
						v24 = v6;
					} else {
						v24 = minecraft->selectedObject.hitVec.distanceTo(mobpos);
					}

					float v25;
					if(this->minecraft->gameMode->isCreativeType()) {
						v24 = 7.0;
						v25 = 12.0;
					} else {
						if(v24 > 3.0) {
							v24 = 3.0;
						}
						if(this->minecraft->options.thirdPerson) {
							v24 = v24 + this->field_154;
						}
						v25 = v24;
					}
					Vec3 v74(v25 * this->viewVector.x, v25 * this->viewVector.y, v25 * this->viewVector.z);
					Vec3 v75(mobpos.x + v74.x, mobpos.y + v74.y, mobpos.z + v74.z);
					float x = v74.x;
					float v27 = v74.y;
					float v30 = v74.z;
					float v31 = minX;
					float v32 = v77;
					float v33 = v78;
					float v34 = v79;
					float v35 = maxY;
					float v37 = v81;
					bool v38 = v74.x < 0.0;
					bool v39 = v74.x <= 0.0;
					this->minecraft->viewEntityMaybe->field_174 = this->viewVector;
					if(v38) {
						v31 = v31 + x;
					} else if(!v39) {
						v34 = v34 + x;
					}
					if(v27 >= 0.0) {
						if(v27 > 0.0) {
							v35 = v35 + v27;
						}
					} else {
						v32 = v32 + v27;
					}
					if(v30 >= 0.0) {
						if(v30 > 0.0) {
							v37 = v37 + v30;
						}
					} else {
						v33 = v33 + v30;
					}

					float v42 = 0;
					Entity* v43 = 0;
					std::vector<Entity*>* ents = this->minecraft->level->getEntities(this->minecraft->viewEntityMaybe, AABB{v31 - 1, v32 - 1, v33 - 1, v34 + 1, v35 + 1, v37 + 1});
					for(int v41 = 0; v41 < ents->size(); ++v41) {
						Entity* v47 = ents->at(v41);
						if(v47->isPickable()) {
							float v48 = v47->getPickRadius();
							float v49 = v47->boundingBox.minZ;
							float v50 = v47->boundingBox.maxX;
							float v51 = v47->boundingBox.maxY;
							float v52 = v47->boundingBox.minX;
							float v53 = v47->boundingBox.minY - v48;
							AABB v83;
							v83.maxZ = v48 + v47->boundingBox.maxZ;
							v83.minY = v53;
							v83.minZ = v49 - v48;
							v83.maxX = v48 + v50;
							v83.maxY = v48 + v51;
							v83.minX = v52 - v48;

							HitResult result = v83.clip(mobpos, v75);
							if(mobpos.x > v83.minX && mobpos.x < v83.maxX && mobpos.y > v83.minY && mobpos.y < v83.maxY && mobpos.z > v83.minZ && mobpos.z < v83.maxZ) {
								if(v42 >= 0.0) {
									v43 = v47;
									v42 = 0.0;
								}
							} else if(result.hitType != 2) {
								float v54 = mobpos.distanceTo(result.hitVec);
								if(v54 < v42 || v42 == 0.0) {
									if(v47 == this->minecraft->player->ridingAt) {
										if(v42 == 0.0) {
											v43 = v47;
										}
									} else {
										v42 = v54;
										v43 = v47;
									}
								}
							}
						}
					}

					if(v43) {
						if(v42 < v24) {
							this->minecraft->selectedObject = HitResult(v43);
						}
					} else if(updated) {
						if(this->minecraft->selectedObject.hitType == 2 && this->viewVector.y < -0.7) {
							Vec3 v83(mobpos.x + 0.0, mobpos.y - 2.0, mobpos.z + 0.0);
							HitResult result = this->minecraft->level->clip(mobpos, v83, 0, 0);
							if(result.hitType != 2) {
								this->minecraft->selectedObject = result;
								this->minecraft->selectedObject.field_24 = 1;
								float v64 = this->viewVector.x;
								float v65 = this->viewVector.z;
								int v66;
								if(fabsf(v64) <= fabsf(v65)) {
									if(v65 >= 0.0) {
										v66 = 3;
									} else {
										v66 = 2;
									}
								} else if(v64 >= 0.0) {
									v66 = 5;
								} else {
									v66 = 4;
								}
								this->minecraft->selectedObject.field_10 = v66;
							}
						}
					}
				}
			}
		}
	}
}
void GameRenderer::render(float pt) {
	int32_t v29;
	if(this->minecraft->player) {
		if(minecraft->mouseGrabbed) {
			minecraft->mouseHandler.poll();
			Minecraft* v5 = this->minecraft;
			float v6 = (float)((float)((float)((float)(v5->options.sensitity * 0.6) + 0.2) * (float)((float)(v5->options.sensitity * 0.6) + 0.2)) * (float)((float)(v5->options.sensitity * 0.6) + 0.2)) * 8.0;
			float v7 = v6 * v5->mouseHandler.field_0;
			float v8 = v6 * v5->mouseHandler.field_4;
			float v9 = this->field_AC;
			float v10 = (float)this->field_C + pt;
			this->field_AC = v10;
			float v11 = v10 - v9;
			this->field_9C = this->field_9C + (float)(v7 * 4.0);
			this->field_A0 = this->field_A0 + (float)(v8 * 4.0);
			bool_t invertMouse = v5->options.invertMouse;
			if(v11 > 3.0) {
				v11 = 3.0;
			}
			//v5->options.invertMouse;
			int32_t v13;
			if(v5->options.invertMouse) {
				v13 = 1;
			} else {
				v13 = -1;
			}
			Screen* currentScreen = v5->currentScreen;
			if(!currentScreen || currentScreen->field_C) {
				v5->player->turn(v11 * this->field_A4, (float)(v11 * this->field_A8) * (float)v13);
			}
		}
	}
	int32_t mx = Mouse::getX();
	int32_t my = Mouse::getY();
	float invGuiScale = Gui::InvGuiScale;

	if(this->minecraft->useTouchscreen()) {
		int32_t v24 = 0;
		while(!Multitouch::_pointers[v24].isButtonDown(1)) {
			if(++v24 == 12) {
				v24 = 0;
				while(!Multitouch::_wasReleasedThisUpdate[v24]) {
					if(++v24 == 12) {
						my = -9999;
						mx = -9999;
						goto LABEL_20;
					}
				}
				break;
			}
		}
		mx = (int)(float)((float)Multitouch::_pointers[v24].getX() * Gui::InvGuiScale);
		my = (int)(float)((float)Multitouch::_pointers[v24].getY() * Gui::InvGuiScale);
	} else {
		mx = mx * invGuiScale;
		my = my * invGuiScale;
	}
LABEL_20:
	this->enableScissorTest = 0;
	int32_t v27;
	if(this->minecraft->isLevelGenerated()) {
		if(t_keepPic >= 0 || this->minecraft->currentScreen != 0 && !this->minecraft->currentScreen->renderGameBehind()) {
			v27 = 0;
LABEL_30:
			v29 = v27;
			goto LABEL_34;
		}
		if(this->minecraft->currentScreen) {
			if(this->minecraft->currentScreen->hasClippingArea(this->scissorRect)) {
				this->enableScissorTest = 1;
			}
		}
		this->renderLevel(pt);
		if(!this->minecraft->options.hideGUI) {
			v27 = 1;
			this->setupGuiScreen(0);
			this->minecraft->gui.render(pt, this->minecraft->currentScreen != 0, mx, my);
			goto LABEL_30;
		}
		v27 = 0;
	} else {
		v27 = 1;
		glViewport(0, 0, this->minecraft->field_1C, this->minecraft->field_20);
		glMatrixMode(0x1701);
		glLoadIdentity();
		glMatrixMode(0x1700);
		glLoadIdentity();
		this->setupGuiScreen(1);
	}
	v29 = 1;
LABEL_34:
	DisableState v36(GL_DEPTH_TEST);
	if(!v27) this->setupGuiScreen(v29 != 1);

	if(this->minecraft->player) {
		if(!this->minecraft->currentScreen) {
			if(this->minecraft->inputHolder) {
				this->minecraft->inputHolder->render(pt);
			}
			if(this->minecraft->player->moveInput) {
				this->minecraft->player->moveInput->render(pt);
			}
		}
	}

	if(this->minecraft->currentScreen) {
		this->minecraft->currentScreen->render(mx, my, pt);
	}
}
void GameRenderer::renderItemInHand(float a2, int32_t a3) {
	Mob* viewEntityMaybe; // r3
	float v6;			  // s15
	float v7;			  // s14
	float v8;			  // s13
	Minecraft* minecraft; // r3
	float Fov;			  // s17
	Minecraft* v11;		  // r3
	Minecraft* v16;		  // r3
	Minecraft* v17;		  // r3

	this->minecraft->player->setupLighting(this->minecraft->options.graphics, a2);
	glLoadIdentity();
	glPushMatrix();
	this->bobHurt(a2);
	if(this->minecraft->options.viewBobbing) {
		this->bobView(a2);
		viewEntityMaybe = this->minecraft->viewEntityMaybe;
		Vec3 v21(viewEntityMaybe->pitch + (float)((float)(viewEntityMaybe->pitch - viewEntityMaybe->prevPitch) * a2), viewEntityMaybe->yaw + (float)((float)(viewEntityMaybe->yaw - viewEntityMaybe->prevYaw) * a2), 0.0);
		Vec3 v22(this->field_130 - v21.x, this->field_134 - v21.y, this->field_138 - v21.z);
		Vec3 v23(v22.x * 0.5, v22.y * 0.5, v22.z * 0.5);
		v6 = this->field_130 - v23.x;
		v7 = this->field_134 - v23.y;
		v8 = this->field_138;
		this->field_130 = v6;
		this->field_134 = v7;
		this->field_138 = v8 - v23.z;
		glRotatef(v21.x - v6, 1.0, 0.0, 0.0);
		glRotatef(v21.y - this->field_134, 0.0, 1.0, 0.0);
	}
	minecraft = this->minecraft;
	if(!minecraft->options.thirdPerson) {
		if(minecraft->viewEntityMaybe->isPlayer()) {
			if(!this->minecraft->viewEntityMaybe->isSleeping()) {
				v17 = this->minecraft;
				if(!v17->options.hideGUI) {
					Fov = this->getFov(a2, 0);
					if(Fov != this->fov) {
						glMatrixMode(0x1701u);
						glLoadIdentity();
						gluPerspective(Fov, (float)this->minecraft->field_1C / (float)this->minecraft->field_20, 0.05, this->field_8);
						glMatrixMode(0x1700u);
					}
					glClear(0x100u);
					DisableState v18(3042);
					EnableClientState v20(32888);
					v11 = this->minecraft;
					if(v11->options.graphics) {
						EnableState v22(2896);
						EnableState v23(0x4000);
						EnableState v24(2977);
						EnableClientState(32885);
						this->itemInHandRenderer->render(a2);
					} else {
						this->itemInHandRenderer->render(a2);
					}
				}
			}
		}
	}
	glPopMatrix();
	v16 = this->minecraft;
	if(!v16->options.thirdPerson) {
		if(v16->viewEntityMaybe->isPlayer()) {
			if(!this->minecraft->viewEntityMaybe->isSleeping()) {
				this->itemInHandRenderer->renderScreenEffect(a2);
				this->bobHurt(a2);
			}
		}
	}
	if(this->minecraft->options.viewBobbing) {
		this->bobView(a2);
	}
}
#include <rendering/Tesselator.hpp>
extern MeshBuffer cube;
void GameRenderer::renderLevel(float a2) {
	Minecraft* minecraft;			// r3
	Mob* player;					// r2
	Minecraft* v6;					// r3
	Mob* viewEntityMaybe;			// r5
	LevelRenderer* levelRenderer;	// r6
	ParticleEngine* particleEngine; // r10
	float v10;						// s19
	float v11;						// s18
	float v12;						// s17
	GLenum v13;						// r0
	Minecraft* v16;					// r3
	LevelRenderer* a1;				// [sp+14h] [bp-52Ch]

	minecraft = this->minecraft;
	if(!minecraft->viewEntityMaybe) {
		player = (Mob*)minecraft->player;
		if(!player) {
			return;
		}
		minecraft->viewEntityMaybe = player;
	}
	this->pick(a2);
	v6 = this->minecraft;
	viewEntityMaybe = v6->viewEntityMaybe;
	levelRenderer = v6->levelRenderer;
	particleEngine = v6->particleEngine;
	v10 = viewEntityMaybe->prevPosX + (float)((float)(viewEntityMaybe->posX - viewEntityMaybe->prevPosX) * a2);
	v11 = viewEntityMaybe->prevPosY + (float)((float)(viewEntityMaybe->posY - viewEntityMaybe->prevPosY) * a2);
	v12 = viewEntityMaybe->prevPosZ + (float)((float)(viewEntityMaybe->posZ - viewEntityMaybe->prevPosZ) * a2);
	glViewport(0, 0, v6->field_1C, v6->field_20);
	this->setupClearColor(a2);
	glClear(0x4500u);
	this->setupCamera(a2, 0);
	this->saveMatrices();
	if(this->enableScissorTest) {
		v13 = 3089;
	} else {
		v13 = 0;
	}
	EnableState v18(v13);
	if(this->enableScissorTest) {
		glScissor(this->scissorRect.minX, this->scissorRect.minY, this->scissorRect.width, this->scissorRect.height);
	}
	this->setupFog(1);
	Frustum::frustum.calculateFrustum();
	FrustumCuller v23{Frustum::frustum, v10, v11, v12};

	this->minecraft->levelRenderer->cullAndSort(&v23, this->field_8, a2);
	this->minecraft->levelRenderer->updateDirtyChunks(viewEntityMaybe, 0);
	{
		DisableState v21(3042);
		glShadeModel(0x1D01u);
		this->minecraft->texturesPtr->loadAndBindTexture("terrain-atlas.tga");
		levelRenderer->renderChunks(0, a2, this->field_150);
		levelRenderer->renderChunks(1, a2, this->field_150);
		levelRenderer->renderChunks(3, a2, this->field_150);
		if(!this->field_150) {
			levelRenderer->renderFarChunks(a2);
		}
		glShadeModel(0x1D00u);
		a1 = this->minecraft->levelRenderer;
		Vec3 v22 = viewEntityMaybe->getPos(a2);
		a1->renderEntities(v22, &v23, this->minecraft->options.graphics, a2);
	}

	{
		EnableState v19(2912);
		DisableState v20(3042);
		if(viewEntityMaybe->isUnderLiquid(Material::water)) {
			glCullFace(0x404u);
		}
		this->setupFog(1);
		this->minecraft->texturesPtr->loadAndBindTexture("terrain-atlas.tga");
		levelRenderer->renderChunks(2, a2, this->field_150);
		if(viewEntityMaybe->isUnderLiquid(Material::water)) {
			glCullFace(0x405u);
		}
	}
	if(this->minecraft->options.fancySkies) {
		glPushMatrix();
		this->setupCamera(a2, 0);
		this->renderSky(levelRenderer, 0.0, a2);
		glPopMatrix();
		levelRenderer->renderClouds(a2);
	}
	this->minecraft->levelRenderer->renderNameTags(a2);
	if(this->field_4C == 1.0) {
		if(viewEntityMaybe->isPlayer()) {
			v16 = this->minecraft;
			if(!v16->currentScreen && v16->selectedObject.hitType != 2 && !viewEntityMaybe->isUnderLiquid(Material::water)) {
#ifndef PCTWEAKS
				if(this->minecraft->useTouchscreen()) {
#endif
					levelRenderer->renderHitSelect((Player*)viewEntityMaybe, this->minecraft->selectedObject, 0, 0, a2);
#ifndef PCTWEAKS
				}
#endif
				levelRenderer->renderHit((Player*)viewEntityMaybe, this->minecraft->selectedObject, 0, 0, a2);
			}
		}
	}
	particleEngine->render(viewEntityMaybe, a2);

	if(this->field_4C == 1.0) {
		this->renderItemInHand(a2, 0);
	}
}
void GameRenderer::renderSky(LevelRenderer* a2, float a3, float a4) {
	float fov;			  // r0
	Minecraft* minecraft; // r3
	float v9;			  // s14

	glMatrixMode(0x1701u);
	glPushMatrix();
	glLoadIdentity();
	fov = this->getFov(a4, 1);
	minecraft = this->minecraft;
	v9 = this->field_8;
	this->fov = fov;
	gluPerspective(fov, (float)minecraft->field_1C / (float)minecraft->field_20, 2.0, v9 * 5120.0);
	glMatrixMode(0x1700u);
	glScalef((float)(this->field_8 / 100.0) * 128.0, (float)(this->field_8 / 100.0) * 128.0, (float)(this->field_8 / 100.0) * 128.0);
	glPushMatrix();
	this->setupFog(0);
	glFogf(0xB63u, 0.0);
	glFogf(0xB64u, 68129.0);
	a2->renderSky(a4);
	this->setupFog(1);
	glMatrixMode(0x1700u);
	glPopMatrix();
	glMatrixMode(0x1701u);
	glPopMatrix();
	glMatrixMode(0x1700u);
}
bool_t _d6e06788_matricesSaved = 0;
void GameRenderer::saveMatrices(void) {
	_d6e06788_matricesSaved = 1;
	glGetFloatv(0xBA7u, this->projectionMat);
	glGetFloatv(0xBA6u, this->modelViewMat);
}
static float _d67239c8[] = {192, 128, 64, 32};

void GameRenderer::setupCamera(float a2, int32_t a3) {
	Minecraft* minecraft; // r3
	float v6;			  // s15
	float fov;			  // r0
	Minecraft* v8;		  // r3

	minecraft = this->minecraft;
	v6 = _d67239c8[minecraft->options.renderDistance];
	this->field_8 = v6;
	if(minecraft->powerVR) {
		if(minecraft->options.renderDistance <= 2) {
			this->field_8 = v6 * 0.8;
		}
	}
	glMatrixMode(0x1701u);
	glLoadIdentity();
	if(this->field_4C != 1.0) {
		glTranslatef(this->field_50, -this->field_54, 0.0);
		glScalef(this->field_4C, this->field_4C, 1.0);
	}
	fov = this->getFov(a2, 1);
	v8 = this->minecraft;
	this->fov = fov;
	gluPerspective(fov, (float)v8->field_1C / (float)v8->field_20, 0.05, this->field_8 * 1.2);
	glMatrixMode(0x1700u);
	glLoadIdentity();
	this->bobHurt(a2);
	if(this->minecraft->options.viewBobbing) {
		this->bobView(a2);
	}
	this->moveCameraToPlayer(a2);
}
void GameRenderer::setupClearColor(float a2) {
	Minecraft* minecraft; // r3
	Color4* v5;			  // r6
	Level* level;		  // r7
	Mob* viewEntityMaybe; // r8
	float v8;			  // s18
	float g;			  // r1
	float b;			  // r2
	float a;			  // r3
	float r;			  // s14
	float v13;			  // s18
	float v14;			  // s15
	float v15;			  // s14
	float v16;			  // s15
	float v17;			  // s14
	float v18;			  // r3
	float v19;			  // r1
	Minecraft* v20;		  // r3
	float v21;			  // s15
	float sunIntensity;	  // r0
	float v23;			  // s9
	float v24;			  // s11
	float v25;			  // s12
	float v26;			  // s13
	float v27;			  // s14
	float v28;			  // s15

	minecraft = this->minecraft;
	v5 = &this->field_84;
	level = minecraft->level;
	viewEntityMaybe = minecraft->viewEntityMaybe;
	v8 = pow((float)(1.0 / (float)(4 - minecraft->options.renderDistance)), 0.25);
	Color4 skyCol = level->getSkyColor(this->minecraft->viewEntityMaybe, a2);
	Color4 v31 = level->getSunriseColor(a2);
	Color4 v29 = level->getFogColor(a2);
	g = v29.g;
	b = v29.b;
	a = v29.a;
	r = skyCol.r;
	v13 = 1.0 - v8;
	v5->r = v29.r;
	v5->g = g;
	v5->b = b;
	v5->a = a;
	v14 = this->field_84.r + (float)((float)(r - this->field_84.r) * v13);
	v15 = skyCol.g;
	this->field_84.r = v14;
	v16 = this->field_84.g + (float)((float)(v15 - this->field_84.g) * v13);
	v17 = skyCol.b;
	this->field_84.g = v16;
	this->field_84.b = this->field_84.b + (float)((float)(v17 - this->field_84.b) * v13);
	if(viewEntityMaybe->isUnderLiquid(Material::water)) {
		*v5 = Color4(0.02, 0.02, 0.2, 1.0);
	} else if(viewEntityMaybe->isUnderLiquid(Material::lava)) {
		*v5 = Color4(0.6, 0.1, 0.0, 1.0);
	}
LABEL_6:
	v20 = this->minecraft;
	v21 = this->field_94 + (float)((float)(this->field_98 - this->field_94) * a2);
	this->field_84.r = this->field_84.r * v21;
	this->field_84.g = this->field_84.g * v21;
	this->field_84.b = this->field_84.b * v21;
	sunIntensity = level->getSunIntensity(a2, (Mob*)v20->player, 0.35);
	v23 = this->field_84.b;
	v24 = 1.0 - (float)(sunIntensity * v31.a);
	v26 = (float)((float)(sunIntensity * v31.a) * v31.g) + (float)(v24 * this->field_84.g);
	this->field_74 = Color4((float)((float)(sunIntensity * v31.a) * v31.r) + (float)(v24 * this->field_84.r), v26, (float)((float)(sunIntensity * v31.a) * v31.b) + (float)(v24 * v23), (float)(v31.a * (float)(sunIntensity * v31.a)) + (float)(v24 * this->field_84.a));
	this->field_74.a = 1.0;
	glClearColor(this->field_74.r, this->field_74.g, this->field_74.b, this->field_74.a);
}
void GameRenderer::setupFog(int32_t a2) {
	Mob* viewEntityMaybe; // r5
	Color4* v5;			  // r1
	float v6;			  // r1

	viewEntityMaybe = this->minecraft->viewEntityMaybe;
	if(a2) {
		v5 = &this->field_84;
	} else {
		v5 = &this->field_74;
	}

	glFogfv(GL_FOG_COLOR, (const GLfloat*)v5);
	glColor4f(1.0, 1.0, 1.0, 1.0);
	if(viewEntityMaybe->isUnderLiquid(Material::water)) {
		glFogi(GL_FOG_MODE, 2048); //TODO uses glFogx
		v6 = 0.1;
LABEL_8:
		glFogf(GL_FOG_DENSITY, v6);
		this->field_150 = 1;
		return;
	}
	if(viewEntityMaybe->isUnderLiquid(Material::lava)) {
		glFogi(GL_FOG_MODE, 2048); //TODO uses glFogx
		v6 = 2.0;
		goto LABEL_8;
	}
	glFogi(GL_FOG_MODE, GL_LINEAR); //TODO uses glFogx
	glFogf(GL_FOG_START, this->field_8 * 0.7);
	glFogf(GL_FOG_END, this->field_8);
	this->field_150 = 0;
	if(a2 < 0) {
		glFogf(GL_FOG_START, 0.0);
		glFogf(GL_FOG_END, this->field_8);
	}
	if(this->minecraft->level->dimensionPtr->field_C) {
		glFogf(GL_FOG_START, 0.0);
	}
}
void GameRenderer::setupGuiScreen(bool_t a2) {
	Minecraft* minecraft;
	float v3;
	int32_t v4;

	minecraft = this->minecraft;
	v3 = (float)minecraft->field_20 * Gui::InvGuiScale;
	v4 = (int32_t)(float)((float)minecraft->field_1C * Gui::InvGuiScale);
	glMatrixMode(0x1701u);
	glLoadIdentity();
	glOrtho(0.0, (float)v4, (float)(int32_t)v3, 0.0, 2000.0, 3000.0);
	glMatrixMode(0x1700u);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -2000.0);
}
static int32_t _D67AD634 = -1;
void GameRenderer::tick(int32_t a2, int32_t a3) {
	Minecraft* minecraft;					// r3
	int v5;									// s17
	float v6;								// r0
	float v7;								// s17
	float v8;								// s13
	float v9;								// s15
	float v10;								// r0
	float v11;								// s15
	float v12;								// s17
	Minecraft* v13;							// r3
	Minecraft* v14;							// r3
	Player* viewEntityMaybe;				// r5
	Level* level;							// r6
	int v17;								// r8
	int v18;								// r7
	int v19;								// r0
	float v20;								// r0
	int v21;								// s14
	float v22;								// s13
	ItemInHandRenderer* itemInHandRenderer; // r0

	--t_keepPic;
	minecraft = this->minecraft;
	if(minecraft->player) {
		if(!--_D67AD634) {
			minecraft->selectedObject.hitType = 2;
		}
		if(a2 == a3) {
			v5 = a2 + 1;
			v6 = powf(fabsf(this->field_9C), 1.2);
			v7 = 1.0 / (float)v5;
			v8 = this->field_9C;
			v9 = (float)(v6 * 0.4) * v7;
			this->field_A4 = v9;
			if(v8 < 0.0) {
				this->field_A4 = -v9;
			}
			v10 = powf(fabsf(this->field_A0), 1.2);
			this->field_9C = 0.0;
			v11 = this->field_A0;
			this->field_A0 = 0.0;
			v12 = (float)(v10 * 0.4) * v7;
			this->field_A8 = v12;
			if(v11 < 0.0) {
				this->field_A8 = -v12;
			}
		}
		this->field_94 = this->field_98;
		this->field_38 = this->field_34;
		this->field_40 = this->field_3C;
		this->field_48 = this->field_44;
		this->field_64 = this->field_60;
		this->field_70 = this->field_6C;
		v13 = this->minecraft;
		if(!v13->viewEntityMaybe) {
			v13->viewEntityMaybe = (Mob*)v13->player;
		}
		this->tickFov();
		v14 = this->minecraft;
		viewEntityMaybe = (Player*)v14->viewEntityMaybe;
		level = v14->level;
		v17 = Mth::floor(viewEntityMaybe->posX);
		v18 = Mth::floor(viewEntityMaybe->posY);
		v19 = Mth::floor(viewEntityMaybe->posZ);
		v20 = level->getBrightness(v17, v18, v19);
		v21 = 3 - this->minecraft->options.renderDistance;
		++this->field_C;
		v22 = v20;
		itemInHandRenderer = this->itemInHandRenderer;
		this->field_98 = this->field_98 + (float)((float)((float)((float)((float)v21 / 3.0) + (float)(v22 * (float)(1.0 - (float)((float)v21 / 3.0)))) - this->field_98) * 0.1);
		itemInHandRenderer->tick();
	}
}
void GameRenderer::tickFov() {
	Minecraft* minecraft; // r3

	minecraft = this->minecraft;
	if(minecraft->viewEntityMaybe == minecraft->player) {
		this->field_5C = this->field_58;
		this->field_58 = this->field_58 + (float)((float)(minecraft->player->getFieldOfViewModifier() - this->field_58) * 0.5);
	}
}
void GameRenderer::unZoomRegion() {
	this->field_4C = 1.0;
}
void GameRenderer::updateAllChunks() {
	this->minecraft->levelRenderer->updateDirtyChunks(this->minecraft->viewEntityMaybe, 1);
}
bool_t GameRenderer::updateFreeformPickDirection(float, struct Vec3&, struct Vec3&) {
	printf("GameRenderer::updateFreeformPickDirection - not implemented(required for touchscreen stuff)\n"); //TODO GameRenderer::updateFreeformPickDirection touchscreen support
	return 0;
}

GameRenderer::~GameRenderer() {
	if(this->itemInHandRenderer) delete this->itemInHandRenderer;
}
