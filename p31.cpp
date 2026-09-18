#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

class Buffer {
public:
    Buffer(int size) : size_(size) {}

    void put(int value) {
        std::unique_lock<std::mutex> lock(mutex_);
        not_full_.wait(lock, [this] { return values_.size() < size_; });
        values_.push(value);
        not_empty_.notify_one();
    }

    int get() {
        std::unique_lock<std::mutex> lock(mutex_);
        not_empty_.wait(lock, [this] { return !values_.empty(); });
        int value = values_.front();
        values_.pop();
        not_full_.notify_one();
        return value;
    }

private:
    int size_;
    std::queue<int> values_;
    std::mutex mutex_;
    std::condition_variable not_full_;
    std::condition_variable not_empty_;
};

int main() {
    const int item_count = 10;
    Buffer buffer(5);

    std::thread producer([&] {
        for (int item = 1; item <= item_count; ++item) {
            buffer.put(item);
            std::cout << "Produced: " << item << '\n';
        }
    });

    std::thread consumer([&] {
        for (int i = 0; i < item_count; ++i) {
            int item = buffer.get();
            std::cout << "Consumed: " << item << '\n';
        }
    });

    producer.join();
    consumer.join();
    return 0;
}
