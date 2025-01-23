#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring> // 老哥说字符串用string,但涉及系统调用时才用这些. 且不是用string.h

// 老哥说dup单独使用的情况极少, 一般配合dup2使用. 
// 而rock老师演示过用dup做标准输入输出的重定向功能... 例如close(0) dup(fd); 

int main()
{
    int fd = open("num.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        perror("open file error");
        return -1;
    }

    int newfd = dup(fd); // 挑出最小的一个值, 0/1/1
    if (newfd == -1)
    {
        perror("dup func error");
        return -1;
    }
    std::cout << "fd = " << fd << '\n';
    std::cout << "newfd = " << newfd << '\n';

    const char* str = "hello world";
    int writeRet = 0;
    writeRet = write(newfd, str, strlen(str)); // 用strlen,而不是sizeof, 同样的也不用const char str[] = "hello world" , 这是数组.

    { //这只是一段临时测试
        const char* str = "hello world";
        const char str3[] = "hello world"; //  这两个写法不一样, 后者是一个数组!!! sizeof(str)大小为12包括'\0' 前者本质是一个8字节的指针.
        std::cout << sizeof(str) << '\n';
        std::cout << sizeof(str3) << '\n';
        // return 0;
    }

    close(fd);
    close(newfd);
    return 0;
}