// mmap,对我们来说,深入理解内存映射的意义不大. 记住基础用法就好.
// 我感觉这段代码有潜在的bug,...演示不太好.

#include<iostream>
#include<unistd.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<cstring>
#include<sys/wait.h>
// void *mmap(void addr[.length], size_t length, int prot, int flags, int fd, off_t offset);
int main()
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("fork func error");
        return -1;
    }
    struct stat st {};
    int fd = open("num.txt", O_RDWR);
    if (fd == -1)
    {
        perror("open num.txt error");
        return -1;
    }
    if (fstat(fd, &st) == -1)
    {
        perror("fstat func error");
        return -1;
    }

    char* mmapAddr = nullptr;
    // 强制类型转化, 后者视觉效果更明显.
    // mmapAddr = (char*)mmap(nullptr, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    mmapAddr = static_cast<char*>(mmap(nullptr, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    if (mmapAddr == MAP_FAILED)
    {
        perror("mmap func error");
        return -1;
    }
    close(fd); // 不需要fd了, 直接用内存映射的地址.

    if (pid > 0)
    {
        strncpy(mmapAddr, "hello world", 12);
        int status;
        // wait(&status); 两个方法基本一样.
        waitpid(pid, &status, 0);
    }
    else if (pid == 0)
    {
        sleep(1); // 等待写完
        std::cout << mmapAddr << '\n';
    }

    if (munmap(mmapAddr, st.st_size) == -1)
    {
        perror("mummap func error");
        return -1;
    }

    return 0;
}
// 知识点补充: NULL、nullptr 和 \0 值都是0, 但字节数不同
// 在C/C++中，NULL通常是一个整数常量0或(void*)0。占用的字节数取决于指针的大小，通常是4字节（32位系统）或8字节（64位系统）。
// 在C++中，nullptr是一个类型安全的空指针，占用的字节数与指针相同，通常是4字节（32位系统）或8字节（64位系统）。
// 这是一个字符常量，占用1个字节。
// C语言中NULL是(void*)0, C++中NULL被定义为0而不是(void*)0, 这些细节就不管了, 别较真...以后看书有相关介绍时再记录一下吧.
// 简单记忆, C语言中NULL是(void*)0, C++中用nullptr,类型为std::nullptr_t确保了类型安全.