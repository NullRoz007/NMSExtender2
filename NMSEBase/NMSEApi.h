#pragma once
#include <iostream>
#include <vector>
#include <windows.h>
#include <functional>
#include "AK.h"
#include "MinHook.h"
#include "GL/glut.h";
#include "ModManager.h";

using namespace std;

extern uintptr_t modBase;

typedef bool(__stdcall *_AK_SoundEngine_IsInitialized)();
extern _AK_SoundEngine_IsInitialized AK_SoundEngine_IsInitialized;

typedef void(__stdcall *_AK_SoundEngine_Term)();
extern _AK_SoundEngine_Term AK_SoundEngine_Term;

typedef void(__stdcall * _AK_SoundEngine_MuteBackgroundMusic)(bool);
extern _AK_SoundEngine_MuteBackgroundMusic AK_SoundEngine_MuteBackgroundMusic;

extern unsigned long AK_SoundEngine_g_PlayingID;

typedef BOOL(__stdcall *twglSwapBuffers) (_In_ HDC hDC);

extern vector<void(*) ()> glFuncs;
extern bool hadFirstSwap;

extern char* console;

extern GLvoid initializeContext();
extern BOOL __stdcall hwglSwapBuffers(_In_ HDC hDC);
extern void StartNMSE(ModManager manager);



class NMSEApi
{
public:
	ModManager manager;
	NMSEApi(ModManager manager);
	~NMSEApi();
	MH_STATUS HookNMSEFunction(const char* target, LPVOID original, LPVOID detour);
};
