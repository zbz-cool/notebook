# Abandon

## 场景

假设先提交了commit A, 但是不知道什么原因, 不能submit(如碰到审核后该按钮是灰色不可点击状态), 这个时候我不得不abandon, 或者被leader因为代码质量问题手动abandon了.

## 解决

这个时候, 你一定要在本地使用git reset --soft 被abandon掉的那次提交之前的提交, 将abandon对应那次提交相当于在提交历史中'删除'. 否则, 当你commit B后push并审核后, 会出现按钮并提示submit including parents: this change are depends on other change wich are not ready.
这是因为本地依然存在commit A, 从而导致commit B依赖于commit A, 但是commit A在gerrit上是被abandon掉的, 是不可见的. 所以导致无法submit.

## git reset --soft 与 --hard的区别

> <https://blog.csdn.net/yangfengjueqi/article/details/61668381>
