/*程序和进程
1程序
程序是一个存储在磁盘上某个目录中的可执行文件。内核使用exec函数，将程序读入内存，并执行程序
2进程和ID
程序的执行实例被称为进程(process).本书的每一也几乎都会使用这一术语。某些操作系统用任务(task)表示正在执行的程序
UNIX系统确保每个进程都有一个唯一的数字标识符，称为进程ID(process ID).进程ID总是一个非负整数。
#include"apue.h"
int main(){
	printf("hello world from process ID %ld\n",(long)getpid());
	exit(0);
}
此程序运行是，它调用函数getpid得到其进程ID。我们将会在后面看到，getpid返回一个pid_t数据类型。我们不知道它的大小，进直到的是标准会保证它能保存在一个长整型中。因为我们必须在printf函数中指定需要答应的每一个变量的大小，所以我们必须把它的值强制转换为它可能会用到的最大的数据类型（这里是长整型）。虽然大多数进程ID可用整型表示，但用长整型可以提高可移植性。
3进程控制
有3个用于进程控制的主要函数：fork、exec和waitpid。
UNIX系统的进程控制功能可以用一个简单的程序说明。该程序从标准输入读取命令，然后执行这些命令。
*/
#include "apue.h"
#include <sys/wait.h>
int main(){
	char buf[MAXLINE];
	pid_t pid;
	int status;
	printf("%% ");
	while(fgets(buf,MAXLINE,stdin)!=NULL){
		if(buf[strlen(buf)-1]=='\n')
			buf[strlen(buf)-1]=0;
		if((pid=fork())<0)err_sys("fork error");
		
		else if(pid==0){
			execlp(buf,buf,(char *)0);
			err_ret("couldn't execute: %s",buf);
			exit(127);
		}
		if((pid=waitpid(pid,&status,0))<0)err_sys("waitpid error");
		printf("%% ");}
		exit(0);
}
/*
1用标准IO函数fgets从标准输入一次读取一行。当键入文件结束符作为含的第一个字符时，fgets返回一个null指针，于是循环停止，进程也就终止
2因为fgets返回的每一行都以换行符终止，后随一个null字节,因此用标准C函数strlen计算字符串的长度，然后用一个null字节替换换行符。这样做是因为execlp函数要求的参数是以null结束的而不是以换行符结束的
3调用dirk创建一个新的进程。新进程是调用进程的一个副本，我们称调用进程为父进程，新创建的进程为子进程。fork对父进程返回新的子进程的进程ID（一个非负整数），对子进程则返回0.因为fork创建一个新进程，所以说它被调用一次（由父进程），但返回两次（分别在父进程和子进程中）。
4在子进程中,调用execlp以执行从标准输入读入的命令。这就用新的程序文件替换了子进程原先执行的程序文件。fork和跟随其后的exec两者的组合就是某些操作系统所称的产生(spawn)一个新进程。waitpid函数返回子进程的终止状态。在这个程序中，没有使用该值。如果需要，可以用此值准确地判断子进程是如何终止的。
5该程序最主要的限制是不能向所执行的命令传递参数。例如不能指定要里出目录项的目录名，只能对工作目录执行ls命令。为了传递参数，先要分析输入行，然后用某种约定把参数分开（可能使用空格或制表符），再将分隔后的各个参数传递给execlp函数。尽管如此，从程序仍可用来说UNIX系统的进程控制功能

线程和线程ID
通常，一个进程只有一个控制线程(thread)——某一个时刻执行的一组及其指令，对于某些问题，如果由多个控制线程分别作用域它的不同部分，那么解决起来就容易很多。另外，多个控制线程也可以充分利用多处理器系统的并行能力。
一个进程内所有线程共享同一个地址空间、文件描述符、栈以及进程相关的属性
与进程相同，线程引用ID表示。但是线程ID只在它所属的进程内其作用。一个进程中的ID在另一个进程中没有意义
