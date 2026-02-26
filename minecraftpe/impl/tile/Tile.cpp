#include <tile/Tile.hpp>
#include <entity/ItemEntity.hpp>
#include <entity/Player.hpp>
#include <item/ClothTileItem.hpp>
#include <item/LeafTileItem.hpp>
#include <item/SaplingTileItem.hpp>
#include <item/StoneSlabTileItem.hpp>
#include <level/Level.hpp>
#include <math/HitResult.hpp>
#include <math/Vec3.hpp>
#include <string.h>
#include <tile/BedTile.hpp>
#include <tile/BeetrootTile.hpp>
#include <tile/BookshelfTile.hpp>
#include <tile/CactusTile.hpp>
#include <tile/CakeTile.hpp>
#include <tile/CarrotTile.hpp>
#include <tile/ChestTile.hpp>
#include <tile/ClayTile.hpp>
#include <tile/ClothTile.hpp>
#include <tile/CropTile.hpp>
#include <tile/DeadBush.hpp>
#include <tile/DirtTile.hpp>
#include <tile/DoorTile.hpp>
#include <tile/FarmTile.hpp>
#include <tile/FenceGateTile.hpp>
#include <tile/FenceTile.hpp>
#include <tile/FireTile.hpp>
#include <tile/FlowerTile.hpp>
#include <tile/FurnaceTile.hpp>
#include <tile/GlassTile.hpp>
#include <tile/GrassTile.hpp>
#include <tile/GravelTile.hpp>
#include <tile/HayBlockTile.hpp>
#include <tile/HeavyTile.hpp>
#include <tile/IceTile.hpp>
#include <tile/InvisibleTile.hpp>
#include <tile/LadderTile.hpp>
#include <tile/LeafTile.hpp>
#include <tile/LightGemTile.hpp>
#include <tile/LiquidTileDynamic.hpp>
#include <tile/LiquidTileStatic.hpp>
#include <tile/MelonTile.hpp>
#include <tile/MetalTile.hpp>
#include <tile/MultiTextureTile.hpp>
#include <tile/Mushroom.hpp>
#include <tile/NetherReactor.hpp>
#include <tile/ObsidianTile.hpp>
#include <tile/OreTile.hpp>
#include <tile/PotatoTile.hpp>
#include <tile/PoweredRailTile.hpp>
#include <tile/PumpkinTile.hpp>
#include <tile/QuartzBlockTile.hpp>
#include <tile/RailTile.hpp>
#include <tile/RedStoneOreTile.hpp>
#include <tile/ReedTile.hpp>
#include <tile/SandStoneTile.hpp>
#include <tile/Sapling.hpp>
#include <tile/SignTile.hpp>
#include <tile/SnowTile.hpp>
#include <tile/StairTile.hpp>
#include <tile/StemTile.hpp>
#include <tile/StoneSlabTile.hpp>
#include <tile/StoneTile.hpp>
#include <tile/StonecutterTile.hpp>
#include <tile/TallGrass.hpp>
#include <tile/ThinFenceTile.hpp>
#include <tile/TntTile.hpp>
#include <tile/TopSnowTile.hpp>
#include <tile/TorchTile.hpp>
#include <tile/TrapDoorTile.hpp>
#include <tile/TreeTile.hpp>
#include <tile/WallTile.hpp>
#include <tile/WebTile.hpp>
#include <tile/WoodSlabTile.hpp>
#include <tile/WoodTile.hpp>
#include <tile/WoolCarpetTile.hpp>
#include <tile/WorkbenchTile.hpp>
#include <tile/entity/TileEntity.hpp>
#include <tile/material/Material.hpp>
#include <util/Util.hpp>
#include <I18n.hpp>

Tile::SoundType Tile::SOUND_NORMAL("stone", 1, 1);
Tile::SoundType Tile::SOUND_WOOD("wood", 1, 1);
Tile::SoundType Tile::SOUND_GRAVEL("gravel", 1, 1);
Tile::SoundType Tile::SOUND_GRASS("grass", 0.5, 1);
Tile::SoundType Tile::SOUND_STONE("stone", 1, 1);
Tile::SoundType Tile::SOUND_METAL("stone", 1, 1.5);
Tile::SoundType Tile::SOUND_GLASS("random.glass", "stone", 1, 1);
Tile::SoundType Tile::SOUND_CLOTH("cloth", 1, 1);
Tile::SoundType Tile::SOUND_SAND("step.gravel", "sand", 1, 1);
Tile::SoundType Tile::SOUND_SILENT("", 0, 0);
std::string Tile::WOOD_NAMES[] = {"oak", "spruce", "birch", "jungle"};

Tile* Tile::rock;
Tile* Tile::grass;
Tile* Tile::dirt;
Tile* Tile::stoneBrick;
Tile* Tile::wood;
Tile* Tile::sapling;
Tile* Tile::unbreakable;
Tile* Tile::water;
Tile* Tile::calmWater;
Tile* Tile::lava;
Tile* Tile::calmLava;
Tile* Tile::sand;
Tile* Tile::gravel;
Tile* Tile::goldOre;
Tile* Tile::ironOre;
Tile* Tile::coalOre;
Tile* Tile::treeTrunk;
Tile* Tile::leaves;
Tile* Tile::sponge;
Tile* Tile::glass;
Tile* Tile::lapisOre;
Tile* Tile::lapisBlock;
Tile* Tile::sandStone;
Tile* Tile::bed;
Tile* Tile::goldenRail;
Tile* Tile::web;
Tile* Tile::tallgrass;
Tile* Tile::deadBush;
Tile* Tile::cloth;
Tile* Tile::flower;
Tile* Tile::rose;
Tile* Tile::mushroom1;
Tile* Tile::mushroom2;
Tile* Tile::goldBlock;
Tile* Tile::ironBlock;
Tile* Tile::stoneSlab;
Tile* Tile::stoneSlabHalf;
Tile* Tile::redBrick;
Tile* Tile::tnt;
Tile* Tile::bookshelf;
Tile* Tile::mossStone;
Tile* Tile::obsidian;
Tile* Tile::torch;
Tile* Tile::stairs_wood;
Tile* Tile::chest;
Tile* Tile::emeraldOre;
Tile* Tile::emeraldBlock;
Tile* Tile::workBench;
Tile* Tile::crops;
Tile* Tile::farmland;
Tile* Tile::furnace;
Tile* Tile::furnace_lit;
Tile* Tile::sign;
Tile* Tile::door_wood;
Tile* Tile::ladder;
Tile* Tile::rail;
Tile* Tile::stairs_stone;
Tile* Tile::wallSign;
Tile* Tile::door_iron;
Tile* Tile::redStoneOre;
Tile* Tile::redStoneOre_lit;
Tile* Tile::topSnow;
Tile* Tile::ice;
Tile* Tile::snow;
Tile* Tile::cactus;
Tile* Tile::clay;
Tile* Tile::reeds;
Tile* Tile::fence;
Tile* Tile::pumpkin;
Tile* Tile::netherrack;
Tile* Tile::lightGem;
Tile* Tile::litPumpkin;
Tile* Tile::cake;
Tile* Tile::invisible_bedrock;
Tile* Tile::trapdoor;
Tile* Tile::stoneBrickSmooth;
Tile* Tile::ironFence;
Tile* Tile::thinGlass;
Tile* Tile::melon;
Tile* Tile::pumpkinStem;
Tile* Tile::melonStem;
Tile* Tile::fenceGate;
Tile* Tile::stairs_brick;
Tile* Tile::woodStairsDark;
Tile* Tile::woodStairsBirch;
Tile* Tile::woodStairsJungle;
Tile* Tile::stairs_stoneBrickSmooth;
Tile* Tile::netherBrick;
Tile* Tile::stairs_netherBricks;
Tile* Tile::activatorRail;
Tile* Tile::stairs_sandStone;
Tile* Tile::cobbleWall;
Tile* Tile::carrots;
Tile* Tile::potatoes;
Tile* Tile::quartzBlock;
Tile* Tile::stairs_quartz;
Tile* Tile::woodSlab;
Tile* Tile::woodSlabHalf;
Tile* Tile::hayBlock;
Tile* Tile::woolCarpet;
Tile* Tile::coalBlock;
Tile* Tile::beetroot;
Tile* Tile::stonecutterBench;
Tile* Tile::glowingObsidian;
Tile* Tile::netherReactor;
Tile* Tile::info_updateGame1;
Tile* Tile::info_updateGame2;
Tile* Tile::info_reserved6;
Tile* Tile::fire;

