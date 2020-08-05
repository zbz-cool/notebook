# Python Notes

## 保存和加载Numpy数据

```python
np.save('one_array.npy', arr2) # 序列化：
arr2_load = np.load('one_array.npy') # 反序列化
```

## python读文件

```python
f = open('test.txt')  # 一次性读取所有行
for line in f:
    list_line = line.split("\t") # 制表符分割
f.close()
```

## [python numba 提速效果还是明显](https://www.cnblogs.com/zhuwjwh/p/11401215.html)

## [conda 虚拟环境](https://baijiahao.baidu.com/s?id=1637641396313583330&wfr=spider&for=pc)

## [with .. as .. 的使用](https://www.jianshu.com/p/1a02a5b63c88)

## [python argparse用法总结](https://www.jianshu.com/p/fef2d215b91d)
