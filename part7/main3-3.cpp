#include<iostream>
#include<unistd.h>
#include <sys/types.h>

// exec函数又6个, execl/execlp/execle + execv/execvp + execlp(被弃用了), 另外execve比较特殊,前者那些函数底层都会调用execve.
// 所以主要就记忆execl/execv/execle, 然后一个p参数. 不要过于较真......
int main()
{
    // 创建五个进程;
    pid_t pid = 0;
    unsigned i = 0;
    for (i = 0; i < 5; i++)
    {
        pid = fork();
        if (pid == -1)
        {
            perror("fork func error");
            return -1;
        }
        if (pid == 0) // 不让创建的子进程继续创建子进程.
        {
            break;
        }
    }
    // 演示if else 和 switch 两种方式. 又遇到一个问题, char* paraArr[]{ "ls", "-al", NULL };需要定义在switch之前.
    // 用1+5共六个进程演示exec -l -v -e -p
    if (i == 0)
    {
        sleep(1);
        std::cout << '\n' << '\n';
        std::cout << "this is 1 child process" << '\n';
        std::cout << "execl:对比与execv的传参" << '\n';
        execl("/bin/ls", "ls", "-al", NULL);
    }
    else if (i == 1)
    {
        sleep(2);
        std::cout << '\n' << '\n';
        std::cout << "this is 2 child process" << '\n';
        std::cout << "execv:" << '\n';

        char* paraArr[]{ const_cast<char*>("ls"), const_cast<char*>("-al"), NULL };
        execv("/bin/ls", paraArr);


        // 知识点补充: 多看几遍,希望能成为永久记忆啊.
        // 1. char* paraArr[]{ "ls", "-al", NULL }; 本质是一个数组,每个元素是char*类型.
        // 疑惑点,一个char*变量指向一个数组可以吗?怎么声明和定义. char(*p) pArr[]{"ls", "-al", NULL };
        // 这东西,容易忘, 记不住啊. 怎么办呢? 多看几遍吧.

        // 2. const char*(等价于char const*)与char* const的区别.
        // 前者两种写法const都是修饰char!!const修饰它左边的东西. 这个指针指向的值(char)不能修改,但指针本身可用修改.
        // 而后者const修饰它左边的*号, 表示指针本事不能修改. 但指针指向的值可用修改!!! 例如paraArr[0]="hello world"就不行. paraArr[0][0]="X"就可用.
        // const char* const(等价于char const* const)与const char* const.
        // 现在清晰了,但我怕忘记啊.

        // 3.int execv(const char* pathname, char* const argv[]); 的历史遗留问题.因为exec系列函数出现在C++发明以前. 
        // 前面分析了, char* paraArr[]{ "ls", "-al", NULL };  作为参数传入char* const argv[]
        // 会报warning,数组的元素前者是char*, 后者是char*const, const修饰*表示指针本身不能修改,但指向的值可用修改. 语法可用这样转化,但会报warning.
        // 如果我写成const char* paraArr[]{ "ls", "-al", NULL }; const char*就不能转化成char*const了.
        // 为了不出现warning和报错. 
        // 解决方法1: 直接不管,要保证这个警告不会出现任何问题.
        // 解决方法2: extrn c???不太懂,用c语言的方法编译c++.但只适合大型项目.略
        // 解决方法3:使用const_cast<char*>("ls") 
        // char* paraArr[]{ const_cast<char*>("ls"), const_cast<char*>("-al"), NULL };
        // 因为warning说不能吧"ls" "-al"是const char*, 不能转化成char*. 所以把"ls"和"-al"的const属性去掉.
        // 而char*传递给char*const, 这样转化是没有警告的.const char*转化成char*虽然C++语法禁止,但编译器允许.

        // 解决方法4:来自chatgpt 使用const_cast<char**>.
        // const char* paraArr[]{ "ls", "-al", NULL };
        // const char* [](在函数参数中等价为const char**) 再去掉const变成char**可用转化为char*const*
        // 但在调用execv时, execv("/bin/ls", const_cast<char**>paraArr);
        // 先按照老哥的方法来吧.老哥的方法似乎更加通用一些, 因为只是去掉const char*的const, 而这方法是去嗲const char**的const属性.

        // 4.在函数参数声明中，char* argv[] 和 char** argv 是完全等价的。前者会退化(decay)为指针. 但如果声明+定义的话就不同了.
        // char* args[] 不能出现在函数体中,只能出现在函数参数中. 例如经典的 int main(int argc, char* argv[])
    }
    else if (i == 2)
    {
        sleep(2);
        std::cout << '\n' << '\n';
        std::cout << "this is 3 child process" << '\n';
        std::cout << "execve: 多一个环境变量参数, $PATH查看" << '\n';
        char* environArr[]{ const_cast<char*>("A=1"), const_cast<char*>("B=2"), NULL };
        if (execle("./main3-3-1", "main2", NULL, environArr) == -1)
        {
            perror("execl func error");
        }
    }

    switch (i)
    {
    case 3:
        sleep(3);
        std::cout << '\n' << '\n';
        std::cout << "this is 3 child process" << '\n';
        std::cout << "execlp: 多一个环境变量参数, $PATH查看" << '\n';
        break;
    case 4:
        sleep(4);
        std::cout << '\n' << '\n';
        std::cout << "this is 4 child process" << '\n';
        std::cout << "execvp: 多一个环境变量参数, $PATH查看" << '\n';
        break;
    default:
        sleep(5);
        std::cout << '\n' << '\n';
        std::cout << "this is parent process" << '\n';
        std::cout << "execlpe:被弃用了" << '\n';
        std::cout << "execve:这是其他几个exec函数的底层函数,不考虑" << '\n';
        break;
    }
    return 0;
}