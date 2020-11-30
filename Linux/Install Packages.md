
## 1. GCC8

```sh
sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-8
sudo apt-get install g++-8

# 配置:将gcc8，g++8作为默认选项
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 100
sudo update-alternatives --config gcc

sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-8 100
sudo update-alternatives --config g++

# 查看是否成功：
gcc --version
g++ --version
```

## 2. anaconda3

```sh
$ bash anaconda3.... # 回车, yes, 回车...........
$ sudo vim ~/.bashrc

# --------
# >>> conda initialize >>>
# !! Contents within this block are managed by 'conda init' !!
__conda_setup="$('/home/zbz/anaconda3/bin/conda' 'shell.bash' 'hook' 2> /dev/null)"
if [ $? -eq 0 ]; then
    eval "$__conda_setup"
else
    if [ -f "/home/zbz/anaconda3/etc/profile.d/conda.sh" ]; then
        . "/home/zbz/anaconda3/etc/profile.d/conda.sh"
    else
        export PATH="/home/zbz/anaconda3/bin:$PATH"
    fi
fi
unset __conda_setup
export PATH="/home/zbz/anaconda3/bin:$PATH"
# <<< conda initialize <<<
# --------

$ source ~/.bashrc


If you'd prefer that conda's base environment not be activated on startup, 
   set the auto_activate_base parameter to false: 

conda config --set auto_activate_base false
```

## 3. bonito

```sh
# 首先安装anaconda3
git clone https://github.com/nanoporetech/bonito.git
cd bonito
python3 -m venv venv3
source venv3/bin/activate
pip install --upgrade pip
pip install -r requirements.txt
python setup.py develop
```

## 4. Ninja

CMake Error: CMake was unable to find a build program corresponding to "Ninja"

执行 `sudo apt install ninja-build`

## 5. cuda toolkit cudnn

Cuda 驱动安装 10.2 版本比较保险  
<https://cyfeng.science/2020/05/02/ubuntu-install-nvidia-driver-cuda-cudnn-suits/>  
<https://medium.com/@sh.tsang/tutorial-cuda-v10-2-cudnn-v7-6-5-installation-ubuntu-18-04-3d24c157473f>

- runfile安装过程中会提醒是否继续
(Existing package manager installation of the driver found.
 It is strongly recommended that you remove this before continuing.)，
选择继续continue，在后续选择安装内容时去除驱动选择。

```sh

# install cuda
sudo sh cuda_10.2.xxx_linux.run

# 配置环境变量 还是使用.bashrc文件举例
echo '# CUDA Soft Link' >> ~/.bashrc
echo 'export PATH=/usr/local/cuda/bin${PATH:+:${PATH}}' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH=/usr/local/cuda/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}' >> ~/.bashrc
source ~/.bashrc

# 测试安装是否成功
nvcc -V

# install cudnn
https://cyfeng.science/2020/05/02/ubuntu-install-nvidia-driver-cuda-cudnn-suits/ 登录 nvidia 账号下载
sudo dpkg -i libcudnn7xxx+cuda10.2_amd64.deb      # (the runtime library)
sudo dpkg -i libcudnn7-dev_xxx+cuda10.2_amd64.deb # (the developer library)
sudo dpkg -i libcudnn7-doc_xxx+cuda10.2_amd64.deb # (the code samples)

# compile && test
cd /usr/src/cudnn_samples_v7/mnistCUDNN/
sudo make clean && sudo make # Compile the MNIST example
./mnistCUDNN # Run the MNIST example, If your installation is successful, you should see Test passed!
```

## 6. hdf5

<http://www.linuxdiyf.com/linux/26164.html>  
<https://support.hdfgroup.org/ftp/HDF5/releases/hdf5-1.12/hdf5-1.12.0/src/>

```sh
tar -zxvf hdf5-xxx.tar.gz   #解压缩
cd hdf5-X.Y.Z
./configure --prefix=/usr/local/hdf5  #安装路径
make
make check                # run test suite.
sudo make install
sudo make check-install        # verify installation.
sudo apt install hdf5-helpers
sudo apt-get install libhdf5-serial-dev
```

## 7. Rust

```sh
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
source $HOME/.cargo/env
rustc --version
rustup install nightly # 升级版本
rustup update nightly  # 如果安装过就更新
rustup default nightly  # 切换到nightly
rustc --version  # 查看是否已经是nightly版本了
```

## 8. C++ gRPC

- 安装新版 `cmake`

```sh
sudo apt-get autoremove cmake # 首先remove掉旧版
http://www.cmake.org/download/ # 然后在cmake 官网上下载最新的cmake包

cd /usr/ # 拷贝到这个目录下

tar -zxvf cmake-xxx.tar.gz # 解压, 安装
cd cmake-xxx
sudo ./bootstrap
sudo make
sudo make install

cd /usr/bin
sudo ln -sf /usr/cmake-xxx/bin/cmake # 然后加入链接

cmake --version
```

- 预安装

```sh
sudo apt-get install build-essential autoconf libtool pkg-config
sudo apt-get install cmake   # cmake >=3.13
sudo apt-get install libssl-dev
sudo apt-get install libgflags-dev
sudo apt-get install clang-5.0 libc++-dev
```

- 安装grpc

```sh
git clone --recurse-submodules -b v1.30.0 git@git.zhlh6.cn:grpc/grpc.git  # 可以选择更高版本
cd grpc
git submodule update --init
mkdir -p cmake/build
cd cmake/build
cmake -DgRPC_INSTALL=ON  -DgRPC_BUILD_TESTS=OFF   ../..
make
sudo make install
```

- 测试

```sh
cd grpc/examples/cpp/helloworld/
mkdir build
cd build
cmake ../..
make
```

- Q & A

如出现错误 : `CMake Error at /usr/local/lib/cmake/grpc/gRPCConfig.cmake:13 (include):`  
需将 `cmake` 更新到最新版本

## [clang-format for win](https://juejin.im/post/6844904174736375815)

## protobuf 安装

默认版本 : `sudo apt-get install libprotobuf-dev protobuf-compiler`  
指定版本 : <https://www.jianshu.com/p/05e91bb8506f>
同时安装两个版本 : <https://blog.csdn.net/u014454538/article/details/89005934>
