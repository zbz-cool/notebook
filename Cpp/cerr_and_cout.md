# cerr, cout 区别

1. cout是标准输出流, cerr是标准错误流
2. cout可以重定向，cerr 不可重定向
3. cout要分配缓冲，cerr 不用，所以从理论上来说，`cerr` 输出要比 `cout` 要快
4. cout和cerr默认都是标准输出设备：显示器.
