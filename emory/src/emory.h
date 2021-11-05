#include <Windows.h>
#include <tchar.h>
#include <vector>
#include <string>

TCHAR* fromString(std::string str);
uintptr_t GetPointerFromString(const char *c);
uintptr_t GetModuleBaseAddress(TCHAR* lpszModuleName, uintptr_t pID);
uintptr_t GetAddressFromOffsets(HANDLE pHandler, uintptr_t gameBaseAddress, std::vector<uintptr_t> pointsOffsets);
HANDLE GetKtanePidAndProcess(TCHAR* windowName, DWORD* pID);
float GetFloatAddressValue(HANDLE pHandler, uintptr_t baseOffset, std::vector<uintptr_t> pointsOffsets);
int GetIntAddressValue(HANDLE pHandler, uintptr_t baseOffset, std::vector<uintptr_t> pointsOffsets);
