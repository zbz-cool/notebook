# Cpp 开发心得

- void 函数, 最后不需要使用return
- 类成员函数, 尽量使用 const(不修改类成员变量), static, override, final等关键词
- 不要在头文件中使用using namespace xxx
- 在构造函数中不使用会出现错误/异常的代码
- 是否可以用template来增加扩展性
- 当函数超过40~60行时, 看是否可以能拆成小函数
- 一些小函数注定不会被重用, 可以用lambda来代替
- 是否有modern C++可以用来更好解决问题
- 组合优于继承
