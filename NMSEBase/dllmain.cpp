#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "ModManager.h";

std::string RunTimePath(void) {
	char buf[MAX_PATH];
	GetModuleFileNameA(NULL, buf, MAX_PATH);
	return std::string(buf).substr(0, std::string(buf).find_last_of("\\/"));
}

void PrintLauncherText(void)
{
	std::ifstream infile;
	std::string path = RunTimePath() + "\\NMSE\\LaunchText.txt";
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
		cout << RunTimePath() + "\\NMSE\LaunchText.txt" << endl;
	}
}

void Init() {
	if (AllocConsole()) {
		freopen("CONOUT$", "w", stdout);
		SetConsoleTitle("NMSE Console");
		PrintLauncherText();
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