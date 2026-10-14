#pragma once
#include <_types.h>
#include <stdio.h>

#ifdef __WIN32__
#define FUNC_ERRNO _errno2
#define FUNC_MKDIR _mkdir2
#else
#define FUNC_ERRNO _errno
#define FUNC_MKDIR _mkdir
#endif
int FUNC_MKDIR(const char*);

int FUNC_ERRNO();
bool exists(const char* a1);
bool createFolderIfNotExists(const char*);
int32_t getRemainingFileSize(FILE* file);

bool createTree(const char*, const char**, int);
