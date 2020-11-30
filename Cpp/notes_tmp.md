## vector

| Function                    | Description                                                        |
| --------------------------- | ------------------------------------------------------------------ |
| size() / resize()           | size是当前vector容器真实占用的大小，也就是容器当前拥有多少个容器。 |
| capacity() / reserve()      | 是指在发生realloc前能允许的最大元素数，即预分配的内存空间。        |
| shrink_to_fit()             | 当总个数确定，但capacity远大于size时，可以考虑缩小预分配空间       |
| begin()                     | 指向第一个元素的迭代器                                             |
| rbegin()                    | 指向最后一个元素的迭代器                                           |
| cbegin()                    | 指向第一个元素的迭代器，是const类型，不能修改迭代器指向的值        |
| emplace_back()              | 避免不必要的临时对象的产生                                         |
| at()                        | 传回索引为index的数据,如果index越界,抛出out_of_range异常           |
| assign(v1.begin(),v1.end()) | 将v1都赋值给容器                                                   |
| assign(10, 0)               | 给vector赋10个为0的值，覆盖原先的内容                              |
| v.data() / &v[0]           | 第一个元素所在的位置（指针）                              |