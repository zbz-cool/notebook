// g++-8 test.cpp -fno-elide-constructors  -o test
#include <iostream>
using namespace std;
struct Copyable {
    Copyable() {
    }
    Copyable(const Copyable& o) {
        cout << "Copied" << endl;
    }
};
Copyable ReturnRvalue() {
    return Copyable();
}
void AcceptVal(Copyable) {
}
void AcceptRef(const Copyable&) {
}
int main() {
    cout << "Pass by value: " << endl;
    AcceptVal(ReturnRvalue());  // 临 时值 被 拷贝 传入
    cout << "Pass by reference: " << endl;
    AcceptRef(ReturnRvalue());  // 临 时值 被 作为 引用 传递
}
