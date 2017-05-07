#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>

#define MAX_LEN 100

//处理函数，没什么好讲的，用户自己定义
void input_handler(int num)
{
    char data[MAX_LEN];
    int len;    
    //读取并输出STDIN_FILENO上的输入
    len = read(STDIN_FILENO, &data, MAX_LEN);
    data[len] = 0; 
    printf("input available:%s\n", data);
}

void main()
{
    int oflags;

    //启动信号驱动机制,将SIGIO信号同input_handler函数关联起来,一旦产生SIGIO信号,就会执行input_handler 
    signal(SIGIO, input_handler);    

    //STDIN_FILENO是打开的设备文件描述符,F_SETOWN用来决定操作是干什么的,getpid()是个系统调用，
    //功能是返回当前进程的进程号,整个函数的功能是STDIN_FILENO设置这个设备文件的拥有者为当前进程。
    fcntl(STDIN_FILENO, F_SETOWN, getpid());    

    //得到打开文件描述符的状态
    oflags = fcntl(STDIN_FILENO, F_GETFL);

    //设置文件描述符的状态为oflags | FASYNC属性,一旦文件描述符被设置成具有FASYNC属性的状态，
    //也就是将设备文件切换到异步操作模式。这时系统就会自动调用驱动程序的fasync方法。
    fcntl(STDIN_FILENO, F_SETFL, oflags | FASYNC);  

    //最后进入一个死循环，程序什么都不干了，只有信号能激发input_handler的运行
    //如果程序中没有这个死循环，会立即执行完毕
    while (1);
}
