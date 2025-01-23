#include <iostream>
#include <sys/types.h>
#include <dirent.h>

// #include <cstring>

unsigned blockNum = 0;

void readDir(const std::string& dirName)
{
    DIR* dir = opendir(dirName.c_str());

    if (!dir) // man 3 opendir查看, /RET来检索.
    {
        perror("opendir func error");
        return;
    }

    dirent* pDirent = nullptr;
    int oldErrorNum = errno;
    while (pDirent = readdir(dir))
    {
        const std::string& fileName = pDirent->d_name; // 对于C++程序, 除非系统调用, 其他全用std::string
        if (fileName == "." || fileName == "..")
        {
            continue;
        }
        if (pDirent->d_type == DT_DIR)
        {
            for (unsigned i = 0; i < blockNum; i++)
            {
                std::cout << "\t";
            }
            std::cout << "dir name is : " << fileName << '\n';
            const std::string childDirName = dirName + "/" + fileName;
            blockNum++;
            readDir(childDirName);
            blockNum--;
        }
        else
        {
            for (unsigned i = 0; i < blockNum; i++)
            {
                std::cout << "\t";
            }
            std::cout << "file name is : " << fileName << '\n';
        }
    }
    if (oldErrorNum != errno)
    {
        perror("readdir error");
        return;
    }
    closedir(dir);

    return;
}

int main(int argc, char* argv[])
{
    std::string fileName{ "./" };
    if (argc > 1)
    {
        // strcpy(fileName.c_str(), argv[1]); // 只用std::string的话就不需要用cstring,也不需要用strcpy这个函数.
        fileName = argv[1];
    }
    readDir(fileName);
    return 0;
}

// // 对于C++程序, 除非系统调用, 其他全用std::string
/*
#define MAX_LEN 100
int main(int argc, char* argv[])
{
    char fileName[MAX_LEN]{ "./" };
    if (argc > 1)
    {
        strcpy(fileName, argv[1]);
    }
    readDir(fileName);
    return 0;
}
*/
