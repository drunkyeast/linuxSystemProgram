#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
// 其实我写了很多文字,感觉没必要,自己想通了不需要看这些文字.
int main()
{
    int fd = open("num.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        perror("open file error");
        return -1;
    }
    int oldfd = dup(STDOUT_FILENO); // oldfd=4, 指向与fd 1标准输出相同文件.
    // dup解释: 返回一个新的文件描述符(最小可用), 指向参数所指向的文件. 再依据文件描述符表的结构, dup就是创建新的文件描述符,指向与参数指向的相同的文件,返回新创建的文件描述符.
    // 我再想我解释半天也无法用很精确的语言描述. 不如直接看man手册的英文描述吧.
    // int dup(int oldfd); 
    // the dup() system call allocates a new file descriptor that refers to the same open file description as teh descreptor oldfd.
    // the new file descriptor number is guaranteed to be the lowest-numbered file descriptor that was unused in the calling process.
    std::cout << "oldfd is " << oldfd << std::endl;
    if (oldfd == -1)
    {
        perror("dup func error");
        return -1;
    }

    // dup2解释: 
    if (dup2(fd, STDOUT_FILENO) == -1) // dup2解释: 让个文件描述符表中的STDOUT_FILENO即fd 1对应的条目的指针, 指向fd所指向的文件. 用write或printf,std::cout都会输出到fd所指向的文件.
        // dup2(oldfd, newfd);
        // the dup2() system call performs the same task as dup(), but instead of using the lowest-numbered unused file descriptor, 
        // it uses the file descriptor number specidied in newfd. In other words, the fiel descriptor newfd is adjusted so that it now refers to the same open file description as oldfd.
    {
        perror("dup2 func error");
        return -1;
    }
    const char* str = "1: user write hello world\n";
    if (write(STDOUT_FILENO, str, strlen(str)) == -1)
    {
        perror("write func error");
        return -1;
    }
    std::cout << "2: use std::cout" << std::endl;
    printf("3: use printf\n");


    if (dup2(oldfd, STDOUT_FILENO) == -1) // 注意一个误区, 这儿STDOUT_FILENO就是2, 但并不指向标准输出文件, 因为前面dup2修改了它, 让fd 2指向了fd指向的文件.
    {
        std::string errStr = std::string("dup2 func error, line num is : ") + std::to_string(__LINE__) + " file name is" + __FILE__;
        perror(errStr.c_str());
        return -1;
    }

    if (write(STDOUT_FILENO, str, strlen(str)) == -1)
    {
        perror("write func error");
        return -1;
    }

    close(fd);
    close(oldfd); // 经典错误, dup创建的这个也占据内存的.要释放. 而且这还是内核区的内存.
    return 0;
}