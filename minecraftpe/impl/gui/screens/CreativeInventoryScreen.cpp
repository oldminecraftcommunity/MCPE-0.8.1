#include <gui/screens/CreativeInventoryScreen.hpp>
#include <Minecraft.hpp>
#include <entity/LocalPlayer.hpp>
#include <gui/buttons/CategoryButton.hpp>
#include <gui/buttons/ImageWithBackground.hpp>
#include <gui/pane/Touch_InventoryPane.hpp>
#include <input/Mouse.hpp>
#include <inventory/Inventory.hpp>
#include <item/Item.hpp>
#include <item/ItemInstance.hpp>
#include <rendering/entity/ItemRenderer.hpp>
#include <tile/Tile.hpp>
#include <rendering/Tesselator.hpp>
#include <gui/NinePatchFactory.hpp>

std::vector<ItemInstance> CreativeInventoryScreen::items;
std::vector<ItemInstance> CreativeInventoryScreen::filteredItems[4];

CreativeInventoryScreen::TabButtonWithMeta::TabButtonWithMeta(int f0, std::shared_ptr<ImageButton> f4) {
	this->field_0 = f0;
	this->field_4 = f4;
}
CreativeInventoryScreen::TabButtonWithMeta::TabButtonWithMeta(const CreativeInventoryScreen::TabButtonWithMeta& a2)
	: field_4(a2.field_4) {
	this->field_0 = a2.field_0;
}
CreativeInventoryScreen::TabButtonWithMeta::TabButtonWithMeta(CreativeInventoryScreen::TabButtonWithMeta&& a2) {
	this->field_0 = a2.field_0;
	this->field_4 = a2.field_4;
	a2.field_4 = 0;
}
CreativeInventoryScreen::TabButtonWithMeta::~TabButtonWithMeta() {
}
CreativeInventoryScreen::CreativeInventoryScreen() {
	this->field_58 = 24;
	this->field_5C = 2;
	this->field_A8 = 0;
	this->field_AC = 0;
	this->field_B0 = 0;
	this->currentPaneMaybe = 0;
	this->field_B8 = 0;
	this->field_BC = 0;
	if(CreativeInventoryScreen::items.size() == 0) {
		CreativeInventoryScreen::populateItems();
	}
}
void CreativeInventoryScreen::_putItemInToolbar(const ItemInstance*) {
}
void CreativeInventoryScreen::closeWindow() {
	this->minecraft->setScreen(0);
}
std::shared_ptr<ImageButton> CreativeInventoryScreen::createInventoryTabButton(int32_t a3, int32_t a4) {
	std::shared_ptr<ImageButton> res(new CategoryButton(a3, this->field_70.get(), this->field_70.get(), &this->field_A4));
	res->height = this->field_58;
	res->width = this->field_58;
	res->setOverrideScreenRendering(1);
	return res;
}
void CreativeInventoryScreen::drawIcon(int a2, std::shared_ptr<ImageButton> a3, bool_t a4, bool_t a5) {
	ItemInstance v14 = this->getItemFromType(a2);
	float v8 = 0.0;
	int v9 = this->field_58;
	float v10 = (float)v9;
	if(a5) {
		v8 = 2.0;
	}
	float v13 = (float)(v10 - v8) / 25.0;
	float v11 = (float)((float)a3->posY + (float)(v10 * 0.5)) - 8.0;
	float v12 = 0.7;
	if(!a4) {
		v12 = 1.0;
	}
	ItemRenderer::renderGuiItemNew(this->minecraft->texturesPtr, &v14, 0, (float)(a3->posX + v9 / 2 - 8) + 1.0, v11, 1.0, v12, v13);
}
int32_t CreativeInventoryScreen::getCategoryFromPanel(const Touch::InventoryPane* a2) {
	int32_t v2 = 0;
	while(this->field_78[v2].get() != a2) {
		if(++v2 == 4) return 0;
	}
	return v2;
}
ItemInstance CreativeInventoryScreen::getItemFromType(int32_t a3) {
	switch(a3) {
		case 2:
			return ItemInstance(Tile::bookshelf);
		case 3:
			return ItemInstance(Item::sword_iron);
		case 4:
			return ItemInstance(Item::seeds_wheat);
		default:
			return ItemInstance(Tile::redBrick);
	}
}
void CreativeInventoryScreen::populateFilteredItems() {
	for(auto&& it: CreativeInventoryScreen::items) {
		int32_t f54;
		if(it.tileClass) {
			f54 = it.tileClass->field_54;
		} else {
			f54 = it.itemClass->field_34;
		}
		CreativeInventoryScreen::filteredItems[f54-1].emplace_back(it);
	}
}
void CreativeInventoryScreen::populateItem(Item* a1, int32_t a2, int32_t a3) {
	CreativeInventoryScreen::items.emplace_back(ItemInstance(a1, a2, a3));
}
void CreativeInventoryScreen::populateItem(Tile* a1, int32_t a2, int32_t a3) {
	CreativeInventoryScreen::items.emplace_back(ItemInstance(a1, a2, a3));
}
void CreativeInventoryScreen::populateItems() {
	CreativeInventoryScreen::populateItem(Tile::rail, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::goldenRail, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::stoneBrick, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::stoneBrickSmooth, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::stoneBrickSmooth, 1, 1);
	CreativeInventoryScreen::populateItem(Tile::stoneBrickSmooth, 1, 2);
	CreativeInventoryScreen::populateItem(Tile::mossStone, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::wood, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::wood, 1, 1);
	CreativeInventoryScreen::populateItem(Tile::wood, 1, 2);
	CreativeInventoryScreen::populateItem(Tile::wood, 1, 3);
	CreativeInventoryScreen::populateItem(Tile::redBrick, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::rock, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::dirt, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::grass, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::clay, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::sandStone, 5, 0);
	CreativeInventoryScreen::populateItem(Tile::sandStone, 5, 1);
	CreativeInventoryScreen::populateItem(Tile::sandStone, 5, 2);
	CreativeInventoryScreen::populateItem(Tile::sand, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::gravel, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::cobbleWall, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::cobbleWall, 5, 1);
	for(int32_t i = 0; i != 4; ++i) {
		CreativeInventoryScreen::populateItem(Tile::treeTrunk, 5, i);
	}
	CreativeInventoryScreen::populateItem(Tile::netherBrick, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::netherrack, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::unbreakable, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::stairs_stone, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::stairs_wood, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::woodStairsDark, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::woodStairsBirch, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::woodStairsJungle, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::stairs_brick, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::stairs_sandStone, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::stairs_stoneBrickSmooth, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::stairs_netherBricks, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::stairs_quartz, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::stoneSlabHalf, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::stoneSlabHalf, 1, 3);
	for(int32_t v2 = 0; v2 != 4; ++v2) {
		CreativeInventoryScreen::populateItem(Tile::woodSlabHalf, 1, v2);
	}
	CreativeInventoryScreen::populateItem(Tile::stoneSlabHalf, 1, 4);
	CreativeInventoryScreen::populateItem(Tile::stoneSlabHalf, 1, 1);
	CreativeInventoryScreen::populateItem(Tile::stoneSlabHalf, 1, 5);
	CreativeInventoryScreen::populateItem(Tile::stoneSlabHalf, 1, 6);
	CreativeInventoryScreen::populateItem(Tile::quartzBlock, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::quartzBlock, 1, 2);
	CreativeInventoryScreen::populateItem(Tile::quartzBlock, 1, 1);
	CreativeInventoryScreen::populateItem(Tile::coalOre, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::ironOre, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::goldOre, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::emeraldOre, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::lapisOre, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::redStoneOre, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::goldBlock, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::ironBlock, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::emeraldBlock, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::lapisBlock, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::coalBlock, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::obsidian, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::ice, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::snow, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::topSnow, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::glass, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::lightGem, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::netherReactor, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::ladder, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::sponge, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::torch, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::thinGlass, 1, 0);
	CreativeInventoryScreen::populateItem(Item::bucket, 1, 0);
	CreativeInventoryScreen::populateItem(Item::bucket, 1, Tile::water->blockID);
	CreativeInventoryScreen::populateItem(Item::bucket, 1, Tile::lava->blockID);
	CreativeInventoryScreen::populateItem(Item::door_wood, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::trapdoor, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::fence, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::fenceGate, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::ironFence, 1, 0);
	CreativeInventoryScreen::populateItem(Item::bed, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::bookshelf, 1, 0);
	CreativeInventoryScreen::populateItem(Item::painting, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::workBench, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::stonecutterBench, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::chest, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::furnace, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::tnt, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::flower, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::rose, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::mushroom1, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::mushroom2, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::cactus, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::melon, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::pumpkin, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::litPumpkin, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::web, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::hayBlock, 1, 0);
	CreativeInventoryScreen::populateItem(Item::reeds, 1, 0);
	CreativeInventoryScreen::populateItem(Item::wheat, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::tallgrass, 5, 1);
	CreativeInventoryScreen::populateItem(Tile::tallgrass, 5, 2);
	CreativeInventoryScreen::populateItem(Tile::deadBush, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::sapling, 1, 0);
	CreativeInventoryScreen::populateItem(Tile::sapling, 1, 1);
	CreativeInventoryScreen::populateItem(Tile::sapling, 1, 2);
	for(int32_t j = 0; j != 4; ++j) {
		CreativeInventoryScreen::populateItem(Tile::leaves, 1, j);
	}
	CreativeInventoryScreen::populateItem(Item::seeds_wheat, 1, 0);
	CreativeInventoryScreen::populateItem(Item::seeds_pumpkin, 1, 0);
	CreativeInventoryScreen::populateItem(Item::seeds_melon, 1, 0);
	CreativeInventoryScreen::populateItem(Item::carrot, 1, 0);
	CreativeInventoryScreen::populateItem(Item::potato, 1, 0);
	CreativeInventoryScreen::populateItem(Item::seeds_beetroot, 1, 0);
	CreativeInventoryScreen::populateItem(Item::hoe_iron, 1, 0);
	CreativeInventoryScreen::populateItem(Item::cake, 1, 0);
	CreativeInventoryScreen::populateItem(Item::egg, 1, 0);
	CreativeInventoryScreen::populateItem(Item::sword_iron, 1, 0);
	CreativeInventoryScreen::populateItem(Item::bow, 1, 0);
	CreativeInventoryScreen::populateItem(Item::flintAndSteel, 1, 0);
	CreativeInventoryScreen::populateItem(Item::shears, 1, 0);
	CreativeInventoryScreen::populateItem(Item::sign, 1, 0);
	CreativeInventoryScreen::populateItem(Item::clock, 1, 0);
	CreativeInventoryScreen::populateItem(Item::compass, 1, 0);
	CreativeInventoryScreen::populateItem(Item::minecart, 1, 0);
	CreativeInventoryScreen::populateItem(Item::mobPlacer, 1, 10);
	CreativeInventoryScreen::populateItem(Item::mobPlacer, 1, 11);
	CreativeInventoryScreen::populateItem(Item::mobPlacer, 1, 12);
	CreativeInventoryScreen::populateItem(Item::mobPlacer, 1, 13);
	for(int i: {0, 8, 7, 0xF, 0xC, 0xE, 1, 4, 5, 0xD, 9, 3, 0xB, 0xA, 2, 6}) {
		CreativeInventoryScreen::populateItem(Tile::cloth, 1, i);
	}
	for(int i: {0, 8, 7, 0xF, 0xC, 0xE, 1, 4, 5, 0xD, 9, 3, 0xB, 0xA, 2, 6}) {
		CreativeInventoryScreen::populateItem(Tile::woolCarpet, 1, i);
	}
	for(int i: {0, 8, 7, 0xF, 0xC, 0xE, 1, 4, 5, 0xD, 9, 3, 0xB, 0xA, 2, 6}) {
		CreativeInventoryScreen::populateItem(Item::dye_powder, 1, i);
	}
	CreativeInventoryScreen::populateFilteredItems();
}

