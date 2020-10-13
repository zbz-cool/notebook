## 1. 开发心得

- void 函数, 最后不需要使用return
- 类成员函数, 尽量使用 const(不修改类成员变量), static, override, final等关键词
- 不要在头文件中使用using namespace xxx
- 在构造函数中不使用会出现错误/异常的代码
- 是否可以用template来增加扩展性
- 当函数超过40~60行时, 看是否可以能拆成小函数
- 一些小函数注定不会被重用, 可以用lambda来代替
- 是否有modern C++可以用来更好解决问题
- 组合优于继承
- 为了减小调用函数时压栈出栈的开销，应该尽量将短小函数声明为inline类型

## 2. using namespace xxx

不要在头文件中使用命名空间的申明, 要在保证

## 3. 编译器隐式为类生成的成员函数

| 函数名 | 说明 | 备注
| -- | -- | --
| T Object( const T &)  | 拷贝构造函数 | 常量左值引用是个“万能”的引用类型，无论左值还是右值，常量还是非常量，一概能够绑定。
| T Object( T &&) | 移动构造函数 | 在实现移动语义一定要注意排除不必要的const关键字。

为了保证移动语义的传递，程序员在编写移动构造函数的时候，应该总是记得使用std::move转换拥有形如堆内存、文件句柄等资源的成员为右值，这样一来，如果成员支持移动构造的话，就可以实现其移动语义。**而即使成员没有移动构造函数，那么接受常量左值的构造函数版本也会轻松地实现拷贝构造，因此也不会引起大的问题。**

## 4. [进程见通信](https://www.cnblogs.com/zgq0/p/8780893.html)

## 5. [参看文档](https://en.cppreference.com/w/cpp)

## 6. 静态检查工具

