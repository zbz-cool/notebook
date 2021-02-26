## Terminal 常用快捷键
| shortcut               | description                | VSCode   |
| :--------------------- | :------------------------- | :------- |
| CTRL+ALT+T             | 打开终端                   | Ctrl + ` |
| Ctrl+a                 | 光标移动到开始位置         |          |
| Ctrl+e                 | 光标移动到最末尾           | no       |
| Ctrl+k                 | 删除此处至末尾的所有内容   | No       |
| Ctrl+u                 | 删除此处至开始的所有内容   |          |
| Ctrl+r                 | 查找历史命令               |          |
| Ctrl+Left_Arrow        | 光标移动到上一个单词的词首 |          |
| Ctrl+Right_Arrow       | 光标移动到下一个单词的词尾 |          |
| Ctrl + L               | 清屏                       | Yes      |
| Ctrl + Alt + PgUp/PgDn | 滚动 terminal 内容(行)     | Yes      |
| Shift + PgUp/PgDn      | 滚动 terminal 内容(页)     | Yes      |

## Linux 进程调度方式
1. SCHED_OTHER 分时调度策略，
2. SCHED_FIFO实时调度策略，先到先服务
3. SCHED_RR实时调度策略，时间片轮转

## history
| param | description                                                                                |
| ----- | ------------------------------------------------------------------------------------------ |
| -c    | 将目前的shell中的所有 history 内容全部消除                                                 |
| -a    | 将目前新增的history 指令新增入 histfiles 中，若没有加 histfiles,则预设写入 ~/.bash_history |
| -r    | 将 histfiles 的内容读到目前这个 shell 的 history 记忆中                                    |

## 查看显卡信息
lspci | grep VGA

## CTRL + Z
1. CTRL+Z挂起进程并放入后台
2. jobs 显示当前暂停的进程
3. bg %N 使第N个任务在后台运行(%前有空格)
4. fg %N 使第N个任务在前台运行
　　
默认bg,fg不带%N时表示对最后一个进程操作!

## 手动启动ssh
`service ssh restart`

## ssh 登录, 自动加载 bashrc

```bash
# ssh login 之后， 会执行 .bash_profile
# 于是新建一个.bash_profile , 内容如下
if [ -f ~/.bashrc ]; then
  . ~/.bashrc
fi
```

## 修改 linux 命令 zbz@xx中的xx的值

```bash
PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@119-3060*2\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
```

## 设置本地域名
如果ping不通外网或局域网内的ip

```bash
sudo vim /etc/resolv.conf # 写入如下内容

search domain.name
nameserver 192.168.2.1
nameserver 8.8.8.8
nameserver 1.1.1.1
nameserver 1.0.0.1

sudo systemctl restart NetworkManager # 重启网络

```