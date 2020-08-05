# std::filesystem

在C++17中, 才被支持

Filesystem TS与C ++ 1z支持无关，它是一个完全独立的规范，不属于C ++ 1z工作草案。您只需要链接-lstdc++fs即可使用它。

（相关的库，libstdc++fs.a是一个静态库，因此对于任何静态库，它应位于链接器命令中依赖它的任何对象之后。）

## 2017年11月更新

与Filesystem TS一样，GCC 8.x 也具有C ++ 17 Filesystem库的实现，该库在使用或时\<filesystem\>在名称空间中和名称空间中定义std::filesystem（注意，这些名称中没有“ experimental”）。GCC的C ++ 17支持尚不完整或不稳定，并且在被认为可以在黄金时间使用之前，您还需要链接到C ++ 17 Filesystem功能。-std=gnu++17-std=c++17-lstdc++fs

## 2019年1月更新

从GCC 9开始，std::filesystem无需使用C ++ 17 组件即可-lstdc++fs（但您仍然需要该库用于std::experimental::filesystem）。

## 直接编译

```sh
g++-8 filesystem-testing.cpp -lstdc++fs -std=c++17
```

## CMake 编译

```sh
target_link_libraries(myTest stdc++fs)
set_property(TARGET myTest PROPERTY CXX_STANDARD 17)
```

## -lstd++fs 的位置

-lstdc++fs必须在该行的末尾（至少在源文件之后）, 因为链接器就是这样工作的, 引用是从左到右解析的，因此您需要在使用静态库的对象之后列出它们。

## sample code

```C++
#include <fstream>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

int main()
{
    fs::create_directories("sandbox/a/b");
    std::ofstream("sandbox/file1.txt");
    std::ofstream("sandbox/file2.txt");
    for (auto& p: fs::directory_iterator("sandbox"))
        std::cout << p << '\n';
    fs::remove_all("sandbox");
}
```
