/*
只使用C, 打印当前的秒, 毫秒, 微妙
*/
#include <stdio.h>
#include <sys/time.h>

int main() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("second:%ld\n", tv.tv_sec); //秒
    printf("millisecond:%ld\n",tv.tv_sec*1000 + tv.tv_usec/1000);  //毫秒
    printf("microsecond:%ld\n",tv.tv_sec*1000000 + tv.tv_usec);  //微秒
    return 0;
}
