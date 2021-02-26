
## 安装 gitlab CI runner

### 先安装 docker

如果有旧版本，先卸载

```
sudo apt-get remove docker docker-engine docker.io containerd runc
```

#### 设置 docker 的 apt 仓库

先安装一些必须的依赖

```
 sudo apt-get update
```

```
 sudo apt-get install \
    apt-transport-https \
    ca-certificates \
    curl \
    gnupg
```

添加 Docker’s official GPG key:

```
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /usr/share/keyrings/docker-archive-keyring.gpg
```

设置为 stable 分支

```
echo \
  "deb [arch=amd64 signed-by=/usr/share/keyrings/docker-archive-keyring.gpg] https://download.docker.com/linux/ubuntu \
  $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
```

#### 安装 docker engine

```
 sudo apt-get update
```

```
 sudo apt-get install docker-ce docker-ce-cli containerd.io
```

测试安装是否成功

```
sudo docker run hello-world
```

docker 安装 具体参见官网：https://docs.docker.com/engine/install/ubuntu/

### 安装 runner

Add the official GitLab repository:

```
# For Debian/Ubuntu/Mint
curl -L "https://packages.gitlab.com/install/repositories/runner/gitlab-runner/script.deb.sh" | sudo bash
```

Install the latest version of GitLab Runner

```
# For Debian/Ubuntu/Mint
export GITLAB_RUNNER_DISABLE_SKEL=true; sudo -E apt-get install gitlab-runner
```

安装完成后，去 Gitlab 上获取一个 token：

* For a [shared runner](https://docs.gitlab.com/ee/ci/runners/#shared-runners),
  have an administrator go to the GitLab Admin Area and click **Overview > Runners**
* For a [group runner](https://docs.gitlab.com/ee/ci/runners/README.html#group-runners),
  go to **Settings > CI/CD** and expand the **Runners** section
* For a [project-specific runner](https://docs.gitlab.com/ee/ci/runners/README.html#specific-runners),
  go to **Settings > CI/CD** and expand the **Runners** section

#### 注册 runner

运行命令

```
sudo gitlab-runner register
``````

输入 gitlab 地址：

```
http://gitlab.qitantech.com/
```

输入刚才获取的 token

输入给这个 runner 取的名字，要有**识别度**，带 ip 之类的

跳过 tag 设置

选择 **runner executor**，前面专门安装了 docker，所以这里选 `docker`

设置默认 image，我选的是 `gcc`

> 官方文档：
>
> https://docs.gitlab.com/runner/install/linux-repository.html
>
> https://docs.gitlab.com/runner/register/
>

## gitlab CI runner 配置

gitLab runner 的配置文件存放的位置和其执行权限相关

+ 当 gitLab runner 作为 root 用户执行时，配置文件保存在 `/etc/gitlab-runner/config.toml`
+ 当 gitLab runner 作为普通用户执行时，配置文件保存在 `~/.gitlab-runner/config.toml`

如果是前者，需要 sudo 权限才能编辑。

在 runner 配置文件里，修改并行任务数为 2 ~ 6 （取决于你的服务器性能）

```
concurrent = 3
```

设置 docker 的 pull policy (如下设置可以让它在网络不好的时候也正常工作)

```
[runners.docker]
  pull_policy = ["always", "if-not-present"]
```

policy 将从左到右依次生效（当 always 失败时执行 if-not-present）
if-not-present ：若近期没有 pull 过 image，则立即 pull，否则使用本地已有的 image

详见:
[How pull policies work](https://docs.gitlab.com/runner/executors/docker.html#how-pull-policies-work)

修改完成后，重启服务使配置生效

```
$ service gitlab-runner restart
```