CreativeInventoryScreen::~CreativeInventoryScreen() {
}

void CreativeInventoryScreen::render(int32_t a2, int32_t a3, float a4) {
	this->renderBackground(0);
	this->minecraft->gui.renderToolBar(a4, 1);
	static Color4 _D6E05DF0(0.75, 0.75, 0.75, 1.0);
	for(auto v27: this->field_98) {
		if(v27.field_4.get() != this->field_A4) {
			v27.field_4->color = _D6E05DF0;
			v27.field_4->render(this->minecraft, a2, a3);
			this->drawIcon(v27.field_0, v27.field_4, 1, v27.field_4->pressed);
		}
	}
	glColor4f(1.0, 1.0, 1.0, 1.0);
	this->field_68->draw(Tesselator::instance, this->field_A8, this->field_AC);
	std::shared_ptr<Touch::InventoryPane> v25 = this->field_78[this->currentPaneMaybe]; //TODO check
	this->fill(v25->field_228.minX - this->field_B8 - v25->field_248, v25->field_228.minY - v25->field_24C, v25->field_228.minX - v25->field_248, v25->field_228.height + v25->field_228.minY + v25->field_24C, 0xFF333333);
	int v15 = v25->field_228.minX + v25->field_228.width + v25->field_248;
	this->fill(v15, v25->field_228.minY - v25->field_24C, v15 + this->field_B8, v25->field_228.minY + v25->field_228.height + v25->field_24C, 0xFF333333);
	v25->render(a2, a3, a4);
	Screen::render(a2, a3, a4);
	for(auto v27: this->field_98) {
		if(v27.field_4.get() == this->field_A4) {
			v27.field_4->color = Color4::WHITE;
			v27.field_4->render(this->minecraft, a2, a3);
			this->drawIcon(v27.field_0, v27.field_4, 0, v27.field_4->pressed);
		}
	}
	this->minecraft->gui.renderOnSelectItemNameText(this->width, this->minecraft->font, this->height - 19);
}
void CreativeInventoryScreen::init()
{
	NinePatchFactory v16(this->minecraft->texturesPtr, "gui/spritesheet.png");
	this->field_68 = std::shared_ptr<NinePatchLayer>(v16.createSymmetrical(IntRectangle{34, 43, 14, 14}, 3, 3, 14, 14));
	int v4 = (height - 25) / 5 - this->field_5C;
	if(v4 >= 30) {
		v4 = 30;
	}
	this->field_58 = v4;
	IntRectangle a5 = {this->minecraft->options.leftHanded ? 65 : 49, this->minecraft->options.leftHanded ? 55 : 43, 14, 14};
	this->field_70 = std::shared_ptr<NinePatchLayer>(v16.createSymmetrical(a5, 3, 3, v4, v4));
	this->field_98.emplace_back(CreativeInventoryScreen::TabButtonWithMeta(1, this->createInventoryTabButton(6, 1)));
	this->field_98.emplace_back(CreativeInventoryScreen::TabButtonWithMeta(2, this->createInventoryTabButton(7, 2)));
	this->field_98.emplace_back(CreativeInventoryScreen::TabButtonWithMeta(3, this->createInventoryTabButton(8, 3)));
	this->field_98.emplace_back(CreativeInventoryScreen::TabButtonWithMeta(4, this->createInventoryTabButton(9, 4)));

	ImageDef v18;
	v18.field_0 = "gui/spritesheet.png";
	v18.field_4 = 0;
	v18.field_8 = 1;
	v18.height = 18.0;
	v18.width = 18.0;
	v18.field_24 = 1;
	v18.field_14 = 60;
	v18.field_18 = 0;
	v18.field_1C = 18;
	v18.field_20 = 18;

	ImageWithBackground* v5 = new ImageWithBackground(5);
	v5->init(this->minecraft->texturesPtr, this->field_58, this->field_58, a5, a5, 2, 2, "gui/spritesheet.png");
	v5->width = this->field_58;
	v5->height = this->field_58 - 1;
	v5->setImageDef(v18, 0);
	this->field_60 = std::shared_ptr<ImageWithBackground>(v5);
	this->field_A4 = this->field_98[0].field_4.get();
	for(auto p: this->field_98) {
		this->buttons.emplace_back(p.field_4.get());
	}
	this->buttons.emplace_back(this->field_60.get());
	this->field_BC = 1;
}
void CreativeInventoryScreen::setupPositions()
{
	this->field_68->setSize((float)((float)this->width - 4.0) - (float)this->field_58, (float)this->height - 25.0);
	int v3;
	if(this->minecraft->options.leftHanded) {
		v3 = 2;
	} else {
		v3 = this->field_58 + 2;
	}
	this->field_AC = 2;
	this->field_A8 = v3;
	this->field_B0 = 0;
	int v6 = ~this->field_60->height + (int)this->field_68->height2;
	float v7;
	if(this->minecraft->options.leftHanded) {
		v7 = (float)((float)v3 + this->field_68->width2) - 2.0;
	} else {
		v7 = (float)(v3 - this->field_58 + 3);
	}
	this->field_60->posX = (int)v7;
	this->field_60->posY = this->field_AC;

	for(auto&& p: this->field_98) {
		p.field_4->posX = (int)v7;
		p.field_4->posY = v6;
		p.field_4->width = this->field_58;
		p.field_4->height = this->field_58;
		v6 -= this->field_58 + this->field_5C;
	}

	if(!this->field_78[0].get()) {
		int v14 = (int)this->field_68->width2 - 14;
		int v15 = this->field_A8;
		IntRectangle r3_0;
		r3_0.minY = this->field_AC + 8;
		r3_0.width = 26 * (v14 / 26);
		this->field_B8 = v14 % 26 / 2;
		int height2 = (int)this->field_68->height2;
		r3_0.minX = v14 % 26 / 2 + v15 + 7;
		r3_0.height = height2 - 16;
		int v17 = CreativeInventoryScreen::filteredItems[0].size();

		this->field_78[0] = std::shared_ptr<Touch::InventoryPane>(new Touch::InventoryPane(this, this->minecraft, r3_0, r3_0.width, 1, v17, 26, 1, 0));
		int v23 = CreativeInventoryScreen::filteredItems[1].size();
		this->field_78[1] = std::shared_ptr<Touch::InventoryPane>(new Touch::InventoryPane(this, this->minecraft, r3_0, r3_0.width, 1, v23, 26, 1, 0));
		int v24 = CreativeInventoryScreen::filteredItems[2].size();
		this->field_78[2] = std::shared_ptr<Touch::InventoryPane>(new Touch::InventoryPane(this, this->minecraft, r3_0, r3_0.width, 1, v24, 26, 1, 0));
		int v21 = CreativeInventoryScreen::filteredItems[3].size();
		this->field_78[3] = std::shared_ptr<Touch::InventoryPane>(new Touch::InventoryPane(this, this->minecraft, r3_0, r3_0.width, 1, v21, 26, 1, 0));
	}
}
bool_t CreativeInventoryScreen::handleBackEvent(bool_t a2) {
	if(!a2) {
		this->closeWindow();
	}
	return 1;
}
void CreativeInventoryScreen::tick() {
	this->field_78[this->currentPaneMaybe]->tick();
}
bool_t CreativeInventoryScreen::renderGameBehind() {
	return this->minecraft->options.graphics;
}
void CreativeInventoryScreen::buttonClicked(Button* a2) {
	if(a2 == this->field_60.get()) {
		this->closeWindow();
	} else {
		if(a2->buttonID > 5) {
			this->field_A4 = a2;
			this->currentPaneMaybe = a2->buttonID - 6;
			this->setupPositions();
		}
	}
}
void CreativeInventoryScreen::mouseClicked(int32_t a2, int32_t a3, int32_t a4) {
	Screen::mouseClicked(a2, a3, a4);
	this->minecraft->gui.handleClick(1, Mouse::getX(), Mouse::getY());
}
void CreativeInventoryScreen::mouseReleased(int32_t a2, int32_t a3, int32_t a4) {
	Screen::mouseReleased(a2, a3, a4);
	for(auto&& p: this->field_98) {
		p.field_4->released(a2, a3);
	}
}
bool_t CreativeInventoryScreen::addItem(const Touch::InventoryPane* a2, int32_t a3) {
	std::vector<ItemInstance>* v7 = &filteredItems[this->getCategoryFromPanel(a2)];
	if(a3 >= v7->size()) {
		return 0;
	}
	const ItemInstance* v8 = &v7->at(a3);
	int32_t id = v8->getId();
	int32_t auxv = v8->getAuxValue();
	int32_t slot = this->minecraft->player->inventory->getLinkedSlotForItemAndAux(id, auxv);
	if(slot < 0 || slot >= this->minecraft->gui.getNumSlots() - 1) {
		ItemInstance v15(*v8);
		int32_t v14 = this->minecraft->player->inventory->selectedSlot + 9;
		this->minecraft->player->inventory->setItem(v14, &v15);
		this->minecraft->player->inventory->linkSlot(this->minecraft->player->inventory->selectedSlot, v14);
		this->minecraft->player->inventory->setItem(this->minecraft->player->inventory->selectedSlot, &v15);
	} else {
		this->minecraft->player->inventory->selectedSlot = slot;
	}
	this->minecraft->gui.resetItemNameOverlay();
	this->minecraft->gui.flashSlot(this->minecraft->player->inventory->selectedSlot);
	return 1;
}
bool_t CreativeInventoryScreen::isAllowed(int32_t) {
	return 1;
}
std::vector<const ItemInstance*> CreativeInventoryScreen::getItems(const Touch::InventoryPane* a3) {
	int32_t cat = this->getCategoryFromPanel(a3);
	int32_t v5 = CreativeInventoryScreen::filteredItems[cat].size();
	std::vector<const ItemInstance*> vec(v5);
	for(int32_t i = 0; i < v5; ++i) {
		vec[i] = &CreativeInventoryScreen::filteredItems[cat][i]; //TODO does something else
	}
	return vec;
}