std::string Tile::TILE_DESCRIPTION_PREFIX = "tile.";

bool_t Tile::shouldTick[256];
bool_t Tile::isEntityTile[256];
bool_t Tile::solid[256];
bool_t Tile::lightEmission[256];
bool_t Tile::lightBlock[256];
Tile* Tile::tiles[256];
bool_t Tile::translucent[256] = {1, 0};
std::shared_ptr<TextureAtlas> Tile::_terrainTextureAtlas;

void Tile::initTiles(std::shared_ptr<TextureAtlas> a1) {
	Tile::_terrainTextureAtlas = a1;
	memset(Tile::tiles, 0, sizeof(Tile::tiles));
	Tile::rock = (new StoneTile(1, "stone"))->init()->setDestroyTime(1)->setExplodeable(10.0f)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 1)->setDescriptionId("stone");
	Tile::grass = (new GrassTile(2))->init()->setDestroyTime(0.6)->setSoundType(Tile::SOUND_GRASS)->setCategory(1, 1)->setDescriptionId("grass");
	Tile::dirt = (new DirtTile(3, "dirt", Material::dirt))->init()->setDestroyTime(0.5f)->setSoundType(Tile::SOUND_GRAVEL)->setCategory(1, 1)->setDescriptionId("dirt");
	Tile::dirt->field_5C = 255;
	Tile::stoneBrick = (new Tile(4, "cobblestone", Material::stone))->init()->setDestroyTime(2.0)->setExplodeable(10.0)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 1)->setDescriptionId("stonebrick");
	Tile::wood = (new WoodTile(5))->init()->setDestroyTime(2.0)->setExplodeable(5.0)->setSoundType(Tile::SOUND_WOOD)->setCategory(1, 1)->setDescriptionId("wood");
	Tile::sapling = (new Sapling(6, "sapling"))->init()->setDestroyTime(0)->setSoundType(Tile::SOUND_GRASS)->setCategory(2, 1)->setDescriptionId("sapling");
	Tile::unbreakable = (new Tile(7, "bedrock", Material::stone))->init()->setDestroyTime(-1.0)->setExplodeable(6000000.0)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 1)->setDescriptionId("bedrock");
	Tile::water = (new LiquidTileDynamic(8, Material::water, "still_water", "flowing_water"))->init()->setDestroyTime(100)->setLightBlock(3)->setCategory(1, 1)->setDescriptionId("water");
	Tile::calmWater = (new LiquidTileStatic(9, Material::water, "still_water", "flowing_water"))->init()->setDestroyTime(100)->setLightBlock(3)->setCategory(1, 1)->setDescriptionId("water");
	Tile::lava = (new LiquidTileDynamic(10, Material::lava, "still_lava", "flowing_lava"))->init()->setDestroyTime(0)->setLightEmission(1.0)->setLightBlock(255)->setCategory(1, 1)->setDescriptionId("lava");
	Tile::calmLava = (new LiquidTileStatic(11, Material::lava, "still_lava", "flowing_lava"))->init()->setDestroyTime(100.0)->setLightEmission(1.0)->setLightBlock(255)->setCategory(1, 1)->setDescriptionId("lava");
	Tile::calmLava->field_5C = 255; //TODO what is this and wheres this thing supposed to be called from
	Tile::sand = (new HeavyTile(12, "sand"))->init()->setDestroyTime(0.5)->setSoundType(Tile::SOUND_SAND)->setCategory(1, 1)->setDescriptionId("sand");
	Tile::sand->field_5C = 255;
	Tile::gravel = (new GravelTile(0xD, "gravel"))->init()->setDestroyTime(0.6)->setSoundType(Tile::SOUND_GRAVEL)->setCategory(1, 1)->setDescriptionId("gravel");
	Tile::goldOre = (new OreTile(14, "gold_ore"))->init()->setDestroyTime(3.0)->setExplodeable(5.0)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 8)->setDescriptionId("oreGold");
	Tile::ironOre = (new OreTile(15, "iron_ore"))->init()->setDestroyTime(3.0)->setExplodeable(5.0)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 8)->setDescriptionId("oreIron");
	Tile::coalOre = (new OreTile(16, "coal_ore"))->init()->setDestroyTime(3.0)->setExplodeable(5.0)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 1)->setDescriptionId("oreCoal");
	Tile::treeTrunk = (new TreeTile(17))->init()->setDestroyTime(2.0)->setSoundType(Tile::SOUND_WOOD)->setCategory(1, 1)->setDescriptionId("log");
	Tile::leaves = (new LeafTile(18, "leaves"))->init()->setDestroyTime(0.2)->setLightBlock(1)->setSoundType(Tile::SOUND_GRASS)->setCategory(2, 1)->setDescriptionId("leaves");
	Tile::sponge = (new Tile(19, "sponge", Material::dirt))->init()->setCategory(2, 1)->setDestroyTime(0.6)->setSoundType(Tile::SOUND_GRASS)->setDescriptionId("sponge");
	Tile::sponge->field_5C = 255;
	Tile::glass = (new GlassTile(20, "glass", Material::glass))->init()->setDestroyTime(0.3)->setSoundType(Tile::SOUND_GLASS)->setCategory(2, 1)->setDescriptionId("glass");
	Tile::lapisOre = (new OreTile(21, "lapis_ore"))->init()->setDestroyTime(3.0)->setExplodeable(5.0)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 1)->setDescriptionId("oreLapis");
	Tile::lapisBlock = (new Tile(22, "lapis_block", Material::stone))->init()->setDestroyTime(3.0)->setExplodeable(5.0)->setSoundType(Tile::SOUND_STONE)->setCategory(2, 8)->setDescriptionId("blockLapis");
	Tile::sandStone = (new SandStoneTile(24, "sandstone"))->init()->setSoundType(Tile::SOUND_STONE)->setDestroyTime(0.8)->setCategory(1, 1)->setDescriptionId("sandStone");
	Tile::bed = (new BedTile(26))->init()->setDestroyTime(0.2)->setCategory(2, 1)->setDescriptionId("bed");
	Tile::goldenRail = (new PoweredRailTile(27))->init()->setDestroyTime(0.7)->setSoundType(Tile::SOUND_METAL)->setCategory(3, 2)->setDescriptionId("goldenRail");
	Tile::web = (new WebTile(30, "web", Material::web))->init()->setLightBlock(1)->setDestroyTime(4.0)->setCategory(2, 8)->setDescriptionId("web");
	Tile::tallgrass = (new TallGrass(31, "tallgrass"))->init()->setDestroyTime(0)->setSoundType(Tile::SOUND_GRASS)->setCategory(2, 8)->setDescriptionId("tallgrass");
	Tile::deadBush = (new DeadBush(32, "tallgrass"))->init()->setDestroyTime(0)->setSoundType(Tile::SOUND_GRASS)->setCategory(2, 1)->setDescriptionId("deadbush");
	Tile::cloth = (new ClothTile(35))->init()->setDestroyTime(0.8)->setSoundType(Tile::SOUND_CLOTH)->setCategory(2, 1)->setDescriptionId("cloth");
	Tile::flower = (new FlowerTile(37, "flower_dandelion"))->init()->setDestroyTime(0)->setSoundType(Tile::SOUND_GRASS)->setCategory(2, 8)->setDescriptionId("flower");
	Tile::rose = (new FlowerTile(38, "flower_rose_blue"))->init()->setDestroyTime(0)->setSoundType(Tile::SOUND_GRASS)->setCategory(2, 8)->setDescriptionId("rose");
	Tile::mushroom1 = (new Mushroom(39, "mushroom_brown"))->init()->setDestroyTime(0)->setSoundType(Tile::SOUND_GRASS)->setLightEmission(0.125)->setCategory(2, 8)->setDescriptionId("mushroom");
	Tile::mushroom2 = (new Mushroom(40, "mushroom_red"))->init()->setDestroyTime(0)->setSoundType(Tile::SOUND_GRASS)->setCategory(2, 8)->setDescriptionId("mushroom");
	Tile::goldBlock = (new MetalTile(41, "gold_block"))->init()->setDestroyTime(3.0)->setExplodeable(10.0)->setSoundType(Tile::SOUND_METAL)->setCategory(2, 8)->setDescriptionId("blockGold");
	Tile::ironBlock = (new MetalTile(42, "iron_block"))->init()->setDestroyTime(5.0)->setExplodeable(10.0)->setSoundType(Tile::SOUND_METAL)->setCategory(2, 8)->setDescriptionId("blockIron");
	Tile::stoneSlab = (new StoneSlabTile(43, 1))->init()->setDestroyTime(2.0)->setExplodeable(10.0)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 1)->setDescriptionId("stoneSlab");
	Tile::stoneSlabHalf = (new StoneSlabTile(44, 0))->init()->setDestroyTime(2.0)->setExplodeable(10.0)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 1)->setDescriptionId("stoneSlab");
	Tile::redBrick = (new Tile(45, "brick", Material::stone))->init()->setDestroyTime(2.0)->setExplodeable(10.0)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 1)->setDescriptionId("brick");
	Tile::tnt = (new TntTile(46, "tnt_side"))->init()->setDestroyTime(0)->setSoundType(Tile::SOUND_GRASS)->setCategory(3, 2)->setDescriptionId("tnt");
	Tile::bookshelf = (new BookshelfTile(47, "bookshelf", Material::wood))->init()->setDestroyTime(1.5)->setSoundType(Tile::SOUND_WOOD)->setCategory(2, 8)->setDescriptionId("bookshelf");
	Tile::mossStone = (new Tile(48, "cobblestone_mossy", Material::stone))->init()->setDestroyTime(2.0)->setExplodeable(10.0)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 1)->setDescriptionId("stoneMoss");
	Tile::obsidian = (new ObsidianTile(49, "obsidian", 0))->init()->setDestroyTime(10)->setExplodeable(2000)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 1)->setDescriptionId("obsidian");
	Tile::torch = (new TorchTile(50, "torch_on", Material::decoration))->init()->setDestroyTime(0)->setLightEmission(0.9375)->setSoundType(Tile::SOUND_WOOD)->setCategory(3, 2)->setDescriptionId("torch");
	Tile::stairs_wood = (new StairTile(53, Tile::wood, 0))->init()->setCategory(1, 1)->setDescriptionId("stairsWood");
	Tile::chest = (new ChestTile(54))->init()->setCategory(2, 1)->setDestroyTime(2.5)->setSoundType(Tile::SOUND_WOOD)->setDescriptionId("chest");
	Tile::emeraldOre = (new OreTile(56, "diamond_ore"))->init()->setDestroyTime(3.0)->setExplodeable(5.0)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 8)->setDescriptionId("oreDiamond");
	Tile::emeraldBlock = (new MetalTile(57, "diamond_block"))->init()->setDestroyTime(5.0)->setExplodeable(10.0)->setSoundType(Tile::SOUND_METAL)->setCategory(2, 8)->setDescriptionId("blockDiamond");
	Tile::workBench = (new WorkbenchTile(58))->init()->setDestroyTime(2.5)->setSoundType(Tile::SOUND_WOOD)->setCategory(2, 1)->setDescriptionId("workbench");
	Tile::crops = (new CropTile(59, "wheat_stage_x"))->init()->setDestroyTime(0)->setSoundType(Tile::SOUND_GRASS)->setCategory(4, 1)->setDescriptionId("crops");
	Tile::farmland = (new FarmTile(60))->init()->setDestroyTime(0.6)->setSoundType(Tile::SOUND_GRAVEL)->setCategory(1, 1)->setDescriptionId("farmland");
	Tile::furnace = (new FurnaceTile(61, 0))->init()->setDestroyTime(3.5)->setSoundType(Tile::SOUND_STONE)->setCategory(2, 1)->setDescriptionId("furnace");
	Tile::furnace_lit = (new FurnaceTile(62, 1))->init()->setDestroyTime(3.5)->setSoundType(Tile::SOUND_STONE)->setLightEmission(0.875)->setCategory(2, 1)->setDescriptionId("furnace");
	Tile::sign = (new SignTile(63, 1))->init()->setDestroyTime(1.0)->setSoundType(Tile::SOUND_WOOD)->setCategory(2, 8)->setDescriptionId("sign");
	Tile::door_wood = (new DoorTile(64, Material::wood))->init()->setDestroyTime(3.0)->setSoundType(Tile::SOUND_WOOD)->setCategory(2, 1)->setDescriptionId("doorWood");
	Tile::ladder = (new LadderTile(65, "ladder", Material::decoration))->init()->setDestroyTime(0.4)->setSoundType(Tile::SOUND_WOOD)->setCategory(2, 1)->setDescriptionId("ladder");
	Tile::rail = (new RailTile(66))->init()->setDestroyTime(0.7)->setSoundType(Tile::SOUND_METAL)->setCategory(3, 2)->setDescriptionId("rail");
	Tile::stairs_stone = (new StairTile(67, Tile::stoneBrick, 0))->init()->setCategory(1, 1)->setDescriptionId("stairsStone");
	Tile::wallSign = (new SignTile(68, 0))->init()->setDestroyTime(1.0)->setSoundType(Tile::SOUND_WOOD)->setCategory(2, 8)->setDescriptionId("sign");
	Tile::door_iron = (new DoorTile(71, Material::metal))->init()->setDestroyTime(5.0)->setSoundType(Tile::SOUND_METAL)->setCategory(2, 1)->setDescriptionId("doorIron");
	Tile::redStoneOre = (new RedStoneOreTile(73, "redstone_ore", 0))->init()->setDestroyTime(3.0)->setExplodeable(5.0)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 8)->setDescriptionId("oreRedstone");
	Tile::redStoneOre_lit = (new RedStoneOreTile(74, "redstone_ore", 1))->init()->setDestroyTime(3.0)->setLightEmission(0.625)->setExplodeable(5.0)->setSoundType(Tile::SOUND_STONE)->setCategory(2, 8)->setDescriptionId("oreRedstone");
	Tile::topSnow = (new TopSnowTile(78, "snow", Material::topSnow))->init()->setDestroyTime(0.1)->setSoundType(Tile::SOUND_CLOTH)->setCategory(2, 1)->setDescriptionId("snow");
	Tile::ice = (new IceTile(79, "ice", Material::ice))->init()->setDestroyTime(0.5)->setLightBlock(3)->setSoundType(Tile::SOUND_GLASS)->setCategory(1, 1)->setDescriptionId("ice");
	Tile::snow = (new SnowTile(80, "snow", Material::snow))->init()->setDestroyTime(0.2)->setSoundType(Tile::SOUND_CLOTH)->setCategory(1, 1)->setDescriptionId("snow");
	Tile::cactus = (new CactusTile(81))->init()->setDestroyTime(0.4)->setSoundType(Tile::SOUND_CLOTH)->setCategory(2, 1)->setDescriptionId("cactus");
	Tile::clay = (new ClayTile(82, "clay", Material::clay))->init()->setDestroyTime(0.6)->setSoundType(Tile::SOUND_GRAVEL)->setCategory(1, 1)->setDescriptionId("clay");
	Tile::reeds = (new ReedTile(83, "reeds", Material::plant))->init()->setDestroyTime(0)->setSoundType(Tile::SOUND_GRASS)->setCategory(2, 1)->setDescriptionId("reeds");
	Tile::fence = (new FenceTile(85, "planks", Material::wood))->init()->setDestroyTime(2.0)->setExplodeable(5.0)->setSoundType(Tile::SOUND_WOOD)->setCategory(2, 1)->setDescriptionId("fence");
	Tile::pumpkin = (new PumpkinTile(86, 0))->init()->setDestroyTime(1.0)->setSoundType(Tile::SOUND_WOOD)->setCategory(2, 1)->setDescriptionId("pumpkin");
	Tile::netherrack = (new Tile(87, "netherrack", Material::stone))->init()->setDestroyTime(0.4)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 1)->setDescriptionId("hellrock");
	Tile::netherrack->field_5C = 255;
	Tile::lightGem = (new LightGemTile(89, "glowstone", Material::glass))->init()->setDestroyTime(0.3)->setCategory(2, 1)->setSoundType(Tile::SOUND_GLASS)->setLightEmission(1.0)->setDescriptionId("lightgem");
	Tile::litPumpkin = (new PumpkinTile(91, 1))->init()->setDestroyTime(1.0)->setSoundType(Tile::SOUND_WOOD)->setLightEmission(1.0)->setCategory(2, 1)->setDescriptionId("litpumpkin");
	Tile::cake = (new CakeTile(92))->init()->setDestroyTime(0.5)->setSoundType(Tile::SOUND_CLOTH)->setDescriptionId("cake")->setCategory(2, 4);
	Tile::invisible_bedrock = (new InvisibleTile(95, "stone", Material::stone))->init()->setDestroyTime(-1.0)->setExplodeable(6000000.0);
	Tile::trapdoor = (new TrapDoorTile(96, Material::wood))->init()->setDestroyTime(3.0)->setSoundType(Tile::SOUND_WOOD)->setCategory(2, 1)->setDescriptionId("trapdoor");
	Tile::stoneBrickSmooth = (new MultiTextureTile(98, "stonebrick", Material::stone))->init()->setDestroyTime(1.5)->setExplodeable(10.0)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 1)->setDescriptionId("stonebricksmooth");
	Tile::ironFence = (new ThinFenceTile(101, "iron_bars", "iron_bars", Material::metal, 1))->init()->setDestroyTime(5.0)->setExplodeable(10.0)->setSoundType(Tile::SOUND_METAL)->setCategory(2, 8)->setDescriptionId("fenceiro"); //iro > iron
	Tile::thinGlass = (new ThinFenceTile(102, "glass", "glass_pane_top", Material::glass, 0))->init()->setDestroyTime(0.3)->setSoundType(Tile::SOUND_GLASS)->setCategory(2, 1)->setDescriptionId("thinGlass");
	Tile::melon = (new MelonTile(103))->init()->setDestroyTime(1.0)->setSoundType(Tile::SOUND_WOOD)->setCategory(2, 4)->setDescriptionId("melon");
	Tile::pumpkinStem = (new StemTile(104, Tile::pumpkin))->init()->setDestroyTime(0)->setSoundType(Tile::SOUND_WOOD)->setCategory(2, 4)->setDescriptionId("pumpkinStem");
	Tile::melonStem = (new StemTile(105, Tile::melon))->init()->setDestroyTime(0)->setSoundType(Tile::SOUND_WOOD)->setCategory(2, 4)->setDescriptionId("pumpkinStem");
	Tile::fenceGate = (new FenceGateTile(107, "planks", Material::wood))->init()->setDestroyTime(2.0)->setExplodeable(5.0)->setSoundType(Tile::SOUND_WOOD)->setCategory(2, 1)->setDescriptionId("fenceGate"); //TODO "planks" is inside the constructor?
	Tile::stairs_brick = (new StairTile(108, Tile::redBrick, 0))->init()->setCategory(1, 1)->setDescriptionId("stairsBrick");
	Tile::woodStairsDark = (new StairTile(134, Tile::wood, 1))->init()->setCategory(1, 1)->setDescriptionId("stairsWoodSpruce");
	Tile::woodStairsBirch = (new StairTile(135, Tile::wood, 2))->init()->setCategory(1, 1)->setDescriptionId("stairsWoodBirch");
	Tile::woodStairsJungle = (new StairTile(136, Tile::wood, 3))->init()->setCategory(1, 1)->setDescriptionId("stairsWoodJungle");
	Tile::stairs_stoneBrickSmooth = (new StairTile(109, Tile::stoneBrickSmooth, 0))->init()->setCategory(1, 1)->setDescriptionId("stairsStoneBrickSmooth");
	Tile::netherBrick = (new Tile(112, "nether_brick", Material::stone))->init()->setDestroyTime(2.0)->setExplodeable(10.0)->setSoundType(Tile::SOUND_STONE)->setCategory(1, 1)->setDescriptionId("netherBrick");
	Tile::stairs_netherBricks = (new StairTile(114, Tile::netherBrick, 0))->init()->setCategory(1, 1)->setDescriptionId("stairsNetherBrick");
	Tile::activatorRail = (new CakeTile(126))->init()->setDestroyTime(0.5)->setSoundType(Tile::SOUND_CLOTH)->setDescriptionId("cake")->setCategory(3, 4);
	Tile::stairs_sandStone = (new StairTile(128, Tile::sandStone, 0))->init()->setCategory(1, 1)->setDescriptionId("stairsSandStone");
	Tile::cobbleWall = (new WallTile(139, Tile::stoneBrick))->init()->setCategory(2, 1)->setDescriptionId("cobbleWall");
	Tile::carrots = (new CarrotTile(141))->init()->setDestroyTime(0)->setCategory(2, 4)->setDescriptionId("carrots");
	Tile::potatoes = (new PotatoTile(142))->init()->setDestroyTime(0)->setCategory(2, 4)->setDescriptionId("potatoes");
	Tile::quartzBlock = (new QuartzBlockTile(155))->init()->setSoundType(Tile::SOUND_STONE)->setDestroyTime(0.8)->setCategory(1, 1)->setDescriptionId("quartzBlock");
	Tile::stairs_quartz = (new StairTile(156, Tile::quartzBlock, 0))->init()->setCategory(1, 1)->setDescriptionId("stairsQuartz");
	Tile::woodSlab = (new WoodSlabTile(157, 1))->init()->setDestroyTime(2.0)->setExplodeable(10.0)->setSoundType(Tile::SOUND_WOOD)->setCategory(1, 1)->setDescriptionId("woodSlab");
	Tile::woodSlabHalf = (new WoodSlabTile(158, 0))->init()->setDestroyTime(2.0)->setExplodeable(10.0)->setSoundType(Tile::SOUND_WOOD)->setCategory(1, 1)->setDescriptionId("woodSlab");
	Tile::hayBlock = (new HayBlockTile(170))->init()->setDestroyTime(0.5)->setSoundType(Tile::SOUND_GRASS)->setCategory(2, 8)->setDescriptionId("hayBlock");
	Tile::woolCarpet = (new WoolCarpetTile(171))->init()->setDestroyTime(0.1)->setSoundType(Tile::SOUND_CLOTH)->setCategory(2, 8)->setLightBlock(0)->setDescriptionId("woolCarpet");
	Tile::coalBlock = (new MetalTile(173, "coal_block"))->init()->setDestroyTime(5.0)->setExplodeable(10.0)->setSoundType(Tile::SOUND_STONE)->setCategory(2, 8)->setDescriptionId("blockCoal");
	Tile::coalBlock->field_5C = 255;
	Tile::beetroot = (new BeetrootTile(244))->init()->setDestroyTime(0)->setCategory(2, 4)->setDescriptionId("beetroot");
	Tile::stonecutterBench = (new StonecutterTile(245))->init()->setDestroyTime(2.5)->setSoundType(Tile::SOUND_STONE)->setCategory(2, 1)->setDescriptionId("stonecutter");
	Tile::glowingObsidian = (new ObsidianTile(246, "glowing_obsidian", 1))->init()->setDestroyTime(10.0)->setLightEmission(0.875)->setExplodeable(2000.0)->setSoundType(Tile::SOUND_STONE)->setCategory(2, 1)->setDescriptionId("glowingobsidian");
	Tile::netherReactor = (new NetherReactor(247, "reactor_core_stage_x", Material::metal))->init()->setDestroyTime(3.0)->setSoundType(Tile::SOUND_METAL)->setCategory(2, 1)->setDescriptionId("netherreactor");
	Tile::info_updateGame1 = (new Tile(248, "missing_tile", Material::dirt))->init()->setDestroyTime(1.0)->setSoundType(Tile::SOUND_GRAVEL)->setCategory(1, 1)->setDescriptionId("info_update");
	Tile::info_updateGame2 = (new Tile(249, "missing_tile", Material::dirt))->init()->setDestroyTime(1.0)->setSoundType(Tile::SOUND_GRAVEL)->setCategory(1, 1)->setDescriptionId("info_update");
	Tile::info_reserved6 = (new Tile(255, Material::dirt))->init();
	Tile::fire = (new FireTile(51, "fire"))->init()->setDestroyTime(0.0)->setLightEmission(1.0)->setSoundType(Tile::SOUND_WOOD)->setCategory(1, 1)->setDescriptionId("fire");

	Item::items[Tile::cloth->blockID] = (new ClothTileItem(Tile::cloth->blockID - 256))->setCategory(2, 1)->setDescriptionId("cloth");
	Item::items[Tile::treeTrunk->blockID] = (new AuxDataTileItem(Tile::treeTrunk->blockID - 256, Tile::treeTrunk))->setCategory(1, 1)->setDescriptionId("log");
	Item::items[Tile::stoneBrickSmooth->blockID] = (new AuxDataTileItem(Tile::stoneBrickSmooth->blockID - 256, Tile::stairs_stoneBrickSmooth))->setCategory(1, 1)->setDescriptionId("stonebricksmooth");
	Item::items[Tile::stoneSlabHalf->blockID] = (new StoneSlabTileItem(Tile::stoneSlabHalf->blockID - 256))->setCategory(1, 1)->setDescriptionId("stoneSlab");
	Item::items[Tile::sapling->blockID] = (new SaplingTileItem(Tile::sapling->blockID - 256))->setCategory(2, 1)->setDescriptionId("sapling");
	Item::items[Tile::leaves->blockID] = (new LeafTileItem(Tile::leaves->blockID - 256))->setCategory(2, 8)->setDescriptionId("leaves");
	Item::items[Tile::sandStone->blockID] = (new AuxDataTileItem(Tile::sandStone->blockID - 256, Tile::sandStone))->setCategory(1, 1)->setDescriptionId("sandStone");
	Item::items[Tile::woodSlabHalf->blockID] = (new AuxDataTileItem(Tile::woodSlabHalf->blockID - 256, Tile::woodSlabHalf))->setCategory(1, 1)->setDescriptionId("woodSlab");
	Item::items[Tile::wood->blockID] = (new AuxDataTileItem(Tile::wood->blockID - 256, Tile::wood))->setCategory(1, 1)->setDescriptionId("wood");
	Item::items[Tile::quartzBlock->blockID] = (new AuxDataTileItem(Tile::quartzBlock->blockID - 256, Tile::quartzBlock))->setCategory(1, 1)->setDescriptionId("quartzBlock");
	Item::items[Tile::cobbleWall->blockID] = (new AuxDataTileItem(Tile::cobbleWall->blockID - 256, Tile::cobbleWall))->setCategory(2, 1)->setDescriptionId("cobbleWall");
	Item::items[Tile::tallgrass->blockID] = (new AuxDataTileItem(Tile::tallgrass->blockID - 256, Tile::tallgrass))->setCategory(2, 8)->setDescriptionId("tallgrass");
	Item::items[Tile::woolCarpet->blockID] = (new AuxDataTileItem(Tile::woolCarpet->blockID - 256, Tile::woolCarpet))->setCategory(2, 8)->setDescriptionId("woolCarpet");

	int32_t bid = 0;
	int32_t actualItemID = -256;
	do {
		if(Tile::tiles[bid]) {
			if(!Item::items[bid]) {
				Item::items[bid] = new TileItem(actualItemID);
				Item::items[bid]->field_38 = Tile::tiles[bid]->field_50;
				Item::items[bid]->field_34 = Tile::tiles[bid]->field_54;
			}
			if(Item::items[bid]) {
				Tile::tiles[bid]->getDescriptionId();
				//~str
			}
		}
		++bid;
		++actualItemID;
	} while(bid != 256);
}
void Tile::teardownTiles() {
	for(int32_t i = 0; i != 256; ++i) {
		delete Tile::tiles[i];
		Tile::tiles[i] = 0;
	}
}

