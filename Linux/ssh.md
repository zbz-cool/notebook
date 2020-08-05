# SSH

## SSH 安装

如果只是想远程登陆别的机器只需要安装客户端（Ubuntu默认安装了客户端），如果要开放本机的SSH服务就需要安装服务器。

```shell
sudo apt-get install openssh-client
sudo apt-get install openssh-server
```

## 口令登录

口令登录非常简单，只需要一条命令，命令格式为： ssh 客户端用户名@服务器ip地址  eg:

```shell
ssh ldz@192.168.0.1
```

如果需要调用图形界面程序可以使用 -X 选项

```shell
ssh -X ldz@192.168.0.1
```

如果客户机的用户名和服务器的用户名相同，登录时可以省略用户名。

```shell
ssh 192.168.0.1
```

还要说明的是，SSH服务的默认端口是22，也就是说，如果你不设置端口的话登录请求会自动送到远程主机的22端口。我们可以使用 -p 选项来修改端口号，比如连接到服务器的1234端口：

```shell
ssh -p 1234 ldz@192.168.0.1
```

## 在本机生成密钥对

使用ssh-keygen命令生成密钥对：

```shell
ssh-keygen -t rsa   #-t表示类型选项，这里采用rsa加密算法
```

然后根据提示一步步的按enter键即可（其中有一个提示是要求设置私钥口令passphrase，不设置则为空，这里看心情吧，如果不放心私钥的安全可以设置一下），执行结束以后会在 /home/当前用户 目录下生成一个 .ssh 文件夹,其中包含私钥文件 id_rsa 和公钥文件 id_rsa.pub。

## 将公钥复制到远程主机中

使用ssh-copy-id命令将公钥复制到远程主机。ssh-copy-id会将公钥写到远程主机的 ~/ .ssh/authorized_key 文件中

```shell
ssh-copy-id ldz@192.168.0.1
```
