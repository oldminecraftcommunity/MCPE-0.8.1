#pragma once
#define UNK
//this should not be used for anything other than testing
#define noinline __attribute__((noinline))

#if defined(PCTWEAKS) && defined(ANDROID)
#error PCTWEAKS and ANDROID are defined at the same time.
#endif
#include <stdint.h>
#include <stdbool.h>

typedef char char_t;
typedef	bool bool_t;
#ifdef DEBUG

#ifdef ANDROID
#include <android/log.h>
inline void _android_debug_thingy(const char* fmt, ...){
	va_list args;
	va_start(args, fmt);
	__android_log_vprint(ANDROID_LOG_DEBUG, "MCPE081DECOMP", fmt, args);
	va_end(args);
}
#define DEBUGMSG _android_debug_thingy
#else
#include <stdio.h>
#define DEBUGMSG printf
#endif

#else
#define DEBUGMSG(...)
#endif
