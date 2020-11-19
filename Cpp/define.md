## #define语句中的#是把参数字符串化,##是连接两个参数成为一个整体。

```Cpp
#include <iostream>

#define to_string(s) #s // 参数字符串化
#define exe(xxx) test_##xxx() // 字符串拼接

void test_abc() {
    std::cout << "test_abc" << std::endl;
}

int main() {
    std::cout << to_string(3.45) + std::string(" is PI!") << std::endl;
    exe(abc);
}
```

## `do {} while(0)` 的优势

```Cpp
void print1() {
    printf("Hello 1");
}
void print2() {
    printf("Hello 2");
}
#define func() print1();print2();
int main() {
    if (0) 
        func();
    return 0;
}
```

上面的代码展开之后就是下面这样子, 宏定义中的东西被拆分了.

```Cpp
int main() {
    if (0) 
        print1();
        print2();
    return 0;
}
```

为了让宏定义不管在任何情况下都是一个整体, 使用`do {//do something } while(0)`将内容包起来就是一个非常好的方法

```Cpp
#define func()               \
     do {                    \
         print1();print2();  \
     } while(0)
```