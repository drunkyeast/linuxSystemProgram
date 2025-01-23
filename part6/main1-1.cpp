#include <iostream>
#include <unistd.h>
#include <fcntl.h>

// 这是很标准的写法
int main()
{
    int fd = open("num.txt", O_RDONLY);
    if (fd == -1)
    {
        perror("open file failed!");
        // exit(1); // rock这样写. 在 main 函数中：如果错误是致命的，直接用 exit(1) 或 return 1 都可以。
        return -1; // 初心老哥这样写. 如果希望更灵活且符合标准，可以使用 return -1 或其他非零值作为错误代码。
    }
    // std::cout << fd << std ::endl;

    int readNum = 0;
    char readBuf[8]{};

    while(readNum = read(fd, readBuf, 8))
    {
        if (readNum == -1)
        {
            perror("read func error");
            return -1;
        }
        std::cout << readBuf << std::flush; // 只刷新不换行.
    }
    std::cout << '\n';
    close(fd);
    return 0;
}