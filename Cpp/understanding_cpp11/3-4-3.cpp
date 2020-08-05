#include <iostream>

class ConvertTo {};
class Convertable {
public:
    explicit operator ConvertTo() const {
        return ConvertTo();
    }
};
void Func(ConvertTo ct) {
}
void test() {
    Convertable c;
    ConvertTo ct(c);  // 直接 初始化， 通过
    // ConvertTo ct2 = c;                          // 拷贝 构造 初始化， 编译 失败
    ConvertTo ct3 = static_cast<ConvertTo>(c);  // 强制 转化， 通过
    // Func(c);                                    // 拷贝 构造 初始化， 编译 失败
}