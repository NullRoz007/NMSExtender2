#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "ModManager.h";
#include "NMSEApi.h";

void PrintLauncherText(void)
{
	std::ifstream infile;
	std::string path = GetRuntimePath() + "\\NMSE\\LaunchText.txt";
	infile.open(path);
	std::string line;
	if (infile.is_open())
	{
		while (getline(infile, line))
		{
			std::cout << line << '\n';
		}
		infile.close();
	}
	else {
		cout << GetRuntimePath() + "\\NMSE\LaunchText.txt" << endl;
	}
}

void Init() {
	if (AllocConsole()) {
		freopen("CONOUT$", "w", stdout);
		SetConsoleTitle("NMSE Console");
		PrintLauncherText();

		//Load Mods
		ModManager modManager = ModManager::ModManager();
		vector<Mod> mods = modManager.GetMods();
		for (auto &mod : mods) {
			HINSTANCE modHandle = modManager.LoadMod(mod);
			if (modHandle == NULL) cout << " [Failed]" << endl;
			else {
				cout << " [Success]" << endl;
				modManager.RunMod(modHandle);
			}
		}
	}
}

extern "C" {
	BOOL WINAPI DllMain(HANDLE hDllHandle, DWORD dwReason, LPVOID lpreserved)
	{
		switch (dwReason)
		{
		case DLL_PROCESS_ATTACH:
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Init, NULL, 0, NULL);
			break;
		case DLL_PROCESS_DETACH:
			break;
		};

		return TRUE;
	}
}