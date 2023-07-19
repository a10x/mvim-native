#include <io.h>
#include <fcntl.h>

#include "MessagingHandler.h"
#include "KeyboardHandler.h"

#include "MVim.cpp"


int main(int argc, char* argv[]) {
    MVim::Setup();
    MVim::Run();
    return 0;
}

