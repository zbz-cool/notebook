## using namespace xxx

不要在头文件中使用命名空间的申明, 要在保证

## 1. 编译器隐式为类生成的成员函数

| 函数名 | 说明 | 备注
| -- | -- | --
| T Object( const T &)  | 拷贝构造函数 | 常量左值引用是个“万能”的引用类型，无论左值还是右值，常量还是非常量，一概能够绑定。
| T Object( T &&) | 移动构造函数 | 在实现移动语义一定要注意排除不必要的const关键字。

为了保证移动语义的传递，程序员在编写移动构造函数的时候，应该总是记得使用std::move转换拥有形如堆内存、文件句柄等资源的成员为右值，这样一来，如果成员支持移动构造的话，就可以实现其移动语义。**而即使成员没有移动构造函数，那么接受常量左值的构造函数版本也会轻松地实现拷贝构造，因此也不会引起大的问题。**

## 2. [进程见通信](https://www.cnblogs.com/zgq0/p/8780893.html)

## 3. [参看文档](https://en.cppreference.com/w/cpp)

## 4. 静态检查工具

[Cppcheck](http://cppcheck.sourceforge.net/)

## 5. Convert int/float to string

```C++
std::ostringstream ss;
ss << num_reads;
std::cout << ss.str() << std::endl;
ss.str("");
ss.clear();

// 控制精度
ss << std::fixed << std::setprecision(2) << num_reads;
```

## 6. 计算时间差

```C++
#include <chrono>
#include <ratio>
#include <ctime>
using namespace std::chrono;
steady_clock::time_point t1 = steady_clock::now();
// doing something
steady_clock::time_point t2 = steady_clock::now();
duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
printf("%s %f ", file_name.c_str(), time_span.count());
```

## 7. std::cout

默认情况下只输出小数点后4位, 需要设置精度

## 8. std::find

```C++
std::vector<int> vec = {1, 2, 3, 4};
// 查找vec中2的位置
const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 2);
```

## 9. std::tuple C++17 不用拆元组, 牛逼

```C++
#include <iostream>
#include <tuple>

std::tuple<int, double, std::string> f() {
    return std::make_tuple(1, 2.3, "456");
}

int main() {
    auto [x, y, z] = f();
    std::cout << x << ", " << y << ", " << z << std::endl;
    return 0;
}
```

## 10. [返回类型自动推导](./返回类型自动推导.cpp)

## 11. 模板变成中, 判断typename类型

```C++
std::is_integral<T>::value
std::is_floating_point<T>::value
```

## 12. template 中的 typename 和 class

typename 和 class 在模板参数列表中没有区别，在 typename 这个关键字出现之前，都是使用 class 来定义模板参数的。但在模板中定义有嵌套依赖类型的变量时，需要用 typename 消除歧义

## 13. override

当重载虚函数时，引入 override 关键字将显式的告知编译器进行重载，编译器将检查基函数是否存在这样的虚函数，否则将无法通过编译：

```C++
struct Base {
    virtual void foo(int);
};

struct SubClass: Base {
    virtual void foo(int) override; // 合法
    virtual void foo(float) override; // 非法, 父类没有此虚函数
};
```

## 14. final

 final 则是为了防止类被继续继承以及终止虚函数继续重载引入的。

```C++
struct Base {
    virtual void foo() final;
};

struct SubClass1 final: Base {
}; // 合法

struct SubClass2 : SubClass1 {
}; // 非法, SubClass1 已 final

struct SubClass3: Base {
    void foo(); // 非法, foo 已 final
};
```

## 15. default & delete

允许显式的声明采用或拒绝编译器自带的函数。例如：

```C++
class Magic {
    public:
    Magic() = default; // 显式声明使用编译器生成的构造
    Magic& operator=(const Magic&) = delete; // 显式声明拒绝编译器生成构造
    Magic(int magic_number);
}
```

## 16. [std::move 左值 右值](https://blog.csdn.net/kitekitebaby/article/details/72566145)

## 17. 泛型 Lambda C++14

```C++
auto add = [](auto x, auto y) {
    return x+y;
};

add(1, 2);
add(1.1, 2.2);
```

## 18. cppcheck 静态检查

```sh
# Recursively check the current folder. Print the progress on the screen and
  # write errors to a file:
  cppcheck . 2> err.txt

  # Recursively check ../myproject/ and don't print progress:
  cppcheck --quiet ../myproject/

  # Check test.cpp, enable all checks:
  cppcheck --enable=all --inconclusive --std=posix test.cpp

  # Check f.cpp and search include files from inc1/ and inc2/:
  cppcheck -I inc1/ -I inc2/ f.cpp
```

## 19. std::boolalpha

`boolalpha`的作用是使`bool`型变量按照`false、true`的格式输出。如不使用该标识符，那么结果会按照`1、0`的格式输出。

```C++
#include <iostream>
int main(int magc, char *magv[])
{
    bool b = true;
    std::cout << "b=" << b << std::endl;
    std::cout << "b=" << std::boolalpha << b << std::endl;
    bool a = false;
    std::cout << "a=" << a << std::endl; // 对之后的流都有效
}
```

## 20. 尽量在类成员函数后面添加const

表示该函数不会修改任何类成员变量, 但可以修改临时变量

## 21. 多尝试使用嵌套类的, 代码会更加可读与简介

```C++
high_five.getGroup(read_id).getAttribute("DateTime").readString(read_start_time);
```

## 22. [使用fork创建子进程](./fork.cpp)

## 23. 使用 `__func__` 与 `__FUNCTION__` 标识当前函数或类

另外还有 `__FILE__` 与 `__LINE__`等预定义宏

```cpp
#include <iostream>
    using namespace std;
struct TestStruct {
    TestStruct()
        : name(__func__) {
    }
    const char* name;
};

void test_function() {
    cout << __FUNCTION__ << endl;  // test_function
}

int main() {
    TestStruct ts;
    cout << ts.name << endl;  // TestStruct
    test_function();
    return 0;
}
```

## 24. 变长参数的宏定义以及__VA_ARGS__

在C99标准中，程序员可以使用变长参数的宏定义。变长参数的宏定义是指在宏定义中参数列表的最后一个参数为省略号，而预定义宏 `__VA_ARGS__` 则可以在宏定义的实现部分替换省略号所代表的字符串。

```cpp
#include <stdio.h>
#define LOG(...) fprintf(stderr, __VA_ARGS__)
int main() {
    int x = 3;         // 一些 代码...
    LOG("x = %d", x);  // 2- 1- 5. cpp: Line 12: x = 3
}
```

## 25. assert 与 static_assert

- 在C++中，标准在`<cassert>`或`<assert.h>`头文件中为程序员提供了`assert`宏，用于在运行时进行断言,例如: `assert(n > 0)`, 不满足 n > 0的, 就abort. 但assert是一个运行时的断言，这意味着不运行程序我们将无法得知是否不满足条件。在一些情况下，这是不可接受的，因为可能单次运行代码并不会调用到assert相关的代码路径。因此这样的校验最好是在编译时期就能完成。

- [static_assert](https://blog.csdn.net/thesys/article/details/5641350) 是C++的标准语法，不需要引用头文件。而由于static_assert是编译时期的断言，其使用范围不像assert一样受到限制。在通常情况下，static_assert可以用于任何名字空间，

```cpp
#include <iostream>

static_assert(sizeof(int) == 6, "This ....."); // 这里也能运行到

int main() {
    printf("zbz");
}
```

## 26. auto 和 decltype 结合起来

```cpp
#include <iostream>
template <typename T, typename U>
auto add(T t, U u) -> decltype(t + u) {
    return t + u;
}

// 令人欣慰的是从 C++14 开始是可以直接让普通函数具备返回值推导，因此下面的写法变得合法：
template <typename T, typename U>
auto add3(T x, U y) {
    return x + y;
}

int main() {
    std::cout << add(4, 5.6);
}
```

## 27. 就地初始化 && 初始化列表

构造函数中赋值 > 初始化列表 > 就地初始化

```C++
#include <iostream>
using namespace std;
class A
{
public:
    int a = 1;
    A() {}
    A(int a_) : a(a_) {}
    A(int a_, bool b) : a(4) { a = a_; }
    static int b = 0; // 非常量静态成员变量初始化需要在类外
    // std::string b("hello"); // 就地初始化不支持圆括号
};

int main()
{
    A a1, a2(3), a3(5, true);
    cout << "a1.a=" << a1.a << endl;
    cout << "a2.a=" << a2.a << endl;
    cout << "a3.a=" << a3.a << endl;
    return 0;
}

/*
a1.a=1
a2.a=3
a3.a=5
*/
```

## 28. initializer list 使用场景(详见<深入理解C++11>)

- 函数入参
- 函数返回值
- 防止类型收窄(编译时做检查)
- 构造函数(默认支持, 不需要显示写明白initializer_list) 例如

```cpp
#include <iostream>
class TestInitList {
public:
    TestInitList(int a, std::string b)
        : a_(a)
        , b_(b) {
    }
    void print() {
        std::cout << a_ << " " << b_ << " " << std::endl;
    }

private:
    int a_;
    std::string b_;
};

int main() {
    TestInitList ti = {3, "hhh"};  // 默认支持 initializer_list
    ti.print();
}
```

## 29. 模板编程, 判断输入参数类型

虽然提供了std::is_same来判断类型, 但是该方法比较慢, 不建议使用

```cpp
#include <iostream>

template <typename T>
void test(T t) {
    if (std::is_same<decltype(t), float>::value) {
        printf("float\n");
    } else if (std::is_same<decltype(t), double>::value) {
        printf("double\n");
    } else if (std::is_same<decltype(t), int>::value) {
        printf("int\n");
    }
}

int main(int argc, char const* argv[]) {
    int a;
    float b;
    double c;
    test(a);
    test(b);
    test(c);
    return 0;
}
```

## 30. 自动遍历

```cpp
#include <iostream>
using namespace std;
// int func(int a[]) { // 数组退化为指针, 就不能使用自动遍历了
//     for (auto e : a)
//         cout << e;
// }
int main() {
    int arr[] = {1, 2, 3, 4, 5};
    for (auto e : arr) {
        cout << e << " ";
    }
    // func(arr);
}
```

## 31. 自动遍历与手动遍历的区别

```cpp
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v = {1, 2, 3, 4, 5};
    for (auto i = v.begin(); i != v.end(); ++i)
        cout << *i << endl;  // i 是迭代器对象
    for (auto e : v)
        cout << e << endl;  // e 是解引用后的对象
}
```

## terminate, abort, exit, quick_exit, at_quick_exit(深入理解C++11: 6.5)

terminate 函数实际是异常处理的一部分, 没有被捕捉的异常就会导致terminate函数的调用, 在默认情况下会调用abort函数.
abort函数不会调用任何的析构函数, 最好不要用该方法来解决进程
exit 是比较安全的退出函数, 会调用自动变量的析构函数, 并且还会调用atexit注册的函数.
quick_exit 是快速退出, 不会调用析构函数, 但是属于正常退出, 在退出时会调用at_quick_exit注册过的函数

## 线程局部存储 thread_local

即在全局或者静态变量的声明中加上关键字__thread，即可将变量声明为TLS变量。每个线程将拥有独立的errCode的拷贝，一个线程中对errCode的读写并不会影响另外一个线程中的errCode的数据。

## lambda

- lambda 函数在C++11标准中默认是内联的, 如果是频繁调用的小函数, 使用lambda在性能上会有优势
- lambda 函数等同于一个局部函数, 只能在父作用域中使用, 使用场景比如 : 小的函数块(需要被多次调用, 且参数可能较多)只在某个很小的作用域内起作用, 超过这个作用域意义不大
-总的来说，lambda函数被设计的目的，就是要就地书写，就地使用。使用lambda的用户，更倾向于在一个屏幕里看到所有的代码，而不是依靠代码浏览工具在文件间找到函数的实现。
- lambda作为局部函数也会使得复杂代码的开发加速。通过lambda函数，程序员可以轻松地在函数内重用代码，而无需费心设计接口。事实上，曾经出现过一般重构的风潮，在那段时期，C++程序员被建议为任何重用的代码创建函数，而lambda局部函数的到来则带来了理性思考和折中实现的可能。当然，lambda函数的出现也导致了函数的作用域在C++11中再次被细分，从而也使得C++编程具备了更多的可能。

## lambda 与 for_each 应用

```cpp
#include <iostream>
#include <algorithm>  // for_each
#include <vector>
using namespace std;

int main() {
    vector<int> vecInt = {1, 2, 3};
    auto multi = [](auto& val) {
        val = val * 2;
    };
    auto print_vecInt = [&]() {  // auto自动推导print_vecInt的类型为lambda函数
        for (auto& e : vecInt) {
            cout << e << " ";
        }
        cout << endl;
    };
    print_vecInt();
    for_each(vecInt.begin(), vecInt.end(), multi);
    print_vecInt();
    for_each(vecInt.begin(), vecInt.end(), [](auto& val) { val = val + 1; });
    print_vecInt();
    return 0;
}
```

使用for_each算法相较于手写的循环在效率、正确性、可维护性上都具有一定优势。最典型的，程序员不用关心iterator，或者说循环的细节，只需要设定边界，作用于每个元素的操作，就可以在近似“一条语句”内完成循环，正如函数指针版本和lambda版本完成的那样。

## [[noreturn]]

主要用于标识那些不会将控制流返回给原调用函数的函数，典型的例子有：有终止应用程序语句的函数、有无限循环语句的函数、有异常抛出的函数等。

```cpp
#include <iostream>
void DoSomething1() {
    printf("dosomething 1\n");
}
void DoSomething2() {
}
[[noreturn]] void ThrowAway() {
    throw "expection";  // 控制流跳转到异常处理
}
void Func() {
    printf("start\n");
    DoSomething1();
    ThrowAway();
    DoSomething2();  // 该函数不可到达
}
int main(int argc, const char** argv) {
    Func();
    return 0;
}
```

## push_back 与 emplace_back

`push_back(A)` 需要先调用构造函数创建A, 然后使用移动构造或者拷贝构造函数添加进容器里
`emplace_back(A)` 只调用一次构造函数, 速度更快

## string size 与 empty

判断string是否为空, 使用 `empty`, 而不是 `str.size() == 0`

