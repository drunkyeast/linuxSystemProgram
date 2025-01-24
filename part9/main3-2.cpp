#include<iostream>
#include<unistd.h>
#include<signal.h>
// man signal 然后看DESCRPITON下面的三点就好. /RET帮助定义一下参数
// SIGKILL与SIGSTOP都无法被捕捉.
// kill（默认，SIGTERM, 编号为15）.     kill -9（SIGKILL, 编号为9）
// C++中信号本身用得很少. C项目用的多. 所以搞C++信号就到这里了.
void signal_handler_func(int signalNum)
{
    std::cout << "catch SIGINT signal" << '\n';
}

int main()
{
    if (signal(SIGINT, signal_handler_func) == SIG_ERR) // SIG_DFL default默认处理, SIG_IGN
    {
        perror("signal func error");
        return -1;
    }
    while (1)
    {
        std::cout << "hello world" << '\n';
        sleep(1);
    }

    return 0;
}