# QT开发环境配置全流程

插提前制作好的系统安装u盘（Ubuntu 18.04），开机，连点 F12 进 BIOS，选从 USB 启动。
然后选择 `install ubuntu`

一路 continue，不安装第三方软件（显卡和wifi）

选 `Erase disk and install Ubuntu`

建议选上 `Use LVM with the new Ubuntu installation`（方便以后扩展硬盘

继续一路 continue 到设置用户名密码。建议主机名修改成短一点的。

## 安装完成后的基础配置

### ssh 相关

新安装的Ubuntu，enable ssh 需要 `apt-get install openssh-server`。光有client是无法从远端访问的。

`sudo apt install net-tools` 然后用 ifconfig 看本机 ip

就可以远程 ssh 登陆了

### C++ 编译链

```
sudo apt install g++
sudo snap install cmake --classic
```

确保安装的是最新版 cmake：https://cmake.org/download/
（我安装的时候是 3.19.1）

### Anaconda

公司共享服务器上直接下载，然后:

`bash ./Anaconda3-2019.10-Linux-x86_64.sh`

一路 yes，然后重启 terminal

## CUDA 相关底层支持

### 安装 CUDA 工具包

非常值得参考的官方文档：https://docs.nvidia.com/cuda/cuda-installation-guide-linux/index.html

与网上大部分教程不同，无需先安装显卡驱动，cuda 包里自带驱动

在这里下载 CUDA Toolkit 10.2 (Nov 2019) ：https://developer.nvidia.com/cuda-toolkit-archive
（如果要求注册账号就注册一下，后续也会用到）

注意版本选择 **CUDA 10.2**

里面再选 Linux -> x86_64 -> Ubuntu -> 18.04 -> deb(local)

注释：为什么选 deb(local)，不按网上教程选 run，因为后面安装 TensorRT 会变简单。

然后按下载页面内指示安装，完成后打上页面内提供的两个补丁。

```
sudo dpkg -i cuda-repo-ubuntu1804-10-2-local_10.2.1-1_amd64.deb
sudo dpkg -i cuda-repo-ubuntu1804-10-2-local_10.2.2-1_amd64.deb
```

完事重启，让显卡驱动生效。

**[ IMPORTANT ! ]**

参考官方文档最后的要求：**Post-installation Actions**

新增环境变量

```
export PATH=/usr/local/cuda-10.2/bin${PATH:+:${PATH}}
export LD_LIBRARY_PATH=/usr/local/cuda-10.2/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
```

（Nsight Compute has moved to /opt/nvidia/nsight-compute/ only in rpm/deb installation method.  这个不知道需不需要额外操作）

检查 cuda 版本：
` nvcc --version`

### 安装cuDNN

官方指引文档：https://docs.nvidia.com/deeplearning/cudnn/install-guide/index.html

下载地址：https://developer.nvidia.com/rdp/cudnn-download

填写问卷，同意协议后，
选择跟 CUDA 版本对应的版本： `Download cuDNN v8.0.5 (November 9th, 2020), for CUDA 10.2`

找到 Ubuntu18.04 的 Deb 包，这两个都要下：

```
cuDNN Runtime Library for Ubuntu18.04 (Deb)
cuDNN Developer Library for Ubuntu18.04 (Deb)
```

下载完后安装：

```
sudo dpkg -i libcudnn8_x.x.x-1+cudax.x_arm64.deb
sudo dpkg -i libcudnn8-dev_8.x.x.x-1+cudax.x_arm64.deb
```

### 安装 TensorRT

务必参考 Nvidia 的官方文档严格执行，否则非常多坑：https://docs.nvidia.com/deeplearning/tensorrt/install-guide/index.html

下载地址：https://developer.nvidia.com/nvidia-tensorrt-download

选择 TensorRT 7 -> TensorRT 7.2.1 -> TensorRT 7.2.1 for Linux and CUDA 10.2 -> TensorRT 7.2.1 for Ubuntu 18.04 and CUDA 10.2 DEB local repo package 下载

```
os="ubuntu1804"
tag="cuda10.2-trt7.2.1.6-ga-20201006"
```

以上两项的参数根据你当时使用的包决定，不能有错

```
sudo dpkg -i nv-tensorrt-repo-${os}-${tag}_1-1_amd64.deb
sudo apt-key add /var/nv-tensorrt-repo-${tag}/7fa2af80.pub

sudo apt-get update
sudo apt-get install tensorrt

sudo apt-get install python3-libnvinfer-dev
sudo apt-get install onnx-graphsurgeon
```

## 其他编译依赖及配置

### 安装 git

```
sudo apt install git
```

设置你的名字和邮箱（下面仅为范例，请修改为自己的名字、邮箱）：

```
git config --global user.name "li.song"
git config --global user.email "song.li@qitantech.com"
```

```
ssh-keygen
cat ~/.ssh/id_rsa.pub
```

把显示出的公钥设定到 git 服务器上（公司的 Gerrit 和外部的 Github）

### 安装 rust

推荐用 `rustup` 安装 https://forge.rust-lang.org/infra/other-installation-methods.html

`curl https://sh.rustup.rs -sSf | sh`

这条命令会触发交互式安装界面

修改安装配置中的 `default toolchain：nightly`
我们需要使用 nightly 版本中的新特性，其他的不要改

会是这样:

```
Current installation options:
   default host triple: x86_64-unknown-linux-gnu
     default toolchain: nightly
               profile: default
  modify PATH variable: yes
```

验证安装：

```
$ rustc --version
rustc 1.50.0-nightly (fa4163942 2020-12-14)
```

### 安装 g++-8

装后面的东西需要用到 g++8

`sudo apt install g++-8`

不会破坏系统内原有的默认 g++ （g++7）

