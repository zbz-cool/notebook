## 1. grep

- `command | grep xxx`
- `grep xxx file` 搜索file中xxx
- `grep -R xxx *` 递归搜索当前目录及子目录下包含xxx的地方

## 2. 通用

- `time command` # command 执行所耗的时间
- `md5sum file` # MD5算法常常被用来验证网络文件传输的完整性，防止文件被人篡改
- `watch`

```sh
watch -n x # 缺省每2秒运行一下程序，可以用-n或-interval来指定间隔的时间。
watch -t # 会关闭watch命令在顶部的时间间隔,命令，当前时间的输出。
watch -d # 选项watch 会高亮显示变化的区域。

watch -n 1 -d netstat -ant # 例如 ：每隔一秒高亮显示网络链接数的变化情况
```

## 3. 磁盘

- `sudo fdisk -l` 查看所有的磁盘
- `mount -t vfat /dev/sdb1 /media` 运行挂载命令

## 4. 账号

```sh
sudo adduser zbz # 创建

# 设置权限
$ sudo vim /etc/sudoers # 添加信息
zbz ALL=(ALL:ALL) ALL
```

## 5. 端口

```sh
netstat -nupl # UDP类型的端口
netstat -ntpl # TCP类型的端口
```

## 6. 进程

- `top`
- `ps -aux | grep base` 查询***进程的详细信息
- `ps -ef | grep xxx` 查询所有进程, 以及父子关系
- `nohup`

```sh
nohup command > log.txt 2>&1 &
nohup command > /dev/null 2>&1 & # 表示不输出
```

- `cat /proc/xxx/status` 参看实际内存, VmRss 为真实的内存使用
- `fuser` 可用于查询文件、目录、socket端口和文件系统的使用进程，并且可以使用 `fuser` 关闭进程, 例如查询显卡使用情况 `sudo fuser -v /dev/nvidia*`

## 7. package

- apt-get

```sh
sudo apt-get install package # 安装包
sudo apt-get install package - - reinstall # 重新安装包
sudo apt-get -f install 修复安装"-f = ――fix-missing"
sudo apt-get remove package 删除包
sudo apt-get remove package - - purge 删除包，包括删除配置文件等
sudo apt-get update 更新源
sudo apt-get upgrade 更新已安装的包
```

- dpkg

```sh
dpkg -l | less # 查看本机安装了哪些包
dpkg -L xxx  # 查看包的安装信息
```

## 8. 文件查看 && 读写

- nano

```sh
1) CTRL-O # 保存
2) Enter # 确认文件名
3) CTRL-X # 退出
```

- du && ls && wc

```sh
du -h xxx # 插件该文件或目录的详细大小
ls -h -al
du -sh # 查看当前文件夹的总大小
du -sh * # 查看当前文件夹下每个文件的大小
du -sh * | sort -n 统计当前文件夹(目录)大小，并按文件大小排序
du -sk filename 查看指定文件大小
ls -l | grep "^-" | wc -l # "^-" 过滤一般文件, 如果只保留目录就是 "^d"

du -sh * # 不能显示隐藏的文件或文件夹。你可以使用 --max-depth（简写为 -d）参数来控制显示层级而不使用 -s 。
du -h -d 1
```

## 9. 环境变量

- 加载顺序 `bashrc, profile`

> <https://blog.csdn.net/pengjunlee/article/details/81585726>
> <https://blog.csdn.net/duzilonglove/article/details/79729840>

```sh
# 一般情况下，Linux 加载环境变量配置文件的执行顺序为：
==> /etc/profile
==> ~/.bash_profile | ~/.bash_login | ~/.profile
==> ~/.bashrc
==> /etc/bashrc
==> ~/.bash_logout
```

- 查看与设置

```sh
export # 查看所有环境变量
echo $tmp # 查看 tmp 的值
unset tmp # 清空 tmp 的值
```

## 10. 可执行程序

```sh
ldd exe # 查看依赖共享库

export LD_LIBRARY_PATH="$LD_LIBRARY_PATH:/path/lib_so" # 设置共享库的位置

patchelf --shrink-rpath basecaller # 清除已有路径
patchelf --set-rpath '$ORIGIN/lib_thirdparty' basecaller # 设置路径
readelf -d ./release/basecaller | grep ORIGIN # 查看路径
ldd basecaller # 查看所有依赖库的情况
./basecaller # 测试运行
```

## 11. 查看系统信息

- `which` : 查询某个命令所在目录
- `nvidia-smi` ：查看显卡
- `cat /etc/issue` 或 `uname -a` ：发行版
- `cat /proc/cpuinfo` ：cpu 信息
- `free` : 内存
- `ls -R` ：递归罗列出文件
- `cat /etc/passwd | awk  -F ':'  '{print $1}'` # 分隔符
- `pwd -P` # 显示出实际路径，而非使用连接（link）路径；pwd显示的是连接路径
- `history`

