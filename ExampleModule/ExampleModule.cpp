#include "stdafx.h"
#include "../NMSEBase/NMSEApi.h";
#include <iostream>
#include <windows.h>

HANDLE monitor;
using namespace std;
int ProcThread() {
	bool flag = true;
	POINT p;
	while (flag) {
		if (GetCursorPos(&p)) {
			cout << p.x << ", ";
			cout << p.y << endl << endl;
		}
		Sleep(175);
	}
	return 0;
}

extern "C" {
	void __declspec(dllexport) __stdcall ModuleStart() {
		monitor = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ProcThread, NULL, NULL, NULL);
	}
}

