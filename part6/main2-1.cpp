#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstring>

#define MAX_LEN 100
// /usr/include/x86_64-linux-gnu/sys/stat.h 要在远程服务器上安装C++插件才有补全. 然后这些头文件的路径如下.
// ./test num.txt.soft  这是处理软链接这个特殊情况. ln -s num.txt num.txt.soft
int main(int argc, char* argv[])
{
    char fileName[MAX_LEN] = "num.txt";

    if (argc > 1)
    {
        strcpy(fileName, argv[1]);
    }
    struct stat statBuf {};
    struct stat statBuf2 {};
    int statRet = stat(fileName, &statBuf);
    int statRet2 = lstat(fileName, &statBuf2);
    if (statRet == -1)
    {
        perror("stat func error");
        return -1;
    }
    if (statRet2 == -1)
    {
        perror("stat func error");
        return -1;
    }

    std::cout << fileName << "的文件大小为: " << statBuf.st_size << '\n';
    std::cout << fileName << "的文件大小为: " << statBuf2.st_size << '\n';
    // ln -s num.txt num.txt.soft

    return 0;
}