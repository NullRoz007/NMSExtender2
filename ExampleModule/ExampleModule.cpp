#include "stdafx.h"
#include "../NMSEBase/NMSEApi.h";
#include "../NMSEBase/NMSEApi.cpp";
#include "../NMSEBase/ModManager.h";
#include "../NMSEBase/ModManager.cpp";
#include <iostream>
#include <windows.h>
#include <gl/GL.h>
#include <wingdi.h>


HANDLE monitor;
HANDLE hSwap;

using namespace std;
bool endPressed = false;
bool lock = false;
void mWglSwapBuffers(HDC hDC) {
	if (GetKeyState(VK_END) & 0x80) {
		if(endPressed == false && !lock){
			//system("start chrome /new-window https://galacticatlas.nomanssky.com");
			endPressed = true;
			lock = true;
		}
	}
	else {
		if(lock) lock = false;
	}

	if (endPressed) {
		const char* str = "Test";
		SelectObject(hDC, GetStockObject(SYSTEM_FONT));
		wglUseFontBitmaps(hDC, 0, 255, 1000);
		glListBase(1000);
		glRasterPos2f(10.0f, 66.0f);
		glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);
	}
}



int ProcThread() {

	return 0;
}

extern "C" {
	int __declspec(dllexport) __stdcall ModuleStart() {
		monitor = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ProcThread, NULL, NULL, NULL);
		return 1;
	}

	int __declspec(dllexport) __stdcall hWglSwapBuffers(HDC hDC) {
		mWglSwapBuffers(hDC);
		return 1;
	}
}

