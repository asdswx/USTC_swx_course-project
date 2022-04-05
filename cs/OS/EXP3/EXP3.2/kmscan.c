#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/kthread.h>
#include <linux/wait.h>
#include <linux/err.h>
#include <linux/moduleparam.h>
#include <linux/types.h>
#include <linux/freezer.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/pid.h>
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/string.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>
#include <linux/signal.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/mm.h>
#include <linux/rmap.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("SWX");
MODULE_DESCRIPTION("kmscan module");
MODULE_VERSION("1.0");

#define KMSCAN_RUN_STOP 0
#define KMSCAN_RUN_START 1

typedef typeof(follow_page)* my_follow_page;
typedef typeof(page_referenced)* my_page_referenced;
static struct proc_dir_entry* kmscan;

static unsigned int kmscan_func = 0;
static unsigned int kmscan_file = 0;
static unsigned int kmscan_active_file = 0;
static unsigned int kmscan_anon = 0;
static unsigned int kmscan_active_anon = 0;
static int vma_count=0;
static unsigned int kmscan_run = KMSCAN_RUN_STOP;

static unsigned int kmscan_sleep_millisecs = 20000;

static unsigned int kmscan_pid = 0;

static struct task_struct* kmscan_thread;

static DECLARE_WAIT_QUEUE_HEAD(kmscan_thread_wait);

static DEFINE_MUTEX(kmscan_thread_mutex);

static int kmscan_show(struct seq_file* m, void* v)
{
    unsigned int* count = (unsigned int*)m->private;
    if (count != NULL)
    {
        seq_printf(m, "%d\n", *count);
    }
    return 0;
}

static int kmscan_open(struct inode* inode, struct file* file)
{
    return single_open(file, kmscan_show, PDE_DATA(inode));
}

struct proc_ops kmscan_ops = {
    .proc_open = kmscan_open,
    .proc_read = seq_read,
    .proc_release = single_release,
};


static int kmscand_should_run(void)
{
    return (kmscan_run & KMSCAN_RUN_START);
}




static void kmscan_to_do(void)
{
    
    
    if (kmscan_func == 1){
		struct task_struct* task;
		struct pid* kpid;
		struct mm_struct* qwq;
		struct vm_area_struct * vm_task;
		vma_count = 0;
		kpid=find_get_pid(kmscan_pid);
		if(kpid){
		task=pid_task(kpid,PIDTYPE_PID);
		qwq=task->mm;
		vm_task=qwq->mmap;
		while(vm_task!=NULL){
		vma_count++;
		vm_task=vm_task->vm_next;
}
		proc_create_data("vma_count", 0664, kmscan, &kmscan_ops, &vma_count);
}
}
        
    else if (kmscan_func == 2){
        struct task_struct* task;
	struct pid* kpid;
	struct mm_struct* qwq;
	struct vm_area_struct * vm_task;
	struct page* vm_page;
	my_follow_page mfollow_page;
	my_page_referenced mpage_referenced;
	unsigned long owo;
	mfollow_page = (my_follow_page)0xffffffff95673af0;
	mpage_referenced=(my_page_referenced)0xffffffff9568e030;
	kmscan_file=0;
	kmscan_active_file=0;
	kmscan_anon=0;
	kmscan_active_anon=0;
	kpid=find_get_pid(kmscan_pid);
	if(kpid){
	task=pid_task(kpid,PIDTYPE_PID);
	qwq=task->mm;
	vm_task=qwq->mmap;
	while(vm_task!=NULL){
	owo=vm_task->vm_start;
		while(owo<vm_task->vm_end){
		vm_page=mfollow_page(vm_task,owo,FOLL_TOUCH);
		if(vm_page!=NULL){
			if(PageAnon(vm_page)){
				kmscan_anon++;
				if(mpage_referenced(vm_page,0,vm_page->mem_cgroup,&vm_page->flags))
					kmscan_active_anon++;

			}
			else{
				kmscan_file++;
				if(mpage_referenced(vm_page,0,vm_page->mem_cgroup,&vm_page->flags))
					kmscan_active_file++;
			}
			
		}
		owo=owo+PAGE_SIZE;	
		}
	vm_task=vm_task->vm_next;
	}
	proc_create_data("file", 0664, kmscan, &kmscan_ops, &kmscan_file);
	proc_create_data("active_file", 0664, kmscan, &kmscan_ops, &kmscan_active_file);
	proc_create_data("anon", 0664, kmscan, &kmscan_ops, &kmscan_anon);
	proc_create_data("active_anon", 0664, kmscan, &kmscan_ops, &kmscan_active_anon);	
}
}
}

