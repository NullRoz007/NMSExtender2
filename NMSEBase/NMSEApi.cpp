#include "stdafx.h"
#include "NMSEApi.h"

int test2;
bool hadFirstSwap = false;
twglSwapBuffers owglSwapBuffers;
HGLRC currentContext;

uintptr_t modBase = (uintptr_t)GetModuleHandle(NULL);
_AK_SoundEngine_IsInitialized AK_SoundEngine_IsInitialized = _AK_SoundEngine_IsInitialized(modBase + 0x11FF570);
_AK_SoundEngine_Term AK_SoundEngine_Term = _AK_SoundEngine_Term(modBase + 0x1205330);
_AK_SoundEngine_MuteBackgroundMusic AK_SoundEngine_MuteBackgroundMusic = _AK_SoundEngine_MuteBackgroundMusic(modBase + 0x12000E0);
DWORD AK_SoundEngine_g_PlayingID_Addr = (modBase + 0x1B647C0);
unsigned long AK_SoundEngine_g_PlayingID = (unsigned long)AK_SoundEngine_g_PlayingID_Addr;


GLvoid initializeContext() {
	hadFirstSwap = true;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, 1080, 1920, 0.0, 1.0, -1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClearColor(0, 0, 0, 1.0);
}


void HookableOnSwapBuffers() {}
NMSEApi api = NMSEApi::NMSEApi(ModManager());

BOOL __stdcall hwglSwapBuffers(_In_ HDC hDC) {
	HGLRC oContext = wglGetCurrentContext();
	if (!hadFirstSwap) {
		currentContext = wglCreateContext(hDC);
		wglMakeCurrent(hDC, currentContext);
		initializeContext();
	}
	else {
		wglMakeCurrent(hDC, currentContext);
	}

	const char* str = "[NMSExtender v1.0]";
	SelectObject(hDC, GetStockObject(SYSTEM_FONT));
	wglUseFontBitmaps(hDC, 0, 255, 1000);
	glListBase(1000);
	glRasterPos2f(10.0f, 50.0f);
	glCallLists(strlen(str), GL_UNSIGNED_BYTE, str);

	for (auto &m : api.manager.loadedMods) {
		Mod mod = m;
		if (mod.hasGLHook) {
			mod.glptr(hDC);
		}
	}

	wglMakeCurrent(hDC, oContext);
	return owglSwapBuffers(hDC);
}

void StartNMSE(ModManager manager) {
	api = NMSEApi::NMSEApi(manager);
	cout << "Loaded: " << api.manager.loadedMods.size() << " mod(s)." << endl;

	void *gptr = GetProcAddress(GetModuleHandle(TEXT("opengl32.dll")), "wglSwapBuffers");
	MH_Initialize();
	MH_CreateHook(gptr, hwglSwapBuffers, reinterpret_cast<void**>(&owglSwapBuffers));
	MH_STATUS status = MH_EnableHook(gptr);
}

NMSEApi::NMSEApi(ModManager m)
{
	manager = m;
}


NMSEApi::~NMSEApi()
{
}

MH_STATUS NMSEApi::HookNMSEFunction(const char* target, LPVOID original, LPVOID detour)
{
	void *gptr = GetProcAddress(GetModuleHandle(TEXT("NMSEBase.dll")), target);
	MH_Initialize();
	MH_CreateHook(gptr, detour, reinterpret_cast<void**>(&original));
	MH_STATUS status = MH_EnableHook(gptr);
	return status;
}
