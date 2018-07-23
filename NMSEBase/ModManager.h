#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <vector>
#include "INIReader.h"

typedef int(__stdcall *ModuleStart_t) (void);
typedef int(__stdcall *hWglSwapBuffers_t) (HDC);

std::string GetRuntimePath(void);
std::vector<std::string> ReadDirectory(const std::string, const std::vector<std::string>);

using namespace std;
struct Mod{
	string modName;
	string modAuthor;
	string modLibrary;
	int hasGLHook;
	hWglSwapBuffers_t glptr;
};

class ModManager
{
public:
	ModManager();
	~ModManager();
	vector<Mod> loadedMods;
	HINSTANCE LoadMod(Mod mod);
	void RunMod(HINSTANCE modDllHandle);
	vector<Mod> GetMods(bool log);
};