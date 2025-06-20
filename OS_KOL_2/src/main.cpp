#include <iostream>
#include <mutex>
#include <thread>
#include <atomic>

// ������������� ��������� �������������
struct NoSync {
    static void sync() {
        // ��� �������������
    }
    static void unsync() {
        // ��� �������������
    }
};

struct MutexSync {
    static std::mutex mtx;
    static void sync() {
        mtx.lock();
    }
    static void unsync() {
        mtx.unlock();
    }
};

std::mutex MutexSync::mtx;

struct AtomicSync {
    static std::atomic_flag lock_flag;
    static void sync() {
        while (lock_flag.test_and_set(std::memory_order_acquire)) {
            // �������� ������������ �����
        }
    }
    static void unsync() {
        lock_flag.clear(std::memory_order_release);
    }
};

std::atomic_flag AtomicSync::lock_flag = ATOMIC_FLAG_INIT;

// �������� ����� Singleton � �������������� ������������� ���������
template <typename SyncStrategy>
class Singleton {
public:
    static Singleton& instance() {
        SyncStrategy::sync();
        if (!_instance) {
            _instance = new Singleton();
        }
        SyncStrategy::unsync();
        return *_instance;
    }

    void doSomething() {
        std::cout << "Doing something...\n";
    }

private:
    Singleton() {}
    static Singleton* _instance;
};

template <typename SyncStrategy>
Singleton<SyncStrategy>* Singleton<SyncStrategy>::_instance = nullptr;

// ������� ��� �������������� �����
void testSingleton() {
    Singleton<MutexSync>::instance().doSomething();
}

int main() {
    std::thread t1(testSingleton);
    std::thread t2(testSingleton);

    t1.join();
    t2.join();

    return 0;
}