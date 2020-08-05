# Message Queues

- IPC(Inter-Process Communication), 进程间通信

- [Unix/Linux C++应用开发-进程通信消息队列](https://blog.csdn.net/wangfengwf/article/details/52822056)  
- [C++的消息队列发送和接收消息实战](https://blog.csdn.net/chengqiuming/article/details/89046535)  
- [ipcs命令详解——共享内存、消息队列、信号量定位利器](https://blog.csdn.net/dalongyes/article/details/50616162)
- [参数详细说明](https://blog.csdn.net/guoping16/article/details/6584024)

```C++
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <chrono>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#define MAX_TEXT 512

struct my_msg_st
{
    long int my_msg_type;
    char some_text[BUFSIZ];
};

void _split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim))
    {
        elems.push_back(item);
    }
}
std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    _split(s, delim, elems);
    return elems;
}

void create_basecaller_process(int &pid)
{
    pid_t fpid; //fpid表示fork函数返回的值
    int count = 0;
    fpid = fork();
    if (fpid < 0)
    {
        pid = -1;
        printf("error in fork!");
    }
    else if (fpid == 0)
    {
        int msgid;
        struct my_msg_st some_data;
        long int msg_to_receive = 0;
        int running = 1;

        printf("I am son, my father id : %d, my id : %d, my son id : %d\n", getppid(), getpid(), fpid);

        //创建消息队列
        msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
        if (msgid == -1)
        {
            fprintf(stderr, "msgget failed with error: %d\n", errno);
            exit(EXIT_FAILURE);
        }

        // printf("create msgget\n");

        while (running)
        {
            // printf("running\n");
            //第5个参数为0表示阻塞方式，当消息队列为空，一直等待
            if (msgrcv(msgid, (void *)&some_data, BUFSIZ, msg_to_receive, 0) == -1)
            {
                fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
                exit(EXIT_FAILURE);
            }
            // printf("msgrcv\n");
            std::vector<std::string>list_results = split(some_data.some_text, ',');
            std::cout << "You wrote : \n";
            for (auto &r : list_results)
            {
                std::cout << r << " ";
            }
            std::cout << std::endl;

            // printf("You wrote: %s", some_data.some_text);
            std::this_thread::sleep_for(std::chrono::seconds(3));
            if (strncmp(some_data.some_text, "end", 3) == 0)
            {
                running = 0;
            }
        }
        if (msgctl(msgid, IPC_RMID, 0) == -1) // 删除消息队列
        {
            fprintf(stderr, "msgctl(IPC_RMID) failed\n");
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        pid = fpid;
        // printf("I am father, my father id : %d, my id : %d, my son id : %d\n", getppid(), getpid(), fpid);
        // count++;
    }
    printf("create process, fpid = %d\n", fpid);
    return;
}

int main_send_message_queue(std::string h5_file, std::string result_file)
{
    return 1;
}

int main()
{
    int status;
    int basecaller_process_pid = 0;
    struct my_msg_st some_data;
    char buffer[BUFSIZ];
    int msgid;
    if ((msgid = msgget((key_t)1234, 0666 | IPC_CREAT)) == -1)
    {
        fprintf(stderr, "msgget failed with errno: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    create_basecaller_process(basecaller_process_pid);

    std::vector<std::string> list_h5_and_result_file = {"./fdf/zbz/fd.h5 model ../result/fastq --fastq", "./fdf/zbz/fd.h55 model ../result/fast11q --f11astq", "end"};
    for (auto &hr : list_h5_and_result_file) {
        some_data.my_msg_type = 1;
        strcpy(some_data.some_text, hr.c_str());

        // std::cout << msgid << " " <<  hr << std::endl;
        if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1)
        {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
    }

    pid_t child = wait(&status);
    printf("status = %d\n", WEXITSTATUS(status));

    printf("main process end, son id = %d\n", basecaller_process_pid);
    return 0;
}
```
