// https://www.jianshu.com/p/e5b781275ba9

#include <iostream>
#include <vector>
#include <initializer_list>

template <class T>
struct S {
    std::vector<T> v;

    S(std::initializer_list<T> l)
        : v(l) {
        std::cout << "constructed with a " << l.size() << "-element list\n";
    }

    void append(std::initializer_list<T> l) {
        v.insert(v.end(), l.begin(), l.end());
    }

    void print() {
        for (auto& tmp : v) {
            std::cout << tmp << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    S<int> list_int = {1, 2, 3, 4, 5}; // 复制初始化
    list_int.append({6, 7, 8});        // 函数调用中的列表初始化
    list_int.print();

    S<std::string> list_str = {"zbz", "lsy"};
    list_str.append({"haode", "zzz"});
    list_str.print();
}