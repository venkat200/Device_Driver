#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/stat.h>
#include <fs.h>


MODULE_LICENSE("My Device Driver Module");
MODULE_AUTHOR("Venkat");

// function definitions
int file_open (struct inode *pinode, struct file *pfile);
ssize_t file_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset);
ssize_t file_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset);
int file_close (struct inode *pinode, struct file *pfile);

// declaration of variables
int variable = 0;

// structure of file
struct file_operations file = {
    .owner = THIS_MODULE,
    .open = file_open,
    .read = file_read,
    .write = file_write, 
    .release = file_close,
};

// module_param(name, datatype, permission_bits) used for exposing parameters in sysfs
module_param(variable, int, 0);

int file_open (struct inode *pinode, struct file *pfile) 
{
    printk(KERN_ALERT "File opened !! \n");
    return 0;
}

ssize_t file_read (struct file *pfile, char __user *buffer, size_t length, loff_t *offset) 
{
    printk(KERN_ALERT "File read !! \n");
    return 0;
}

ssize_t file_write (struct file *pfile, const char __user *buffer, size_t length, loff_t *offset) 
{
    printk(KERN_ALERT "File updated !! \n");
    return length;
}

int file_close (struct inode *pinode, struct file *pfile) 
{
    printk(KERN_ALERT "File closed !! \n");
    return 0;
}

// init function
int MyDeviceDriver_init(void) 
{
    register_chrdev(50, "My Device Driver", &file);
    printk(KERN_INFO "Hello, This is my device driver module :) \n");
    printk(KERN_ALERT "The value passed : %d \n", variable);

    return 0;
}

// exit function
void MyDeviceDriver_exit(void) 
{
    unregister_chrdev(50, "My Device Driver");
    printk(KERN_INFO "Goodbye, will meet you again !! \n");
}


module_init(MyDeviceDriver_init);
module_exit(MyDeviceDriver_exit);