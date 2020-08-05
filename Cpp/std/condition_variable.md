> <https://blog.csdn.net/llmblcwwmm/article/details/106820773>

## 条件变量 虚假唤醒

生产者线程不断生产数据并放入g_deque中，10个消费者线程不断从g_deque中获取数据并删除。
没有数据的时候消费者线程调用wait函数阻塞当前线程，当生产者数据放入g_deque之后调用notify_all函数唤醒所有等待的线程。
因为是10个消费者线程共同竞争数据，所以最终只有一个线程得到数据，另外9个线程被唤醒之后发现g_deque为空继续调用wait函数阻塞自己，
这就导致了一个虚假唤醒的概念:明明当前线程已经被唤醒了，却得不到需要的数据。

## 解释

网络对于虚假唤醒的解释主要有两种:一种就是上面解释的由notify_all唤醒之后却得不到需要的数据，一种是有的系统会出于某种原因唤醒正在阻塞队列的线程，这时候消费者线程也是得不到需要的数据的.
经过测试, 只存在第一种可能.

## 解决方法

```cpp
while (g_deque.empty())
{
    g_cond.wait(lck);
}

// 或

g_cond.wait(lck, [] {return !g_deque.empty(); });
```

## 例子

```cpp
#include <queue>
#include <chrono>
#include <mutex>
#include <thread>
#include <iostream>
#include <condition_variable>

int main() {
    std::queue<int> produced_nums;
    std::mutex mtx;
    std::condition_variable cv;
    bool notified = false;  // 通知信号

    // 生产者
    auto producer = [&]() {
        for (int i = 0;; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(900));
            std::unique_lock<std::mutex> lock(mtx);
            std::cout << "producing " << i << std::endl;
            produced_nums.push(i);
            notified = true;
            cv.notify_all();  // 此处也可以使用 notify_one
        }
    };

    // 消费者
    auto consumer = [&]() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            while (!notified) {  // 避免虚假唤醒
                cv.wait(lock);
            }
            // 短暂取消锁，使得生产者有机会在消费者消费空前继续生产
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));  // 消费者慢于生产者
            lock.lock();
            while (!produced_nums.empty()) {
                std::cout << "consuming " << produced_nums.front() << std::endl;
                produced_nums.pop();
            }
            notified = false;
        }
    };

    // 分别在不同的线程中运行
    std::thread p(producer);
    std::thread cs[2];
    for (int i = 0; i < 2; ++i) {
        cs[i] = std::thread(consumer);
    }
    p.join();
    for (int i = 0; i < 2; ++i) {
        cs[i].join();
    }
    return 0;
}
```
