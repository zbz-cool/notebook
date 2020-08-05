// queue 模板类也需要两个模板参数，一个是元素类型，一个容器类型，元素类型是必要的，容器类型是可选的，默认为deque 类型。

#include <list>
#include <queue>
#include <iostream>

template <typename T, class Container = std::list<T>>
class MyQueue {
public:
    void push(T value) {
        _queue.push(value);
        return;
    }
    void pop(T& value) {
        if (!_queue.empty()) {
            value = _queue.front();
            _queue.pop();
        }
    }

private:
    std::queue<T, Container> _queue;
};

int main() {
    MyQueue<int> my_queue;
    int tmp;
    my_queue.push(3);
    my_queue.pop(tmp);
    std::cout << tmp << std::endl;
    return 0;
}