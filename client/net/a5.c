//#include <linux/config.h>  
  
//#include <linux/modversions.h>  
  
#include <linux/init.h>  
  
#include <linux/module.h>  
  
#include <linux/kernel.h>  
  
#include <linux/signal.h>  
  
#include <linux/sched.h>  
  
  
  
#define SIG_MYINT 33  
  
#define PS_PID 30 //the user process id  
  
  
  
static int mysig_init(void)  
  
{  
  
siginfo_t info;  
  
struct task_struct *p;  
  
  
  
info.si_signo = SIG_MYINT;  
  
info.si_code = -1;//__SI_RT;  
  
info.si_int = 0x8;  
  
  
  
read_lock(&tasklist_lock);  
  
for_each_task(p)  
  
{  
  
if (p->pid == PS_PID)  
  
{  
  
read_unlock(&tasklist_lock);  
  
goto find_ps;  
  
}  
  
}  
  
read_unlock(&tasklist_lock);  
  
printk("can't find the process <%d>, you should run it first!  ", PS_PID);  
  
return -1;  
  
  
  
find_ps:  
  
printk("send signal to user space.  ");  
  
send_sig_info(SIG_MYINT, &info, p);  
  
  
  
return 0;  
  
}  
  
  
  
static void mysig_exit(void)  
  
{  
  
printk("my signal test exit.  ");  
 kill(1, 1); 
}  
  
  
  
MODULE_LICENSE("GPL");  
  
MODULE_AUTHOR("xxxx");  
  
  
  
module_init(mysig_init);  
  
module_exit(mysig_exit);  
  
