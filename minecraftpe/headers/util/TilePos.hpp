#pragma once
#include <_types.h>
#include <stdlib.h>

struct TilePos{
	int32_t x, y, z;
	TilePos(TilePos&& p) {
		//this thing is not like TilePos(p.x, p.y, p.z) or x(p.x), ...
		//this should compile into ldr str ldr str ldr str
		//while the other ones compile into ldr ldr ldr str str str
		//*cant believe id have to work with asm to achieve perfect lib recompilation </3*
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
	}
	TilePos(const TilePos& p){
		this->x = p.x;
		this->y = p.y;
		this->z = p.z;
		//cant even move it to TilePos(int,int,int) </3 - the most magical language in the existence
		//top 10 reasons to be like java

	}
	TilePos(int x, int y, int z) : x(x), y(y), z(z){

	}
	TilePos(){}
	bool_t operator<(const TilePos& a2) const {
		return 981131 * this->y + 8976890 * this->x + this->z < (uint32_t) ((981131 * a2.y + 8976890 * a2.x + a2.z));
	}
	//inlined in std::_Hashtable<TilePos,std::pair<TilePos const,TileEntity *>,std::allocator<std::pair<TilePos const,TileEntity *>>,std::_Select1st<std::pair<TilePos const,TileEntity *>>,std::equal_to<TilePos>,std::hash<TilePos>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,true,false,true>::_M_find_before_node(uint,TilePos const&,uint)
	bool_t operator==(const TilePos& a2) const {
		return this->x == a2.x && this->y == a2.y && this->z == a2.z;
	}

	TilePos& operator=(const TilePos& a2){
		this->x = a2.x;
		this->y = a2.y;
		this->z = a2.z;
		return *this;
	}
};

namespace std {
	template<>
	struct hash<TilePos>
	{
		//i hate c++ so much
		size_t operator()(const TilePos& a2) const noexcept {
			return 0xEF88B * a2.y + 0x88F9FA * a2.x + a2.z;
		}
	};
}

