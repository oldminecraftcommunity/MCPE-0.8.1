#include <tile/entity/TileEntityFactory.hpp>
#include <tile/entity/FurnaceTileEntity.hpp>
#include <tile/entity/ChestTileEntity.hpp>
#include <tile/entity/NetherReactorTileEntity.hpp>
#include <tile/entity/SignTileEntity.hpp>

TileEntity* TileEntityFactory::createTileEntity(int32_t type) {
	switch(type) {
		case 1:
			return new FurnaceTileEntity();
		case 2:
			return new ChestTileEntity();
		case 3:
			return new NetherReactorTileEntity();
		case 4:
			return new SignTileEntity();
		default:
			return 0;
	}
}
