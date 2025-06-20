#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "ring_buffer.hpp"

int main() {
    std::string filename;
    size_t capacity;
    size_t senderCount;

    std::cout << "Enter binary file name: ";
    std::getline(std::cin, filename);
    std::cout << "Enter message buffer capacity: ";
    std::cin >> capacity;
    std::cout << "Enter number of sender processes: ";
    std::cin >> senderCount;
    std::cin.ignore();

    try {
        RingBuffer ring(filename, capacity);

        std::vector<std::string> senderCmds;
        for (size_t i = 0; i < senderCount; ++i) {
            std::string cmd = "start cmd /k \"sender.exe " + filename + "\"";
            senderCmds.push_back(cmd);
        }

        for (auto& cmd : senderCmds) {
            system(cmd.c_str());
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }

        std::cout << "All sender processes started.\n";

        while (true) {
            std::cout << "Enter command (read/exit): ";
            std::string cmd;
            std::getline(std::cin, cmd);
            if (cmd == "read") {
                try {
                    auto msg = ring.readMessage();
                    std::cout << "Received: " << msg << "\n";
                }
                catch (const std::exception& e) {
                    std::cout << "Waiting for messages...\n";
                }
            }
            else if (cmd == "exit") {
                std::cout << "Receiver exiting...\n";
                break;
            }
            else {
                std::cout << "Unknown command.\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    return 0;
}
