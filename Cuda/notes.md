### [有多个 GPU 时, 指定某个设备来运行](https://blog.csdn.net/fengbingchun/article/details/76902556)
```
cudaGetDeviceCount(&device_count); // 获取设备信息
cudaSetDevice(dev); // 指定执行设备
```

### CPU 与GPU 分工与协作
基于CPU+GPU的异构计算平台可以优势互补，CPU负责处理逻辑复杂的串行程序，而GPU重点处理数据密集型的并行计算程序，从而发挥最大功效。

### CUDA 工具
- 编译器: nvcc (C/C++)
- 调试器: nvcc-gdb
- 性能分析: nsight, nvprof
- 函数库: cublas, nvblas, cusolver, cufftw, cusparse, nvgraph

### grid, block, thread
1. 一个 kernel 所启动的所有线程成为一个网格(grid)
2. 同一个网格上的线程共享相同的全局内存空间, grid 是线程结构的第一层次
3. 网格又可以分为很多线程块(block), 一个线程块里面包含了很多线程, 这是第二个层次
4. warp: 32 个线程一组, 这是第三个层次  
5. warp 是最基本的执行单位, 一个 warp 中所有的线程需要执行相同的指令. 如果 warp 中的指令不一致, 就会导致执行效率的降低.
6. block 太大就会导致分配给该block的资源太大.  
7. block 太小就不能完成任务了, 一般包含128, 256个线程, 数量必须是warp(32)的整数倍.
8. thread 在 block 内共享资源.
9. 一般情况下, <<<gs, bs>>> 中, gs 可以为3维, 但bs一般是一维.
10. 不同GPU架构, grid 和 block 的维度有限制.
11. 一个线程块上的线程是放在同一个流式多处理器 (SM) 上的, 不能放在多个流式多处理器上.

### Memory
- Local Memory -> per-thread
- Shared Memory -> per-block
- Global Memory -> per-application
- Shard Memory 比 Global Memory 快 100 倍左右, 但是 Shared Memory 的空间是非常小的, 大约只有64字节, 而 Global Memory 可以有4, 8, 16G.

- 如果一个block要使用4KB的内存, 但寄存器一共只有64KB, 那么同一时刻只有16个block在并行计算. 所以开发时应该让block尽可能的少使用寄存器的资源.

- 设计GPU程序时, 尽量保证不要让不同线程(thread)访问同一个内存地址(bank), 否则会导致串行访问, 导致效率下降.

### 三个函数类型
1. `__global__`：在device上执行，从host中调用（一些特定的GPU也可以从device上调用），返回类型必须是void，不支持可变参数参数，不能成为类成员函数。注意用`__global__` 定义的kernel是异步的，这意味着host不会等待kernel执行完就执行下一步。
2. `__device__`：在device上执行，单仅可以从device中调用，不可以和`__global__`同时用。
3. `__host__`：在host上执行，仅可以从host上调用，一般省略不写，不可以和`__global__`同时用，但可和`__device__`，此时函数会在device和host都编译。

### [CUDA Shared Memory 共享内存](https://dorianzi.github.io/2020/04/02/cuda-shared-memory/)

CUDA里的shared memory是block级别的，所以两件事需要keep in mind：
1. 当你allocate shared memory的时候，你其实在每个block里面都创建了一份同样大小却互相独立的share memory
2. 当你进行__syncthreads()操作的时候，你只能保证此block里的thread在同步，此block里的shared memory在同步
这两个点在影响着shared memory使用的性能
