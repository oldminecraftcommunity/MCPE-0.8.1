#include <crafting/Recipes.hpp>
#include <crafting/FurnaceRecipes.hpp>
#include <crafting/ShapelessRecipe.hpp>
#include <crafting/ShapedRecipe.hpp>
#include <crafting/ToolRecipes.hpp>
#include <crafting/WeaponRecipes.hpp>
#include <crafting/OreRecipes.hpp>
#include <crafting/FoodRecipes.hpp>
#include <crafting/StructureRecipes.hpp>
#include <crafting/ArmorRecipes.hpp>
#include <crafting/ClothDyeRecipes.hpp>
#include <item/Item.hpp>
#include <tile/Tile.hpp>

Recipes::Shape::Shape(const std::string& a2) {
	this->shape.push_back(a2);
}
Recipes::Shape::Shape(const std::string& a2, const std::string& a3) {
	this->shape.push_back(a2);
	this->shape.push_back(a3);
}
Recipes::Shape::Shape(const std::string& a2, const std::string& a3, const std::string& a4) {
	this->shape.push_back(a2);
	this->shape.push_back(a3);
	this->shape.push_back(a4);
}

Recipes::Type::Type(const Recipes::Type& a2)
	: itemInstance(a2.itemInstance) {
	this->item = a2.item;
	this->tile = a2.tile;
	this->chr = a2.chr;
}
Recipes::Type::Type(char_t a2, Item* a3) {
	this->item = a3;
	this->tile = 0;
	this->chr = a2;
}
Recipes::Type::Type(char_t a2, const ItemInstance& a3)
	: itemInstance(a3) {
	this->item = 0;
	this->tile = 0;
	this->chr = a2;
}
Recipes::Type::Type(char_t a2, Tile* a3) {
	this->tile = a3;
	this->item = 0;
	this->chr = a2;
}

Recipes* Recipes::instance = 0;

