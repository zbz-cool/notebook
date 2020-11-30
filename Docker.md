> [Docker 容器使用教程](https://www.runoob.com/docker/docker-container-usage.html)

## 安装 Docker 所需条件
需要 64 位架构的系统和Linux 3.10 内核或更高版本。这里作者使用了 Ubuntu15.04 系统的 3.19 内核版本。

## Docker Images
Docker image 是 Docker container 最基本的模板。image 通用容器使系统和应用易于安装，Docker image 是用来运行的容器，你可以找到许多 images （多种操作系统和软件已经被安装好了的 Docker）在这里 https://hub.docker.com/.

## Docker Container
Docker 容器（Docker Container）是一个 Image，在运行的 Docker image 上读取和写入。Docker 是一个联合的文件系统作为容器后台，容器的任何变化，都将被保存在一个基本 image 新的层上。我们安装应用程序的层就是容器。每个在主机机上运行的容器都是独立的，因此，提供了一个安全的应用平台。

## Docker Registry
Docker registry 是为 Docker images 提供的库。它提供了公共和私有库。公共 Docker 库被叫做 Docker Hub。这里我们能够上传 push 和 pull 我们自己的 images.

## 修改 Docker 默认存储位置
默认情况下, 保存在`/var/lib/docker`, 修改方法为:  
1. `sudo /etc/init.d/docker stop`
2. `cd /var/lib`
3. `sudo mv docker docker.bak`
4. `sudo cp -rf docker /<my_new_location>/`
5. `sudo ln -s /<my_new_location>/docker docker`  # 使用软连接的方式, 修改文件真实保存的位置
6. `sudo /etc/init.d/docker start`

## 将非root用户加入docker组，以允许免sudo执行docker
1. `sudo gpasswd -a 用户名 docker`
1. `sudo service docker restart` # 重启服务并刷新docker组成员
1. `newgrp - docker`

## 命令

| Command                                         | Description                                          |
| ----------------------------------------------- | ---------------------------------------------------- |
| docker ps                                       | 查看活动的容器的状态, 类似 ps 命令                   |
| docker ps -a                                    | 查看所有容器的状态, 类似 ps 命令                     |
| docker stats                                    | 类似top命令查看容器状态                              |
| docker info                                     | 查看 Docker 的基本信息                               |
| docker pull ubuntu                              | 载入 ubuntu 镜像                                     |
| docker logs id                                  | 查看标准输出                                         |
| docker stop id                                  | 停止容器                                             |
| docker run ubuntu:15.10 /bin/echo "Hello world" | 启动容器执行一次程序                                 |
| docker run -d ubuntu:15.10                      | 后台运行容器                                         |
| docker run -it ubuntu:15.10 /bin/bash           | 交互式运行容器                                       |
| docker start id                                 | 已经停止的容器，我们可以使用命令 docker start 来启动 |
| docker rm id                                    | 删除某个容器                                         |
|docker images | 本地主机上的镜像 |