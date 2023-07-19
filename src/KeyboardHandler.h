#pragma once

#include <Windows.h>
#include <Psapi.h>
#include <functional>
#include <unordered_map>

struct ProcessUtils {
	
	static bool isChromeActive();
};

class KeyboardHandler{
public:
	static KeyboardHandler* get();
	inline static void deleteInstance() {delete instance;}

	void registerKeyPress(int key, std::function<void()> func);

	~KeyboardHandler();
	KeyboardHandler(const KeyboardHandler&) = delete;
	KeyboardHandler& operator=(const KeyboardHandler&) = delete;

private:
	KeyboardHandler();
	void keyboardInputHook(WPARAM inputType, LPARAM rawKeyInfo);

	static KeyboardHandler* instance;
	static LRESULT CALLBACK _keyboardInputHook(int nCode, WPARAM inputType, LPARAM rawKeyInfo);

	std::unordered_map<int, std::function<void()>> keyRegistry;
	HHOOK keyboardHook;
};
