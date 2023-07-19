#include <io.h>
#include <fcntl.h>

#include "MessagingHandler.h"
#include "KeyboardHandler.h"

#include "KeyPresses.cpp"

namespace MVim {

	static void Setup() {
		_setmode(_fileno(stdout), _O_BINARY);
		_setmode(_fileno(stdin), _O_BINARY);

		KeyboardHandler* keyboardHandler = KeyboardHandler::get();
		keyboardHandler->registerKeyPress('A', KeyPresses::onKeyA);
	}

	static void Run() {
		KeyboardHandler* keyboardHandler = KeyboardHandler::get();

		MSG msg{ 0 };

		while (GetMessage(&msg, NULL, 0, 0) != 0);

		keyboardHandler->get()->deleteInstance();
	}

}

