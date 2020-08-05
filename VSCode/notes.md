# VSCode 使用分享

## 为什么推荐使用 VSCode

1. 免费, 新功能更新速度快
2. 对 C++, Python, Rust 语言都有较好的支持, 避免多个 IDE 相互切换使用
3. 支持远程编译调试代码
4. 插件丰富, 对 Git, Markdown, CMake 等都有较好的支持
5. 跨平台 Win, Linux, macOS 都有对应的安装包

## VSCode 连接远程服务器进行开发

官方教程 : <https://code.visualstudio.com/docs/remote/ssh>

## VSCode + CMake + C++

官方教程 : https://code.visualstudio.com/docs/cpp/cmake-linux

### C++ debug

<https://code.visualstudio.com/docs/cpp/cmake-linux>
 如调试时, 需要传递参数给 main 函数, 需在 .vscode/settings.json 中加如下配置:

```json
"cmake.debugConfig": {
    "args": ["param1", "param2"]
}
```  

## VSCode + Python

官方教程 : https://code.visualstudio.com/docs/python/python-tutorial

```python
# .vscode/launch.json
{
    "version": "0.2.0",
    "configurations": [
        {
           "name": "Python: Current File",
            "type": "python",
            "request": "launch",
            "program": "${file}",
            "console": "integratedTerminal",
            "args": ["-p/home/zbz/pHMM/tmpdata/rawdata"] // 参数配置
        }
    ]
}
```

## VSCode 常用插件推荐

[常用插件](./VSCode%20常用插件推荐.md)

## VSCode 缺陷

remote x11 配置起来很麻烦  
暂时没有找到方法将远程服务器画出的界面传递出来, 哪位同学如果找到方法, 可以给大家分享一下, 谢谢

## VSCode + Markdown

[Markdown Notes](./Markdown%20Notes.md)

double clicking an element in the Markdown preview will automatically open the editor for the file and scroll to the line nearest the clicked element

## VS Code C++ 编译可以通过，但是有红色波浪线的问题

[配置 c_cpp_properties.json](./VS%20Code%20C++%20编译可以通过，但是有红色波浪线的问题.md)

## Shortcuts

[Shortcut.md](./Shortcut.md)

## 查看 VSCode 内存情况

```sh
Shift + Ctrl + P
input : process explorer
```

## 查看正在运行的插件

```sh
Ctrl + Shift + P
input : Show running extensions
```
