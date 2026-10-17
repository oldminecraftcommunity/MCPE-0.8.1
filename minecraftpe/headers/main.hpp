#pragma once
#include <_types.h>
#ifndef ANDROID
#include <AppPlatform_sdl.hpp>

#else
#include <android/AppPlatform_android23.hpp>
extern bool contextWasLost;
extern std::string nativeUtf8Input;
#endif
