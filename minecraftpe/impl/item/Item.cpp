#include <item/Item.hpp>
#include <rendering/TextureAtlas.hpp>
#include <I18n.hpp>
#include <item/ShovelItem.hpp>
#include <item/PickaxeItem.hpp>
#include <item/HatchetItem.hpp>
#include <item/FlintAndSteelItem.hpp>
#include <item/FoodItem.hpp>
#include <item/BowItem.hpp>
#include <item/CoalItem.hpp>
#include <item/WeaponItem.hpp>
#include <item/BowlFoodItem.hpp>
#include <item/HoeItem.hpp>
#include <item/SeedItem.hpp>
#include <tile/Tile.hpp>
#include <item/ArmorItem.hpp>
#include <item/HangingEntityItem.hpp>
#include <item/SignItem.hpp>
#include <item/DoorItem.hpp>
#include <tile/material/Material.hpp>
#include <item/BucketItem.hpp>
#include <item/MinecartItem.hpp>
#include <item/SaddleItem.hpp>
#include <item/TilePlanterItem.hpp>
#include <item/EggItem.hpp>
#include <item/CompassItem.hpp>
#include <item/ClockItem.hpp>
#include <item/DyePowderItem.hpp>
#include <item/BedItem.hpp>
#include <item/ShearsItem.hpp>
#include <item/MonsterPlacerItem.hpp>
#include <item/SeedFoodItem.hpp>
#include <item/SnowballItem.hpp>
#include <item/CameraItem.hpp>
#include <entity/Player.hpp>
#include <level/Level.hpp>
#include <math/Mth.hpp>

Item* Item::shovel_iron;
Item* Item::pickAxe_iron;
Item* Item::hatchet_iron;
Item* Item::flintAndSteel;
Item* Item::apple;
Item* Item::bow;
Item* Item::arrow;
Item* Item::coal;
Item* Item::emerald;
Item* Item::ironIngot;
Item* Item::goldIngot;
Item* Item::sword_iron;
Item* Item::sword_wood;
Item* Item::shovel_wood;
Item* Item::pickAxe_wood;
Item* Item::hatchet_wood;
Item* Item::sword_stone;
Item* Item::shovel_stone;
Item* Item::pickAxe_stone;
Item* Item::hatchet_stone;
Item* Item::sword_emerald;
Item* Item::shovel_emerald;
Item* Item::pickAxe_emerald;
Item* Item::hatchet_emerald;
Item* Item::stick;
Item* Item::bowl;
Item* Item::mushroomStew;
Item* Item::sword_gold;
Item* Item::shovel_gold;
Item* Item::pickAxe_gold;
Item* Item::hatchet_gold;
Item* Item::string;
Item* Item::feather;
Item* Item::sulphur;
Item* Item::hoe_wood;
Item* Item::hoe_stone;
Item* Item::hoe_iron;
Item* Item::hoe_emerald;
Item* Item::hoe_gold;
Item* Item::seeds_wheat;
Item* Item::wheat;
Item* Item::bread;
Item* Item::helmet_cloth;
Item* Item::chestplate_cloth;
Item* Item::leggings_cloth;
Item* Item::boots_cloth;
Item* Item::helmet_chain;
Item* Item::chestplate_chain;
Item* Item::leggings_chain;
Item* Item::boots_chain;
Item* Item::helmet_iron;
Item* Item::chestplate_iron;
Item* Item::leggings_iron;
Item* Item::boots_iron;
Item* Item::helmet_diamond;
Item* Item::chestplate_diamond;
Item* Item::leggings_diamond;
Item* Item::boots_diamond;
Item* Item::helmet_gold;
Item* Item::chestplate_gold;
Item* Item::leggings_gold;
Item* Item::boots_gold;
Item* Item::flint;
Item* Item::porkChop_raw;
Item* Item::porkChop_cooked;
Item* Item::painting;
Item* Item::sign;
Item* Item::door_wood;
Item* Item::bucket;
Item* Item::minecart;
Item* Item::saddle;
Item* Item::door_iron;
Item* Item::redStone;
Item* Item::snowBall;
Item* Item::leather;
Item* Item::brick;
Item* Item::clay;
Item* Item::reeds;
Item* Item::paper;
Item* Item::book;
Item* Item::slimeBall;
Item* Item::egg;
Item* Item::compass;
Item* Item::clock;
Item* Item::yellowDust;
Item* Item::dye_powder;
Item* Item::bone;
Item* Item::sugar;
Item* Item::cake;
Item* Item::bed;
Item* Item::shears;
Item* Item::melon;
Item* Item::seeds_pumpkin;
Item* Item::seeds_melon;
Item* Item::beef_raw;
Item* Item::beef_cooked;
Item* Item::chicken_raw;
Item* Item::chicken_cooked;
Item* Item::mobPlacer;
Item* Item::carrot;
Item* Item::potato;
Item* Item::potatoBaked;
Item* Item::pumpkinPie;
Item* Item::netherbrick;
Item* Item::netherQuartz;
Item* Item::camera;
Item* Item::beetroot;
Item* Item::seeds_beetroot;
Item* Item::beetrootSoup;
Item* Item::items[512];
std::string Item::ICON_DESCRIPTION_PREFIX = "item.";
Random Item::random;
bool_t Item::_D6E4C850_ItemsInitialized = 0;
std::shared_ptr<TextureAtlas> Item::_itemTextureAtlas;
Item::Tier Item::Tier::GOLD{0, 32, 12.0, 0};
Item::Tier Item::Tier::EMERALD{3, 1561, 8.0, 3};
Item::Tier Item::Tier::IRON{2, 250, 6.0, 2};
Item::Tier Item::Tier::STONE{1, 131, 4.0, 1};
Item::Tier Item::Tier::WOOD{0, 59, 2.0, 0};

