# C++11: std::threads managed by a designated class

```C++
#include <iostream>
#include <thread>
#include <chrono>

class MyClass {
public:
    /* Explicitly using the default constructor to
     * underline the fact that it does get called */
    MyClass() : _thread() {}
    ~MyClass() {
        _stop_thread = true;
        if(_thread.joinable()) _thread.join();
    }

    void start() {
        // This will start the thread. Notice move semantics!
        _thread = std::thread(&MyClass::thread_main, this);
    }

private:
    std::thread _thread;
    bool _stop_thread = false;
    void thread_main() {
        while(!_stop_thread){
            // Do something useful, e.g:
            std::this_thread::sleep_for( std::chrono::seconds(1) );
            std::cout << __FUNCTION__ << " " << __LINE__ << std::endl;
        }
    }
};

int main() {
    MyClass mc;
    mc.start();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    return 0;
}
```

## References

- [C++11: std::threads managed by a designated class](https://rafalcieslak.wordpress.com/2014/05/16/c11-stdthreads-managed-by-a-designated-class/)
