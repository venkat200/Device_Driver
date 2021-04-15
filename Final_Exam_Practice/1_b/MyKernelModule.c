// Name        : Venkata Ramanan A
// Roll Number : CED17I046

// Question 1(b)
// Write a module which prints your name in log.

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("My Module");
MODULE_AUTHOR("Venkata Ramanan");

// init function
static int __init MyKernelModule_init(void)
{
    printk(KERN_INFO "Hello Kernel :) \n");
    printk(KERN_INFO "My name is Venkata Ramanan and This is my Kernel module :) \n");
    return 0;  
}

// exit function
static void __exit MyKernelModule_exit(void)
{
    printk(KERN_INFO "Goodbye Kernel, will meet you again !! \n");
}

module_init(MyKernelModule_init);
module_exit(MyKernelModule_exit);