void Item::initItems(std::shared_ptr<TextureAtlas> a2){
	printf("Item::initItems - not implemented\n");
	Item::_itemTextureAtlas = a2;

	if(Item::_D6E4C850_ItemsInitialized) return;
	Item::_D6E4C850_ItemsInitialized = 1;

	Item::shovel_iron = (new ShovelItem(0, Item::Tier::IRON))->setIcon("shovel", 2)->setCategory(3, 2)->setDescriptionId("shovelIron");
	Item::pickAxe_iron = (new PickaxeItem(1, Item::Tier::IRON))->setIcon("pickaxe", 2)->setCategory(3, 2)->setDescriptionId("pickaxeIron");
	Item::hatchet_iron = (new HatchetItem(2, Item::Tier::IRON))->setIcon("axe", 2)->setCategory(3, 2)->setDescriptionId("hatchetIron");
	Item::flintAndSteel = (new FlintAndSteelItem(3))->setIcon("flint_and_steel", 0)->setCategory(3, 2)->setDescriptionId("flintAndSteel");
	Item::apple = (new FoodItem(4, 4, 0.6, 0))->setIcon("apple", 0)->setCategory(4, 4)->setDescriptionId("apple");
	Item::bow = (new BowItem(5))->setIcon("bow_standby", 0)->setCategory(3, 2)->setDescriptionId("bow");
	Item::arrow = (new Item(6))->setIcon("arrow", 0)->setCategory(4, 2)->setDescriptionId("arrow");
	Item::coal = (new CoalItem(7))->setIcon("coal", 0)->setCategory(4, 8)->setDescriptionId("coal");
	Item::emerald = (new Item(8))->setIcon("diamond", 0)->setCategory(4, 8)->setDescriptionId("emerald");
	Item::ironIngot = (new Item(9))->setIcon("iron_ingot", 0)->setCategory(4, 8)->setDescriptionId("ingotIron");
	Item::goldIngot = (new Item(10))->setIcon("gold_ingot", 0)->setCategory(4, 8)->setDescriptionId("ingotGold");
	Item::sword_iron = (new WeaponItem(11, Item::Tier::IRON))->setIcon("sword", 2)->setCategory(3, 2)->setDescriptionId("swordIron");
	Item::sword_wood = (new WeaponItem(12, Item::Tier::WOOD))->setIcon("sword", 0)->setCategory(3, 2)->setDescriptionId("swordWood");
	Item::shovel_wood = (new ShovelItem(13, Item::Tier::WOOD))->setIcon("shovel", 0)->setCategory(3, 2)->setDescriptionId("shovelWood");
	Item::pickAxe_wood = (new PickaxeItem(14, Item::Tier::WOOD))->setIcon("pickaxe", 0)->setCategory(3, 2)->setDescriptionId("pickaxeWood");
	Item::hatchet_wood = (new HatchetItem(15, Item::Tier::WOOD))->setIcon("axe", 0)->setCategory(3, 2)->setDescriptionId("hatchetWood");
	Item::sword_stone = (new WeaponItem(16, Item::Tier::STONE))->setIcon("sword", 1)->setCategory(3, 2)->setDescriptionId("swordStone");
	Item::shovel_stone = (new ShovelItem(17, Item::Tier::STONE))->setIcon("shovel", 1)->setCategory(3, 2)->setDescriptionId("shovelStone");
	Item::pickAxe_stone = (new PickaxeItem(18, Item::Tier::STONE))->setIcon("pickaxe", 1)->setCategory(3, 2)->setDescriptionId("pickaxeStone");
	Item::hatchet_stone = (new HatchetItem(19, Item::Tier::STONE))->setIcon("axe", 1)->setCategory(3, 2)->setDescriptionId("hatchetStone");
	Item::sword_emerald = (new WeaponItem(20, Item::Tier::EMERALD))->setIcon("sword", 4)->setCategory(3, 2)->setDescriptionId("swordDiamond");
	Item::shovel_emerald = (new ShovelItem(21, Item::Tier::EMERALD))->setIcon("shovel", 4)->setCategory(3, 2)->setDescriptionId("shovelDiamond");
	Item::pickAxe_emerald = (new PickaxeItem(22, Item::Tier::EMERALD))->setIcon("pickaxe", 4)->setCategory(3, 2)->setDescriptionId("pickaxeDiamond");
	Item::hatchet_emerald = (new HatchetItem(23, Item::Tier::EMERALD))->setIcon("axe", 4)->setCategory(3, 2)->setDescriptionId("hatchetDiamond");
	Item::stick = (new Item(24))->setIcon("stick", 0)->handEquipped()->setCategory(4, 1)->setDescriptionId("stick");
	Item::bowl = (new Item(25))->setIcon("bowl", 0)->setCategory(4, 4)->setDescriptionId("bowl");
	Item::mushroomStew = (new BowlFoodItem(26, 8))->setIcon("mushroom_stew", 0)->setCategory(4, 4)->setDescriptionId("mushroomStew");
	Item::sword_gold = (new WeaponItem(27, Item::Tier::GOLD))->setIcon("sword", 3)->setDescriptionId("swordGold");
	Item::shovel_gold = (new ShovelItem(28, Item::Tier::GOLD))->setIcon("shovel", 3)->setCategory(3, 2)->setDescriptionId("shovelGold");
	Item::pickAxe_gold = (new PickaxeItem(29, Item::Tier::GOLD))->setIcon("pickaxe", 3)->setCategory(3, 2)->setDescriptionId("pickaxeGold");
	Item::hatchet_gold = (new HatchetItem(30, Item::Tier::GOLD))->setIcon("axe", 3)->setCategory(3, 2)->setDescriptionId("hatchetGold");
	Item::string = (new Item(31))->setIcon("string", 0)->setCategory(4, 2)->setDescriptionId("string");
	Item::feather = (new Item(32))->setIcon("feather", 0)->setCategory(4, 2)->setDescriptionId("feather");
	Item::sulphur = (new Item(33))->setIcon("gunpowder", 0)->setCategory(4, 2)->setDescriptionId("sulphur");
	Item::hoe_wood = (new HoeItem(34, Item::Tier::WOOD))->setIcon("hoe", 0)->setCategory(3, 2)->setDescriptionId("hoeWood");
	Item::hoe_stone = (new HoeItem(35, Item::Tier::STONE))->setIcon("hoe", 1)->setCategory(3, 2)->setDescriptionId("hoeStone");
	Item::hoe_iron = (new HoeItem(36, Item::Tier::IRON))->setIcon("hoe", 2)->setCategory(3, 2)->setDescriptionId("hoeIron");
	Item::hoe_emerald = (new HoeItem(37, Item::Tier::EMERALD))->setIcon("hoe", 4)->setCategory(3, 2)->setDescriptionId("hoeDiamond");
	Item::hoe_gold = (new HoeItem(38, Item::Tier::GOLD))->setIcon("hoe", 3)->setCategory(3, 2)->setDescriptionId("hoeGold");
	Item::seeds_wheat = (new SeedItem(39, Tile::crops->blockID, Tile::farmland->blockID))->setIcon("seeds_wheat", 0)->setCategory(4, 4)->setDescriptionId("seeds");
	Item::wheat = (new Item(40))->setIcon("wheat", 0)->setCategory(4, 4)->setDescriptionId("wheat");
	Item::bread = (new FoodItem(41, 5, 0.6, 0))->setIcon("bread", 0)->setCategory(4, 4)->setDescriptionId("bread");
	Item::helmet_cloth = (new ArmorItem(42, ArmorItem::CLOTH, 0, 0))->setIcon("helmet", 0)->setCategory(3, 4)->setDescriptionId("helmetCloth");
	Item::chestplate_cloth = (new ArmorItem(43, ArmorItem::CLOTH, 0, 1))->setIcon("chestplate", 0)->setCategory(3, 4)->setDescriptionId("chestplateCloth");
	Item::leggings_cloth = (new ArmorItem(44, ArmorItem::CLOTH, 0, 2))->setIcon("leggings", 0)->setCategory(3, 4)->setDescriptionId("leggingsCloth");
	Item::boots_cloth = (new ArmorItem(45, ArmorItem::CLOTH, 0, 3))->setIcon("boots", 0)->setCategory(3, 4)->setDescriptionId("bootsCloth");
	Item::helmet_chain = (new ArmorItem(46, ArmorItem::CHAIN, 1, 0))->setIcon("helmet", 1)->setCategory(3, 4)->setDescriptionId("helmetChain");
	Item::chestplate_chain = (new ArmorItem(47, ArmorItem::CHAIN, 1, 1))->setIcon("chestplate", 1)->setCategory(3, 4)->setDescriptionId("chestplateChain");
	Item::leggings_chain = (new ArmorItem(48, ArmorItem::CHAIN, 1, 2))->setIcon("leggings", 1)->setCategory(3, 4)->setDescriptionId("leggingsChain");
	Item::boots_chain = (new ArmorItem(49, ArmorItem::CHAIN, 1, 3))->setIcon("boots", 1)->setCategory(3, 4)->setDescriptionId("bootsChain");
	Item::helmet_iron = (new ArmorItem(50, ArmorItem::IRON, 2, 0))->setIcon("helmet", 2)->setCategory(3, 4)->setDescriptionId("helmetIron");
	Item::chestplate_iron = (new ArmorItem(51, ArmorItem::IRON, 2, 1))->setIcon("chestplate", 2)->setCategory(3, 4)->setDescriptionId("chestplateIron");
	Item::leggings_iron = (new ArmorItem(52, ArmorItem::IRON, 2, 2))->setIcon("leggings", 2)->setCategory(3, 4)->setDescriptionId("leggingsIron");
	Item::boots_iron = (new ArmorItem(53, ArmorItem::IRON, 2, 3))->setIcon("boots", 2)->setCategory(3, 4)->setDescriptionId("bootsIron");
	Item::helmet_diamond = (new ArmorItem(54, ArmorItem::DIAMOND, 3, 0))->setIcon("helmet", 4)->setCategory(3, 4)->setDescriptionId("helmetDiamond");
	Item::chestplate_diamond = (new ArmorItem(55, ArmorItem::DIAMOND, 3, 1))->setIcon("chestplate", 4)->setCategory(3, 4)->setDescriptionId("chestplateDiamond");
	Item::leggings_diamond = (new ArmorItem(56, ArmorItem::DIAMOND, 3, 2))->setIcon("leggings", 4)->setCategory(3, 4)->setDescriptionId("leggingsDiamond");
	Item::boots_diamond = (new ArmorItem(57, ArmorItem::DIAMOND, 3, 3))->setIcon("boots", 4)->setCategory(3, 4)->setDescriptionId("bootsDiamond");
	Item::helmet_gold = (new ArmorItem(58, ArmorItem::GOLD, 4, 0))->setIcon("helmet", 3)->setCategory(3, 4)->setDescriptionId("helmetGold");
	Item::chestplate_gold = (new ArmorItem(59, ArmorItem::GOLD, 4, 1))->setIcon("chestplate", 3)->setCategory(3, 4)->setDescriptionId("chestplateGold");
	Item::leggings_gold = (new ArmorItem(60, ArmorItem::GOLD, 4, 2))->setIcon("leggings", 3)->setCategory(3, 4)->setDescriptionId("leggingsGold");
	Item::boots_gold = (new ArmorItem(61, ArmorItem::GOLD, 4, 3))->setIcon("boots", 3)->setCategory(3, 4)->setDescriptionId("bootsGold");
	Item::flint = (new Item(62))->setIcon("flint", 0)->setCategory(3, 2)->setDescriptionId("flint");
	Item::porkChop_raw = (new FoodItem(63, 3, 0.6, 1))->setIcon("porkchop_raw", 0)->setCategory(4, 4)->setDescriptionId("porkchopRaw");
	Item::porkChop_cooked = (new FoodItem(64, 8, 0.6, 1))->setIcon("porkchop_cooked", 0)->setCategory(4, 4)->setDescriptionId("porkchopCooked");
	Item::painting = (new HangingEntityItem(65, 83))->setIcon("painting", 0)->setCategory(2, 8)->setDescriptionId("painting");
	Item::sign = (new SignItem(67))->setIcon("sign", 0)->setCategory(2, 8)->setDescriptionId("sign");
	Item::door_wood = (new DoorItem(68, Material::wood))->setIcon("door_wood", 0)->setCategory(2, 1)->setDescriptionId("doorWood");
	Item::bucket = (new BucketItem(69))->setIcon("bucket", 0)->setCategory(3, 2)->setDescriptionId("bucket");
	Item::minecart = (new MinecartItem(72, 0))->setIcon("minecart_normal", 0)->setCategory(3, 2)->setDescriptionId("minecart");
	Item::saddle = (new SaddleItem(73))->setIcon("saddle", 0)->setCategory(3, 4)->setDescriptionId("saddle");
	Item::door_iron = (new DoorItem(74, Material::metal))->setIcon("door_iron", 0)->setCategory(2, 1)->setDescriptionId("doorIron");
	Item::redStone = (new Item(75))->setIcon("redstone_dust", 0)->setCategory(3, 8)->setDescriptionId("redstone");
	Item::snowBall = (new SnowballItem(76))->setIcon("snowball", 0)->setCategory(3, 8)->setDescriptionId("snowball");
	Item::leather = (new Item(78))->setIcon("leather", 0)->setCategory(4, 2)->setDescriptionId("leather");
	Item::brick = (new Item(80))->setIcon("brick", 0)->setCategory(4, 1)->setDescriptionId("brick");
	Item::clay = (new Item(81))->setIcon("clay_ball", 0)->setCategory(4, 1)->setDescriptionId("clay");
	Item::reeds = (new TilePlanterItem(82, Tile::reeds))->setIcon("reeds", 0)->setCategory(4, 4)->setDescriptionId("reeds");
	Item::paper = (new Item(83))->setIcon("paper", 0)->setCategory(4, 8)->setDescriptionId("paper");
	Item::book = (new Item(84))->setIcon("book_normal", 0)->setCategory(4, 8)->setDescriptionId("book");
	Item::slimeBall = (new Item(85))->setIcon("slimeball", 0)->setCategory(4, 8)->setDescriptionId("slimeball");
	Item::egg = (new EggItem(88))->setIcon("egg", 0)->setCategory(4, 4)->setDescriptionId("egg");
	Item::compass = (new CompassItem(89))->setIcon("compass_item", 0)->setCategory(3, 2)->setDescriptionId("compass");
	Item::clock = (new ClockItem(91))->setIcon("clock_item", 0)->setCategory(3, 2)->setDescriptionId("clock");
	Item::yellowDust = (new Item(92))->setIcon("glowstone_dust", 0)->setCategory(4, 2)->setDescriptionId("yellowDust");
	Item::dye_powder = (new DyePowderItem(95))->setIcon("dye_powder", 0)->setCategory(4, 8)->setDescriptionId("dyePowder");
	Item::bone = (new Item(96))->setIcon("bone", 0)->setCategory(4, 2)->setDescriptionId("bone");
	Item::sugar = (new Item(97))->setIcon("sugar", 0)->setCategory(4, 4)->setDescriptionId("sugar");
	Item::cake = (new TilePlanterItem(98, Tile::cake))->setMaxStackSize(1)->setIcon("cake", 0)->setCategory(2, 4)->setDescriptionId("cake");
	Item::bed = (new BedItem(99))->setMaxStackSize(1)->setIcon("bed", 0)->setCategory(2, 1)->setDescriptionId("bed");
	Item::shears = (new ShearsItem(103))->setIcon("shears", 0)->setCategory(3, 2)->setDescriptionId("shears");
	Item::melon = (new FoodItem(104, 2, 0.6, 0))->setIcon("melon", 0)->setCategory(2, 4)->setDescriptionId("melon");
	Item::seeds_pumpkin = (new SeedItem(105, Tile::pumpkinStem->blockID, Tile::farmland->blockID))->setIcon("seeds_pumpkin", 0)->setCategory(4, 4)->setDescriptionId("seedsPumpkin");
	Item::seeds_melon = (new SeedItem(106, Tile::melonStem->blockID, Tile::farmland->blockID))->setIcon("seeds_melon", 0)->setCategory(4, 4)->setDescriptionId("seedsMelon");
	Item::beef_raw = (new FoodItem(107, 3, 0.6, 1))->setIcon("beef_raw", 0)->setCategory(4, 4)->setDescriptionId("beefRaw");
	Item::beef_cooked = (new FoodItem(108, 8, 0.6, 1))->setIcon("beef_cooked", 0)->setCategory(4, 4)->setDescriptionId("beefCooked");
	Item::chicken_raw = (new FoodItem(109, 2, 0.6, 1))->setIcon("chicken_raw", 0)->setCategory(4, 4)->setDescriptionId("chickenRaw");
	Item::chicken_cooked = (new FoodItem(110, 6, 0.6, 1))->setIcon("chicken_cooked", 0)->setCategory(4, 4)->setDescriptionId("chickenCooked");
	Item::mobPlacer = (new MonsterPlacerItem(127))->setIcon("spawn_egg", 0)->setCategory(3, 2)->setDescriptionId("monsterPlacer");
	Item::carrot = (new SeedFoodItem(135, 4, 0.6, 0, Tile::carrots->blockID, Tile::farmland->blockID))->setIcon("carrot", 0)->setCategory(4, 4)->setDescriptionId("carrots");
	Item::potato = (new SeedFoodItem(136, 1, 0.6, 0, Tile::potatoes->blockID, Tile::farmland->blockID))->setIcon("potato", 0)->setCategory(4, 4)->setDescriptionId("potatos"); //PotatOS
	Item::potatoBaked = (new FoodItem(137, 6, 0.6, 0))->setIcon("potato_baked", 0)->setCategory(4, 4)->setDescriptionId("potatoBaked");
	Item::pumpkinPie = (new FoodItem(144, 8, 0.6, 0))->setIcon("pumpkin_pie", 0)->setCategory(4, 4)->setDescriptionId("pumpkinPie");
	Item::netherbrick = (new Item(149))->setIcon("netherbrick", 0)->setDescriptionId("netherbrickItem")->setCategory(4, 1);
	Item::netherQuartz = (new Item(150))->setIcon("quartz", 0)->setDescriptionId("netherquartz")->setCategory(4, 16);
	Item::camera = (new CameraItem(200))->setIcon("egg", 0)->setCategory(3, 8)->setDescriptionId("camera");
	Item::beetroot = (new FoodItem(201, 1, 0.6, 0))->setIcon("beetroot", 0)->setCategory(4, 4)->setDescriptionId("beetroot");
	Item::seeds_beetroot = (new SeedItem(202, Tile::beetroot->blockID, Tile::farmland->blockID))->setIcon("seeds_beetroot", 0)->setCategory(4, 4)->setDescriptionId("seedsBeetroot");
	Item::beetrootSoup = (new BowlFoodItem(203, 8))->setIcon("beetroot_soup", 0)->setCategory(4, 4)->setDescriptionId("beetrootSoup");

	int32_t v556 = 0;
	do {
		Item* item = Item::items[v556 + 256];
		if(item) {
			if(item->field_38 == -1) {
				item->getDescriptionId();
				//delete item->getDescriptionId(); //TODO ????
			}
		}
		++v556;
	} while(v556 != 256);
}

