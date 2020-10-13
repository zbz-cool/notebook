# 怎么写 hpp 文件

hpp，**其实质就是将.cpp的实现代码混入.h头文件当中，定义与实现都包含在同一文件**，则该类的调用者只需要include该hpp文件即可，无需再将cpp加入到project中进行编译。而实现代码将直接编译到调用者的obj文件中，不再生成单独的obj，采用hpp将大幅度减少调用 project中的cpp文件数与编译次数，也不用再发布烦人的lib与dll，**因此非常适合用来编写公用的开源库。**

## hpp的优点不少，但是编写中有以下几点要注意：

1. 是Header   Plus   Plus 的简写。
2. 与*.h类似，hpp是C++程序头文件 。
3. 是VCL专用的头文件,已预编译。
4. 是一般模板类的头文件。
5. 一般来说，\*.h里面只有声明，没有实现，而\*.hpp里声明实现都有，后者可以减少.cpp的数量。
6. \*.h里面可以有using   namespace   std，而\*.hpp里则无。
7. 不可包含全局对象和全局函数。
    由于hpp本质上是作为.h被调用者include，所以当hpp文件中存在全局对象或者全局函数，而该hpp被多个调用者include时，将在链接时导致符号重定义错误。要避免这种情况，需要去除全局对象，将全局函数封装为类的静态方法。
8、类之间不可循环调用。
9、不可使用静态成员。

## 参考

> <https://blog.csdn.net/follow_blast/article/details/81706698>
> <https://www.cnblogs.com/mydomain/archive/2013/04/06/3001859.html>