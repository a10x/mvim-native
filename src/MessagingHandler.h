#pragma once

#include <iostream>
#include <string>
#include <string_view>

struct Message {
    std::string wrapped;
    std::string_view message;
    size_t size = 0;
};

struct MessageUtils {
    static Message Wrap(std::string& message);
    static void Unwrap(Message& message);
    static Message Unwrap(std::string& message);

    static std::string IntToHex(uint32_t value);
    static std::string IntToCharStr(uint32_t value);

    //least significant byte is position 0 and most signifcant byte is position 3
    inline static uint32_t ReplaceIntByte(uint32_t originalInt, uint8_t position, uint8_t newByte) {
        return originalInt | (newByte << (8 * position));
    }
};

struct Messenger{
    Message receiveMessage();
    void sendMessage(Message& message);
    void sendMessage(std::string& message);
    uint32_t getIncomingMessageSize();
};

