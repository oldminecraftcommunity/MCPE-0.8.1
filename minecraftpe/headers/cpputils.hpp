#pragma once
#include <_types.h>
#include <Config.hpp>
#include <vector>
#include <string>
#include <memory>

struct RestRequestJob;
struct Minecraft;

template <typename T> void safeRemove(T*& p){
	if(p){
		delete p;
		p = 0;
	}
}

template <typename T> void safeStopAndRemove(T&);


void splitString(const std::string&, char_t, std::vector<std::string>&);
bool_t exists(const char_t* a1);
int recursiveDelete(const char_t*);
bool_t DeleteDirectory(const std::string& a1, bool_t);
int _errno();
int mkdir(const char*);
bool createFolderIfNotExists(const char*);
bool createTree(const char*, const char**, int);
