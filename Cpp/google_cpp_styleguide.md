> <https://github.com/zh-google-styleguide/zh-google-styleguide/tree/master/google-cpp-styleguide>

## 1. 命名

| Name | Style | Example |
| -- | -- | -- |
| 文件名 | 全部小写, 使用下划线连接 | foo_bar.h 和 foo_bar.cc, 对应于类 FooBar |
| 类, 结构体, 类型定义 (typedef), 枚举, 类型模板参数  | 首字母大写的驼峰 | UrlTable |
| 变量名 | 全小写, 下划线连接, 类的成员变量下划线结尾 | a_local_variable<br> a_struct_data_member<br> a_class_data_member_ |
|声明为 constexpr 或 const 的变量|命名时以 "k" 开头, 大小写混合|const int kDaysInAWeek = 7;|
| 头文件的 `#ifdef xxx` 的申明| `_PATH_FILENAME_H_` | |

## 2. 类

- 不要在构造函数中调用**虚函数**, 也不要在无法报出错误时进行可能失败的初始化, 在没有使程序崩溃或者使用异常等方法的条件下, 构造函数很难上报错误
- 不要定义隐式类型转换. 对于转换运算符和单参数构造函数, 请使用 explicit 关键字.
- 如果你的类型需要, 就让它们支持拷贝 / 移动. 否则, 就把隐式产生的拷贝和移动函数禁用.
- 仅当只有数据成员时使用 struct, 其它一概使用 class.
- 使用组合 (YuleFox 注: 这一点也是 GoF 在 Design Patterns 里反复强调的) 常常比使用继承更合理. 如果使用继承的话, 定义为 public 继承.不要过度使用实现继承. 组合常常更合适一些. 尽量做到只在 "是一个" ("is-a", YuleFox 注: 其他 "has-a" 情况下请使用组合) 的情况下使用继承: 如果 Bar 的确 "是一种" Foo, Bar 才能继承 Foo.必要的话, 析构函数声明为 virtual. 如果你的类有虚函数, 则析构函数也应该为虚函数.**避免使用多重继承, 使用时, 除一个基类含有实现外, 其他基类均为纯接口**
- 存取函数一般内联在头文件中
- 声明次序: public -> protected -> private
- 函数体尽量短小, 紧凑, 功能单一
- 不要将大段的函数定义内联在类定义中. 通常，只有那些普通的, 或性能关键且短小的函数可以内联在类定义中.
- 类内部的函数一般会自动内联。所以某函数一旦不需要内联，其定义就不要再放在头文件里，而是放到对应的 .cc 文件里。这样可以保持头文件的类相当精炼，也很好地贯彻了声明与定义分离的原则。

## 头文件

- 包含文件的名称使用 . 和 .. 虽然方便却易混乱, 使用比较完整的项目路径看上去很清晰, 很条理, 包含文件的次序除了美观之外, 最重要的是可以减少隐藏依赖, 使每个头文件在 "最需要编译" (对应源文件处 :D) 的地方编译
- #define 保护, 命名格式当是: `<PROJECT>_<PATH>_<FILE>_H_`, 例如, 项目 foo 中的头文件 foo/src/bar/baz.h 的宏格式为 FOO_BAR_BAZ_H_
- 所有头文件要能够自给自足。换言之，用户和重构工具不需要为特别场合而包含额外的头文件。详言之，统统包含它所需要的其它头文件.
- 尽可能地避免使用前置声明。使用 #include 包含需要的头文件即可
    1. 前置声明隐藏了依赖关系，头文件改动时，用户的代码会跳过必要的重新编译过程。
    2. 前置声明可能会被库的后续更改所破坏。前置声明函数或模板有时会妨碍头文件开发者变动其 API. 例如扩大形参类型，加个自带默认参数的模板形参等等。
    3. 很难判断什么时候该用前置声明，什么时候该用 #include 。极端情况下，用前置声明代替 includes 甚至都会暗暗地改变代码的含义

- 使用标准的头文件包含顺序可增强可读性, 避免隐藏依赖: 相关头文件, C 库, C++ 库, 其他库的 .h, 本项目内的 .h, 例如foo.cpp文件的次序如下:
    1. dir2/foo2.h (优先位置, 详情如下)
    2. C 系统文件
    3. C++ 系统文件
    4. 其他库的 .h 文件
    5. 本项目内 .h 文件

## 函数

- 函数的参数顺序为: 输入参数在先, 后跟输出参数.
- 我们倾向于编写简短, 凝练的函数, 我们承认长函数有时是合理的, 因此并不硬性限制函数的长度. 如果**函数超过 40 行**, 可以思索一下能不能在不影响程序结构的前提下对其进行分割, 即使一个长函数现在工作的非常好, 一旦有人对其修改, 有可能出现新的问题, 甚至导致难以发现的 bug. 使函数尽量简短, 以便于他人阅读和修改代码.
- 所有按引用传递的参数必须加上 const, 事实上这在 Google Code 是一个硬性约定: 输入参数是值参或 const 引用, 输出参数为指针. 输入参数可以是 const 指针, 但决不能是非 const 的引用参数, 除非特殊要求, 比如 swap().

## 其他

- 不成熟的优化诱惑非常大, 而它的无效性也同样严重, 优化的第一原则就是: 不要优化, 第二原则是: 还是不要优化, 再三测试, 而后优化.
- 不要把注意力集中在如何使代码更快上, 首先关注的应该是使代码尽可能地清晰和易读, 清晰的代码更容易正确编写, 更容易理解, 更容易重构, 当然也更容易优化, 使事情复杂的行为, 包括优化, 总是以后再进行的, 而且只在有必要的时候进行.