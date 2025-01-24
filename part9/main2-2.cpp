#include<iostream>
#include<sys/types.h>
#include<signal.h>
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "process needs a pid parament" << '\n';
        return -1;
    }
    if (kill(atoi(argv[1]), SIGINT) == -1)
    {
        perror("kill func error");
        return -1;
    }

    return 0;
}