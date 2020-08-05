#include <iostream>
using namespace std;
class Moveable {
public:
    Moveable()
        : i(new int(3)) {
    }
    ~Moveable() {
        delete i;
    }
    Moveable(const Moveable& m)
        : i(new int(*m.i)) {
        printf("copy constr\n");
    }
    Moveable(Moveable&& m)
        : i(m.i) {
        m.i = nullptr;
        printf("move constr\n");
    }
    int* i;
};

// void test_forward(Moveable t) {
//     printf("value\n");
// }

void test_forward(Moveable& t) {
    printf("lvalue reference\n");
}

void test_forward(Moveable&& t) {
    printf("rvalue reference\n");
}

template <typename T>
void test(T&& t) {
    cout << is_rvalue_reference<decltype(t)>::value << endl;  // 0
    cout << is_lvalue_reference<decltype(t)>::value << endl;  // 1
    test_forward(forward<T>(t));
}

int main() {
    Moveable a;
    // Moveable c(move(a));  // 会调用移动构造函数
    // Moveable cc = move(a);     // 与上面等价
    Moveable&& ccc = move(a);                                   // 不会调用移动构造函数, ccc直接指向a
    cout << is_rvalue_reference<decltype(ccc)>::value << endl;  // 1
    test(ccc);
    // cout << *a.i << endl;  // 运行时 错误
}

// g++ 3-3-6.cpp -fno-elide-constructors