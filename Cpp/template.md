## template 基本语法

- C++98不支持函数模板的默认模板参数, 但在C++11开始这一限制被解除
- 类模板的默认模板参数必须遵照"从右往左"的顺序, 但函数模板不存在这个限制
- 模板的变化多样性是由于将类型被当成了参数, 但这种"变化"实际上在代码编译好后就固定下来了，可以称之为编译期的可变性。
- 由于C++11正式废弃“模板导出”这一特性，因此在模板类的变量在调用成员函数的时候，需要看到完整的成员函数定义。因此现在的模板类中的成员函数，通常都是以内联的方式实现。当然，我们也可以将 `vector<T>::clear` 的定义部分放在类型之外，只不过这个时候的语法就显得蹩脚许多. 例如：

```cpp
template <typename T>
class vector {
public:
    void clear() {
        // Function body
    }
private:
    T* elements;
};
```

- 编译器可以一定程度上推导模板类型

```cpp
template <typename T> T Add(T a, T b) {
    return a + b;
}

Add<int>(3, 4); // 正确
Add(3, 4); // 正确
```

- 但编译器是没办法去根据返回值推断类型

```cpp
float data[1024];

template <typename T> T GetValue(int i)
{
    return static_cast<T>(data[i]);
}

float a = GetValue(0); // 出错了！
int b = GetValue(1); // 也出错了！
GetValue<float>(1); // 正确
```

- C++支持部分模板参数自动推导, 但必须**先写需要指定的模板参数，再把能推导出来的模板参数放在后面**

```cpp
template <typename DstT, typename SrcT> DstT c_style_cast(SrcT v) // 模板参数 DstT 需要人肉指定，放前面。
{
    return (DstT)(v);
}

int v = 0;
// 形象地说，DstT会先把你指定的参数吃掉，剩下的就交给编译器从函数参数列表中推导啦。
float i = c_style_cast<float>(v);
```

- 模板还可以接收整数

这里的整型数比较宽泛，包括布尔型，不同位数、有无符号的整型，甚至包括指针;  
其中有一点需要注意，因为模板的匹配是在编译的时候完成的，所以实例化模板的时候所使用的参数，也必须要在编译期就能确定。

```cpp
#include <iostream>
#include <algorithm>
#include <vector>

template <typename T, int Size>
void test1() {
    std::vector<T> data(Size, 0);
    for_each(data.begin(), data.end(), [](auto& e) { std::cout << e << " "; });
    std::cout << std::endl;
}

int main() {
    int a = 6;
    test1<int, a>();  // 编译失败, 不能在编译器确定
    test1<int, 6>();  // 有时候想通过传参的方式来申请list的长度, 那么可以用模板的方式来实现

}
```

## 特化

- 特化的作用 : 根据类型的if else效率低, 编译了很多无用的代码, 模板特化可以指导编译器根据不同的类型编译不同的代码. 使用重载(函数名相同, 但参数类型, 个数不同)可以一定程度上解决这个问题, 但是重载函数必须指定具体的类型, 如果类型种类非常多, 重载起来就很痛苦了.

- 元编程意味着你撰写一段程序A，程序A会运行后生成另外一个程序B，程序B才是真正实现功能的程序。那么这个时候程序A可以称作程序B的元程序，撰写程序A的过程，就称之为“元编程”。
- 找出程序之间的相似性，进行“元编程”。而在C++中，元编程的手段，可以是宏，也可以是模板。

- 类特化例子

```cpp
#include <iostream>
template <typename T>
class Test {
public:
    static void test_template() {
        printf("default\n");
    }
};

template <>
class Test<int> {
public:
    static void test_template() {
        printf("int\n");
    }
};

int main() {
    Test<int>::test_template(); // 根据类型执行不同代码, 避免运行期判断
    Test<float>::test_template();
}
```

- 函数特化例子

```cpp
#include <iostream>
template <typename T>
void test_template() {
    printf("default\n");
}

template <>
void test_template<int>() {
    printf("int\n");
}

int main() {
    test_template<int>();
    test_template<float>();
}
```

- 类模板和类模板的特化的作用，仅仅是指导编译器选择哪个编译，但是特化之间、特化和它原型的类模板之间，是分别独立实现的。所以如果多个特化、或者特化和对应的类模板有着类似的内容，很不好意思，你得写上若干遍了。

```cpp
template <typename T> class TypeToID
{
public:
    static int const NotID = -2;
};

template <> class TypeToID<float>
{
public:
    static int const ID = 1;
};

void PrintID()
{
    cout << "ID of float: " << TypeToID<float>::ID << endl;       // Print "1"
    cout << "NotID of float: " << TypeToID<float>::NotID << endl; // Error! TypeToID<float>使用的特化的类，这个类的实现没有NotID这个成员。
    cout << "ID of double: " << TypeToID<double>::ID << endl;     // Error! TypeToID<double>是由模板类实例化出来的，它只有NotID，没有ID这个成员。
}
```

- 模板是从最特殊到最一般形式进行匹配的

虽然下面代码中 `int*` 匹配 `T*` 也是合理的, 但是模板的匹配规则是**从最特殊到最一般**, 所以会优先匹配 `int*`

