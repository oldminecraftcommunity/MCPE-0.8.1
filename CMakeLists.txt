cmake_minimum_required(VERSION 3.1)

project(minecraftpe08decomp)
set (CMAKE_CXX_STANDARD 11)
include_directories(stb)
include_directories(glm)
include_directories(RakNet/Source/)

# i love python
SET(JSONCPP_WITH_TESTS OFF)
SET(JSONCPP_WITH_POST_BUILD_UNITTEST OFF)
include_directories(jsoncpp/jsoncpp/include)
add_subdirectory(jsoncpp/jsoncpp)
include_directories(jsoncpp/jsoncpp/src/lib_json/)

include_directories(utf8proc)

add_subdirectory(RakNet)
add_subdirectory(utf8proc)
add_subdirectory(minecraftpe)
