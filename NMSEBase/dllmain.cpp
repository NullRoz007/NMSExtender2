#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "ModManager.h";
#include "NMSEApi.h";
#include <gl/gl.h> 
#include <GL/glut.h>

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
}

ModManager modManager;
void SetupConsole() {
	bool debug = true;
	//Setup Bebug Console

	if (debug) {
		if (AllocConsole()) {
			
			freopen("conin$", "r", stdin);
			freopen("conout$", "w", stdout);
			freopen("conout$", "w", stderr);
			SetConsoleTitle("NMSE Console");
			PrintLauncherText();

			//Load Mods
			vector<Mod> mods = modManager.GetMods(true);
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
}

void Init() {
	modManager = ModManager::ModManager();
	SetupConsole();
	StartNMSE(modManager);
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