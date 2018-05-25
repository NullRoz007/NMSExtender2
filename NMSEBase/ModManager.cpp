#include "stdafx.h"
#include <string>
#include <iostream>
#include <filesystem>
#include <sstream>
#include "ModManager.h"
#include <windows.h>
#include "INIReader.h"

using namespace std::experimental::filesystem;
typedef void (__stdcall *ModuleStart) (void);

string GetRuntimePath(void) {
	char buf[MAX_PATH];
	GetModuleFileNameA(NULL, buf, MAX_PATH);
	return string(buf).substr(0, string(buf).find_last_of("\\/"));
}

std::vector<std::string> ReadDirectory(const string &dirPath, const vector<string> dirSkipList = {})
{
	vector<string> listOfFiles;
	recursive_directory_iterator iter(dirPath);
	recursive_directory_iterator end;

	while (iter != end) {
		if (is_directory(iter->path()) && (find(dirSkipList.begin(), dirSkipList.end(), iter->path().filename()) != dirSkipList.end())) {
			iter.disable_recursion_pending();
		}
		else {
			listOfFiles.push_back(iter->path().string());
		}

		error_code ec;
		iter.increment(ec);
		if (ec) {
			std::cerr << "Error While Accessing file: " << iter->path().string() << " :: " << ec.message() << '\n';
		}
	}
	return listOfFiles;
}

ModManager::ModManager()
{
}


ModManager::~ModManager()
{
}

HINSTANCE ModManager::LoadMod(Mod mod) {
	
	string fullLibPath = GetRuntimePath() + "\\NMSE\\" + mod.modLibrary;
	HINSTANCE dllHandle = LoadLibrary(fullLibPath.c_str());
	if (!dllHandle) return NULL;
	else return dllHandle;
}

void ModManager::RunMod(HINSTANCE modDllHandle) {
	ModuleStart ModuleStartPtr = (ModuleStart)GetProcAddress(modDllHandle, "ModuleStart");
	ModuleStartPtr();
}

vector<Mod> ModManager::GetMods()
{
	vector<Mod> mods;
	string MODS_PATH = GetRuntimePath() + "\\NMSE\\";
	std::cout << "Fetching Mods from " << MODS_PATH << endl;

	if (exists(MODS_PATH) && is_directory(MODS_PATH)) {
		vector<string> files = ReadDirectory(MODS_PATH);
		for (auto str : files) {
			vector<string> string_parts;
			istringstream f(str);
			string s;
			
			while (getline(f, s, '.')) string_parts.push_back(s);
			if (string_parts[1] == "ini" && string_parts.size() == 2) {
				INIReader fileReader(str);
				if (fileReader.ParseError() < 0) {
					cout << "Can't load " << str << endl;
				}


				Mod nmseModule;
				nmseModule.modName = fileReader.Get("ModData", "modName", "UNKNOWN");
				nmseModule.modLibrary = fileReader.Get("ModData", "modLibrary", "UNKNOWN");
				nmseModule.modAuthor = fileReader.Get("ModData", "modAuthor", "UNKNOWN");
				cout << "Loading: "+ nmseModule.modName + " [" + nmseModule.modLibrary + "]";
				mods.push_back(nmseModule);
			}
		}
	}
	return mods;
}
