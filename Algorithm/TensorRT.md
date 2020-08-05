# TensorRT

- [官方文档](https://developer.nvidia.com/tensorrt)

- [官方文档 ONNX](https://docs.nvidia.com/deeplearning/tensorrt/developer-guide/index.html#onnx_workflow)

- [官方安装文档](https://docs.nvidia.com/deeplearning/tensorrt/developer-guide/index.html)

- [TensorRT Open Source Software C++](https://github.com/nvidia/TensorRT)

## [How to Convert a Model from PyTorch to TensorRT and Speed Up Inference](https://www.learnopencv.com/how-to-convert-a-model-from-pytorch-to-tensorrt-and-speed-up-inference/)

- Train a model using PyTorch
- Convert the model to ONNX format (ONNX :  Open Neural Network Exchange)
- Use NVIDIA TensorRT for inference

- [“Hello World” For TensorRT](https://github.com/NVIDIA/TensorRT/tree/master/samples/opensource/sampleMNIST)

- [高性能深度学习支持引擎实战——TensorRT](https://zhuanlan.zhihu.com/p/35657027)

### What's this trt different with tensorrt engine? (which commonly used when convert onnx model to tensorrt engine)

1. This repository converts directly from PyTorch -> TensorRT (no intermediate file representation)

2. This repository provides utilities, like TRTModule, which behaves similar to a PyTorch module. So you can rapidly prototype your application / test against TensorRT.

### How using C++ api (Torch2trt)

- [python直接转RT](https://github.com/NVIDIA-AI-IOT/torch2trt)

Under the hood, the result is the same, an optimized TensorRT engine. You can use this engine in C++ by serializing it.

For example, assuming you have a working TRTModule returned from torch2trt, you can save the serialized engine by calling

```python
with open('model.engine', 'wb') as f:
    f.write(model_trt.engine.serialize())
```

This can be used like any other serialized TensorRT engine in C++.

## pytorch model to onnx model 会出现警告, 可以忽略

`UserWarning: No names were found for specified dynamic axes of provided input.Automatically generated names will be applied to each dynamic axes of input output
'Automatically generated names will be applied to each dynamic axes of input {}'.format(key))`

## [Inference time PyTorch vs TRT](https://github.com/onnx/onnx-tensorrt/issues/294)

Im using onnxruntime to implement pytorch model, but it runs twice slower!!!

## <https://github.com/rmccorm4/tensorrt-utils> 包装了tensorrt

- 目录 : /media/qt/data/zbz/tensorrt-utils
- 运行 : `python inference/infer.py`
- 分析 : 只使用了一组随机数进行测试, 测试速度为 `3.6 * 10^4 samples per second`, 而直接使用 pytorch 的速度为  `4.2 * 10^5 samples per second`

## 安装 tensorrt

1. 下载解压 TensorRT-7.1.3.4.Ubuntu-18.04.x86_64-gnu.cuda-10.2.cudnn8.0.tar.gz 文件, 可以在 <https://docs.nvidia.com/deeplearning/tensorrt/install-guide/index.html> 网址进行下载, 保存在2.116的~/media_data/install_tensorrt文件夹下
2. cd TensorRT-${version}/python
3. source venv3/bin/xxxx (激活特定的虚拟环境)
4. pip3 install tensorrt-*-cp3x-none-linux_x86_64.whl

## 运行bonito to tensorrt

1. 登录 192.168.2.116
2. cd /home/zbz/bonito_tenserrt_0.1.5
3. source venv3/bin/activate
4. python bonito/basecaller_bak.py  # 生成bonito.onnx
5. python bonito/trt_inference.py # 生成bonito_engine.onnx, 并且运行tensorrt
6. 但速度没有加快, samples per second 3.8E+05
