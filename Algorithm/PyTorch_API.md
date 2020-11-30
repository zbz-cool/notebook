|||
|-|-|
torch.round | Returns a new tensor with each of the elements of input rounded to the closest integer.
torch.detach | 返回一个新的Variable，从当前计算图中分离下来的，但是仍指向原变量的存放位置,不同之处只是requires_grad为false，得到的这个Variable永远不需要计算其梯度，不具有grad

### 打印 Tensor
```python
torch.set_printoptions(profile="full")
print(x[600]) # prints the whole tensor
torch.set_printoptions(profile="default") # reset
```
