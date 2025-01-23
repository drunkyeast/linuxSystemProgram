#include<iostream>
#include<unistd.h>
int main()
{
    std::cout << getdtablesize() << '\n';
    dup(0);
    return 0;
}