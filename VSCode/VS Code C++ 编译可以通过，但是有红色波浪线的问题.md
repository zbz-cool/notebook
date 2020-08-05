# VS Code C++ 编译可以通过，但是有红色波浪线的问题

## command + p, 然后输入 >C/C++

选择 编辑配置(JSON)

1. Ctrl + Shift + P
2. C/C++: Edit Configurations(JSON)

然后在工作区会出现一个.vscode文件夹, 其中会有一个.json文件的配置

## 打开命令行 输入

```sh
$ gcc-8 -v -E -x c++ - # 会有以下的信息  
#include "..." search starts here:
#include <...> search starts here:
 /usr/include/c++/8
 /usr/include/x86_64-linux-gnu/c++/8
 /usr/include/c++/8/backward
 /usr/lib/gcc/x86_64-linux-gnu/8/include
 /usr/local/include
 /usr/lib/gcc/x86_64-linux-gnu/8/include-fixed
 /usr/include/x86_64-linux-gnu
 /usr/include
End of search list.
```

将上面的头文件路径复制到刚刚的json文件中

如下

```json
{
  "configurations": [
    {
      "name": "Linux",
      "includePath": [
        "${workspaceFolder}/**",
        "/usr/include/c++/8/**",
        "/usr/include/x86_64-linux-gnu/c++/8/**",
        "/usr/include/c++/8/backward/**",
        "/usr/lib/gcc/x86_64-linux-gnu/8/include/**",
        "/usr/local/include/**",
        "/usr/lib/gcc/x86_64-linux-gnu/8/include-fixed/**",
        "/usr/include/x86_64-linux-gnu/**",
        "/usr/include/**"
      ],
      "defines": [],
      "compilerPath": "/usr/bin/g++-8",
      "cStandard": "c11",
      "cppStandard": "c++14",
      "intelliSenseMode": "clang-x64",
      "configurationProvider": "ms-vscode.cmake-tools"
    }
  ],
  "version": 4
}
```

注意要在后面加 /**

然后红色波浪线就不会出现了。
