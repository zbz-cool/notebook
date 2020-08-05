# `C++` 高效的 `string_view`

了解`string`对象的内存分配行为后,接下来我们如何考虑使用什么方法来避免字符串频繁的拷贝,有些经验的“老油条”应该都领略过了`const string&`这类参数类型声明并不能从根本上解决问题（上一篇文章的程序输出已经隐藏地说明了这一点）,因为按引用传参仅能避免了参数传递的字符串拷贝,但在被调用函数内部,只要涉及`string`对象赋值操作，`string`内部仍然执行拷贝依然存在,特别是大字符串的赋值操作会触发堆内存分配,我们知道堆内存管理是一个高时间成本消耗的操作。

`C++`的`string`对象,如果大于默认的字符串长度阀值。对于长度为N的字符串,时间成本为`O(n)`,空间成本是`2xS(n)`;

于是`C++17`就有了`string_view`这个标准库的扩展，这个扩展极大地解决了string拷贝的空间成本和时间成本问题。我们本篇要介绍的是`string_view`是`C++`程序猿在处理字符串操作的一大福音。因为`string_view`基本没有涉及内存的额外分配。

```C++
#include <string>
#include <iostream>
#include <string_view>

void* operator new(std::size_t count){
  std::cout<<"分配了堆内存"<<count<<"字节."<<std::endl;
  return malloc(count);
}

void operator delete(void* p){
   std::cout<<"释放堆内存:"<<p<<std::endl;
   free(p);
}

void show_str(const std::string &str){
   std::cout<<std::endl;
   std::cout<<"show_str()临时变量tmp初始化"<<std::endl;
   std::string tmp=str;
   printf("str副本的地址:%p\n",str.c_str());
   printf("tmp副本的地址:%p\n",tmp.c_str());
}

void show_stv(std::string_view stv){
   printf("string_view对象str的内部地址:%p\n",stv.data());
}

int main(void){
  std::cout<<std::endl;
  std::cout<<"-------初始化string对象-------"<<std::endl;
  std::string you="How do you do~,My name is peter!";
  std::cout<<std::endl;
  
  std::cout<<"-------初始化string_view对象-------"<<std::endl;
  std::string_view stv(you.c_str(),you.size());
  std::cout<<std::endl;
  std::cout<<"---------show_str---------"<<std::endl;
  printf("main函数:you副本中的字符串地址:%p\n",you.c_str());
  show_str(you);

  std::cout<<std::endl;
  std::cout<<"字符串字面量直接传参方式"<<std::endl;
  show_str("How do you do~,My name is peter!");

  std::cout<<std::endl;
  std::cout<<"---------show_stv----------"<<std::endl;
  std::cout<<std::endl;
  std::cout<<"字符串字面量直接传参方式"<<std::endl;
  show_stv(stv);

  std::cout<<std::endl;
  std::cout<<"数组字符串传参方式"<<std::endl;
  show_stv("How do you do~,My name is peter!");

  std::cout<<std::endl;

  return 0; 
}
/*
-------初始化string对象-------
分配了堆内存33字节.

-------初始化string_view对象-------

---------show_str---------
main函数:you副本中的字符串地址:0x7ffff3dec0c0

show_str()临时变量tmp初始化
分配了堆内存33字节.
str副本的地址:0x7ffff3dec0c0
tmp副本的地址:0x7ffff3dec0f0
释放堆内存:0x7ffff3dec0f0

字符串字面量直接传参方式
分配了堆内存33字节.

show_str()临时变量tmp初始化
分配了堆内存33字节.
str副本的地址:0x7ffff3dec0f0
tmp副本的地址:0x7ffff3dec120
释放堆内存:0x7ffff3dec120
释放堆内存:0x7ffff3dec0f0

---------show_stv----------

字符串字面量直接传参方式
string_view对象str的内部地址:0x7ffff3dec0c0

数组字符串传参方式
string_view对象str的内部地址:0x7fb1d3dd40e0

释放堆内存:0x7ffff3dec0c0
*/
```

到这里我们从上图程序输出可以发现,`string_view`对象从初始化到打印几次调用show_stv()函数都无法涉及触发new操作,并且因为`string_view`实际上不持有字符串副本,因此`string_view`从空间成本和时间成本远远胜于string对象。
因为`string_view`内部的私有数据成员_M_str是一个类似C版本的char*指针,该私有数据成员指向初始化`string_view`构造函数的字符串副本的地址。我们向被调用函数传递`string_view`类型的参数，你可以不科学的因为认为如下类似的代码是相当的

`show_stv(std::string_view)`效果相当于`show_stv(char*)`  

因为它们涉及赋值操作的时间成本是`O(1)`,另外,`string_view`内部并不持有一个字符串副本 ,所以涉及空间消耗可以认为`S(1)`.

## `string_view`的适用场合

由于`string_view`对象无法被使用它的函数修改，因此要更新`string_view`所引用的字符串副本,还是需要修改它所引用的string类型的内部字符串副本。

- 字符串查找
- 遍历字符串
- 显示字符串
