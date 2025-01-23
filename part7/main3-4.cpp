#include<iostream>
#include<unistd.h>
// 一个终端对应一个会话,一个会话对应多个进程组,进程组有一个组长管理多个进程,可降低内核工作压力.
// setsid可让进程脱离原来的会话session/终端, 创建一个新的会话.
// chdir更改工作目录(启动时的目录,与相对路径有关.),例如一个进程启动了,要把这个进程启动时所在的目录删掉,就要先修改后才能删.以及/mnt/usb这种目录下启动进程
// 文件掩码修改: umask是吗? 方便后面守护进程创建文件.
// 关闭父进程的文件描述符.
#include <sys/stat.h>
#include <sys/types.h>
int main()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork func error");
        return -1;
    }
    else if (pid == 0)
    {
        if (setsid() == -1)
        {
            perror("setsid func error");
            return -1;
        }
        if (chdir("/tmp") == -1)
        {
            perror("chdir func error");
            return -1;
        }
        // mode_t就是unsigned int
        mode_t ret = umask(0); // This system call always succeeds and the previous value of the mask is returned.
        printf("ret of umask : %o, 应该是八进制的0022\n");

        std::cout << "getdtablesize() is : " << getdtablesize() << '\n';
        for (unsigned i = 0; i < getdtablesize(); i++) // The current limit on the number of open files per process. 65535
        {
            close(i);
        }
        sleep(30);
        std::cout << "child process finished" << '\n';
    }
    else if (pid > 0)
    {
        sleep(10);
        std::cout << "parent process finished" << '\n';
        std::cout << "子进程已经脱离这个终端/会话了, 父进程结束后就结束了\n";
        std::cout << "ps -aux | grep test : 可以查看子进程的状态,它不属于任何tty/终端\n";
    }


    return 0;
}