#include "emory.h"
#include <Windows.h>
#include <TlHelp32.h>
#include <iostream>
#include <tchar.h>
#include <vector>
#include <sstream>

TCHAR* fromString(std::string str) {
    TCHAR *param=new TCHAR[str.size()+1];
    param[str.size()]=0;
    std::copy(str.begin(),str.end(),param);
    return param;
}

uintptr_t GetPointerFromString(const char *c) {
	ptrdiff_t h;
	sscanf(c, "%tx", &h);
	return (uintptr_t)h;
}

uintptr_t GetModuleBaseAddress(TCHAR* lpszModuleName, uintptr_t pID) {
	uintptr_t dwModuleBaseAddress = 0;
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pID);
	MODULEENTRY32 ModuleEntry32 = { 0 };
	ModuleEntry32.dwSize = sizeof(MODULEENTRY32);

	if (Module32First(hSnapshot, &ModuleEntry32)) 
	{
		do {
			if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0)
			{
				dwModuleBaseAddress = (uintptr_t) ModuleEntry32.modBaseAddr;
				break;
			}
		} while (Module32Next(hSnapshot, &ModuleEntry32));


	}
	CloseHandle(hSnapshot);
	return dwModuleBaseAddress;
}

HANDLE GetKtanePidAndProcess(TCHAR* windowName, DWORD* pID) {
	HWND hGameWindow = FindWindow(NULL, windowName);

	if (hGameWindow == NULL) {
		std::cout << "Start the game!" << std::endl;
		return 0;
	}

	GetWindowThreadProcessId(hGameWindow, pID);

	HANDLE pHandler = OpenProcess(PROCESS_ALL_ACCESS, FALSE, *pID);

	if (pHandler == INVALID_HANDLE_VALUE || pHandler == NULL) {
		std::cout << "Failed to open process" << std::endl;
		return 0;
	}

	return pHandler;
}

uintptr_t GetAddressFromOffsets(HANDLE pHandler, uintptr_t gameBaseAddress, std::vector<uintptr_t> pointsOffsets) {
	uintptr_t baseAddress;

	ReadProcessMemory(pHandler, (LPVOID)(gameBaseAddress+pointsOffsets[0]), &baseAddress, sizeof(baseAddress), NULL);

	uintptr_t pointsAddress = baseAddress;

	for (int i = 1; i < pointsOffsets.size() - 1; i++) {
		ReadProcessMemory(pHandler, (LPVOID)(pointsAddress + pointsOffsets.at(i)), &pointsAddress, sizeof(pointsAddress), NULL);
	}

	pointsAddress += pointsOffsets.at(pointsOffsets.size() - 1);

	return pointsAddress;
}

float GetFloatAddressValue(HANDLE pHandler, uintptr_t baseOffset, std::vector<uintptr_t> pointsOffsets) {
	float timer = 0.0f;

	uintptr_t address = GetAddressFromOffsets(
		pHandler,
		baseOffset,
		pointsOffsets
	);

	ReadProcessMemory(pHandler, (LPVOID)(address), &timer, sizeof(address), NULL);

    return timer;
}

int GetIntAddressValue(HANDLE pHandler, uintptr_t baseOffset, std::vector<uintptr_t> pointsOffsets) {
	int timer = 0;

	uintptr_t address = GetAddressFromOffsets(
		pHandler,
		baseOffset,
		pointsOffsets
	);

	ReadProcessMemory(pHandler, (LPVOID)(address), &timer, sizeof(address), NULL);

    return timer;
}