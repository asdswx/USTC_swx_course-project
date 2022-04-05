#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/timer.h>
#include <linux/list.h>
#include <linux/pid.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SWX");
MODULE_DESCRIPTION("this module can realize three functions!/n");

static int func =0;
static int pid=0;
module_param(func,int,0644);
module_param(pid,int,0644);
struct timer_list my_timer_list;
void timer_function(struct timer_list* t){
		struct task_struct* task;
		int counter=0;
		for_each_process(task){counter++; }
		printk(KERN_ALERT"The number of kernel process is %d\n",counter);
		
		mod_timer(&my_timer_list,jiffies+5*HZ);
	}

static int __init my_module_init(void){
if(func==1){
	struct task_struct* task;
	printk(KERN_ALERT" my_module_init() begin!\n");
	printk(KERN_ALERT"PID \t STATE \t COMMAND\t\n");
	for_each_process(task){
	printk(KERN_ALERT"%d \t %ld \t %s\t\n",task->pid,task->state,task->comm);
	
}
}
if(func==2){
	
	printk(KERN_ALERT" my_module_init() begin!\n");
	timer_setup(&my_timer_list,timer_function,0);
	my_timer_list.expires=jiffies+5*HZ;
	add_timer(&my_timer_list);
	
		
}
if(func==3){
	struct task_struct* task,*ptask,*ctask,*ttask,*stask;
	struct list_head* mylist,*plist,*slist;
	struct pid* kpid;

	kpid=find_get_pid(pid);
	if(kpid){
	task=pid_task(kpid,PIDTYPE_PID);
	printk(KERN_ALERT"pid receive succeddfully:%d !\n",task->pid);
	ptask=task->parent;
	printk(KERN_ALERT"His father is : pid=%d,\tstate=%ld,\tcomm=%s\t\n",ptask->pid,ptask->state,ptask->comm);
	mylist=&task->children;
	list_for_each(plist,mylist){
	ctask=list_entry(plist,struct task_struct,sibling);
	printk(KERN_ALERT"His children is : pid=%d,\tstate=%ld,\tcomm=%s\t\n",ctask->pid,ctask->state,ctask->comm);

}
	slist=&task->sibling;
	list_for_each(plist,slist){
	stask=list_entry(plist,struct task_struct,sibling);
	if(stask->pid!=0){
	printk(KERN_ALERT"His siblings is : pid=%d,\tstate=%ld,\tcomm=%s\t\n",stask->pid,stask->state,stask->comm);}
}
	printk(KERN_ALERT"His siblings is : pid=%d,\tstate=%ld,\tcomm=%s\t\n",task->pid,task->state,task->comm);

	ttask=task;
	printk(KERN_ALERT"His thread is : pid=%d,\tstate=%ld,\tcomm=%s\t\n",ttask->pid,ttask->state,ttask->comm);
	while_each_thread(task,ttask){
	printk(KERN_ALERT"His thread is : pid=%d,\tstate=%ld,\tcomm=%s\t\n",ttask->pid,ttask->state,ttask->comm);
}
}
}
	return 0;	

}

static void __exit my_module_exit(void)
{
	if(func==2){
	del_timer_sync(&my_timer_list);
}
    printk(KERN_ALERT" module has exited!\n");
}


module_init(my_module_init);

module_exit(my_module_exit);


