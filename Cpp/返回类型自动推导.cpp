#include <iostream>
#include <tuple>

template <typename R, typename T, typename U>
R add(T x, U y) {
    return x + y;
}

// C++11 还引入了一个叫做尾返回类型（trailing return type）
// 利用 auto 关键字将返回类型后置
template <typename T, typename U>
auto add2(T x, U y) -> decltype(x + y) {
    return x + y;
}

// 令人欣慰的是从 C++14 开始是可以直接让普通函数具备返回值推导，因此下面的写法变得合法：
template <typename T, typename U>
auto add3(T x, U y) {
    return x + y;
}

int main() {
    // before c++11
    auto a = add<double, int, double>(1, 2.0);
    std::cout << a << std::endl;

    // after c++11
    auto w = add2<int, double>(1, 2.0);
    if (std::is_same<decltype(w), double>::value) {
        std::cout << "w is double: ";
    }
    std::cout << w << std::endl;

    // after c++14
    auto q = add3<double, int>(1.0, 2);
    std::cout << "q: " << q << std::endl;

    // 也可以不指定类型
    auto z = add3(2.1, 2);
    std::cout << "q: " << z << std::endl;

    return 0;
}
