#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include "ring_buffer.hpp"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: sender <filename>\n";
        return 1;
    }

    std::string filename = argv[1];

    try {
        RingBuffer ring(filename);

        std::cout << "Sender ready\n";

        while (true) {
            std::cout << "Enter command (send/exit): ";
            std::string cmd;
            std::getline(std::cin, cmd);

            if (cmd == "send") {
                std::cout << "Enter message: ";
                std::string message;
                std::getline(std::cin, message);

                if (message.size() >= 20) {
                    std::cout << "Message too long (max 19 chars).\n";
                    continue;
                }

                while (true) {
                    try {
                        ring.writeMessage(message);
                        std::cout << "Message sent.\n";
                        break;
                    }
                    catch (const std::exception& e) {
                        std::cout << "Waiting for space...\n";
                        std::this_thread::sleep_for(std::chrono::milliseconds(500));
                    }
                }
            }
            else if (cmd == "exit") {
                std::cout << "Sender exiting...\n";
                break;
            }
            else {
                std::cout << "Unknown command.\n";
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error in sender: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