```cpp
// ...
// TypeToID 的其他代码，略过不表
// ...

template <typename T> // 嗯，需要一个T
class TypeToID<T*>    // 我要对所有的指针类型特化，所以这里就写T*
{
public:
    typedef T SameAsT;
    static int const ID = 0x80000000; // 用最高位表示它是一个指针
};

template <> // 嗯，int* 已经是个具体的不能再具体的类型了，所以模板不需要额外的类型参数了
class TypeToID<int*> // 嗯，对int*的特化。在这里呢，要把int*整体看作一个类型
{
public:
    static int const ID = 0x12345678; // 给一个缺心眼的ID
};

void PrintID()
{
    cout << "ID of int*: " << TypeToID<int*>::ID << endl;  // 输出 0x12345678
}
```

## 剥离类型的指针属性

`typedef typename RemovePointer<T>::Result Result;` 这条语句中包含了 `typename`, 一般情况下是不需要的, 但是如果模板具有复杂的类型设置, 就需要了.

```cpp
#include <iostream>

template <typename T>
class RemovePointer {
public:
    typedef T Result;  // 如果放进来的不是一个指针，那么它就是我们要的结果。
};

template <typename T>
class RemovePointer<T*>  // 祖传牛皮藓，专治各类指针
{
public:
    ////////********////////
    typedef typename RemovePointer<T>::Result Result;  // 正如我们刚刚讲的，去掉一层指针，把 T* 这里的 T 取出来。
};

void Foo() {
    // 如果是传进来的是一个指针，我们就剥夺一层，直到指针形式不存在为止。
    // 例如 RemovePointer<int**>，Result 是 RemovePointer<int*>::Result，
    // 而 RemovePointer<int*>::Result 又是 int，最终就变成了我们想要的 int，其它也是类似。
    RemovePointer<float****>::Result x = 5.0f;
    std::cout << x << std::endl;
}

int main(int argc, char const* argv[]) {
    Foo();
    return 0;
}
```

## C++98 实现变参模板

这时只能使用具有默认值的模板参数 `typename T1 = void` 来实现了

```cpp
template <typename T0, typename T1 = void> struct DoWork;

template <typename T> struct DoWork<T> {};
template <>           struct DoWork<int> {};
template <>           struct DoWork<float> {};
template <>           struct DoWork<int, int> {};

DoWork<int> i;
DoWork<float> f;
DoWork<double> d;
DoWork<int, int> ii;
```

## C++11 实现变参模板

`typename... Ts` 相当于一个声明，是说 `Ts` 不是一个类型，而是一个不定常的类型列表。同C语言的不定长参数一样，它通常只能放在参数列表的最后。看下面的例子：

```cpp
template <typename... Ts, typename U> class X {};              // (1) error!
template <typename... Ts>             class Y {};              // (2)
template <typename... Ts, typename U> class Y<U, Ts...> {};    // (3)
template <typename... Ts, typename U> class Y<Ts..., U> {};    // (4) error!
```

为什么第(1)条语句会出错呢？(1)是模板原型，模板实例化时，要以它为基础和实例化时的类型实参相匹配。因为C++的模板是自左向右匹配的，所以不定长参数只能结尾。其他形式，无论写作Ts, U，或者是Ts, V, Us,，或者是V, Ts, Us都是不可取的。(4) 也存在同样的问题。

但是，为什么(3)中， 模板参数和(1)相同，都是typename... Ts, typename U，但是编译器却并没有报错呢？

答案在这一节的早些时候。(3)和(1)不同，它并不是模板的原型，它只是Y的一个偏特化。回顾我们在之前所提到的，偏特化时，模板参数列表并不代表匹配顺序，它们只是为偏特化的模式提供的声明，也就是说，它们的匹配顺序，只是按照<U, Ts...>来，而之前的参数只是告诉你Ts是一个类型列表，而U是一个类型，排名不分先后。

- 例子

> <https://www.cnblogs.com/qicosmos/p/4325949.html>

```cpp
#include <iostream>

template <typename... Args>
auto average(Args... t) {
    return (t + ...) / sizeof...(t);
}

template <typename T, typename... Args>
auto is_one_of(T c, Args... x) {
    return ((c == x) || ...);
}

int main() {
    std::cout << average(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) << std::endl;
    std::cout << std::boolalpha << is_one_of<char>('a', 'a', 'c') << std::endl;
    std::cout << std::boolalpha << is_one_of<int>(3, 3, 4) << std::endl;
    return 0;
}
```

## 外部模板

`extern template void fun<int>(int);` 外部模板与外部变量非常类似, C++11中“模板的显式实例化定义、外部模板声明和使用”好比“全局变量的定义、外部声明和使用”方式的再次应用。不过相比于外部变量声明，不使用外部模板声明并不会导致任何问题。如我们在本节开始讲到的，外部模板定义更应该算作一种针对编译器的编译时间及空间的优化手段。很多时候，由于程序员低估了模板实例化展开的开销，因此大量的模板使用会在代码中产生大量的冗余。这种冗余，有的时候已经使得编译器和链接器力不从心。但这并不意味着程序员需要为四五十行的代码写很多显式模板声明及外部模板声明。只有在项目比较大的情况下。我们才建议用户进行这样的优化。总的来说，就是在既不忽视模板实例化产生的编译及链接开销的同时，也不要过分担心模板展开的开销。
