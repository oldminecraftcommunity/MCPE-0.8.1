cmake_minimum_required(VERSION 3.16)

if(ANDROID)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
ENDIF()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=protected -fvisibility-inlines-hidden")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=protected -fvisibility-inlines-hidden")

project(minecraftpe08decomp)
set (CMAKE_CXX_STANDARD 11)
SET(USE_ISAAC OFF)
include_directories(glm)
include_directories(OpenAES/inc/)
include_directories(RakNet/Source/)

OPTION(DYNAMICSOUNDS "Build without relying on embedded sound data. Sounds must be provided later in the sounds/ directory (extract them from .so lib using tools/pcm2wav.py)." OFF)

# i love python
OPTION(JSONCPP_WITH_TESTS "Compile and run JsonCpp test executables" ON)
OPTION(JSONCPP_WITH_POST_BUILD_UNITTEST "Automatically run unit-tests as a post build step" ON)
SET(JSONCPP_WITH_TESTS OFF)
SET(JSONCPP_WITH_POST_BUILD_UNITTEST OFF)
include_directories(jsoncpp/jsoncpp/include)
add_subdirectory(jsoncpp/jsoncpp)
include_directories(jsoncpp/jsoncpp/src/lib_json/)

add_subdirectory(RakNet)
add_subdirectory(OpenAES)
add_subdirectory(minecraftpe)
