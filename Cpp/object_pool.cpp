// https://www.cnblogs.com/qicosmos/p/4995248.html

#include <memory>
#include <vector>
#include <functional>
#include <iostream>

template <class T>
class SimpleObjectPool {
public:
    using DeleterType = std::function<void(T*)>;

    void add(std::unique_ptr<T> t) {
        pool_.push_back(std::move(t));
    }

    std::unique_ptr<T, DeleterType> get() {
        if (pool_.empty()) {
            throw std::logic_error("no more object");
        }

        // every time add custom deleter for default unique_ptr
        std::unique_ptr<T, DeleterType> ptr(pool_.back().release(), [this](T* t) { pool_.push_back(std::unique_ptr<T>(t)); });

        pool_.pop_back();
        return std::move(ptr);
    }

    bool empty() const {
        return pool_.empty();
    }

    size_t size() const {
        return pool_.size();
    }

private:
    std::vector<std::unique_ptr<T>> pool_;
};

// 测试代码：
class A {};

void test_object_pool() {
    SimpleObjectPool<A> p;
    p.add(std::unique_ptr<A>(new A()));
    p.add(std::unique_ptr<A>(new A()));

    {
        auto t = p.get();
        p.get();
    }

    {
        p.get();
        p.get();
    }

    std::cout << p.size() << std::endl;
}

int main() {
    test_object_pool();
    return 0;
}

// g++-8 test.cpp -o test -lstdc++fs -std=c++17 -lpthread