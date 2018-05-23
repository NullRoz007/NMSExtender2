#include "stdafx.h"
#include <string>
#include <iostream>
#include <filesystem>
#include "ModManager.h"

ModManager::ModManager()
{
}


ModManager::~ModManager()
{
}

ModDetails* ModManager::GetMods(void)
{
	string MODS_PATH = "./NMSE/";
	std::cout << "Fetching Mods..." << endl;
	for (auto &p : std::experimental::filesystem::directory_iterator(MODS_PATH)) {
		cout << p << endl;
	}

	return nullptr;
}