void Item::teardownItems() {
	for(int32_t i = 0; i != 512; ++i) {
		Item* v1 = Item::items[i];
		if(v1) {
			delete v1;
			Item::items[i] = 0;
		}
	}
}
TextureAtlasTextureItem* Item::getTextureItem(const std::string& a1) {
	return Item::_itemTextureAtlas->getTextureItem(a1);
}

Item::Item(int32_t id) {
	this->maxStackSize = 64;
	this->itemTexture = "items-opaque.png";
	this->field_C = 1;
	this->field_10 = 1;
	this->maxItemdamage = 0;
	this->handEquipped_ = 0;
	this->stackedByData = 0;
	this->field_40 = 0;
	this->iconUV.minX = this->iconUV.minY = this->iconUV.maxX = this->iconUV.maxY = 0;
	this->itemID = id + 256;
	this->field_38 = -1;
	this->descriptionID = "";
	if(Item::items[id + 256]) {
		printf("Item conflict id @ %d! Id already used\n", id + 256);
	}
	Item::items[this->itemID] = this;

}
HitResult Item::getPlayerPOVHitResult(Level* level, struct Player* player, bool_t a5) {
	float v7;  // s16
	float v8;  // s17
	float v9;  // s12
	float v10; // s11
	float v11; // s14

	v7 = player->prevPitch + (float)(player->pitch - player->prevPitch);
	v8 = player->prevYaw + (float)(player->yaw - player->prevYaw);
	v9 = (float)(player->prevY + (float)(player->posY - player->prevY)) + 1.62 - player->ridingHeight;
	Vec3 start(player->prevX + (float)(player->posX - player->prevX), v9, player->prevZ + (float)(player->posZ - player->prevZ));
	v10 = -(float)(v7 * 57.296);
	v11 = -Mth::cos(v10);
	Vec3 end(start.x + (float)((float)(v11 * Mth::sin((float)((float) - (float)(v8 * 57.296) - 3.1416))) * 5.0), start.y + (float)(Mth::sin(v10) * 5.0), start.z + (float)((float)(v11 * Mth::cos((float)((float) - (float)(v8 * 57.296) - 3.1416))) * 5.0));
	return level->clip(start, end, a5, !a5);
}
TextureUVCoordinateSet Item::getTextureUVCoordinateSet(const std::string& a2, int32_t a3) {
	return *Item::_itemTextureAtlas->getTextureItem(a2)->getUV(a3);
}
Item* Item::setCategory(int32_t a2, int32_t a3) {
	this->field_34 = a2;
	this->field_38 = a3;
	return this;
}
void Item::setMaxDamage(int32_t a2) {
	this->maxItemdamage = a2;
}
void Item::setStackedByData(bool_t a2) {
	this->stackedByData = a2;
}

