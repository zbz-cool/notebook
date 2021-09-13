# core dump

```bash
ulimit -c # 查询, 如果是 0, 说明没有打开
ulimit -c unlimited # 打开
ulimit -c 0 # 关闭
```

```bash
# 编译时需要需要加参数 -g
gdb exe core # 启动 gdb 调试, 进入调试环境
bt # 打印调用栈
up # 切换到上级栈
down # 切换到下级栈
```