Recipes::Recipes() {
	ToolRecipes::addRecipes(this);
	WeaponRecipes::addRecipes(this);
	OreRecipes::addRecipes(this);
	FoodRecipes::addRecipes(this);
	StructureRecipes::addRecipes(this);
	ArmorRecipes::addRecipes(this);
	ClothDyeRecipes::addRecipes(this);

	this->addShapedRecipe(ItemInstance(Item::paper, 3), "###", definition<Item*>('#', Item::reeds));
	this->addShapedRecipe(ItemInstance(Item::book, 1), "#", "#", "#", definition<Item*>('#', Item::paper));
	this->addShapedRecipe(ItemInstance(Tile::fence, 2), "###", "###", definition<Item*>('#', Item::stick));
	this->addShapedRecipe(ItemInstance(Tile::cobbleWall, 6, 0), "###", "###", definition<Tile*>('#', Tile::stoneBrick));
	this->addShapedRecipe(ItemInstance(Tile::fenceGate, 1), "#W#", "#W#", definition<Item*, Tile*>('#', Item::stick, 'W', Tile::wood));
	this->addShapedRecipe(ItemInstance(Tile::bookshelf, 1), "###", "XXX", "###", definition<Tile*, Item*>('#', Tile::wood, 'X', Item::book) /*inlined*/);
	this->addShapedRecipe(ItemInstance(Tile::snow, 1), "##", "##", definition<Item*>('#', Item::snowBall));
	this->addShapedRecipe(ItemInstance(Tile::clay, 1), "##", "##", definition<Item*>('#', Item::clay));
	this->addShapedRecipe(ItemInstance(Tile::redBrick, 1), "##", "##", definition<Item*>('#', (Item*)Item::brick));
	this->addShapedRecipe(ItemInstance(Tile::lightGem, 1), "##", "##", definition<Item*>('#', Item::yellowDust));
	this->addShapedRecipe(ItemInstance(Tile::cloth, 1), "##", "##", definition<Item*>('#', Item::string));
	this->addShapedRecipe(ItemInstance(Tile::tnt, 1), "X#X", "#X#", "X#X", definition<Item*, Tile*>('X', Item::sulphur, '#', Tile::sand));
	this->addShapedRecipe(ItemInstance(Tile::stoneSlabHalf, 6, 3), "###", definition<Tile*>('#', Tile::stoneBrick));
	this->addShapedRecipe(ItemInstance(Tile::stoneSlabHalf, 6, 0), "###", definition<Tile*>('#', Tile::rock));
	this->addShapedRecipe(ItemInstance(Tile::stoneSlabHalf, 6, 1), "###", definition<Tile*>('#', Tile::sandStone));


	for(int32_t a3 = 0; a3 != 4; ++a3) {
		if(a3 != 3) {
			this->addShapedRecipe(ItemInstance(Tile::woodSlabHalf, 6, a3), "###", definition<ItemInstance>('#', ItemInstance(Tile::wood, 1, a3)));
		}
	}

	this->addShapedRecipe(ItemInstance(Tile::stoneSlabHalf, 6, 4), "###", definition<Tile*>('#', Tile::redBrick));
	this->addShapedRecipe(ItemInstance(Tile::stoneSlabHalf, 6, 5), "###", definition<Tile*>('#', Tile::stoneBrickSmooth));
	this->addShapedRecipe(ItemInstance(Tile::stoneSlabHalf, 6, 6), "###", definition<Tile*>('#', Tile::quartzBlock));
	this->addShapedRecipe(ItemInstance(Tile::ladder, 2), "# #", "###", "# #", definition<Item*>('#', Item::stick));
	this->addShapedRecipe(ItemInstance(Item::door_wood, 1), "##", "##", "##", definition<Tile*>('#', Tile::wood));
	this->addShapedRecipe(ItemInstance(Tile::trapdoor, 2), "###", "###", definition<Tile*>('#', Tile::wood));
	this->addShapedRecipe(ItemInstance(Item::sign, 1), "###", "###", " X ", definition<Tile*, Item*>('#', Tile::wood, 'X', Item::stick) /*inlined*/);
	std::vector<ItemInstance> cakestuff = {ItemInstance(Item::cake, 1), ItemInstance(Item::bucket, 3)};
	this->addShapedRecipe(cakestuff, Recipes::Shape("AAA", "BEB", "CCC").shape, definition<ItemInstance, Item*, Item*, Item*>('A', ItemInstance(Item::bucket, 1, 1), 'B', Item::sugar, 'C', Item::wheat, 'E', Item::egg));
	this->addShapedRecipe(ItemInstance(Item::sugar, 1), "#", definition<Item*>('#', Item::reeds));
	this->addShapedRecipe(ItemInstance(Tile::wood, 4, 0), "#", definition<ItemInstance>('#', ItemInstance(Tile::treeTrunk, 1, 0)));
	this->addShapedRecipe(ItemInstance(Tile::wood, 4, 1), "#", definition<ItemInstance>('#', ItemInstance(Tile::treeTrunk, 1, 1)));
	this->addShapedRecipe(ItemInstance(Tile::wood, 4, 2), "#", definition<ItemInstance>('#', ItemInstance(Tile::treeTrunk, 1, 2)));
	this->addShapedRecipe(ItemInstance(Item::stick, 4), "#", "#", definition<Tile*>('#', Tile::wood));
	this->addShapedRecipe(ItemInstance(Tile::torch, 4), "X", "#", definition<Item*, Item*>('X', Item::coal, '#', Item::stick));
	this->addShapedRecipe(ItemInstance(Tile::torch, 4), "X", "#", definition<ItemInstance, Item*>('X', ItemInstance(Item::coal, 1, 1), '#', Item::stick));
	this->addShapedRecipe(ItemInstance(Item::bowl, 4), "# #", " # ", definition<Tile*>('#', Tile::wood));
	this->addShapedRecipe(ItemInstance(Tile::rail, 16), "X X", "X#X", "X X", definition<Item*, Item*>('X', Item::ironIngot, '#', Item::stick));
	this->addShapedRecipe(ItemInstance(Tile::goldenRail, 6), "X X", "X#X", "XRX", definition<Item*, Item*, Item*>('X', Item::goldIngot, 'R', Item::redStone, '#', Item::stick));
	this->addShapedRecipe(ItemInstance(Item::minecart, 1), "# #", "###", definition<Item*>('#', Item::ironIngot));
	this->addShapedRecipe(ItemInstance(Tile::litPumpkin, 1), "A", "B", definition<Tile*, Tile*>('A', Tile::pumpkin, 'B', Tile::torch));
	this->addShapedRecipe(ItemInstance(Item::bucket, 1, 0), "# #", " # ", definition<Item*>('#', Item::ironIngot));
	this->addShapedRecipe(ItemInstance(Item::flintAndSteel, 1), "A ", " B", definition<Item*, Item*>('A', Item::ironIngot, 'B', Item::flint));
	this->addShapedRecipe(ItemInstance(Item::bread, 1), "###", definition<Item*>('#', Item::wheat));
	this->addShapedRecipe(ItemInstance(Tile::stairs_wood, 4, 0), "#  ", "## ", "###", definition<ItemInstance>('#', ItemInstance(Tile::wood, 1, 0)));
	this->addShapedRecipe(ItemInstance(Tile::woodStairsDark, 4), "#  ", "## ", "###", definition<ItemInstance>('#', ItemInstance(Tile::wood, 1, 1)));
	this->addShapedRecipe(ItemInstance(Tile::woodStairsBirch, 4), "#  ", "## ", "###", definition<ItemInstance>('#', ItemInstance(Tile::wood, 1, 2)));
	this->addShapedRecipe(ItemInstance(Tile::stairs_stone, 4), "#  ", "## ", "###", definition<Tile*>('#', Tile::stoneBrick));
	this->addShapedRecipe(ItemInstance(Tile::stairs_brick, 4), "#  ", "## ", "###", definition<Tile*>('#', (Tile*)Tile::redBrick));
	this->addShapedRecipe(ItemInstance(Tile::stairs_sandStone, 4), "#  ", "## ", "###", definition<Tile*>('#', Tile::sandStone));
	this->addShapedRecipe(ItemInstance(Tile::stairs_stoneBrickSmooth, 4), "#  ", "## ", "###", definition<Tile*>('#', Tile::stoneBrickSmooth));
	this->addShapedRecipe(ItemInstance(Tile::stairs_netherBricks, 4), "#  ", "## ", "###", definition<Tile*>('#', (Tile*)Tile::netherBrick));
	this->addShapedRecipe(ItemInstance(Item::painting, 1), "###", "#X#", "###", definition<Item*, Tile*>('#', Item::stick, 'X', Tile::cloth));
	this->addShapedRecipe(ItemInstance(Item::clock, 1), " # ", "#X#", " # ", definition<Item*, Item*>('#', Item::goldIngot, 'X', Item::redStone));
	this->addShapedRecipe(ItemInstance(Item::compass, 1), " # ", "#X#", " # ", definition<Item*, Item*>('#', Item::ironIngot, 88, Item::redStone));
	this->addShapedRecipe(ItemInstance(Item::bed, 1), "###", "XXX", definition<Tile*, Tile*>('#', Tile::cloth, 'X', Tile::wood));
	this->addShapedRecipe(ItemInstance(Tile::ironFence, 16), "###", "###", definition<Item *>('#', Item::ironIngot));
	this->addShapedRecipe(ItemInstance(Tile::netherReactor, 1), "X#X", "X#X", "X#X", definition<Item *,Item *>('#', Item::emerald, 'X', Item::ironIngot));
	this->addShapedRecipe(ItemInstance(Tile::woolCarpet, 3, 14), "##", definition<ItemInstance>('#', ItemInstance(Tile::cloth, 1, 14)));
}
void Recipes::addShapedRecipe(const ItemInstance& a2, const std::string& a3, const std::string& a4, const std::string& a5, const std::vector<Recipes::Type>& a6) {
	Recipes::Shape v8(a3, a4, a5);
	this->addShapedRecipe(a2, v8.shape, a6);
}
void Recipes::addShapedRecipe(const ItemInstance& a2, const std::string& a3, const std::string& a4, const std::vector<Recipes::Type>& a5) {
	Recipes::Shape v7(a3, a4);
	this->addShapedRecipe(a2, v7.shape, a5);
}
void Recipes::addShapedRecipe(const ItemInstance& a2, const std::string& a3, const std::vector<Recipes::Type>& a4) {
	Recipes::Shape v7(a3);
	this->addShapedRecipe(a2, v7.shape, a4);
}
void Recipes::addShapedRecipe(const ItemInstance& a2, const std::vector<std::string> a3, const std::vector<Recipes::Type>& a4) { //TODO last arg type might be slightly different
	std::vector<ItemInstance> v7;
	v7.emplace_back(ItemInstance(a2));
	this->addShapedRecipe(v7, a3, a4); //TODO check
}
void Recipes::addShapedRecipe(const std::vector<ItemInstance>& results, const std::vector<std::string, std::allocator<std::string>> shape, const std::vector<Recipes::Type>& ingridients) { //TODO check signature
	if(shape.begin() != shape.end()) {
		std::string v39 = "";
		int32_t v8 = shape.size();
		int32_t v9 = shape[0].length();
		for(int32_t v7 = 0; v7 < shape.size(); ++v7) {
			v39 += shape[v7];
		}

		int32_t v10 = 0;
		std::map<char_t, ItemInstance> v43;
		while(1) {
			if(v10 >= ingridients.size()) {
				int32_t v20 = v8 * v9;
				ItemInstance* v22 = new ItemInstance[v20];

				for(int32_t i = 0; i < v20; ++i) {
					auto&& p = v43.find(v39[i]);
					if(p != v43.end()) { //TODO
						v22[i] = p->second;
					}
				}
				ShapedRecipe* v29 = new ShapedRecipe(v9, v8, v22, results);
				this->recipes.emplace_back(v29);
				return;
			}
			const Recipes::Type* v11 = &ingridients[v10];
			if(v11->item) {
				v43.insert({v11->chr, ItemInstance(v11->item)});
			} else if(v11->tile) {
				v43.insert({v11->chr, ItemInstance(v11->tile, 1, -1)});
			} else if(!v11->itemInstance.isNull()) {
				v43.insert({v11->chr, ItemInstance(v11->itemInstance)});
			}
			++v10;
		}
	}
}
void Recipes::addShapelessRecipe(const ItemInstance& a2, const std::vector<Recipes::Type>& a3) {
	std::vector<ItemInstance> v14;
	for(int32_t v3 = 0; v3 < a3.size(); ++v3) {
		const Recipes::Type* v7 = &a3[v3];
		if(v7->item) {
			v14.emplace_back(ItemInstance(v7->item));
		} else if(v7->tile) {
			v14.emplace_back(ItemInstance(v7->tile));
		} else if(!v7->itemInstance.isNull()) {
			v14.push_back(v7->itemInstance);
		}
	}
	std::vector<ItemInstance> a1;
	a1.push_back(a2);
	this->recipes.emplace_back(new ShapelessRecipe(a1, v14));
}
Recipes* Recipes::getInstance() {
	if(!Recipes::instance) {
		Recipes::instance = new Recipes();
	}
	return Recipes::instance;
}
Recipe* Recipes::getRecipeFor(const ItemInstance& a2) {
	for(uint32_t i = 0; i < this->recipes.size(); ++i) {
		Recipe* v5 = this->recipes[i];
		ItemInstance v10(v5->getResultItem()->at(0));
		if ( !a2.sameItem(&v10) )
		{
			if (a2.count == 0 )
			{
				if ( a2.getAuxValue() == v10.getAuxValue() )
				{
					return v5;
				}
			}
			if ( a2.count == v10.count )
			{
				if ( a2.getAuxValue() == v10.getAuxValue() )
				{
					return v5;
				}
			}
		}
	}
	return 0;
}
std::vector<Recipe*>* Recipes::getRecipes() { //TODO prob different type
	return &this->recipes;
}
void Recipes::teardownRecipes() {
	if(Recipes::instance) {
		delete Recipes::instance;
		Recipes::instance = 0;
	}
	FurnaceRecipes::teardownFurnaceRecipes();
}

Recipes::~Recipes() {
	for(int32_t i = 0; i < this->recipes.size(); ++i) {
		if(this->recipes[i]) {
			delete this->recipes[i];
		}
	}
}
