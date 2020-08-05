# list

## splice

实现list拼接的功能。将源list的内容部分或全部元素删除，拼插入到目的list, 函数有以下三种声明

```C++
void splice(iterator position, list<T, Allocator> &x);
void splice(iterator position, list<T, Allocator> &x, iterator i);
void splice(iterator position, list<T, Allocator> &x, iterator first, iterator last);
```

- 函数说明

将x的元素移动到目的list的指定位置，高效的将他们插入到目的list并从x中删除。目的list的大小会增加，增加的大小为插入元素的大小。x的大小相应的会减少同样的大小。

前两个函数不会涉及到元素的创建或销毁, 第三个函数会, 指向被删除元素的迭代器会失效。

| 参数 | 说明 |
| -- | -- |
| position | 目的list的位置，用来标明 插入位置|
| x | 源list|
| first, last | x 里需要被移动的元素的迭代器。区间为[first, last). 包含first指向的元素，不包含last指向的元素。|

```C++
#include <iostream>
#include <list>
#include <algorithm>

using std::cout;
using std::endl;
using std::list;

template <typename T>
class print
{
public:
    void operator()(const T &iter) const
    {
        cout << iter << " ";
        return;
    }
};

void list_splice()
{
    std::list<int> mylist1 = {1, 2, 3, 4}, mylist2 = {10, 20, 30};
    std::list<int>::iterator it;

    it = mylist1.begin();
    ++it; // points to 2

    mylist1.splice(it, mylist2);

    std::for_each(mylist1.begin(), mylist1.end(), print<int>());  // mylist1: 1 10 20 30 2 3 4
    std::cout << endl;

    std::for_each(mylist2.begin(), mylist2.end(), print<int>()); // mylist2 (empty)
    std::cout << endl;

    // "it" still points to 2 (the 5th element) 此处的it由于是指向的mylist1,splice后，此迭代器依然存在于mylist1中, 故而不失效
    // 而后面的splice，由于it指向的地址被插入到mylist2中，而使迭代器it失效

    mylist2.splice(mylist2.begin(), mylist1, it);
    // mylist1: 1 10 20 30 3 4
    // mylist2: 2
    // "it" is now invalid.

    it = mylist1.begin();
    std::advance(it, 3); // "it" points now to 30

    // 注意此处mylist前后交换了，这可以用作list形如循环移位的操作
    mylist1.splice(mylist1.begin(), mylist1, it, mylist1.end()); // mylist1: 30 3 4 1 10 20

    std::cout << "mylist1 contains : ";
    std::for_each(mylist1.begin(), mylist1.end(), print<int>());
    std::cout << '\n';

    std::cout << "mylist2 contains : ";
    std::for_each(mylist2.begin(), mylist2.end(), print<int>());
    std::cout << '\n';
}

int main()
{
    // list_splice();
    list_splice();
    return 0;
}
```
