## using 与 typedef 都可以用来设置别名, using的使用更加直观

```cpp
#include <vector>
#include <iostream>
#include <list>
#include <queue>

template <typename T>
void test_2(T value) {
    typedef std::vector<T> VV;  // 使用typedef
    VV vv = {value};
    std::cout << "vv : " << vv[0] << std::endl;

    using V = std::vector<T>;  // 使用using
    V v = {value};
    std::cout << "v : " << v[0] << std::endl;
    return;
}

int main() {
    // stypedef 与 using 都可以用来设置别名, 下面这种方式是等价的.
    typedef unsigned long long uint64;
    using uint64 = unsigned long long;
    test_2<int>(4);
    return 0;
}
```

## 另外using还可以用于继承基类的构造函数

```cpp
#include <iostream>
struct A {
    A(int i) {
        std::cout << "A::i " << i << std::endl;
    }
    A(double d, int i) {
        std::cout << "A::d " << i << " A::i " << i << std::endl;
    }
    A(float f, int i, const char* c) {
        std::cout << "A::f " << f << " A::i " << i << " A::c " << c << std::endl;
    }

    void function(int i) {
        printf("A::function\n");
    }
};

struct B : A {
    using A::A;         // 使用 using 继承基类构造函数
    using A::function;  // 使用 using 直接使用基类方法
    void function(double i) {
        printf("B::function\n");
    }
    int d{0};  // 就地初始化
};

int main() {
    B b(356);  // b.d 被初始化为0
    B bb(3.4, 3);
    B bbb(3.2, 4, "zfdf");
    b.function(2);
    b.function(2.1);
}
/*
A::i 356
A::d 3 A::i 3
A::f 3.2 A::i 4 A::c zfdf
A::function
B::function
*/
```
