# Git

## 待学习

- `git bisect` 使用二分法, 来查找哪个 commit 引入了错误

## 提交一个文件中的部分修改 `git add -i`

## 获得一个干净的工作区

`git stash push [-u | --include-untracked]` 将 untracked 的文件也stash

## 从 Git 历史中删除一个文件

例如敏感信息, 或一个超大临时文件

`git filter-branch --tree-filter 'rm -f passwords.txt' HEAD`, 但该操作会改变对应的SHA1值, 所以要非常小心谨慎

## `git commit --amend`

- 修改最后一次提交, 只修改comments; 或者添加修改内容, 并且修改comments.

## 拉取远程分支并创建本地分支

```sh
git fetch
git branch -r # 查看远端分支
git checkout -b xxx origin/xxx # 拉取远端分支, 并切换到该分支上
```

## commit 一个已经 tracked 的文件, 是记录该文件的改动部分, 还是拷贝整个文件

是拷贝整个文件, 用空间换时间的方法来提高切换分支的效率

## `git reset HEAD <file>`

`git add file` 之后, 提示可以用 `git reset HEAD <file>`, 来撤销add的操作  
**工作原理是** : `HEAD` 是特别指针, 指向当前分支, `git reset HEAD` 是用当前分支里的 `file` 来还原暂存区中的 `file`.

## `git branch`

- `git branch -a` # 查看本地和远端的所有分支
- `git branch -a -vv` # 所有分支, 带上SHA1信息
- `git branch -r` # 只查看远端分支
- `git branch` # 查看本地分支

## `git rebase -i` 抛弃, 修改, 合并历史提交

**前提** : 不要通过rebase对任何已经提交到公共仓库中的 commit 进行修改(自己玩的分支除外)

`git rebase -i  [startpoint]  [endpoint]` 即弹出交互式的界面让用户编辑完成合并操作，`[startpoint] [endpoint]` 则指定了一个编辑区间，如果不指定 `[endpoint]`，则该区间的终点默认是当前分支HEAD所指向的commit **(注：该区间指定的是一个前开后闭的区间)**

> <https://www.jianshu.com/p/4a8f4af4e803>

## git cherry-pick

将某个分支的某个提交合并到当前分支
> <http://www.ruanyifeng.com/blog/2020/04/git-cherry-pick.html>
