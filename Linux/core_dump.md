# Linux Core dump

<http://blog.chinaunix.net/uid-26074921-id-2353637.html>
<https://www.cnblogs.com/jefree/p/4439034.html>

```bash
ulimit -c # 如果为0, 表示没有打开
ulimit -c unlimited # 打开core dump

sudo vim /etc/profile # 如果想重启之后有效, 需要修改这个文件
     # 添加 ulimit -S -c unlimited > /dev/null 2>&1
source /etc/profile
```

默认情况下会在可执行程序目录下生成 core 文件  
使用 gdb 的方式来查看错误信息
