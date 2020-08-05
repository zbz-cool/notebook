> <https://blog.csdn.net/quinta_2018_01_09/article/details/93638251>

RAII是 Resource Acquisition Is Initialization（wiki上面翻译成 “资源获取就是初始化”）的简称，是C++语言的一种管理资源、避免泄漏的惯用法。

如果把资源用类进行封装起来，对资源操作都封装在类的内部，在析构函数中进行释放资源。当定义的局部变量的生命结束时，它的析构函数就会自动的被调用，如此，就不用程序员显示的去调用释放资源的操作了。

经典的用法是std::lock_guard, 在需要保护的资源开头用 std::lock_guard 获得锁, 超出作用域之后, 释放锁
