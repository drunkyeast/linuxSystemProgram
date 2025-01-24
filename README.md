part1-5     基础,没什么代码,可直接跳过
part6       文件IO          打开读写最常用/lseek/stat/目录递归操作/dup dup2
part7       linux进程       进程创建/execl等/几个丰富的补充知识点/进程通往自由之路.
part8       linux进程间通信  管道与mmap
part9~11    信号/多线程/内存管理 C++项目不太需要了解linux系统调用的这些部分知识.


关于git的知识点:删除本地和远程仓库最新的commit并重新commit的方法.
git commit -m "C++..."后, 我后面觉得命名成git commit -m "part9~11"更好. 同时修改了一下README.md
然后就要开始操作:
1.用vscode的un do last commit, 或者用命令git reset --soft HEAD~
2.修改一下README.md.
3.git checkout -b tmp, git commit -m "part9~11", git push origin tmp. 
4.去github上面项目的setting-\>general-\>default branch, 把默认分支修改为tmp.
5.然后才能git push origin --delete main删除远程main分支.
6.删除本地的tmp分支,本地tmp与main分支时一样的.git push origin main.
7.最后在github上,把默认分支改回main,然后git push origin --delete tmp.
