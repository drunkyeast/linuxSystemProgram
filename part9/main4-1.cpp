// 处理僵尸进程用信号. 这里的写法很不标准.
// 再次强调, 我们是C++项目, 信号用的少, 信号就讲这些了. 我们不太会写多进程程序.
// 有兴趣再去拓展信号集. sigaction函数(signal逐渐被淘汰了,用这个升级版). rock老师就讲过这个. 
#include<iostream>
#include<unistd.h>
#include<signal.h>
#include<wait.h>
void SIGCHILD_handler_func(int sigChild)
{
    if (wait(nullptr) == -1)
    {
        perror("wait func error");
        return;
    }
}

int main()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork func error");
        return -1;
    }
    else if (pid > 0)
    {
        signal(SIGCHLD, SIGCHILD_handler_func);
        std::cout << "hello world" << '\n';
    }

    return 0;
}