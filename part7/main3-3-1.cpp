#include<iostream>
#include<unistd.h>

extern char** environ;
// char* argv[];

// env 命令输出bash进程的所有环境变量.
int main()
{
    for (char** ptr = environ; *ptr != NULL; ptr++)
    {
        std::cout << *ptr << '\n';
    }

    return 0;
}