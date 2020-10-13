#ifndef __TEST__
#define __TEST__

#include <iostream>

// int a = 0;
/* 不可包含全局对象和全局函数
由于hpp本质上是作为.h被调用者include，所以当hpp文件中存在全局对象或者全局函数，
而该hpp被多个调用者include时，将在链接时导致符号重定义错误。要避免这种情况，
需要去除全局对象，将全局函数封装为类的静态方法。
*/

//void test() {  // 直接在头文件中定义函数, 如果有多个cpp会include该头文件, 那么再链接阶段, 会出现重复定义的问题
    // to do something
//}

void test2_print(); // 将声明和定义分开, 就不会出现该问题

inline void test_inline() {  // 定义成inline函数, 不会出现重复定义的问题
    std::cout << "test_inline" << std::endl;
}

static void print() { // 定义成静态函数, 不会出现重复定义的问题
    std::cout << "include print" << std::endl;
}

class MyClass {
public:
    void PrintA() {
        static int C = 0; // 成员函数内的静态变量, 可以直接初始化
        C++;
        std::cout << "A : " << A << " C : " << C << std::endl;
        A++;
    }

private:
    // 类的静态变量, 必须在类外做初始化, 如果在头文件中初始化, 会出现重复定义的错误
    // 如果实在没办法, 可以将A再某个cpp中定义
    static int A; 
    const static int B = 0; // 常量静态变量, 可以在类内直接初始化
};

#endif
