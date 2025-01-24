#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<cstring>
// 匿名管道由于没有名称，只能在一些具有亲缘关系的进程直接传递信息。
// 而命名管道是一个真正独立的文件。可以在任意两个进程之间进行通信
// 命名管道不支持文件定位操作，严格遵守先进先出的原则。
// 所以命名管道也被称为FIFO文件（first in first out）。
// 且不涉及多进程共享访问资源的问题。

// 对比匿名管道. 父子进程都又匿名管道的读写端口.
// 命名管道创建一次, 然后通过父子进程各自open这个文件获取读写端口.
int main()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork func error");
        return -1;
    }
    else if (pid > 0) // 
    {
        if (mkfifo("tmp", 0644) == -1)
        {
            perror("mkfifo func error");
            return -1;
        }
        int inFifoFd = open("tmp", O_WRONLY, 0644);
        if (inFifoFd == -1)
        {
            perror("open inFifoFd error");
            return -1;
        }
        const char* str = "hello world";
        if (write(inFifoFd, str, strlen(str)) == -1)
        {
            perror("write func error");
            return -1;
        }
        close(inFifoFd);

    }
    else if (pid == 0)
    {
        sleep(1); // 等父进程先创建文件.
        int outFifoFd = open("tmp", O_RDONLY);
        if (outFifoFd == -1)
        {
            perror("open outFifoFd error");
            return -1;
        }
        char readBuf[32]{};
        if (read(outFifoFd, readBuf, 32) == -1)
        {
            perror("read func error");
            return -1;
        }
        std::cout << readBuf << '\n';
        close(outFifoFd);
        if (unlink("tmp") == -1) // 释放命名管道.
        {
            perror("unlink func error");
            return -1;
        }
    }


    return 0;
}