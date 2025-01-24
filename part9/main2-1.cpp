// ulimit -c unlimited
// g++ -g main.cpp -o test  // -g生产core文件
// gdb test
// core-file core
#include<iostream>


int main()
{
    int* p = nullptr;
    *p = 1;

    return 0;
}