#include "KeyboardHandler.h"

  //////////////////////////////////////////////////////////////////////////
 //                             PROCESS_UTILS                            //
//////////////////////////////////////////////////////////////////////////

#include <iostream>

bool ProcessUtils::isChromeActive(){
	bool isChrome = true;
	
	const HWND hwnd = GetForegroundWindow();
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);

	if (pid == ProcessUtils::cachedPid) return isChrome;

	const HANDLE handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	char path[MAX_PATH + 1] = {0};
	const char chromeFile[] = "chrome.exe";
	int pathLength = GetModuleFileNameExA(handle, 0, path, MAX_PATH);

	if (pathLength >= 10){
		for (int i = 0; i < 10; ++i) {
			if (path[pathLength - 1 - i] != chromeFile[9 - i]) { isChrome = false; break; }
		}
	}

	if (isChrome)ProcessUtils::cachedPid = pid;
	if (handle)CloseHandle(handle);

	return isChrome;
}

  ///////////////////////////////////////////////////////////////////////////
 //                           KEYBOARD_HANDLER                            //
///////////////////////////////////////////////////////////////////////////

KeyboardHandler* KeyboardHandler::instance = nullptr;

KeyboardHandler* KeyboardHandler::get(){
	if (!KeyboardHandler::instance) {
		KeyboardHandler::instance = new KeyboardHandler();
	}
	return KeyboardHandler::instance;
}

LRESULT CALLBACK KeyboardHandler::_keyboardInputHook(int nCode, WPARAM inputType, LPARAM rawKeyInfo) {
	if (nCode != HC_ACTION) return CallNextHookEx(NULL, nCode, inputType, rawKeyInfo);

	KeyboardHandler::get()->keyboardInputHook(inputType, rawKeyInfo);

	return CallNextHookEx(NULL, nCode, inputType, rawKeyInfo);
}

KeyboardHandler::KeyboardHandler(){
	this->keyboardHook = SetWindowsHookExA(WH_KEYBOARD_LL, KeyboardHandler::_keyboardInputHook, NULL, NULL);
}	

KeyboardHandler::~KeyboardHandler(){
	UnhookWindowsHookEx(this->keyboardHook);
}

void KeyboardHandler::registerKeyPress(int key, std::function<void()> func){
	this->keyRegistry[key] = func;
}

void KeyboardHandler::keyboardInputHook(WPARAM inputType, LPARAM rawKeyInfo){
	PKBDLLHOOKSTRUCT keyInfo = (PKBDLLHOOKSTRUCT) rawKeyInfo;
	if (inputType == WM_KEYDOWN && ProcessUtils::isChromeActive()) {
		int key = keyInfo->vkCode;
		if(this->keyRegistry.contains(key)) this->keyRegistry[key]();
	}
}
