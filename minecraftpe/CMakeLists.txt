cmake_minimum_required(VERSION 3.5)
project(minecraftpe08decomp LANGUAGES CXX)
#evil jsoncpp overring this thing </3
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/build)

find_package(OpenGL REQUIRED)
if(WIN32)
else()
	find_package(OpenAL REQUIRED)
endif()
find_package(SDL REQUIRED)
find_package(ZLIB REQUIRED)
add_compile_options(-fpermissive -Wno-write-strings -Winfinite-recursion -Werror=return-type -g0 -DIMTOOLAZYTOFIX16ERRS -DPCTWEAKS)

file(GLOB_RECURSE IMPLCPP *.cpp)
file(GLOB_RECURSE HEADC *.h)
file(GLOB_RECURSE HEADCPP *.hpp)


add_executable(minecraftpe08decomp ${IMPLCPP} ${HEADC} ${HEADCPP}
	impl/pcm_data.c
	impl/math/Mth.cpp
	impl/util/Random.cpp
	headers/utils.h
	impl/utils.c
	impl/util/Synth.cpp
	impl/util/PerlinNoise.cpp
	impl/util/ImprovedNoise.cpp
	impl/util/Color4.cpp
	headers/AppPlatform.hpp
	headers/level/LevelSource.hpp
	headers/level/biome/Biome.hpp
	headers/level/gen/feature/Feature.hpp
	headers/ImageData.hpp
	headers/_AssetFile.hpp
	impl/_AssetFile.cpp
	impl/network/mco/LoginInformation.cpp
	headers/network/mco/LoginInformation.hpp
	headers/entity/MobCategory.hpp
	headers/tile/material/Material.hpp
	headers/tile/material/DecorationMaterial.hpp
	headers/tile/material/GasMaterial.hpp
	headers/tile/material/LiquidMaterial.hpp
	headers/tile/material/WebMaterial.hpp
	impl/tile/material/Material.cpp
	impl/tile/material/DecorationMaterial.cpp
	impl/tile/material/GasMaterial.cpp
	impl/tile/material/LiquidMaterial.cpp
	impl/tile/material/WebMaterial.cpp
	headers/_PrintStream.hpp
	impl/nbt/Tag.cpp
	impl/AppPlatform.cpp
	impl/level/biome/Biome.cpp
	impl/entity/MobCategory.cpp
	headers/Minecraft.hpp
	headers/IConfigListener.hpp
	impl/IConfigListener.cpp
	headers/Config.hpp
	headers/KeyMapping.hpp
	impl/KeyMapping.cpp


	headers/OptionStrings.hpp
	impl/OptionStrings.cpp
	headers/Options.hpp
	headers/Motive.hpp
	impl/Motive.cpp
	impl/util/Util.cpp
	impl/math/AABB.cpp
	impl/math/Vec3.cpp
	headers/level/biome/FlatBiome.hpp
	headers/level/biome/ForestBiome.hpp
	headers/level/biome/RainforestBiome.hpp
	headers/level/biome/SwampBiome.hpp
	headers/level/biome/TaigaBiome.hpp
	headers/level/gen/feature/BirchFeature.hpp
	headers/level/gen/feature/CactusFeature.hpp
	headers/level/gen/feature/ClayFeature.hpp
	headers/level/gen/feature/FlowerFeature.hpp
	headers/level/gen/feature/LargeCaveFeature.hpp
	headers/level/gen/feature/LargeFeature.hpp
	headers/level/gen/feature/OreFeature.hpp
	headers/level/gen/feature/PineFeature.hpp
	headers/level/gen/feature/ReedsFeature.hpp
	headers/level/gen/feature/SpringFeature.hpp
	headers/level/gen/feature/SpruceFeature.hpp
	headers/level/gen/feature/TallgrassFeature.hpp
	headers/level/gen/feature/TreeFeature.hpp
	impl/nbt/EndTag.cpp
	impl/nbt/NbtIo.cpp
	impl/nbt/ByteTag.cpp
	impl/nbt/ShortTag.cpp
	impl/nbt/ByteArrayTag.cpp
	impl/nbt/IntTag.cpp
	impl/nbt/LongTag.cpp
	impl/nbt/FloatTag.cpp
	impl/nbt/DoubleTag.cpp
	impl/nbt/StringTag.cpp
	impl/nbt/ListTag.cpp
	impl/nbt/CompoundTag.cpp
	headers/App.hpp
	headers/AppContext.hpp
	impl/App.cpp
	impl/AppPlatform_sdl.cpp
	headers/AppPlatform_sdl.hpp
	headers/NinecraftApp.hpp
	headers/rendering/TextureAtlas.hpp
	headers/rendering/TextureAtlasTextureItem.hpp
	headers/rendering/Tesselator.hpp
	headers/rendering/MeshBuffer.hpp
	impl/cpputils.cpp
	impl/unigl.c
)

target_include_directories(minecraftpe08decomp PUBLIC "headers/")
target_link_libraries(minecraftpe08decomp)
if(WIN32)
	target_compile_definitions(minecraftpe08decomp PRIVATE AL_LIBTYPE_STATIC)
	target_link_libraries(minecraftpe08decomp pthread)
endif()
target_link_libraries(minecraftpe08decomp ${OPENAL_LIBRARY} ZLIB::ZLIB ${OPENGL_LIBRARIES} ${SDL_LIBRARIES} RakNetLibStatic jsoncpp_lib utf8proc)
