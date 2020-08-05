# C++标准库

[C++ 标准库概览（一分钟就看完了）](https://www.cnblogs.com/findumars/p/6760029.html)

## [numeric](https://blog.csdn.net/qq_37653144/article/details/80135046)

## algorithm

| Name         | Descriptoin                                                                                                                |
| ------------ | -------------------------------------------------------------------------------------------------------------------------- |
| swap         | 交换                                                                                                                       |
| reverse      | 反转[first, last)区间的数据                                                                                                |
| sort         | sort函数对[first, last)区间的函数进行排序，查看源码可知使用的是快速排序法。                                                |
| partial_sort | [部分排序](http://c.biancheng.net/view/564.html)                                                                           |
| unique       | 从输入序列中“删除”所有相邻的重复元素，并将这些元素移到最后，返回一个迭代器指针，指针指向的正是最后那些重复元素的第一个元素 |

### sort

```C++
template <class RandomAccessIterator, class Compare>
  void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
```

第三个参数`comp`可不写，不写第三个参数的话默认是升序排列。

如果想要降序排列：

1. `sort`之后再使用`reverse`。
2. 将 `greater<int>()` 添加到第三个参数中，注意`greater`函数是在`funtional`头文件中的，如果你要比较的对象是`int`，则尖括号中写`int`，如果不是则写你需要排序的元素的类型。
3. 自己写比较函数，特别是当你排序的元素是结构体或类的对象。

```C++
bool bigger(struct a, struct b)
{
    return (a.score > b.score);
}
struct student{
    string name;
    char gender;
    int score;
    };
vector<student> v;
sort(v.begin(), v.end(), bigger);
```

注意比较函数中的两个参数必须是vector中元素的类型，如此处vector v中的元素是一个struct类型，则比较函数的两个参数也必须是struct类型。