Item::~Item() {
	//~descriptionID
	//~itemTextures
}
int32_t Item::getMaxStackSize(const struct ItemInstance*) {
	return this->maxStackSize;
}
Item* Item::setMaxStackSize(int32_t a2) {
	this->maxStackSize = a2;
	return this;
}
bool_t Item::canBeDepleted() {
	if(this->maxItemdamage <= 0) return 0;
	return !this->stackedByData;
}
TextureUVCoordinateSet* Item::getIcon(int32_t, int32_t, bool_t) {
	return &this->iconUV;
}
Item* Item::setIcon(const std::string& a2, int32_t a3) {
	this->iconUV = this->getTextureUVCoordinateSet(a2, a3);
	return this;
}
Item* Item::setIcon(TextureUVCoordinateSet a) {
	this->iconUV = a;
	return this;
}
bool_t Item::isMirroredArt() {
	return 0;
}
ItemInstance* Item::use(struct ItemInstance* r, Level*, struct Player*) {
	return r;
}
bool_t Item::useOn(struct ItemInstance*, struct Level*, int32_t, int32_t, int32_t, int32_t) {
	return 0;
}
bool_t Item::useOn(struct ItemInstance*, struct Player*, Level*, int32_t, int32_t, int32_t, int32_t, float, float, float) {
	return 0;
}
int32_t Item::getMaxUseDuration() {
	return 0;
}
ItemInstance Item::useTimeDepleted(ItemInstance* a3, Level*, struct Player*) {
	return ItemInstance(*a3);
}
int32_t Item::getUseAnimation() {
	return 0;
}
void Item::releaseUsing(struct ItemInstance*, Level*, struct Player*, int32_t) {
}
float Item::getDestroySpeed(struct ItemInstance*, struct Tile*) {
	return 1;
}
bool_t Item::canDestroySpecial(const struct Tile*) {
	return 0;
}
int32_t Item::getLevelDataForAuxValue(int32_t a2) {
	return 0;
}
bool_t Item::isStackedByData() {
	return this->stackedByData;
}
int32_t Item::getMaxDamage() {
	return this->maxItemdamage;
}
int32_t Item::getAttackDamage(struct Entity*) {
	return 1;
}
void Item::hurtEnemy(struct ItemInstance*, Mob*, Mob*) {
}
void Item::interactEnemy(struct ItemInstance*, Mob*, Player*) {
}
bool_t Item::mineBlock(struct ItemInstance*, int32_t, int32_t, int32_t, int32_t, struct Mob*) {
	return 0;
}
Item* Item::handEquipped() {
	this->handEquipped_ = 1;
	return this;
}
bool_t Item::isHandEquipped() {
	return this->handEquipped_;
}
bool_t Item::isFood() {
	return 0;
}
bool_t Item::isSeed() {
	return 0;
}
bool_t Item::isArmor() {
	return 0;
}
bool_t Item::isLiquidClipItem(int32_t) {
	return 0;
}
std::string Item::getName(const struct ItemInstance* a2) {
	return I18n::get(this->getDescriptionId(a2) + ".name");
}
std::string Item::getDescription(void) {
	return I18n::get(this->getDescriptionId());
}
std::string Item::getDescription(const struct ItemInstance* a2) {
	return I18n::get(this->getDescriptionId(a2));
}
std::string Item::getDescriptionId() {
	return this->descriptionID;
}
std::string Item::getDescriptionId(const struct ItemInstance*) {
	return this->descriptionID;
}
Item* Item::setDescriptionId(const std::string& a2) {
	std::string v5 = Item::ICON_DESCRIPTION_PREFIX + a2;
	this->descriptionID = v5;
	return this;
}
bool_t Item::isEmissive(int32_t) {
	return 0;
}
int32_t Item::getAnimationFrameFor(Mob*) {
	return 0;
}
