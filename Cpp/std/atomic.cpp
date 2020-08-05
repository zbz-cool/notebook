#include <thread>
#include <atomic>
#include <iostream>
#include <list>
#include <vector>
#include <mutex>

// std::atomic<T>`模板类可以使对象操作为原子操作，避免多线程竞争问题；请看如下代码，一目了然
// https://en.cppreference.com/w/cpp/atomic/atomic
// 只支持"bool", "int", "short", "char"等基本类型

class Test {
public:
    Test() = default;

    void start() {
        std::vector<std::thread> threads;
        for (int i = 0; i < 10; ++i) {
            threads.push_back(std::thread(&Test::CThreadFunc, this));
        }

        for (auto& th : threads) {
            if (th.joinable()) {
                th.join();
            }
        }
        std::cout << "_i_value:" << _i_value << ", _atomic_value:" << _atomic_value << std::endl;
    }

private:
    int _i_value = 0;
    std::atomic<int> _atomic_value = {0};  // sta::atomic<T> 原子操作
    static std::mutex _i_value_mutex;

    void CThreadFunc() {
        for (int i = 0; i < 10000; ++i) {
            // std::lock_guard<std::mutex> lck(Test::_i_value_mutex); //_i_value需要加锁才可正常工作
            _i_value++;

            _atomic_value++;  // 不加锁，也可正常工作
        }
    }
};

std::mutex Test::_i_value_mutex;

int main() {
    Test st;
    st.start();
    return 0;
}
