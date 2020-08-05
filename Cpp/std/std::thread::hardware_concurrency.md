# [std::thread::hardware_concurrency](https://en.cppreference.com/w/cpp/thread/thread/hardware_concurrency)

Returns the number of concurrent threads supported by the implementation. The value should be considered only a hint.

## Return value

Number of concurrent threads supported. If the value is not well defined or not computable, returns ​0​.

## Example

```C++
#include <iostream>
#include <thread>

int main() {
    unsigned int n = std::thread::hardware_concurrency();
    std::cout << n << " concurrent threads are supported.\n";
}
```

## Possible output

```log
4 concurrent threads are supported.
```
