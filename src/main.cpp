#include <io.h>
#include <fcntl.h>

#include "MessagingHandler.h"
#include "KeyboardHandler.h"

int main(int argc, char* argv[]) {
    _setmode(_fileno(stdout), _O_BINARY);
    _setmode(_fileno(stdin), _O_BINARY);
    

    ProcessUtils::isChromeActive();

    //Messenger messenger;
    
   // Message m = messenger.receiveMessage();
    //messenger.sendMessage(m);

    return 0;
}