Tile::SoundType::SoundType(const std::string& s, float a, float b) {
	this->field_4 = b;
	this->field_0 = a;
	this->field_8 = "step." + s;
	this->field_C = "step." + s;
}

Tile::SoundType::SoundType(const std::string& f8, const std::string& s, float a, float b) {
	this->field_4 = b;
	this->field_0 = a;
	this->field_8 = f8;
	this->field_C = "step." + s;
}

Tile::Tile(int32_t blockID, const Material* mat) {
	this->blockResistance = 0; //XXX doesnt seem to exist in mcpe?
	this->textureUV.minX = 0;
	this->textureUV.minY = 0;
	this->textureUV.maxX = 0;
	this->textureUV.maxY = 0;
	this->blockID = blockID;
	this->minX = 0;
	this->minY = 0;
	this->minZ = 0;
	this->maxX = 1;
	this->maxY = 1;
	this->maxZ = 1;
	this->material = mat;
	this->aabb.minX = 0;
	this->aabb.minY = 0;
	this->aabb.minZ = 0;
	this->soundType = &Tile::SOUND_NORMAL;
	this->slipperiness = 0.6;
	this->field_3C = 1;
	this->field_50 = -1;
	this->aabb.maxX = 1;
	this->field_5C = 0;
	this->aabb.maxY = 1;
	this->aabb.maxZ = 1;
	this->replaceable = 0;
	this->descriptionId = "";
	if(Tile::tiles[blockID]) {
		printf("Slot %d is already occupied by %p when adding %p\n", blockID, &Tile::tiles[blockID], this);
	}
}

