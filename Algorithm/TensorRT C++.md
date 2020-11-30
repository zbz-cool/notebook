https://github.com/NVIDIA/TensorRT
https://github.com/NVIDIA/TensorRT/tree/master/samples/opensource/sampleOnnxMNIST


文档 : 动态形状的输入, C++/Python 该怎么写
https://docs.nvidia.com/deeplearning/tensorrt/developer-guide/index.html#work_dynamic_shapes


Pytorch 1.4.0 for TensorRT 7.0 and higher
Pytorch 1.5.0 and 1.6.0 for TensorRT 7.1.2 and higher

## 安装 Tensorrt

### 安装文件所在目录

\\smb-cd.lfs.qitantech.com\0-InnerShareFolder\0-常用软件\cuda_cudnn_ubuntu18.04

### install cuda
sudo sh cuda_10.2.xxx_linux.run

### 配置环境变量 还是使用.bashrc文件举例
echo '# CUDA Soft Link' >> ~/.bashrc
echo 'export PATH=/usr/local/cuda/bin${PATH:+:${PATH}}' >> ~/.bashrc
echo 'export LD_LIBRARY_PATH=/usr/local/cuda/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}' >> ~/.bashrc
source ~/.bashrc

### 测试安装是否成功
nvcc -V

### install cudnn
https://cyfeng.science/2020/05/02/ubuntu-install-nvidia-driver-cuda-cudnn-suits/ 登录 nvidia 账号下载
sudo dpkg -i libcudnn7xxx+cuda10.2_amd64.deb      # (the runtime library)
sudo dpkg -i libcudnn7-dev_xxx+cuda10.2_amd64.deb # (the developer library)
sudo dpkg -i libcudnn7-doc_xxx+cuda10.2_amd64.deb # (the code samples)

### 安装Tensorrt
1. 下载解压 TensorRT-7.1.3.4.Ubuntu-18.04.x86_64-gnu.cuda-10.2.cudnn8.0.tar.gz 文件, 可以在 <https://docs.nvidia.com/deeplearning/tensorrt/install-guide/index.html> 网址进行下载, 保存在2.116的~/media_data/install_tensorrt文件夹下
2. cd TensorRT-${version}/python
3. source venv3/bin/xxxx (激活特定的虚拟环境)
4. pip3 install tensorrt-*-cp3x-none-linux_x86_64.whl  # 其中x表示python的版本

### 复制 tensorrt 的 so 文件
sudo scp zbz@192.168.2.157:/home/qt/git-projects/QitanRpcBasePlatformProjects/BasecallService/0-Release/tmp_lib/libcudnn.so.8            /usr/lib/
sudo scp zbz@192.168.2.157:/home/qt/git-projects/QitanRpcBasePlatformProjects/BasecallService/0-Release/tmp_lib/libcudnn_ops_infer.so.8  /usr/lib/
sudo scp zbz@192.168.2.157:/home/qt/git-projects/QitanRpcBasePlatformProjects/BasecallService/0-Release/tmp_lib/libcudnn_cnn_infer.so.8  /usr/lib/

### 有可能需要安装pycuda
pip3 install --global-option=build_ext --global-option="-I/usr/local/cuda/targets/x86_64-linux/include/" --global-option="-L/usr/local/cuda/targets/x86_64-linux/lib/" pycuda