#include <iostream>
#include <future>
#include <thread>

int main() {
    // 将一个返回值为 7 的 lambda 表达式封装到 task 中
    // std::packaged_task 的模板参数为要封装函数的类型
    std::packaged_task<int()> task([]() {
        int sum = 0;
        for (int i = 0; i < 1000000; ++i) {
            sum += i;
        }
        return sum;
    });

    // 获得 task 的期物
    std::future<int> result = task.get_future();  // 在一个线程中执行 task
    std::thread(std::move(task)).detach();
    std::cout << "waiting...";
    result.wait();  // 在此设置屏障，阻塞到期物的完成
    // 输出执行结果
    std::cout << "done!" << std::endl << "future result is " << result.get() << std::endl;
    return 0;
}