Tile::Tile(int32_t blockID, TextureUVCoordinateSet uv, const Material* mat) {
	this->blockResistance = 0; //XXX doesnt seem to exist in mcpe?
	this->textureUV = uv;
	this->minX = 0;
	this->minY = 0;
	this->minZ = 0;
	this->maxX = 1;
	this->maxY = 1;
	this->maxZ = 1;
	this->blockID = blockID;
	this->field_3C = 1;
	this->aabb.minX = 0;
	this->soundType = &Tile::SOUND_NORMAL;
	this->material = mat;
	this->slipperiness = 0.6;
	this->field_50 = -1;
	this->field_5C = 0;
	this->aabb.minY = 0;
	this->aabb.maxX = 1;
	this->aabb.maxY = 1;
	this->aabb.maxZ = 1;
	this->aabb.minZ = 0;
	this->replaceable = 0;
	this->descriptionId = "";
	if(Tile::tiles[blockID]) {
		printf("Slot %d is already occupied by %p when adding %p\n", blockID, &Tile::tiles[blockID], this);
	}
}

Tile::Tile(int32_t blockID, std::string s, const Material* mat) {
	this->blockResistance = 0; //XXX doesnt seem to exist in mcpe?
	this->blockID = blockID;
	this->maxX = 1;
	this->maxY = 1;
	this->textureUV.minX = 0;
	this->textureUV.minY = 0;
	this->textureUV.maxX = 0;
	this->textureUV.maxY = 0;
	this->minX = 0;
	this->minY = 0;
	this->minZ = 0;
	this->maxZ = 1;
	this->field_3C = 1;
	this->material = mat;
	this->aabb.maxX = 1;
	this->aabb.maxY = 1;
	this->aabb.maxZ = 1;
	this->soundType = &Tile::SOUND_NORMAL;
	this->slipperiness = 0.6;
	this->aabb.minX = 0;
	this->field_50 = -1;
	this->aabb.minY = 0;
	this->field_5C = 0;
	this->aabb.minZ = 0;
	this->replaceable = 0;
	this->descriptionId = "";
	TextureUVCoordinateSet v10 = this->getTextureUVCoordinateSet(s, 0);
	this->textureUV = v10;
}

