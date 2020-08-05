# xargs命令详解，xargs与管道的区别

> <https://www.cnblogs.com/wangqiguo/p/6464234.html>

## xargs是什么，与管道有什么不同

```sh
$ echo '--help' | cat
--help

$ echo '--help' | xargs cat
Usage: cat [OPTION]... [FILE]...
Concatenate FILE(s), or standard input, to standard output.

  -A, --show-all           equivalent to -vET
  -b, --number-nonblank    number nonempty output lines
  -e                       equivalent to -vE
  -E, --show-ends          display $ at end of each line
  -n, --number             number all output lines
  -s, --squeeze-blank
```

- 管道传递过来的是标准输入, 类似于 `scanf`
- xargs 传递过来的是参数
