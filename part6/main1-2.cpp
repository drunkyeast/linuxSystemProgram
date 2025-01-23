#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring> // 老哥用的cstring, rock用的string.h

int main()
{
    int fd = open("num2.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    // 如果不写0644的话可能有问题
    // O_CREAT和O_APPEND都好理解.
    if (fd == -1)
    {
        perror("open file error");
        return -1; // 老哥说return 1也可以
    }

    const char* str = "hello wordl";
    int writeRet = write(fd, str, strlen(str)); // 这儿不用+1, 因为这是在文件中. 这些细节很烦.
    if(writeRet == -1) // 老哥说write只用判断-1, 0不用管. 而read返回值为0时表示读到末尾. EOF时-1,是C语言里的概念.
    {
        perror("write func error"); // 会自动换行的, 或者用fprintf控制不换行. fprintf(stderr, "Error opening file: %s", strerror(errno));
        return -1;
    }
    writeRet = write(fd, "\n", 1); // 这儿不用+1, 因为这是在文件中. 这些细节很烦.
    if(writeRet == -1) // 老哥说write只用判断-1
    {
        perror("write func error");
        return -1;
    }
    
    int seekRet = 0;
    if ((seekRet = lseek(fd, 0, SEEK_END)) == -1)
    {
        perror("seek func error");
        return -1;
    }
    std::cout << "file size is : " << seekRet << '\n';
    close(fd);
    return 0;
}