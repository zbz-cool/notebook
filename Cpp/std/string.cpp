#include <string>
#include <iostream>

int main()
{
    // 查找子串
    std::string str = "hello world";
    std::cout << str.find("lo") << std::endl;
    std::cout << str.find("zbz") << std::endl;
    std::cout << std::boolalpha << (str.find("zbz") == std::string::npos) << std::endl;  // 找不到子串时, 返回std::string::npos

    // string& insert (size_t pos, const string& str); // 在 pos - 1 的位置插入子串, 会修改父串
    std::cout << str.insert(str.size(), "zbz") << std::endl; //
    std::cout << str.insert(str.find_last_of(' '), "zbz") << std::endl;

    str = "1010.9999";  // 会直接删除小数点
    int a = stoi(str);
    std::cout << a << std::endl;
}