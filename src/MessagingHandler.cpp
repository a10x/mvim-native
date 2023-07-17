#include "MessagingHandler.h"

  //////////////////////////////////////////////////////////////////////////
 //                               MESSENGER                              //
//////////////////////////////////////////////////////////////////////////


uint32_t Messenger::getIncomingMessageSize() {
    uint32_t size = 0;
    for (int i = 0; i < 4; ++i)size = MessageUtils::ReplaceIntByte(size, i, (uint8_t)getchar());
    return size;
}

Message Messenger::receiveMessage(){
    uint32_t size = this->getIncomingMessageSize();

    Message received;
    received.size = size;
    received.wrapped.reserve(size);

    for (int i = 0; i < size; ++i) received.wrapped.push_back(getchar());

    MessageUtils::Unwrap(received);
    
    return received;
}

void Messenger::sendMessage(Message& message){
    std::cout << MessageUtils::IntToCharStr(message.size);
    std::cout << message.wrapped;
}

void Messenger::sendMessage(std::string& message){
    Message draft = MessageUtils::Wrap(message);
    this->sendMessage(draft);

}


  //////////////////////////////////////////////////////////////////////////
 //                             MESSAGE_UTILS                            //
//////////////////////////////////////////////////////////////////////////


Message MessageUtils::Wrap(std::string& message){
    Message draft;

    draft.size = message.size() + 11;
    draft.wrapped.reserve(draft.size);

    draft.wrapped.append("{\"text\":\"");
    draft.wrapped.append(message);
    draft.wrapped.append("\"}");

    std::string_view wrappedView = draft.wrapped;
    draft.message = wrappedView.substr(9, draft.size - 11);

    return draft;
}

void MessageUtils::Unwrap(Message& message){
    std::string_view wrappedView = message.wrapped;
    message.message = wrappedView.substr(9, message.size - 11);
}

Message MessageUtils::Unwrap(std::string& message){
    Message received;
    received.wrapped = message;
    received.size = message.size();

    MessageUtils::Unwrap(received);

    return received;
}

std::string MessageUtils::IntToHex(uint32_t value){
    char hex[5] = {0};
    uint8_t masked;

    for (int i = 3; i >= 0; --i) {
        masked = value & 0xf;
        hex[i] = masked < 10 ? '0' + masked : 'A' + (masked - 10);
        value >>= 4;
    }

    hex[4] = '\0';

    return std::string(hex);
}

std::string MessageUtils::IntToCharStr(uint32_t value) {
    std::string charStr;
    uint8_t masked;

    for (int i = 0; i < 4; ++i) {
        masked = value & 0xff;
        charStr.push_back(masked);
        value >>= 8;
    }
    return charStr;
}