static int kmscand_thread(void* nothing)
{
    set_freezable();
    set_user_nice(current, 5);
    while (!kthread_should_stop())
    {
        mutex_lock(&kmscan_thread_mutex);
        if (kmscand_should_run())
            kmscan_to_do();
        mutex_unlock(&kmscan_thread_mutex);
        try_to_freeze();
        if (kmscand_should_run())
        {
            schedule_timeout_interruptible(
                msecs_to_jiffies(kmscan_sleep_millisecs));
        }
        else
        {
            wait_event_freezable(kmscan_thread_wait,
                kmscand_should_run() || kthread_should_stop());
        }
    }
    return 0;
}
#ifdef CONFIG_SYSFS
#define KMSCAN_ATTR_RO(_name) \
        static struct kobj_attribute _name##_attr = __ATTR_RO(_name)

#define KMSCAN_ATTR(_name)                         \
        static struct kobj_attribute _name##_attr = \
                __ATTR(_name, 0644, _name##_show, _name##_store)

static ssize_t sleep_millisecs_show(struct kobject* kobj,
    struct kobj_attribute* attr, char* buf)
{
    return sprintf(buf, "%u\n", kmscan_sleep_millisecs);
}

static ssize_t sleep_millisecs_store(struct kobject* kobj,
    struct kobj_attribute* attr,
    const char* buf, size_t count)
{
    unsigned long msecs;
    int err;

    err = kstrtoul(buf, 10, &msecs);
    if (err || msecs > UINT_MAX)
        return -EINVAL;

    kmscan_sleep_millisecs = msecs;

    return count;
}
KMSCAN_ATTR(sleep_millisecs);

static ssize_t func_show(struct kobject* kobj,
    struct kobj_attribute* attr, char* buf)
{
    return sprintf(buf, "%u\n", kmscan_func);
}

static ssize_t func_store(struct kobject* kobj,
    struct kobj_attribute* attr,
    const char* buf, size_t count)
{
    unsigned long tmp;
    int err;

    err = kstrtoul(buf, 10, &tmp);
    if (err || tmp > UINT_MAX)
        return -EINVAL;

    kmscan_func = tmp;

    return count;
}
KMSCAN_ATTR(func);

static ssize_t run_show(struct kobject* kobj, struct kobj_attribute* attr,
    char* buf)
{
    return sprintf(buf, "%u\n", kmscan_run);
}

static ssize_t run_store(struct kobject* kobj, struct kobj_attribute* attr,
    const char* buf, size_t count)
{
    int err;
    unsigned long flags;
    err = kstrtoul(buf, 10, &flags);
    if (err || flags > UINT_MAX)
        return -EINVAL;
    if (flags > KMSCAN_RUN_START)
        return -EINVAL;
    mutex_lock(&kmscan_thread_mutex);
    if (kmscan_run != flags)
    {
        kmscan_run = flags;
    }
    mutex_unlock(&kmscan_thread_mutex);

    if (flags & KMSCAN_RUN_START)
        wake_up_interruptible(&kmscan_thread_wait);
    return count;
}
KMSCAN_ATTR(run);

static ssize_t pid_show(struct kobject* kobj,
    struct kobj_attribute* attr, char* buf)
{
    return sprintf(buf, "%u\n", kmscan_pid);
}

static ssize_t pid_store(struct kobject* kobj,
    struct kobj_attribute* attr,
    const char* buf, size_t count)
{
    unsigned long tmp;
    int err;

    err = kstrtoul(buf, 10, &tmp);
    if (err || tmp > UINT_MAX)
        return -EINVAL;

    kmscan_pid = tmp;

    return count;
}
KMSCAN_ATTR(pid);

static struct attribute* kmscan_attrs[] = {
    // 扫描进程的扫描间隔 默认为20秒 
    &sleep_millisecs_attr.attr,
    &pid_attr.attr,
    &func_attr.attr,
    &run_attr.attr,
    NULL,
};
static struct attribute_group kmscan_attr_group = {
    .attrs = kmscan_attrs,
    .name = "kmscan",
};
#endif
static int kmscan_init(void)
{
    int err;
	kmscan = proc_mkdir("kmscan", NULL);
    if (kmscan == NULL) {
        printk("%s proc create %s failed\n", __func__, "kmscan");
        return -EINVAL;
    }
    kmscan_thread = kthread_run(kmscand_thread, NULL, "kmscan");
    if (IS_ERR(kmscan_thread))
    {
        pr_err("kmscan: creating kthread failed\n");
        err = PTR_ERR(kmscan_thread);
        goto out;
    }
#ifdef CONFIG_SYSFS

    err = sysfs_create_group(mm_kobj, &kmscan_attr_group);
    if (err)
    {
        pr_err("kmscan: register sysfs failed\n");
        kthread_stop(kmscan_thread);
        goto out;
    }
#else
    kmscan_run = KMSCAN_RUN_STOP;

#endif
out:
    return err;
}

static void kmscan_exit(void)
{
    if (kmscan_thread)
    {
        kthread_stop(kmscan_thread);
        kmscan_thread = NULL;
    }

#ifdef CONFIG_SYSFS
    sysfs_remove_group(mm_kobj, &kmscan_attr_group);
#endif
	proc_remove(kmscan);
    printk("kmscan exit success!\n");
}

module_init(kmscan_init);
module_exit(kmscan_exit);