```sh
# bash中默认命令记忆可达1000个。这些命令保存在主文件夹内的.bash_history中.
# ~/.bash_history：记录的是前一次登录以前所执行过的命令。至于本次登录的命令暂时存储在内存中，注销成功后会写入文件中。

history n  # 显示最后n条历史记录
history -c # 将目前shell中的所有history命令消除。对命令历史文件没有影响
history -w # 将本次登录的命令写入命令历史文件中, 默认写入~/.bash_history。
history -r # 将命令历史文件中的内容读入到目前shell的history记忆中。
```

- ls

```sh
1、ls -R

ls 递归列出文件

ls  -lS  # 以文件大小排序(升序和降序)#默认降序排序
ls -h # 将文件内容大小以GB、KB等易读的方式显示
ls -a/-A # --all的缩写，显示所有的文件，包括隐藏文件
```

## 12. 代理

- 本地虚拟机设置代理

```sh
$ vim ~/.bashrc
export ALL_PROXY="socks://192.168.2.123:7890/"
export all_proxy="socks://192.168.2.123:7890/"
export ftp_proxy="ftp://192.168.2.123:7890/"
export http_proxy="http://192.168.2.123:7890/"
export https_proxy="https://192.168.2.123:7890/"
export socks_proxy="socks://192.168.2.123:7890/"
$ source ~/.bashrc
```

## 13. Terminal 显示修改

- Terminal 文件显示背景

```sh
# 在linux下, 如果某个文件夹是777 权限, 则背景为蓝色.
cd ~
dircolors -p > .dircolors
vim .dircolors
# 修改 OTHER_WRITABLE 34;42 为 34:49;01
# 重新打开 terminal
# https://blog.csdn.net/gengli2017/article/details/82917827
```

- Terminal 命令输入时的路径显示

打开 `.bashrc`, 将所有 `PS1` 中的小写 `w` 改成大写 `W`

## 14. 传输

- ftp

- [ssh](./ssh.md)

```sh
sudo apt-get install openssh-server # install
ssh user@ip_address # 远程登录
ssh-keygen -t rsa # 创建公私钥
ssh-copy-id zbz@xx.x.xx.xx # 拷贝公钥

# 手动拷贝公钥到远程服务器
直接将本地id_rsa.pub(win一般在C:\Users\zbzco\.ssh)拷给到/home/zbz
mkdir .ssh
touch .ssh/authorized_keys
cat id_rsa.pub >> .ssh/authorized_keys
```

- [scp](./scp.md)

```sh
1) scp zbz@192.168.2.101:/home/zbz/tmp /home/zbz/tmp
2) scp /home/zbz/tmp zbz@192.168.2.101:/home/zbz/tmp # note : 如果是文件夹, 则需要加-r
```

## 15. 换源

- 命令

```sh
sudo vim /etc/apt/sources.list
sudo apt update
sudo apt upgrade
```

- Ubuntu 16.04

```sh
deb http://mirrors.aliyun.com/ubuntu/ xenial main
deb-src http://mirrors.aliyun.com/ubuntu/ xenial main
deb http://mirrors.aliyun.com/ubuntu/ xenial-updates main
deb-src http://mirrors.aliyun.com/ubuntu/ xenial-updates main
deb http://mirrors.aliyun.com/ubuntu/ xenial universe
deb-src http://mirrors.aliyun.com/ubuntu/ xenial universe
deb http://mirrors.aliyun.com/ubuntu/ xenial-updates universe
deb-src http://mirrors.aliyun.com/ubuntu/ xenial-updates universe
deb http://mirrors.aliyun.com/ubuntu/ xenial-security main
deb-src http://mirrors.aliyun.com/ubuntu/ xenial-security main
deb http://mirrors.aliyun.com/ubuntu/ xenial-security universe
deb-src http://mirrors.aliyun.com/ubuntu/ xenial-security universe
```

- Ubuntu 18.04
  
```sh
deb http://mirrors.aliyun.com/ubuntu/ bionic main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-proposed main restricted universe multiverse
deb http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-security main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-updates main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-proposed main restricted universe multiverse
deb-src http://mirrors.aliyun.com/ubuntu/ bionic-backports main restricted universe multiverse
```

- pip 换源

```sh
$ sudo vim ~/.pip/pip.conf # 将如下输入
[global]
index-url = http://pypi.douban.com/simple
trusted-host = pypi.douban.com
timeout = 6000
```
