> <https://www.jianshu.com/p/b2883dbf3854>

mutable字面意思是可变的，其实直接定义的local variable都是可变的，所以mutable对于修饰普通的local variable是没有意义的。事实上，编译器会禁止你这么做.

mutable只能用于类成员变量.

在const类或const成员函数中修改一些状态.

经典场景

- mutex, const函数的并发支持

```cpp
#include <mutex>
class A
{
public:
    int get() const
    {
        std::lock_guard<std::mutex> lk(m);
        return value;
    }

    void set(int v)
    {
        value = v;
        return;
    }

private:
    mutable std::mutex m; // 不加mutable，编译就会报错
    int value;
};
int main()
{
    A a;
    return 0;
}
```

- 内部缓存（非类的内部状态）
- lambda表达式
