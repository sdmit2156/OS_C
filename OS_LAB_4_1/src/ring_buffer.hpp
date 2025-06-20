#pragma once

#include <string>
#include <mutex>

class RingBuffer {
public:
    struct Header {
        size_t head;
        size_t tail;
        size_t count;
        size_t capacity;
    };

    explicit RingBuffer(const std::string& filename, size_t capacity = 0);

    void writeMessage(const std::string& message);
    std::string readMessage();

    bool isFull();
    bool isEmpty();

private:
    std::string filename;
    std::mutex mtx;

    Header header;

    void loadHeader();
    void saveHeader();

    void writeToFile(size_t index, const std::string& message);
    std::string readFromFile(size_t index);

    static constexpr size_t MESSAGE_SIZE = 20;
};
