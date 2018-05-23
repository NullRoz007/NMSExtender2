#include <iostream>
#include <windows.h>
#include <TlHelp32.h>
#include "NMSEHelper.h"

using namespace std;

bool InjectDLL(PROCESS_INFORMATION* pInfo, const char* dllPath) {
	bool result = false;
	HANDLE nmsProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pInfo->dwProcessId);
	if (nmsProcess) {
		LPVOID baseAddress = VirtualAllocEx(nmsProcess, NULL, strlen(dllPath) + 1, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (baseAddress) {
			LPVOID loadLibraryAddress = (LPVOID)GetProcAddress(LoadLibraryA("kernel32.dll"), "LoadLibraryA");
			WriteProcessMemory(nmsProcess, baseAddress, dllPath, strlen(dllPath) + 1, NULL);
			HANDLE thread = CreateRemoteThread(nmsProcess, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibraryAddress, baseAddress, 0, 0);
			if (thread != NULL) {
				switch (WaitForSingleObject(thread, 5000)) {
					case WAIT_OBJECT_0:
						result = TRUE;
						break;
					case WAIT_ABANDONED:
						cout << "Abandoned" << endl;
						break;
					case WAIT_TIMEOUT:
						cout << "Timed out" << endl;
						break;
					case WAIT_FAILED:
						cout << "Failed"<< endl;
						break;
				}
			}
			else {

				cout << "Error: \n" << GetLastError() << endl;
			}
			CloseHandle(thread);
			
		}
		else {
			cout << "Error: \n" << GetLastError() << endl;
		}
		VirtualFreeEx(nmsProcess, baseAddress, 0, MEM_RELEASE);
		CloseHandle(nmsProcess);
	}
	return result;
}

PROCESS_INFORMATION CreateNMS(char* nmsPath, HANDLE* creationHandle)
{
	STARTUPINFO startup_information;
	PROCESS_INFORMATION process_information;
	memset(&startup_information, 0, sizeof(startup_information));
	memset(&process_information, 0, sizeof(process_information));

	startup_information.cb = sizeof(startup_information);

	if (CreateProcess(nmsPath, NULL, NULL, NULL, false, CREATE_SUSPENDED, NULL, NULL, &startup_information, &process_information)) {
		*creationHandle = process_information.hThread;
	}
	else {
		std::cerr << "No Man's Sky failed to start:\n" << GetLastError() << std::endl;
	}
	return process_information;
}

BOOL GetPrivileges() {
	HANDLE Token;
	TOKEN_PRIVILEGES tp;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &Token))
	{
		LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
		tp.PrivilegeCount = 1;
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		if (AdjustTokenPrivileges(Token, 0, &tp, sizeof(tp), NULL, NULL) == 0) {
			return FALSE;
		}
		else {
			return TRUE;
		}
	}
	return 1;
}

int main() {
	bool privResult = GetPrivileges();
	if (!privResult) {
		cout << "Failed to get privileges." << endl;
	}

	NMSEHelper helper = NMSEHelper::NMSEHelper();

	HANDLE nmsHandle = NULL;
	PROCESS_INFORMATION process_information = CreateNMS((char*)"NMS.exe", &nmsHandle);
	std::string RTPATH = helper.RunTimePath();
	if (nmsHandle) {
		char* path = strcat((char*)RTPATH.c_str(), "\\NMSEBase.dll");
		if (InjectDLL(&process_information, path)) {
			ResumeThread(nmsHandle);
			exit(0);
		}
		else {
			exit(1);
		}
	}
	else {
		cout << "Mr Murray, I don't feel so good..." << GetLastError() << endl;
		
	}
	cin.get();
}