[Cppcheck](http://cppcheck.sourceforge.net/)

## 7. Convert int/float to string

```C++
std::ostringstream ss;
ss << num_reads;
std::cout << ss.str() << std::endl;
ss.str("");
ss.clear();

// 控制精度
ss << std::fixed << std::setprecision(2) << num_reads;
```

## 8. 计算时间差

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

## 9. std::cout

默认情况下只输出小数点后4位, 需要设置精度

## 10. setw、setfill

setw控制符只对后面紧跟的起作用，而setfill控制符一旦设定，就会对后面一直起作用，直到你重新设置。

```cpp
#include <iostream> 
using namespace std; 
#include <iomanip> 
int main() 
{ 
    cout<<setw(8)<<setfill('*')<<123<<endl; 
    cout<<setw(8)<<456<<endl; 
    return 0; 
} 
//输出结果是： 
/*
*****123 
*****456 
*/
//如果只想填满紧跟后面的，必须重新设置： 
#include <iostream> 
using namespace std; 
#include <iomanip> 
int main() 
{ 
    cout<<setw(8)<<setfill('*')<<123<<endl; 
    cout<<setw(8)<<setfill(' ')<<456<<endl; 
    return 0; 
} 
//注意：重新设置的填充符是空格 
//这样运行结果是： 
/*
*****123 
空格456
*/
```

## 11. std::find

```C++
std::vector<int> vec = {1, 2, 3, 4};
// 查找vec中2的位置
const std::vector<int>::iterator itr = std::find(vec.begin(), vec.end(), 2);
```

## 12. std::tuple C++17 不用拆元组, 牛逼

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

## 13. [返回类型自动推导](./返回类型自动推导.cpp)

## 14. 模板变成中, 判断typename类型

```C++
std::is_integral<T>::value
std::is_floating_point<T>::value
```

## 15. template 中的 typename 和 class

typename 和 class 在模板参数列表中没有区别，在 typename 这个关键字出现之前，都是使用 class 来定义模板参数的。但在模板中定义有嵌套依赖类型的变量时，需要用 typename 消除歧义

## 16. override

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

## 17. final

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

## 18. default & delete

允许显式的声明采用或拒绝编译器自带的函数。例如：

```C++
class Magic {
    public:
    Magic() = default; // 显式声明使用编译器生成的构造
    Magic& operator=(const Magic&) = delete; // 显式声明拒绝编译器生成构造
    Magic(int magic_number);
}
```

## 19. [std::move 左值 右值](https://blog.csdn.net/kitekitebaby/article/details/72566145)

## 20. 泛型 Lambda C++14

```C++
auto add = [](auto x, auto y) {
    return x+y;
};

add(1, 2);
add(1.1, 2.2);
```

## 21. cppcheck 静态检查

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

## 22. std::boolalpha

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

## 23. 尽量在类成员函数后面添加const

表示该函数不会修改任何类成员变量, 但可以修改临时变量

## 24. 多尝试使用嵌套类的, 代码会更加可读与简介

```C++
high_five.getGroup(read_id).getAttribute("DateTime").readString(read_start_time);
```

## 25. [使用fork创建子进程](./fork.cpp)

## 26. 使用 `__func__` 与 `__FUNCTION__` 标识当前函数或类

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

## 27. 变长参数的宏定义以及__VA_ARGS__

在C99标准中，程序员可以使用变长参数的宏定义。变长参数的宏定义是指在宏定义中参数列表的最后一个参数为省略号，而预定义宏 `__VA_ARGS__` 则可以在宏定义的实现部分替换省略号所代表的字符串。

```cpp
#include <stdio.h>
#define LOG(...) fprintf(stderr, __VA_ARGS__)
int main() {
    int x = 3;         // 一些 代码...
    LOG("x = %d", x);  // 2- 1- 5. cpp: Line 12: x = 3
}
```

## 28. assert 与 static_assert

- 在C++中，标准在`<cassert>`或`<assert.h>`头文件中为程序员提供了`assert`宏，用于在运行时进行断言,例如: `assert(n > 0)`, 不满足 n > 0的, 就abort. 但assert是一个运行时的断言，这意味着不运行程序我们将无法得知是否不满足条件。在一些情况下，这是不可接受的，因为可能单次运行代码并不会调用到assert相关的代码路径。因此这样的校验最好是在编译时期就能完成。

- [static_assert](https://blog.csdn.net/thesys/article/details/5641350) 是C++的标准语法，不需要引用头文件。而由于static_assert是编译时期的断言，其使用范围不像assert一样受到限制。在通常情况下，static_assert可以用于任何名字空间，

```cpp
#include <iostream>

static_assert(sizeof(int) == 6, "This ....."); // 这里也能运行到

int main() {
    printf("zbz");
}
```

## 29. auto 和 decltype 结合起来

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

## 30. 就地初始化 && 初始化列表

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

## 31. initializer list 使用场景(详见<深入理解C++11>)

- 填空时，默认初始化
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
    int i = {}; // i = 0， 默认初始化
    int j = {5.0}; // 编译错误， 防止类型收窄
}
```

example one

```cpp
class P {
public:
    P(int a, int b){}
    P(initializer_list<int> initlist){}
};

P p(1, 2); // P(int, int)
P q{1, 2}; // P{initializer_list<int>}
P r{1, 2, 3}; // P{initializer_list<int>}
P s={1,2}; // P{initializer_list<int>}
```

example two

```cpp
class P {
public:
    P(int a, int b){}
};

P p(1, 2); // P(int, int)
P q{1, 2}; // P(int, int)
P r{1, 2, 3}; // fail
P s={1,2}; // P(int, int)
```

## 32. 模板编程, 判断输入参数类型

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

## 33. 自动遍历

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

## 34. 自动遍历与手动遍历的区别

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

## 35. terminate, abort, exit, quick_exit, at_quick_exit(深入理解C++11: 6.5)

terminate 函数实际是异常处理的一部分, 没有被捕捉的异常就会导致terminate函数的调用, 在默认情况下会调用abort函数.
abort函数不会调用任何的析构函数, 最好不要用该方法来解决进程
exit 是比较安全的退出函数, 会调用自动变量的析构函数, 并且还会调用atexit注册的函数.
quick_exit 是快速退出, 不会调用析构函数, 但是属于正常退出, 在退出时会调用at_quick_exit注册过的函数

## 36. 线程局部存储 thread_local

即在全局或者静态变量的声明中加上关键字__thread，即可将变量声明为TLS变量。每个线程将拥有独立的errCode的拷贝，一个线程中对errCode的读写并不会影响另外一个线程中的errCode的数据。

## 37. lambda

- lambda 函数在C++11标准中默认是内联的, 如果是频繁调用的小函数, 使用lambda在性能上会有优势
- lambda 函数等同于一个局部函数, 只能在父作用域中使用, 使用场景比如 : 小的函数块(需要被多次调用, 且参数可能较多)只在某个很小的作用域内起作用, 超过这个作用域意义不大
-总的来说，lambda函数被设计的目的，就是要就地书写，就地使用。使用lambda的用户，更倾向于在一个屏幕里看到所有的代码，而不是依靠代码浏览工具在文件间找到函数的实现。
- lambda作为局部函数也会使得复杂代码的开发加速。通过lambda函数，程序员可以轻松地在函数内重用代码，而无需费心设计接口。事实上，曾经出现过一般重构的风潮，在那段时期，C++程序员被建议为任何重用的代码创建函数，而lambda局部函数的到来则带来了理性思考和折中实现的可能。当然，lambda函数的出现也导致了函数的作用域在C++11中再次被细分，从而也使得C++编程具备了更多的可能。

## 38. lambda 与 for_each 应用

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

### 38.1. lambda 用法举例

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

class Person {
public:
    Person(std::string first_name, std::string last_name)
        : first_name_(first_name)
        , last_name_(last_name) {
    }

    std::string first_name() const {
        return first_name_;
    }

    std::string last_name() const {
        return last_name_;
    }

private:
    std::string first_name_;
    std::string last_name_;
};

int main() {
    std::cout << "-- 1 --" << std::endl;
    int id_value = 0;
    int id_ref = 0;
    auto function_value = [id_value]() mutable {  // 必须要有 mutable, 不然无法修改id
        std::cout << id_value << " ";
        id_value++;
    };

    auto function_ref = [&id_ref]() mutable {
        std::cout << id_ref << " ";
        id_ref++;
    };
    id_value = 42;     // lambda 内外对值的修改， 不会相互影响
    function_value();  // 0
    function_value();  // 1  这里输出为1的原因是，lambda 类似于匿名的类成员函数，id_value 作为他的成员变量，之前的改动，会被记录下来
    std::cout << id_value << std::endl;  // 42

    id_ref = 42;                       // lambda 内外对值的修改， 会相互影响
    function_ref();                    // 42
    function_ref();                    // 43
    std::cout << id_ref << std::endl;  // 44

    std::cout << "-- 2 --" << std::endl;
    int min = 3, max = 7;
    std::vector<int> vec_int = {1, 2, 3, 4, 5, 7, 8, 9};
    for (auto i : vec_int)
        std::cout << i << " ";
    std::cout << std::endl;

    // lambda 与 stl 容器一起使用
    vec_int.erase(remove_if(vec_int.begin(), vec_int.end(), [min, max](int n) { return min < n && n < max; }), vec_int.end());
    for (auto i : vec_int)
        std::cout << i << " ";
    std::cout << std::endl;

    std::cout << "-- 3 --" << std::endl;
    auto cmp = [](const Person& p1, const Person& p2) {
        return p1.last_name() < p2.last_name();
    };

    // 该写法是错误的，如使用lambda作为容器的比较函数，声明时，必须将lambda名作为构造参数，而匿名function object则不会出现该问题
    // std::set<Person, decltype(cmp)> set_person;
    std::set<Person, decltype(cmp)> set_person(cmp);
    set_person.emplace("bizhang", "zhou");
    set_person.emplace("shuyang", "liu");
    set_person.emplace("zhongping", "chen");

    for (auto& sp : set_person) {
        std::cout << sp.last_name() << " " << sp.first_name() << std::endl;
    }
    return 0;
}
```

## 39. [[noreturn]]
>>>>>>> Stashed changes

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

## 40. push_back 与 emplace_back

`push_back(A)` 需要先调用构造函数创建A, 然后使用移动构造或者拷贝构造函数添加进容器里
`emplace_back(A)` 只调用一次构造函数, 速度更快

## 41. string size 与 empty

判断string是否为空, 使用 `empty()`, 而不是 `str.size() == 0`

## 42. [内存碎片产生原因及终极解决办法](https://blog.csdn.net/tong5956/article/details/74937178)

1. 内部碎片 : 由于采用固定大小的内存分区，当一个进程不能完全使用分给它的固定内存区域时就产生了内部碎片，通常内部碎片难以完全避免；

2. 外部碎片 : 由于某些未分配的连续内存区域太小，以至于不能满足任意进程的内存分配请求，从而不能被进程利用的内存区域。
现在普遍采用的段页式内存分配方式就是将进程的内存区域分为不同的段，然后将每一段由多个固定大小的页组成。通过页表机制，使段内的页可以不必连续处于同一内存区域，从而减少了外部碎片，然而同一页内仍然可能存在少量的内部碎片，只是一页的内存空间本就较小，从而使可能存在的内部碎片也较少。

一个不断产生内存碎片的系统，不管产生的内存碎片多么小，只要时间 足够长，就会将内存用完。

## 43. 为什么尽量不用 using namespace std;

c++库中的类和函数都是在命名空间std里面声明的，但为什么尽量不用using name std呢？因为不管你是否需不需要，这个命名空间std都会导出命名空间的所有名称，这与命名空间的初衷相矛盾。

```cpp
// 你可以这样写：
using std::cin;
using std::cout;
using std::endl;
// 或者是直接在代码里面这样：
std::cin >> a;
```

## 44. `vector`中`v[i]`与`v.at(i)`的区别

如果v非空，A行和B行没有任何区别。如果v为空，B行会抛出`std::out_of_range`异常，A行的行为未定义。
c++标准不要求`vector<T>::operator[]`进行下标越界检查，原因是为了效率，总是强制下标越界检查会增加程序的性能开销。设计vector是用来代替内置数组的，所以效率问题也应该考虑。不过使用`operator[]`就要自己承担越界风险了。如果需要下标越界检查，请使用at。

```cpp
#include <iostream>
#include <vector>

using namespace std;
int main() {
    vector<int> A = {1, 2, 3};
    cout << A.at[3] << endl; // 编译器报错
    cout << A[3] << endl; // 编译器不报错, 运行期数组越界
}
```

## 45. 如何判断浮点数是否相等

对两个浮点数判断大小和是否相等不能直接用==来判断，会出错！明明相等的两个数比较反而是不相等！对于两个浮点数比较只能通过相减并与预先设定的精度比较，记得要取绝对值。

```cpp
if (fabs(f1 - f2) < 预先指定的精度）
{
    ...
}
```

## 46. 虚函数

在类的成员函数前面加virtual关键字的函数；
一般把虚函数定义在public区，方便在主函数中调用
如果一个类有一个虚函数，则该类就有一个虚函数列表，所有该类的对象都共享这个虚函数表；(QT调试过程中显示的是vptr)
如果一个类有一个或者一个以上的虚函数，则该类有且只有一张虚函数表，每个类都只有一个虚函数表，该类的所有对象都共享这张虚函数表
子类的虚函数表中子类的虚函数覆盖父类的虚函数的情况，当子类将父类的虚函数override时，就覆盖了父类的虚函数；

满足override的条件：函数名相同，函数的返回值相同，形参列表相同；

纯虚函数：形式为virtual void fun1() = 0;
纯虚函数不需要实现，原因是不会被调用到；

抽象基类：至少有一个纯虚函数的类；
抽象基类不能产生该类的对象，但可以有该类的指针或引用；
在子类中必须将父类的纯虚函数实现，不然该子类也是抽象基类；

### 46.1. 不能被子类继承的函数
构造函数、拷贝构造函数、析构函数、赋值运算符重载函数

### 46.2. 哪些函数不能声明成虚函数
非成员函数、构造函数、静态成员函数、内联成员函数、友元函数

### 46.3. 基类的析构函数为什么要用virtual虚析构函数

防止内存泄露，delete p（基类）的时候，它很机智的先执行了派生类的析构函数，然后执行了基类的析构函数。
如果基类的析构函数不是虚函数，在delete p（基类）时，调用析构函数时，只会看指针的数据类型，而不会去看赋值的对象，这样就会造成内存泄露

### 46.4. 虚拟函数表

虚函数表的实现
https://www.cnblogs.com/yinbiao/p/10987640.html

虚拟函数表是在编译期就建立了。
虚拟函数表指针（this）是在执行构造函数的时进行初始化。

### 46.5. 简述多态实现的原理

编译器发现一个类中有虚函数，便会立即为此类生成虚函数表 vtable。虚函数表的各表项为指向对应虚函数的指针。编译器还会在此类中隐含插入一个指针 vptr（对 vc 编译器来说，它插在类的第一个位置上）指向虚函数表。调用此类的构造函数时，在类的构造函数中，编译器会隐含执行 vptr 与 vtable 的关联代码，将 vptr 指向对应的 vtable，将类与此类的 vtable 联系了起来。另外在调用类的构造函数时，指向基础类的指针此时已经变成指向具体的类的 this 指针，这样依靠此 this 指针即可得到正确的 vtable。  

如此才能真正与函数体进行连接，这就是动态联编，实现多态的基本原理。  

注意：一定要区分虚函数，纯虚函数、虚拟继承的关系和区别。牢记虚函数实现原理，因为多态
C++面试的重要考点之一，而虚函数是实现多态的基础。

## 47. 拷贝赋值函数， 应该在函数入口判断是否是自己

如果是自己应该直接返回`*this`

```cpp
MyClass& MyClass::operator=(const MyClass& mc) {
    if (this == &mc)
        return *this;
    ....
}
```

## 48. static
<https://blog.csdn.net/chenyijun/article/details/81938287>  
#### 48.0.1. C语言的static关键字有三种用途，可从两个方面来分析：**1：作用域，2：生存期**
1. 静态局部变量
    1. 该变量在全局数据区分配内存(局部变量在栈区分配内存);
    2. 静态局部变量在程序执行到该对象的声明处时被首次初始化，即以后的函数调用不再进行初始化(局部变量每次函数调用都会被初始化);
    3. 静态局部变量一般在声明处初始化，如果没有显式初始化，会被程序自动初始化为0(局部变量不会被初始化);
    4. 它始终驻留在全局数据区，直到程序运行结束。但其作用域为局部作用域，也就是不能在函数体外面使用它(局部变量在栈区，在函数结束后立即释放内存);
2. 静态全局变量
    1. 定义在函数体外，用于修饰全局变量，表示该变量只在本文件可见
    2. 作用域：该文件内部， 生存期：整个程序运行期间
    3. 静态全局变量不能被其它文件所用(全局变量可以);
    4. 其它文件中可以定义相同名字的变量，不会发生冲突
3. 静态函数
    1. 静态函数跟静态全局变量的作用类似，即静态函数不能被其它文件所用
    2. 其它文件中的可以定义相同的名字的函数，不会发生冲突
    3. 作用域：该文件内部， 生存期：整个程序运行期间

#### 48.0.2. C++ 语言的 static 关键字有二种用途
1. 静态数据成员
    1. 用于修饰 class 的数据成员，即所谓“静态成员”。这种数据成员的生存期大于 class 的对象（实体 instance）。
    2. 静态数据成员是每个 class 有一份，普通数据成员是每个 instance 有一份，因此静态数据成员也叫做类变量，而普通数据成员也叫做实例变量。
2. 静态成员函数
    1. 用于修饰 class 的成员函数。静态函数属于类的，不属于某一个具体的对象。
    2. 访问方式，可以通过对像调用，也可以用类名::函数名进行访问。
    3. 静态成员之间可以相互访问，包括静态成员函数访问静态数据成员和访问静态成员函数;
    4. 非静态成员函数可以任意地访问静态成员函数和静态数据成员;
    5. 静态成员函数不能访问非静态成员函数和非静态数据成员;
    6. 调用静态成员函数，可以用成员访问操作符(.)和(->)为一个类的对象或指向类对象的指针调用静态成员函数,也可以用类名::函数名调用(因为他本来就是属于类的，用类名调用很正常)


```cpp
#include <iostream>

void test_static() {
    static int a = 0;  // 只会声明一次，且在该作用域之类，a会一直存在
    std::cout << ++a << std::endl;
}

int main() {
    test_static();  // 1
    test_static();  // 2
    return 0;
}
```

## 49. `new[] 与 delete[]`

```cpp
#include <iostream>
#include <string>

int main() {
    std::string* str = new std::string[3];

    // delete 只删除了第一个 string， 但是后面两个string没有删除， 导致内存泄漏
    // delete str; // error : invalid pointer
    delete[] str;
    return 0;
}
```

## 50. switch 的 case 中如有变量声明, 需要用括号包起来, 不然会报错

## 51. goto 之后如果有变量声明, 会报错

## 52. float* 与 vector<float> 的转化

```cpp
float* sinal = (float*)malloc(signal_len * sizeof(float));
std::vector<float> signal_data(signal_len, 0);
memcpy(signal_data.data(), signal, signal_len * sizeof(float));
```

## 53. make_shared 初始化

`auto ofm = std::make_shared<OutputFileManager>(result_path_, is_fastq_);`

## 54. 在 main 函数执行前, 还会执行什么代码?

1. 设置栈指针
2. 初始化 static 静态和 global 全局变量，即 data 段的内容
3. 将未初始化部分的全局变量赋初值：数值型 `short，int，long` 等为 `0，bool` 为 FALSE，指针为 NULL，等等，即.bss段的内容
4. 运行全局构造器，估计是C++中构造函数之类的吧
5. 将main函数的参数，`argc，argv` 等传递给main函数，然后才真正运行main函数

## inline 使用

inline是加在实现上，就算加在声明上，编译器也会忽略掉。内联展开是在编译时进行的，只有链接的时候源文件之间才有关系。所以内联要想跨源文件必须把实现写在头文件里。如果一个 `inline` 函数会在多个源文件中被用到，那么必须把它定义在头文件中。

注意：将函数的定义（{…}之间的部分）放在头文件中是强制的，除非该函数仅仅被单个 .cpp 文件使用。尤其是，如果你将内联函数的定义放在 .cpp 文件中并且在其他 .cpp文件中调用它，连接器将给出 `“unresolved external”` 错误。

最佳实践是：**仅把inline关键字放在类外部函数的定义前**。

inline函数的特征是在调用的地方插入相应函数的代码，所以编译之后的目标文件里是没有inline函数体的，因为在要调用的地方它都已经用相应的语句替换掉了（当然这只限于内联成功的情况）。如果我们将inline函数写在cpp文件里，但是绝大多数情况下，在我们用第三方类库的时候，我们只有头文件和目标文件（没有cpp文件），当你调用那个内联函数时，编译器没办法找到它。所以说将inline函数写在cpp文件中是没什么用的。

## `lock_guard, unique_lock`

区域锁`lock_guard`使用起来比较简单，除了构造函数外没有其他 `member function`，在整个区域都有效。

区域锁 `unique_guard` 除了 `lock_guard` 的功能外，提供了更多的 `member_function`，相对来说更灵活一些。

`unique_guard` 可以通过 `lock/unlock` 可以比较灵活的控制锁的范围，减小锁的粒度。

通过 `try_lock_for/try_lock_until` 则可以控制加锁的等待时间，此时这种锁为乐观锁。

## __gnu_cxx 中__pool_alloc内存分配器的使用

__pool_alloc内部使用链表进行管理内存、预分配内存、不归还内存给操作系统等机制来减少malloc的调用次数。

```cpp
#include<iostream>
#include<vector>
#include<string>
#include<ext/pool_allocator.h>

int main()
{
    int nLoop = 0;
    std::cin >> nLoop;
    std::vector<int, __gnu_cxx::__pool_alloc<int> > vec;
    for (int i = 0; i < nLoop; i++) {
        vec.push_back(i);
    }

    std::cout << "allo end\n";
    std::string str;
    std::cin >> str;
    return 0;
}
```

## std::list 排序

list 底层是链表，迭代器不支持随机访问，所以不能外 std::sort 进行排序，必须使用自带的sort函数.
能用自带的 sort，就不用外部的 sort

```cpp
#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

template <typename T>
void MyPrint(T t) {
    for (const auto& i : t) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::list<int> my_list = {3, 1, 2};  // list 不支持随机访问（直接计算迭代器，访问元素）
    my_list.sort();
    MyPrint(my_list);

    std::vector<int> my_vec = {3, 1, 2};
    std::sort(my_vec.begin(), my_vec.end());
    MyPrint(my_vec);
}
```
