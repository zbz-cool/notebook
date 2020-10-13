#include "test.hpp"

void test2_print() {
    test_inline();
    std::cout << "test2 print" << std::endl;
    print();

    MyClass mc;
    mc.PrintA();
}