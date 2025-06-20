#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include <windows.h>
#include <fstream>
#include "Message.h"

const std::string TEST_FILE = "test_msg.bin";

TEST_CASE("Basic message tests") {
    Message msg{};

    SECTION("New message is empty") {
        REQUIRE(msg.isEmpty == true);
        REQUIRE(msg.text[0] == '\0');
    }

    SECTION("Can store short text") {
        std::string testText = "Test";
        strcpy_s(msg.text, testText.c_str());
        REQUIRE(std::string(msg.text) == testText);
        REQUIRE(msg.isEmpty == true);
    }
}

TEST_CASE("File operations") {
    {
        std::ofstream out(TEST_FILE, std::ios::binary);
        Message emptyMsg{};
        emptyMsg.isEmpty = true;
        out.write(reinterpret_cast<char*>(&emptyMsg), sizeof(Message));
    }

    SECTION("Write and read message") {
        {
            std::fstream file(TEST_FILE, std::ios::in | std::ios::out | std::ios::binary);
            Message msg{};
            strcpy_s(msg.text, "Hello");
            msg.isEmpty = false;
            file.write(reinterpret_cast<char*>(&msg), sizeof(Message));
        }

        {
            std::ifstream in(TEST_FILE, std::ios::binary);
            Message readMsg{};
            in.read(reinterpret_cast<char*>(&readMsg), sizeof(Message));

            REQUIRE(readMsg.isEmpty == false);
            REQUIRE(std::string(readMsg.text) == "Hello");
        }
    }

    std::remove(TEST_FILE.c_str());
}