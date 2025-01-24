#include<iostream>
#include<unistd.h>
#include<signal.h>

int main()
{
    if (signal(SIGINT, SIG_DFL) == SIG_ERR) // SIG_DFL default默认处理, SIG_IGN
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