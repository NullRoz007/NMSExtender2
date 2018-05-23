#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include "INIReader.h"

using namespace std;
struct ModDetails {
	string modName;
	string modAuthor;
	string modLibrary;
};

class ModManager
{
public:
	ModManager();
	~ModManager();

	ModDetails* GetMods(void);
};