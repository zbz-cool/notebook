# scp常规的使用方式

## scp可以进行简单的远程复制文件的功能

它是一个在各个主机之间进行复制或文件传输的一个命令工具。它使用一种同ssh一样的安全机制来进行文件的传输。

注意：下面定义的远程计算机的主机域名是 192.168.1.104， 上传文件的路径是 /usr/local/nginx/html/webs 下面的文件；且 服务器的账号是 root， 那么密码需要自己输入自己的密码即可。

### 从本地上传文件到远程计算机或服务器的命令如下

先进入本地目录下，然后运行如下命令：

```shell
scp my_local_file.zip root@192.168.1.104:/usr/local/nginx/html/webs
```

### 从远程主机复制文件到本地主机(下载)的命令如下：（假如远程文件是about.zip）

先进入本地目录下，然后运行如下命令：

```shell
scp root@192.168.1.104:/usr/local/nginx/html/webs/about.zip .
```

## 多文件传输

### 2-1 从本地文件复制多个文件到远程主机（多个文件使用空格分隔开）

先进入本地目录下，然后运行如下命令：

```shell
scp index.css json.js root@192.168.1.104:/usr/local/nginx/html/webs
```

### 2-2 从远程主机复制多个文件到当前目录

先进入本地目录下，然后运行如下命令：

```shell
scp root@192.168.1.104:/usr/local/nginx/html/webs/\{index.css,json.js\} .
```

## 复制整个文件夹(使用r switch 并且指定目录)

3-1 从本地文件复制整个文件夹到远程主机上（文件夹假如是diff）
先进入本地目录下，然后运行如下命令：

```shell
scp -v -r diff root@192.168.1.104:/usr/local/nginx/html/webs
```

3-2 从远程主机复制整个文件夹到本地目录下（文件夹假如是diff）
先进入本地目录下，然后运行如下命令：

```shell
scp -r root@192.168.1.104:/usr/local/nginx/html/webs/diff .
```

## 在两个远程主机之间复制文件

scp也可以把文件从一个远程主机复制到另一个远程主机上。
如下命令：

```shell
scp root@192.168.1.104:/usr/local/nginx/html/webs/xx.txt root@192.168.1.105:/usr/local/nginx/html/webs/
```

## 使用压缩来加快传输

在文件传输的过程中，我们可以使用压缩文件来加快文件传输，我们可以使用 C选项来启用压缩功能，该文件在传输过程中被压缩，
在目的主机上被解压缩。

如下命令：

```shell
scp -vrC diff root@192.168.1.104:/usr/local/nginx/html/webs
```
