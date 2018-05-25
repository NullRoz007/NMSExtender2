#pragma once
#include <windows.h>
#include "AK.h"

uintptr_t modBase = (uintptr_t)GetModuleHandle(NULL);

typedef bool(__stdcall *_AK_SoundEngine_IsInitialized)();
_AK_SoundEngine_IsInitialized AK_SoundEngine_IsInitialized = _AK_SoundEngine_IsInitialized(modBase + 0x11FF570);

/*typedef unsigned __int64 (__stdcall *_AK_SoundEngine_Query_GetGameObjectFromPlayingId)(unsigned long);
_AK_SoundEngine_Query_GetGameObjectFromPlayingId AK_SoundEngine_Query_GetGameObjectFromPlayingId = _AK_SoundEngine_Query_GetGameObjectFromPlayingId(modBase + 0x1206DB0);
*/

DWORD AK_SoundEngine_g_PlayingID_Addr  = (modBase + 0x1B647C0);
unsigned long AK_SoundEngine_g_PlayingID = (unsigned long)AK_SoundEngine_g_PlayingID_Addr;

bool HookFunction(void * fToHook, void * fToOverwrite, int len) {
	if (len < 5) {
		return false;
	}

	DWORD curProtection;
	VirtualProtect(fToHook, len, PAGE_EXECUTE_READWRITE, &curProtection);
	
	memset(fToHook, 0x90, len);
	
	DWORD relativeAddress = ((DWORD)fToOverwrite - (DWORD)fToHook) - 5;

	*(BYTE*)fToHook = 0xE9;
	*(DWORD*)((DWORD)fToHook + 1) = relativeAddress;

	DWORD temp;
	VirtualProtect(fToHook, len, curProtection, &temp);

	return true;
}