### 安装 hdf5 1.12.0

- hdf5 1.12.0    : https://www.hdfgroup.org/downloads/hdf5/source-code/

下载压缩包，然后：

```
tar -xvf hdf5-1.12.0.tar.gz
cd hdf5-1.12.0
./configure --prefix=/usr/local/hdf5 --enable-cxx
make
make check                # run test suite.
sudo make install
sudo make check-install        # verify installation.
```

### 安装proto buffer

follow the instruction here：https://github.com/protocolbuffers/protobuf/blob/master/src/README.md

`sudo apt-get install autoconf automake libtool curl make g++ unzip`

```
git clone https://github.com/protocolbuffers/protobuf.git
cd protobuf
git checkout v3.13.0
git submodule update --init --recursive
./autogen.sh
```

```
./configure --prefix=/usr
make
make check
sudo make install
sudo ldconfig # refresh shared library cache.
```

检查版本：
`protoc --version`

我们约定使用的版本是 `v3.13.0`，如果装错了版本，就直接在原来的source目录：`sudo make uninstall`

### 安装onnx-tensorrt

/*
onnx-tensorrt 似乎非必须
*/

clone 这两个库：

+ https://github.com/onnx/onnx-tensorrt
+ https://github.com/NVIDIA/TensorRT/

```
cd onnx-tensorrt/
git submodule update --init --recursive
mkdir build && cd build
cmake .. -DTENSORRT_ROOT=<path_to_trt> 
```

↑ <path_to_trt> 替换成刚刚clone下来的TensorRT库的路径

```
make -j
```

最后把路径添加到环境变量里

// Ensure that you update your LD_LIBRARY_PATH to pick up the location of the newly built library:

`export LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH `

这命令只是临时生效，永久生效需要自己去改 ~/.bashrc，范例如下：

```
# onnx-tensorRT
export LD_LIBRARY_PATH=/home/lisong/tools/onnx-tensorrt/build:$LD_LIBRARY_PATH
```

若要可执行命令 onnx2trt，添加软连接：

`sudo ln -s /home/lisong/tools/onnx-tensorrt/build/onnx2trt /usr/local/bin/ onnx2trt`

↑ onnx-tensorrt 虽然会同时安装 onnx，但 onnx 的命名空间被 onnx2trt_onnx 包住，所以链接时一样会找不到 onnx

### 独立安装 onnx

（参考这篇里的onnx部分：https://zhuanlan.zhihu.com/p/158895888）

```
git clone https://github.com/onnx/onnx.git
cd onnx
git submodule update --init --recursive
mkdir build && cd build
cmake ..
make -j
sudo make install
```

## 其他一些也许有用的配置

### vim 无法正常使用上下左右键和 Backspace

Vim-tiny简易版卸载，重新安装完整版vim

```
$sudo apt-get remove vim-common
$sudo apt-get install vim
```

### clang-format 需要单独安装

`sudo apt-get install clang-format`

### Linux 命令行中 tab 忽略大小写

```
cd ~
vi .inputrc
set completion-ignore-case on
```

保存退出，重启终端

### 一些有用的别名设置

`vi ~/.bashrc` 添加你常用的 alias：

```
# Personal settings
alias vv='watch -n 10 nvidia-smi'
```

### 网络不好时

在你本机 V2ray 已经设定允许局域网连接的情况下：

#### git 设置代理

https://jeshs.github.io/2019/04/git%E5%9F%BA%E7%A1%80%E4%BB%A3%E7%90%86/

#命令

```
git config --global http.proxy socks5://192.168.2.XXX:10808
```

#取消代理

```
git config --global --unset http.proxy
```

#### Linux 全局设置代理

```
export ALL_PROXY="socks://192.168.2.XXX:10808/"
export all_proxy="socks://192.168.2.XXX:10808/"
export ftp_proxy="ftp://192.168.2.XXX:10808/"
export http_proxy="http://192.168.2.XXX:10809/"
export https_proxy="https://192.168.2.XXX:10809/"
export socks_proxy="socks://192.168.2.XXX:10808/"
```

取消代理

```
unset http_proxy
unset https_proxy
```

#### pip 换源

国内可用的镜像源：

+ 阿里云 http://mirrors.aliyun.com/pypi/simple/
+ 中国科技大学 https://pypi.mirrors.ustc.edu.cn/simple/
+ 豆瓣(douban) http://pypi.douban.com/simple/
+ 清华大学 https://pypi.tuna.tsinghua.edu.cn/simple/
+ 中国科学技术大学 http://pypi.mirrors.ustc.edu.cn/simple/

修改 `~/.pip/pip.conf` (没有就创建一个)， 内容如下：

```
    [global]
    index-url = https://pypi.tuna.tsinghua.edu.cn/simple
```

### git 别名设置

```
$ git config --global alias.co checkout
$ git config --global alias.br branch
$ git config --global alias.ci commit
$ git config --global alias.st status
$ git config --global alias.unstage 'reset HEAD --'
$ git config --global alias.last 'log -1 HEAD'
```

### 服务器免密码登录

`vi ~/.ssh/authorized_keys`
在里面添加自己本地机器的 pub key

### VScode 的 Remote-SSH 插件配置

VScode 里按 `F1`，输入并选择 `Remote-SSH:Open Configuration File`

输入以下内容并保存（修改为你自己的用户名和 IP）

```
Host MyServer
    HostName 192.168.2.XXX
    User username
```

## 注意事项

所有上面操作做完后，你机器通常工作在 conda base 环境下。此时它有默认的 python protobuff 版本 3.0.0，而我们安装的（针对 C++ 等其它语言的）protobuff 版本为 3.13.0。因此 python 版和其他语言之间可能发生不可知的兼容性问题。