bool_t Tile::containsX(const Vec3& vec) {
	if(vec.y < this->minY) return 0;
	if(vec.y > this->maxY) return 0;
	return vec.z >= this->minZ && vec.z <= this->maxZ;
}
bool_t Tile::containsY(const Vec3& vec) {
	if(vec.x < this->minX) return 0;
	if(vec.x > this->maxX) return 0;
	return vec.z >= this->minZ && vec.z <= this->maxZ;
}
bool_t Tile::containsZ(const Vec3& vec) {
	if(vec.x < this->minX) return 0;
	if(vec.x > this->maxX) return 0;
	return vec.y >= this->minY && vec.y <= this->maxY;
}
int32_t Tile::getIDByName(const std::string& s, bool_t a2) {
	/*if(a2){
		std::string lower = Util::toLower(s);

	}*/
	printf("Tile::getIDByName - not implemented\n");
	return 0;
}
struct TextureAtlasTextureItem* Tile::getTextureItem(const std::string& s) {
	return Tile::_terrainTextureAtlas->getTextureItem(s);
}

TextureUVCoordinateSet Tile::getTextureUVCoordinateSet(const std::string& s, int32_t a4) {
	return *Tile::_terrainTextureAtlas->getTextureItem(s)->getUV(a4);
}
bool_t Tile::isFaceVisible(Level* level, int32_t x, int32_t y, int32_t z, int32_t face) {
	switch(face) {
		case 0:
			--y;
			break;
		case 1:
			++x;
			break;
		case 2:
			--z;
			break;
		case 3:
			++z;
			break;
		case 4:
			--x;
			break;
		case 5:
			++x;
			break;
	}
	return 0; //TODO !level->isSolidRenderTile(x, y, z);
}
void Tile::popResource(Level* level, int32_t x, int32_t y, int32_t z, const struct ItemInstance& a6) {
	float xOffset;	 // s19
	float yOffset;	 // s18
	float zOffset;	 // s16
	ItemEntity* v13; // r5

	if(!level->isClientMaybe) {
		if(level->levelData.getGameType() != 1) {
			xOffset = level->random.nextFloat();
			yOffset = level->random.nextFloat();
			zOffset = level->random.nextFloat();

			v13 = new ItemEntity(level, (float)x + (float)((float)(xOffset * 0.7) + 0.15), (float)y + (float)((float)(yOffset * 0.7) + 0.15), (float)z + (float)((float)(zOffset * 0.7) + 0.15), a6);
			v13->delayBeforePickup = 10;
			level->addEntity(v13);
		}
	}
}
Tile* Tile::setCategory(int32_t a2, int32_t a3) {
	this->field_50 = a3;
	this->field_54 = a2;
	return this;
}
int32_t Tile::transformToValidBlockId(int32_t a1) {
	return Tile::transformToValidBlockId(a1, 0, 0, 0);
}
int32_t Tile::transformToValidBlockId(int32_t oldid, int32_t x, int32_t y, int32_t z) {
	Tile* v4;
	if(oldid) {
		if(!Tile::tiles[oldid]) {
			if((((int8_t)x + (int8_t)y + (int8_t)z) & 1) != 0) {
				v4 = Tile::info_updateGame1;
			} else {
				v4 = Tile::info_updateGame2;
			}
			return v4->blockID;
		}
	}
	return oldid;
}
Tile::~Tile() {
}

