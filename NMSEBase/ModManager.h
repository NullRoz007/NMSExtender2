#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <vector>
#include "INIReader.h"


std::string GetRuntimePath(void);
std::vector<std::string> ReadDirectory(const std::string, const std::vector<std::string>);

using namespace std;
struct Mod{
	string modName;
	string modAuthor;
	string modLibrary;
};

class ModManager
{
public:
	ModManager();
	~ModManager();

	HINSTANCE LoadMod(Mod mod);
	void RunMod(HINSTANCE modDllHandle);
	vector<Mod> GetMods();
};