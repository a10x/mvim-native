#include "KeyboardHandler.h"

bool ProcessUtils::isChromeActive(){
	const HWND hwnd = GetForegroundWindow();
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	const HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	
	char path[MAX_PATH + 1] = {0};
	const char chromeFile[] = "chrome.exe";
	int pathLength = GetModuleFileNameExA(handle, 0, path, MAX_PATH);

	bool isChrome = true;

	if (pathLength >= 10){
		for (int i = 0; i < 10; ++i) {
			if (path[pathLength - 1 - i] != chromeFile[9 - i]) { isChrome = false; break; }
		}
	}

	if (handle)CloseHandle(handle);

	return isChrome;

}
