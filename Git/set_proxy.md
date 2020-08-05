# [Git 设置代理](https://baijiahao.baidu.com/s?id=1603409484949165821&wfr=spider&for=pc)

## 使用命令

### http代理

```sh
git config --global https.proxy http://127.0.0.1:10800
git config --global https.proxy https://127.0.0.1:10800
```

### socks5代理

```sh
git config --global http.proxy 'socks5://127.0.0.1:10800'
git config --global https.proxy 'socks5://127.0.0.1:10800'
```

## 编辑文件~/.gitconfig

```sh
[http]
proxy = socks5://127.0.0.1:10800
[https]
proxy = socks5://127.0.0.1:10800
```

然后就可以直接使用git命令重新下载了。

## 取消代理

```sh
git config --global --unset http.proxy
git config --global --unset https.proxy
```