int32_t Tile::getTileType() {
	return 0;
}
bool_t Tile::onFertilized(Level*, int32_t, int32_t, int32_t) {
	return 0;
}
bool_t Tile::isCubeShaped() {
	return 1;
}
int32_t Tile::getRenderShape() {
	return 0;
}
Tile* Tile::setShape(float a2, float a3, float a4, float a5, float a6, float a7) {
	this->minZ = a4;
	this->minX = a2;
	this->minY = a3;
	this->maxX = a5;
	this->maxY = a6;
	this->maxZ = a7;
	return this;
}
void Tile::updateShape(LevelSource*, int32_t, int32_t, int32_t) {
}
void Tile::updateDefaultShape(void) {
}
void Tile::addLights(Level*, int32_t, int32_t, int32_t) {
}
float Tile::getBrightness(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	return level->getBrightness(x, y, z);
}
bool_t Tile::shouldRenderFace(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t face) {
	if((y | x | (uint32_t)z) > 0xff) return 0;
	if(face == 0) {
		if(this->minY > 0) return 1;
	} else if(face == 1) {
		if(this->maxY < 1) return 1;
	} else if(face == 2) {
		if(this->minX > 0) return 1;
	} else if(face == 3) {
		if(this->maxZ < 1) return 1;
	} else if(face == 4) {
		if(this->minX > 0) return 1;
	} else if(face == 5) {
		if(this->maxX < 1) return 1;
	}
	Tile* tile = Tile::tiles[level->getTile(x, y, z)];
	if(tile) {
		if(face != 1 || tile->blockID != Tile::topSnow->blockID) {
			return !tile->isSolidRender();
		}
		return 0;
	}
	return 1;
}
TextureUVCoordinateSet* Tile::getTexture(int32_t) {
	return &this->textureUV;
}
TextureUVCoordinateSet* Tile::getTexture(int32_t a2, int32_t a3) {
	return this->getTexture(a2);
}
TextureUVCoordinateSet* Tile::getTexture(LevelSource* level, int32_t x, int32_t y, int32_t z, int32_t a6) {
	int32_t meta = level->getData(x, y, z);
	return this->getTexture(a6, meta);
}
TextureUVCoordinateSet* Tile::getCarriedTexture(int32_t a2, int32_t a3) {
	return this->getTexture(a2, a3);
}
AABB* Tile::getAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	this->aabb.minX = x + this->minX;
	this->aabb.minY = y + this->minY;
	this->aabb.minZ = z + this->minZ;
	this->aabb.maxX = x + this->maxX;
	this->aabb.maxY = y + this->maxY;
	this->aabb.maxZ = z + this->maxZ;
	return &this->aabb;
}
void Tile::addAABBs(Level* level, int32_t x, int32_t y, int32_t z, const AABB* entBB, std::vector<AABB>& vec) {
	AABB* bb = this->getAABB(level, x, y, z);
	if(bb) {
		if(bb->maxX > entBB->minX && bb->minX < entBB->maxX && bb->maxY > entBB->minY && bb->minY < entBB->maxY && bb->maxZ > entBB->minZ && bb->minZ < entBB->maxZ) {
			vec.emplace_back(*bb);
		}
	}
}
AABB Tile::getTileAABB(Level* level, int32_t x, int32_t y, int32_t z) {
	AABB ret;
	ret.minX = x + this->minX;
	ret.minY = y + this->minY;
	ret.minZ = z + this->minZ;
	ret.maxX = x + this->maxX;
	ret.maxY = y + this->maxY;
	ret.maxZ = z + this->maxZ;

	return ret;
}
bool_t Tile::isSolidRender() {
	return 1;
}
bool_t Tile::isPathfindable(LevelSource* level, int32_t x, int32_t y, int32_t z) {
	return !this->material->blocksMotion();
}
bool_t Tile::isUnbreakable() {
	return this->blockHardness < 0;
}
bool_t Tile::isLiquidTile() {
	return 0;
}
int32_t Tile::getTileEntityType(void) {
	return 0;
}
bool_t Tile::mayPick() {
	return 1;
}
bool_t Tile::mayPick(int32_t, bool_t) {
	return this->mayPick();
}
bool_t Tile::mayPlace(Level* level, int32_t x, int32_t y, int32_t z, uint8_t a6) {
	return this->mayPlace(level, x, y, z);
}
bool_t Tile::mayPlace(Level* level, int32_t x, int32_t y, int32_t z) {
	int32_t id = level->getTile(x, y, z);
	if(id == 0) return 1;
	const Material* mat = Tile::tiles[id]->material;
	return mat->isReplaceable();
}
int32_t Tile::getTickDelay() {
	return 10;
}
void Tile::tick(Level* level, int32_t x, int32_t y, int32_t z, Random* rng) {
}
void Tile::animateTick(Level*, int32_t, int32_t, int32_t, Random*) {
}
void Tile::destroy(Level*, int32_t, int32_t, int32_t, int32_t) {
}
void Tile::playerWillDestroy(Level*, int32_t, int32_t, int32_t, int32_t, Player*) {
}
void Tile::neighborChanged(Level* level, int32_t x, int32_t y, int32_t z, int32_t nx, int32_t ny, int32_t nz, int32_t nid) {
	TileEntity* te = level->getTileEntity(x, y, z);
	if(te) {
		te->onNeighborChanged(nx, ny, nz);
	}
}
void Tile::onPlace(Level*, int32_t, int32_t, int32_t) {
}
void Tile::onRemove(Level*, int32_t, int32_t, int32_t) {
}
void Tile::onGraphicsModeChanged(bool_t a2) {
	this->goodGraphics = a2;
}
int32_t Tile::getResource(int32_t, Random*) {
	return this->blockID;
}
int32_t Tile::getResourceCount(Random*) {
	return 1;
}
float Tile::getDestroyProgress(Player* player) {
	float v4, v5;
	if(this->blockHardness < 0) return 0;
	if(player->canDestroy(this)) {
		v4 = player->getDestroySpeed(this) / this->blockHardness;
		v5 = 30;
	} else {
		v4 = 1.0 / this->blockHardness;
		v5 = 100;
	}
	return v4 / v5;
}
void Tile::spawnResources(Level* level, int32_t x, int32_t y, int32_t z, int32_t meta) {
	return this->spawnResources(level, x, y, z, meta, 1.0);
}
void Tile::spawnResources(Level* a2, int32_t a3, int32_t a4, int32_t a5, int32_t a6, float a7) {
	int i;			  // r7
	Random* p_random; // r4
	int v13;		  // r11
	int v14;		  // r10
	float f;		  // s21
	float f1;		  // s20
	float f2;		  // s19
	int v18;		  // r0
	ItemEntity* v19;  // r10

	i = 0;
	if(!a2->isClientMaybe) {
		p_random = &a2->random;
		v13 = this->getResourceCount(&a2->random);
		while(i < v13) {
			if(p_random->nextFloat() <= a7) {
				v14 = this->getResource(a6, p_random);
				if(v14 > 0) {
					f = p_random->nextFloat();
					f1 = p_random->nextFloat();
					f2 = p_random->nextFloat();
					v18 = this->getSpawnResourcesAuxValue(a6);
					v19 = new ItemEntity(a2, (float)a3 + (float)((float)(f * 0.7) + 0.15), (float)a4 + (float)((float)(f1 * 0.7) + 0.15), (float)a5 + (float)((float)(f2 * 0.7) + 0.15), ItemInstance(v14, 1, v18));
					v19->delayBeforePickup = 10;
					a2->addEntity(v19);
				}
			}
			++i;
		}
	}
}
bool_t Tile::spawnBurnResources(Level*, float, float, float) {
	return 0;
}
float Tile::getExplosionResistance(Entity* e) {
	return this->blockResistance / 5.0;
}
HitResult Tile::clip(Level* level, int32_t x, int32_t y, int32_t z, const Vec3& a7, const Vec3& a8) {
	bool_t v9;	// r5
	bool_t v10; // s19
	Vec3* v11;	// r4
	bool_t v12; // s19
	bool_t v13; // s19
	bool_t v14; // s19
	bool_t v15; // s19
	int v16;	// r5
	bool_t v17; // [sp+Ch] [bp-70h]
	bool_t v18; // [sp+10h] [bp-6Ch]
	bool_t v19; // [sp+14h] [bp-68h]
	bool_t v20; // [sp+18h] [bp-64h]
	bool_t v21; // [sp+1Ch] [bp-60h]

	this->updateShape(level, x, y, z);
	Vec3 v24((float)x, (float)y, (float)z);
	Vec3 v25(a7.x - v24.x, a7.y - v24.y, a7.z - v24.z);
	Vec3 v26(a8.x - v24.x, a8.y - v24.y, a8.z - v24.z);
	Vec3 v27; // [sp+4Ch] [bp-30h] BYREF
	Vec3 v28; // [sp+58h] [bp-24h] BYREF
	Vec3 v29; // [sp+64h] [bp-18h] BYREF
	Vec3 v30; // [sp+70h] [bp-Ch] BYREF
	Vec3 v31; // [sp+7Ch] [bp+0h] BYREF
	Vec3 v32; // [sp+88h] [bp+Ch] BYREF
	v21 = v25.clipX(v26, this->minX, v27);
	v20 = v25.clipX(v26, this->maxX, v28);
	v19 = v25.clipY(v26, this->minY, v29);
	v17 = v25.clipY(v26, this->maxY, v30);
	v9 = v25.clipZ(v26, this->minZ, v31);
	v18 = v25.clipZ(v26, this->maxZ, v32);
	if(!v21 || !this->containsX(v27)) {
		v21 = 0;
	}
	if(!v20 || !this->containsX(v28)) {
		v20 = 0;
	}
	if(!v19 || !this->containsY(v29)) {
		v19 = 0;
	}
	if(!v17 || !this->containsY(v30)) {
		v17 = 0;
	}
	if(!v9 || !this->containsZ(v31)) {
		v9 = 0;
	}
	if(!v18 || !this->containsZ(v32)) {
		v18 = 0;
	}
	if(v21) {
		if(!v20 || (v10 = v25.distanceToSqr(v28), v10 >= v25.distanceToSqr(v27))) {
			v11 = &v27;
			if(!v19) {
LABEL_81:
				if(!v17) {
					if(!v9) {
						goto LABEL_63;
					}
					if(!v11) {
						goto LABEL_65;
					}
					goto LABEL_26;
				}
LABEL_21:
				v13 = v25.distanceToSqr(v30);
				if(v13 >= v25.distanceToSqr(*v11)) {
					goto LABEL_83;
				}
LABEL_61:
				if(!v9) {
					v11 = &v30;
					if(!v18) {
						goto LABEL_30;
					}
					goto LABEL_29;
				}
				v11 = &v30;
				goto LABEL_26;
			}
			goto LABEL_18;
		}
	} else if(!v20) {
		if(!v19) {
			if(!v17) {
				if(!v9) {
					v11 = 0;
					goto LABEL_63;
				}
				goto LABEL_65;
			}
			goto LABEL_61;
		}
		goto LABEL_57;
	}
	if(!v19) {
		v11 = &v28;
		if(!v17) {
LABEL_83:
			if(!v9) {
LABEL_63:
				if(!v18) {
					goto LABEL_67;
				}
				if(!v11) {
LABEL_34:
					v11 = &v32;
LABEL_35:
					if(v11 == &v30) {
						v16 = 1;
						goto LABEL_45;
					}
					if(v11 == &v31) {
						v16 = 2;
						goto LABEL_45;
					}
					v16 = -1;
LABEL_39:
					if(v11 == &v32) {
						v16 = 3;
					}
					goto LABEL_45;
				}
LABEL_29:
				v15 = v25.distanceToSqr(v32);
				if(v15 >= v25.distanceToSqr(*v11)) {
LABEL_30:
					if(v11 == &v27) {
						v16 = 4;
						goto LABEL_39;
					}
					if(v11 == &v28) {
						v16 = 5;
						goto LABEL_45;
					}
					goto LABEL_32;
				}
				goto LABEL_34;
			}
LABEL_26:
			v14 = v25.distanceToSqr(v31);
			if(v14 >= v25.distanceToSqr(*v11)) {
				goto LABEL_85;
			}
LABEL_65:
			v11 = &v31;
			if(!v18) {
LABEL_32:
				if(v11 == &v29) {
					v16 = 0;
LABEL_45:
					Vec3 v33((float)x + v11->x, (float)y + v11->y, (float)z + v11->z);
					return HitResult(x, y, z, v16, v33);
				}
				goto LABEL_35;
			}
			goto LABEL_29;
		}
		goto LABEL_21;
	}
	v11 = &v28;
LABEL_18:
	v12 = v25.distanceToSqr(v29);
	if(v12 >= v25.distanceToSqr(*v11)) {
		goto LABEL_81;
	}
LABEL_57:
	if(v17) {
		v11 = &v29;
		goto LABEL_21;
	}
	v11 = &v29;
	if(v9) {
		goto LABEL_26;
	}
LABEL_85:
	if(v18) {
		goto LABEL_29;
	}
LABEL_67:
	if(v11) {
		goto LABEL_30;
	}
	return HitResult();
}

