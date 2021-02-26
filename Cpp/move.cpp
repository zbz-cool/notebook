// C++ 的 move 语义与编译器优化

// https://blog.liangqin.ren/2021/03/c-%E7%9A%84-move-%E8%AF%AD%E4%B9%89%E4%B8%8E%E7%BC%96%E8%AF%91%E5%99%A8%E4%BC%98%E5%8C%96/

#include <string>
#include <vector>
#include <iostream>

int main() {
    std::string A(100000, '#');
    std::vector<std::string> from;
    for (int i = 0; i < 50000; i++) {
        from.push_back(A);
    }

    std::vector<std::string> to;
    for (int i = 0; i < 50000; i++) {
        // copy
        // to.push_back(from[i]); // 2.947
        // to.emplace_back(from[i]); // 2.9
        
        // move
        // to.emplace_back(std::move(from[i])); // 1.413
    }
}