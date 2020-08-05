# Linux 启动进程的三种方式

## system函数-调用shell进程，开启新进程

system函数，是通过启动shell进程，然后执行shell命令进程。

## exec系列函数-替换进程映像

exec系列函数调用时，启动新进程，替换掉当前进程。即程序不会再返回到原进程，
除非exec调用失败。

## fork

fork和exec的替换不同，调用fork函数，可复制一个和父进程一模一样的子进程。
执行的代码也完全相同，但子进程有自己的数据空间，环境和文件描述符。

> <https://www.cnblogs.com/shijingjing07/p/5647788.html>
