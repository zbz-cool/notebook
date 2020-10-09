// https://www.runoob.com/cprogramming/c-function-signal.html

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int);

int main()
{
    signal(SIGINT, sighandler);

    while (1)
    {
        printf("开始休眠一秒钟...\n");
        sleep(1);
    }

    return (0);
}

void sighandler(int signum)
{
    printf("捕获信号 %d，跳出...\n", signum );
    exit(1);
}
