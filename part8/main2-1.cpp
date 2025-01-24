// 对于开发人员,C++多线程用的比较多,所以进程间通信用的比较少.
// 对多进程程序来说,进程间通信时绝对的核心. 且对于理解linux系统很重要.
// 管道/mmap(读作memory map)/信号(后面会专门讲)/本地网络/消息队列(后面网络会专门讲)

#include<iostream>
#include<unistd.h>
#include<cstring> // 系统调用要用到strlen函数

int main()
{
    int pipeFd[2]{};
    if (pipe(pipeFd) == -1) // 好像系统调用函数都是-1表示失败.
    {
        perror("pipe func error");
        return -1;
    }
    // 父子进程都要关闭一端. pipeFd[0]是输入, pipeFd[1]是输出.
    // 父进程读数据,但要把读入的数据放到pipe的写端. 进程读但对应管道的写. 子进程写数据但对应管道的读. 所以要注意一下这个语言表达. 不让容易混淆.

    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork func error");
        return -1;
    }
    else if (pid > 0) // 父进程读数据. "读入"怎么理解?从stdin读入数据,然后放入pipe的写端口!!
    {
        sleep(1);
        close(pipeFd[0]);
        const char* str = "hello world";
        if (write(pipeFd[1], str, strlen(str)) == -1) // write返回值为0几乎不可能,所以不考虑.
        {
            perror("write func error");
            return -1;
        }
        close(pipeFd[1]);
    }
    else if (pid == 0) // 子进程写数据. "写入"怎么理解?管道里面有了数据,从管道里面读数据,读完后再写到stdout或其他文件.
    {
        close(pipeFd[1]);
        char readBuf[32]{};
        if (read(pipeFd[0], readBuf, 32) == -1)
        {
            perror("read func error");
            return -1;
        }
        std::cout << readBuf << '\n';
        close(pipeFd[0]);
    }


    return 0;
}