void Tile::wasExploded(Level*, int32_t, int32_t, int32_t) {
}
int32_t Tile::getRenderLayer() {
	return 0;
}
bool_t Tile::use(Level*, int32_t, int32_t, int32_t, Player*) {
	return 0;
}
void Tile::stepOn(Level*, int32_t, int32_t, int32_t, Entity*) {
}
void Tile::fallOn(Level*, int32_t, int32_t, int32_t, Entity*, float) {
}
int32_t Tile::getPlacementDataValue(Level* level, int32_t x, int32_t y, int32_t z, int32_t a6, float a7, float a8, float a9, struct Mob* a10, int32_t a11) {
	return a11;
}
void Tile::prepareRender(Level*, int32_t, int32_t, int32_t) {
}
void Tile::attack(Level*, int32_t, int32_t, int32_t, Player*) {
}
void Tile::handleEntityInside(Level*, int32_t, int32_t, int32_t, Entity*, Vec3&) {
}
int32_t Tile::getColor(int32_t) {
	return 0xffffffff;
}
int32_t Tile::getColor(LevelSource*, int32_t, int32_t, int32_t) {
	return 0xffffff;
}
float Tile::getThickness() {
	return 0;
}
bool_t Tile::isSignalSource() {
	return 0;
}
int32_t Tile::getSignal(LevelSource*, int32_t, int32_t, int32_t) {
	return 0;
}
int32_t Tile::getSignal(LevelSource*, int32_t, int32_t, int32_t, int32_t) {
	return 0;
}
int32_t Tile::getDirectSignal(Level*, int32_t, int32_t, int32_t, int32_t) {
	return 0;
}
void Tile::entityInside(Level*, int32_t, int32_t, int32_t, Entity*) {
}
void Tile::playerDestroy(Level* level, Player* player, int32_t x, int32_t y, int32_t z, int32_t a7) {
	return this->spawnResources(level, x, y, z, a7);
}
bool_t Tile::canSurvive(Level*, int32_t, int32_t, int32_t) {
	return 1;
}
std::string Tile::getName() {
	return I18n::get(this->getDescriptionId() + ".name");
}
std::string Tile::getDescriptionId(void) {
	return this->descriptionId;
}
std::string Tile::getDescriptionId(const struct ItemInstance*) {
	return this->getDescriptionId();
}
std::string Tile::getTypeDescriptionId(int32_t) {
	return "";
}
Tile* Tile::setDescriptionId(const std::string& a2) {
	std::string v6 = Tile::TILE_DESCRIPTION_PREFIX;
	v6 += a2;
	this->descriptionId = v6;
	return this;
}
void Tile::triggerEvent(Level*, int32_t, int32_t, int32_t, int32_t, int32_t) {
}
TextureUVCoordinateSet* Tile::getTextureNum(int32_t) {
	return &this->textureUV;
}
Tile* Tile::setSoundType(const Tile::SoundType& st) {
	this->soundType = &st;
	return this;
}
Tile* Tile::setLightBlock(int32_t a2) {
	Tile::lightBlock[this->blockID] = a2;
	return this;
}
Tile* Tile::setLightEmission(float a2) {
	Tile::lightEmission[this->blockID] = (a2 * 15);
	return this;
}
Tile* Tile::setExplodeable(float a2) {
	this->blockResistance = a2 * 3;
	return this;
}
Tile* Tile::setDestroyTime(float a2) {
	this->blockHardness = a2;
	if(this->blockResistance < (a2 * 5)) {
		this->blockResistance = a2 * 5;
	}
	return this;
}
void Tile::setTicking(bool_t a2) {
	Tile::shouldTick[this->blockID] = a2;
}
int32_t Tile::getSpawnResourcesAuxValue(int32_t) {
	return 0;
}
Tile* Tile::init() {
	int32_t v4;
	Tile::tiles[this->blockID] = this;
	this->setShape(this->minX, this->minY, this->minZ, this->maxX, this->maxY, this->maxZ);
	Tile::solid[this->blockID] = this->isSolidRender();
	if(this->isSolidRender()) v4 = 255;
	else v4 = 0;
	Tile::lightBlock[this->blockID] = v4;
	Tile::translucent[this->blockID] = this->material->blocksLight();
	return this;
}
