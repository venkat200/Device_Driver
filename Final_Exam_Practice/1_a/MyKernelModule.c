// Name        : Venkata Ramanan A
// Roll Number : CED17I046

// Question 1(a)
// Write a module that can take an integer parameter when it is loaded with insmod command.

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/stat.h>

MODULE_LICENSE("My Module");
MODULE_AUTHOR("Venkata Ramanan");

// declaration of static variable
static int int_type_variable = 100;

// module_param(name, datatype, permission_bits) used for exposing parameters in sysfs
module_param(int_type_variable, int, S_IRUSR | S_IWUSR| S_IRGRP | S_IROTH);
MODULE_PARM_DESC(int_type_variable, "An integer");

// init function
static int __init MyKernelModule_init(void)
{
    printk(KERN_INFO "Hello Kernel, My name is Venkata Ramanan and This is my Kernel module :) \n");
    printk(KERN_INFO "int_type_variable is a integer type parameter loaded from insmod = %d \n", int_type_variable);
    return 0;  
}

// exit function
static void __exit MyKernelModule_exit(void)
{
    printk(KERN_INFO "Goodbye Kernel, will meet you again !! \n");
}

module_init(MyKernelModule_init);
module_exit(MyKernelModule_exit);