# std::optional

> <https://blog.csdn.net/janeqi1987/article/details/100567933>
> <https://zhuanlan.zhihu.com/p/57500660>
> <https://zh.cppreference.com/w/cpp/utility/optional>

场景：如果有这样一个函数，通过返回值来判断计算结果是否有效，如果结果有效，才能使用结果。

例如：计算a、b相除。b有可能为0，所以需要考虑相除结果是否有效。

```C++
bool div_int(int a, int b, int &result) {
    if (b == 0) {
        return false;
    }
    result = a / b;
    return true;
}

TEST_F(before_optional) {
    int result = 0; // 接收结果
    auto ret = div_int(2, 1, result);
    ASSERT(ret);
    ASSERT_EQ(2, result); // 如果返回值为true, 结果才有效

    auto b = div_int(2, 0, result);
    ASSERT(!b);
}
```

这样的使用方式很不方便，需要两个变量来描述结果。这种场景下应该使用c++17中的std::optional。我们用std::optional改写上面这个例子：

//div_int可以通过optional优化：optional中，结果是否有效和结果都保存在其中

```C++
#include <iostream>
#include <optional>

std::optional<int> div_int(int a, int b) {
    if (b != 0)
        return std::make_optional<int>(a / b);
    return {};
}

int main() {
    auto div = [](int a, int b) {
        std::optional<int> results;
        if (false != (results = div_int(a, b)).has_value())
            std::cout << results.value() << std::endl;
        else
            printf("error\n");
    };
    div(10, 4);  // 2
    div(10, 0);  // error
}
```

如果开发项目中没有支持到c++17可以用boost库中的optional。
